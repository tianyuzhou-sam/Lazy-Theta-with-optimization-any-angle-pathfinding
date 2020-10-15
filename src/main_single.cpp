#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include "tileadaptor.hpp"
#include "find_path.hpp"


int main()
{
    constexpr int mapSizeX = 70; // width
    constexpr int mapSizeY = 20; // length

    // initialize the map, 0 means no obstacles; each sub vector is a column.
    std::vector<std::vector<int>> Map(mapSizeX, std::vector<int> (mapSizeY, 0));

    Vectori startPoint = {1, 1};
    Vectori endPoint = {mapSizeX - 2, mapSizeY - 2};

    // This is a lambda function to create the wall
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


    std::vector<Vectori> path = find_path(startPoint, endPoint, Map);


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
    std::cout << duration.count() << std::endl; 


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
    for(int y = 0; y < static_cast<int>(Map[0].size()); y++)
    {
        for(int x = 0; x < static_cast<int>(Map.size()); x++)
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
