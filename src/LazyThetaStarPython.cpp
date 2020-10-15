#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include <chrono>
#include <math.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "tileadaptor.hpp"
#include "find_path.hpp"
#include "utility.hpp"


inline std::vector<int> FindPath(
    std::vector<int> &startPoint,
    std::vector<int> &endPoint,
    std::vector<int> &Map,
    int &mapSizeX,
    int &mapSizeY)
{
    //Instantiating our path adaptor
    //passing the map size, and the map
    Vectori mapSize(mapSizeX, mapSizeY);

    TileAdaptor adaptor(mapSize, Map);
    
    //This is a bit of an exageration here for the weight, but it did make my performance test go from 8s to 2s
    Pathfinder pathfinder(adaptor, 100.f /*weight*/);

    //The map was edited so we need to regenerate teh neighbors
    // pathfinder.generateNodes();

    //doing the search
    //merly to show the point of how it work
    //as it would have been way easier to simply transform the vector to id and pass it to search
    std::vector<int> Path = pathfinder.search(adaptor.posToId({startPoint[0], startPoint[1]}), adaptor.posToId({endPoint[0], endPoint[1]}), mapSize);

    // // Visualization for debug
    // std::cout << "This is the path:" << std::endl;
    // for (unsigned long idx=0; idx < Path.size(); idx=idx+2)
    // {
    //     std::cout << Path[idx] << ", " << Path[idx+1] << std::endl;
    // }

    // std::vector<int> path = Path;

    // if(path.size())
    // {
    //     path.pop_back();
    //     path.pop_back();
    //     path.erase(path.begin());
    //     path.erase(path.begin());
    // }

    // //nodes
    // int x = 0;
    // for(unsigned long idx=0; idx < path.size(); idx=idx+2)
    //     Map[path[idx+1] * mapSizeX + path[idx]] = 1 + x++;

    // //draw map
    // for(int y = 0; y < mapSizeY; y++)
    // {
    //     for(int x = 0; x < mapSizeX; x++)
    //     {
    //         if ((startPoint[0] == x) && (startPoint[1] == y))
    //             std::cout << "S";
    //         else if ((endPoint[0] == x) && (endPoint[1] == y))
    //             std::cout << "E";
    //         else
    //         {
    //             if ((Map[y * mapSizeX + x] != 255) && (Map[y * mapSizeX + x] != 0))
    //                 std::cout << Map[y * mapSizeX + x];
    //             else if (Map[y * mapSizeX + x] == 255)
    //                 std::cout << "#";
    //             else
    //                 std::cout << " ";
    //         }
    //     }

    //     std::cout << std::endl;
    // }

    // std::cout << "#  = walls" << std::endl;
    // std::cout << "S  = start" << std::endl;
    // std::cout << "E  = end" << std::endl;
    // std::cout << "number = path nodes" << std::endl;

    return Path;
}


inline PYBIND11_MODULE(LazyThetaStarPython, module) {
    module.doc() = "Python wrapper of Lazy Theta Star c++ implementation";

    module.def("FindPath", &FindPath, "Find a collision-free path");
    // module.def("FindPathAll", &FindPathAll, "Find all the collision-free paths");
}