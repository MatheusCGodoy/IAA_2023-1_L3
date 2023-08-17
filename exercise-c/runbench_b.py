import os

fileList = [fn for fn in os.listdir('castle') if fn.endswith('-cards.pddl')]

for problem in fileList:
    result_theirs = os.popen('./fast-downward/fast-downward.py' + ' castle/domain.pddl' + ' castle/' + problem + ' --search "astar(blind())"').read()
    result_mine = os.popen('./fast-downward/fast-downward.py' + ' castle/domain.pddl' + ' castle/' + problem + ' --search "astar(planopt_relaxed_task_graph())"').read()
    print('PROBLEMA: ' + problem)
    print('\n' + result_theirs)
    with open('out_' + problem.split('.')[0] + '.txt', 'w') as file:
        file.write('FastDownward A* with blind heur:\n')
        file.write(result_theirs)
        file.write('\n\nOur prunning:\n')
        file.write(result_mine)
        file.close()