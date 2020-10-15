#include <iostream>
#include <vector>
#include <array>

#include "tileadaptor.hpp"

#include <chrono>

int main()
{
    constexpr int mapSizeX = 70;
    constexpr int mapSizeY = 20;

    //Normaly would have used a std::vector of size x*y but just for this test it's
    //Gonna be way easier and readeable to do it this way
    std::array<std::array<int, mapSizeY>, mapSizeX> Map;

    Vectori startPoint = {1, 1};
    Vectori endPoint = {mapSizeX - 2, mapSizeY - 2};

    auto makeWall = [&Map](const Vectori& pos, const Vectori& size)
    {
        for(int x = 0; x < size.x; x++)
        {
            for(int y = 0; y < size.y; y++)
            {
                Map[pos.x + x][pos.y + y] = 255;
            }
        }
    };

    // auto start = std::chrono::high_resolution_clock::now();

    //Instantiating our path adaptor
    //passing the map size and a lambda that return false if the tile is a wall
    TileAdaptor adaptor({mapSizeX, mapSizeY}, [&Map](const Vectori& vec){return Map[vec.x][vec.y] != 255;});
    //This is a bit of an exageration here for the weight, but it did make my performance test go from 8s to 2s
    Pathfinder pathfinder(adaptor, 100.f /*weight*/);

    //set everythings to space
    for(auto& cs : Map)
        for(auto& c : cs)
            c = 0;

    //borders
    makeWall({0, 0}, {mapSizeX, 1});
    makeWall({0, 0}, {1, mapSizeY});
    makeWall({0, mapSizeY - 1}, {mapSizeX, 1});
    makeWall({mapSizeX - 1, 0}, {1, mapSizeY});

    //walls
    makeWall({5, 0}, {1, mapSizeY - 6});
    makeWall({mapSizeX - 6, 5}, {1, mapSizeY - 6});

    makeWall({mapSizeX - 6, 5}, {4, 1});
    makeWall({mapSizeX - 4, 8}, {4, 1});

    makeWall({20, 0}, {1, mapSizeY - 4});
    makeWall({mapSizeX - 20, 5}, {14, 1});

    //start and end point
    Map[startPoint.x][startPoint.y] = 0;
    Map[endPoint.x][endPoint.y] = 0;

    auto start = std::chrono::high_resolution_clock::now();

    //The map was edited so we need to regenerate teh neighbors
    pathfinder.generateNodes();

    // auto start = std::chrono::high_resolution_clock::now();

    //doing the search
    //merly to show the point of how it work
    //as it would have been way easier to simply transform the vector to id and pass it to search
    auto nodePath = pathfinder.search(adaptor.posToId(startPoint), adaptor.posToId(endPoint));

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
    std::cout << duration.count() << std::endl; 

    //Convert Ids onto map position
    std::vector<Vectori> path;
    path.reserve(nodePath.size());

    for(const auto id : nodePath)
        path.push_back(adaptor.idToPos(id));


    //There is also a serach function that do the conversion between your data type
    //And the id, it take lambdas to convert between the two
    //Here's an exemple of how it would be called for this code
//    auto path = pathfinder.search(startPoint, endPoint,
//                                        {
//                                            [&adaptor](const auto id)
//                                            {
//                                                return adaptor.idToPos(id);
//                                            }
//                                        },
//                                        {
//                                            [&adaptor](const auto& data)
//                                            {
//                                                return adaptor.posToId(data);
//                                            }
//                                        });


    //If we found a path we just want to remove the first and last node
    //Because it will be at our start and end position
    if(path.size())
    {
        path.pop_back();
        path.erase(path.begin());
    }

    //nodes
    int x = 0;
    for(const auto& node : path)
        Map[node.x][node.y] = 1 + x++;

    //draw map
    for(int y = 0; y < Map[0].size(); y++)
    {
        for(int x = 0; x < Map.size(); x++)
        {
            if ((startPoint.x == x) && (startPoint.y == y))
                std::cout << "S";
            else if ((endPoint.x == x) && (endPoint.y == y))
                std::cout << "E";
            else
            {
                if ((Map[x][y] != 255) && (Map[x][y] != 0))
                    std::cout << Map[x][y];
                else if (Map[x][y] == 255)
                    std::cout << "#";
                else
                    std::cout << " ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << "#  = walls" << std::endl;
    std::cout << "S  = start" << std::endl;
    std::cout << "E  = end" << std::endl;
    std::cout << "number = path nodes" << std::endl;

    return 0;
}
