#include <iostream>
#include <vector>
#include <chrono>
// #include "k_means.hpp"
#include "k_means_new.hpp"


int main()
{
    Point pt1 = { .x = 100.0, .y = 100.0 };
    Point pt2 = { .x = 99.0, .y = 99.0 };
    Point pt3 = { .x = 100.0, .y = 99.0 };
    Point pt4 = { .x = 99.0, .y = 100.0 };
    Point pt5 = { .x = 0.0, .y = 0.0 };
    Point pt6 = { .x = 0.0, .y = 0.5 };
    Point pt7 = { .x = 0.5, .y = 0.0 };
    Point pt8 = { .x = 0.5, .y = 0.5 };
    Point pt9 = { .x = -100.0, .y = -100.0 };
    Point pt10 = { .x = -101.0, .y = -101.0 };
    Point pt11 = { .x = 1000.0, .y = 1000.0 };
    Point pt12 = { .x = -101.5, .y = -101.5 };

    // std::vector<Point> data;
    DataFrame data;
    data.push_back(pt1);
    data.push_back(pt2);
    data.push_back(pt5);
    data.push_back(pt6);
    data.push_back(pt3);
    data.push_back(pt4);
    data.push_back(pt7);
    data.push_back(pt8);
    data.push_back(pt9);
    data.push_back(pt10);
    data.push_back(pt11);
    data.push_back(pt12);


    size_t k = 4;
    size_t number_of_iterations = 100;

    auto start = std::chrono::high_resolution_clock::now();

    // auto [means, assignments] = k_means(data, k, number_of_iterations);
    auto [means, assignments, points_index_2d] = k_means_new(data, k, number_of_iterations);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time used [microseconds]:" << duration.count() << std::endl;

    for (auto& cluster : means) {
        // std::cout << cluster << std::endl;
        std::cout << cluster.x << ", " << cluster.y << std::endl;
    }

    for (auto& pt : assignments) {
        // std::cout << cluster << std::endl;
        std::cout << pt << std::endl;
    }
    
    for (auto& vec : points_index_2d) {
        std::cout << "This is a cluster." << std::endl;

        for (auto& ele : vec) {
            std::cout << ele << std::endl;
        }
        
    }

    return 0;
}

