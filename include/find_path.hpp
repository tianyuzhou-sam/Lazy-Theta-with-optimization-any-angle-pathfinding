#include <iostream>
#include <vector>
#include <array>

#include "tileadaptor.hpp"

#include <chrono>


inline std::vector<Vectori> find_path(Vectori &startPoint, Vectori &endPoint, const std::vector<std::vector<int>> &Map)
{

    //Instantiating our path adaptor
    //passing the map size and a lambda that return false if the tile is a wall

    std::function<bool(const Vectori&)> read_map = [&Map](const Vectori& vec)
    {
        return Map[vec.x][vec.y] != 255;
    };


    // TileAdaptor adaptor({static_cast<int>(Map.size()), static_cast<int>(Map[0].size())}, [&Map](const Vectori& vec){return Map[vec.x][vec.y] != 255;});
    
    TileAdaptor adaptor({static_cast<int>(Map.size()), static_cast<int>(Map[0].size())}, read_map);
    
    //This is a bit of an exageration here for the weight, but it did make my performance test go from 8s to 2s
    Pathfinder pathfinder(adaptor, 100.f /*weight*/);

    //The map was edited so we need to regenerate teh neighbors
    pathfinder.generateNodes();

    // auto start = std::chrono::high_resolution_clock::now();

    //doing the search
    //merly to show the point of how it work
    //as it would have been way easier to simply transform the vector to id and pass it to search
    auto nodePath = pathfinder.search(adaptor.posToId(startPoint), adaptor.posToId(endPoint));


    //Convert Ids onto map position
    std::vector<Vectori> path;
    path.reserve(nodePath.size());

    for(const auto id : nodePath)
        path.push_back(adaptor.idToPos(id));

    return path;
}
