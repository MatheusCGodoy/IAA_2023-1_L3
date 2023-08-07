#include "relaxed_task_graph.h"

#include <iostream>
#include <vector>

using namespace std;

namespace planopt_heuristics
{
    RelaxedTaskGraph::RelaxedTaskGraph(const TaskProxy &task_proxy)
        : relaxed_task(task_proxy),
          variable_node_ids(relaxed_task.propositions.size())
    {

        for (Proposition propo : relaxed_task.propositions)
        {
            variable_node_ids[propo.id] = graph.add_node(NodeType::OR); // crate a node for each proposition
        }

        initial_node_id = graph.add_node(NodeType::AND); // create node for initial state
        for (PropositionID propo : relaxed_task.initial_state)
        {
            graph.add_edge(variable_node_ids[propo], initial_node_id); // edge from each variable to initial node
        }

        goal_node_id = graph.add_node(NodeType::AND); // create node for goal state
        for (PropositionID propo : relaxed_task.goal)
        {
            graph.add_edge(goal_node_id, variable_node_ids[propo]); // edge from goalnode to each variable precond
        }

        /*
          TODO: add your code for exercise 2 (b) here. Afterwards
            - variable_node_ids[i] should contain the node id of the variable node for variable i
            - initial_node_id should contain the node id of the initial node
            - goal_node_id should contain the node id of the goal node
            - the graph should contain precondition and effect nodes for all operators
            - the graph should contain all necessary edges.
        */

        for(RelaxedOperator oper : relaxed_task.operators)
        {
            NodeID oper_id = graph.add_node(NodeType::AND);
            
            // Operator Preconditions
            NodeID precond_node_id = graph.add_node(NodeType::AND);
            graph.add_edge(oper_id, precond_node_id);
            
            for(PropositionID precond : oper.preconditions)
            {
                graph.add_edge(precond_node_id, precond);
            }
            
            // Operator Effects
            NodeID conjunction_id = graph.add_node(NodeType::AND);
            graph.add_edge(conjunction_id, oper_id);
            
            for(PropositionID effect : oper.effects)
            {
                graph.add_edge(effect, conjunction_id);
            }
        }
    }

    void RelaxedTaskGraph::change_initial_state(const GlobalState &global_state)
    {
        // Remove all initial edges that where introduced for relaxed_task.initial_state.
        for (PropositionID id : relaxed_task.initial_state)
        {
            graph.remove_edge(variable_node_ids[id], initial_node_id);
        }

        // Switch initial state of relaxed_task
        relaxed_task.initial_state = relaxed_task.translate_state(global_state);

        // Add all initial edges for relaxed_task.initial_state.
        for (PropositionID id : relaxed_task.initial_state)
        {
            graph.add_edge(variable_node_ids[id], initial_node_id);
        }
    }

    bool RelaxedTaskGraph::is_goal_relaxed_reachable()
    {
        // Compute the most conservative valuation of the graph and use it to
        // return true iff the goal is reachable in the relaxed task.

        graph.most_conservative_valuation();
        return graph.get_node(goal_node_id).forced_true;
    }

    int RelaxedTaskGraph::additive_cost_of_goal()
    {
        // Compute the weighted most conservative valuation of the graph and use it
        // to return the h^add value of the goal node.

        // TODO: add your code for exercise 2 (c) here.
        return -1;
    }

    int RelaxedTaskGraph::ff_cost_of_goal()
    {
        // TODO: add your code for exercise 2 (e) here.
        return -1;
    }

}
