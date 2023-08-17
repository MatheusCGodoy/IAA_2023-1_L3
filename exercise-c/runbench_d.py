import os

fileList = [fn for fn in os.listdir('castle') if fn.endswith('-cards.pddl')]

for problem in fileList:
    result_theirs = os.popen('./fast-downward/fast-downward.py' + ' castle/domain.pddl' + ' castle/' + problem + ' --search "astar(lmcut())"').read()
    result_mine = os.popen('./fast-downward/fast-downward.py' + ' castle/domain.pddl' + ' castle/' + problem + ' --search "eager_greedy([planopt_add()])"').read()
    result_theirs_optimal = os.popen('./fast-downward/fast-downward.py' + ' castle/domain.pddl' + ' castle/' + problem + ' --search "astar(lmcut())" --translate-option --relaxed').read()
    print('PROBLEMA: ' + problem)
    print('\n' + result_mine)
    with open('out_' + problem.split('.')[0] + '_add.txt', 'w') as file:
        file.write('FastDownward A* with lmcut heur (optimal plan) h*:\n')
        file.write(result_theirs)
        file.write('\n\nOur planopt_add:\n')
        file.write(result_mine)
        file.write('\n\nFastDownward A* with lmcut heur (optimal relaxed plan) h+:\n')
        file.write(result_theirs_optimal)
        file.close()