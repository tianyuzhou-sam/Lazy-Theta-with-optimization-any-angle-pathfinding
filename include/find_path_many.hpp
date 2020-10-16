#ifndef FIND_PATH_MANY_HPP
#define FIND_PATH_MANY_HPP

#include <iostream>
#include <vector>
#include <array>
#include "tileadaptor.hpp"
#include "utility.hpp"
#include "get_combination.hpp"


inline std::vector<std::vector<int>> find_path_many(
    int *agent_position,
    std::vector<int> targets_position,
    const std::vector<int> &Map,
    const int &mapSizeX,
    const int &mapSizeY)
{
    std::vector<int> start_goal_pair = get_combination(targets_position.size()/2 + 1, 2);
    std::vector<std::vector<int>> path_many;
    // path_many.reserve(start_goal_pair.size());

    //Instantiating our path adaptor
    //passing the map size, and the map
    Vectori mapSize(mapSizeX, mapSizeY);
    TileAdaptor adaptor(mapSize, Map);
    //This is a bit of an exageration here for the weight, but it did make my performance test go from 8s to 2s
    Pathfinder pathfinder(adaptor, 100.f /*weight*/);

    for (unsigned long idx = 0; idx < start_goal_pair.size(); idx = idx + 2)
    {
        int start_idx = start_goal_pair[idx];
        int goal_idx = start_goal_pair[idx+1];

        int start[2];
        int goal[2];

        if (start_idx != 0)
        {
            start[0] = targets_position[2*(start_idx-1)];
            start[1] = targets_position[2*(start_idx-1)+1];
        }
        else
        {
            start[0] = agent_position[0];
            start[1] = agent_position[1];
        }

        if (goal_idx != 0)
        {
            goal[0] = targets_position[2*(goal_idx-1)];
            goal[1] = targets_position[2*(goal_idx-1)+1];

        }
        else
        {
            goal[0] = agent_position[0];
            goal[1] = agent_position[1];
        }

        //doing the search
        // std::vector<int> path_single = pathfinder.search(adaptor.posToIdArray(start), adaptor.posToIdArray(goal), mapSize);
        std::vector<int> path_single = pathfinder.search(start[1]*mapSizeX+start[0], goal[1]*mapSizeX+goal[0], mapSize);
        path_many.push_back(path_single);
    }

    return path_many;
}

#endif