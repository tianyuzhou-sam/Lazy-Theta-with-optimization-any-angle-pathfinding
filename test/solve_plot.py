#!/usr/bin/env python3
import os
import sys
sys.path.append(os.getcwd()+'/build')
sys.path.append(os.getcwd()+'/src')
import LazyThetaStarPython
import numpy as np
import time
import matplotlib.pyplot as plt

import Simulator as helper


if __name__ == "__main__":
    # define the world
    map_width_meter = 20.0
    map_height_meter = 20.0
    map_resolution = 2
    value_non_obs = 0 # the cell is empty
    value_obs = 255 # the cell is blocked
    # create a simulator
    Simulator = helper.Simulator(map_width_meter, map_height_meter, map_resolution, value_non_obs, value_obs)
    # number of obstacles
    num_obs = 50
    # [width, length] size of each obstacle [meter]
    size_obs = [1, 1]
    # generate random obstacles
    Simulator.generate_random_obs(num_obs, size_obs)
    # convert 2D numpy array to 1D list
    world_map = Simulator.map_array.flatten().tolist()


    # This is for a single start and goal
    start = [5, 8]
    end = [35, 34]
    # solve it
    t0 = time.time()
    path_single = LazyThetaStarPython.FindPath(start, end, world_map, Simulator.map_width, Simulator.map_height)
    t1 = time.time()
    print("Time used for a single path is [sec]: " + str(t1-t0))
    print("This is the path.")
    for idx in range(0,len(path_single),2):
        str_print = str(path_single[idx]) + ', ' + str(path_single[idx+1])
        print(str_print)
    # visualization (uncomment next line if you want to visualize a single path)
    Simulator.plot_single_path(path_single)    


    # This is for an agent and a set of targets
    agent_position = [0, 0]
    targets_position = [35,35, 10,38, 30,6, 25,29]
    t0 = time.time()
    # solve it
    path_many = LazyThetaStarPython.FindPathMany(agent_position, targets_position, world_map, Simulator.map_width, Simulator.map_height)
    t1 = time.time()
    print("These are all the paths. Time used [sec]:" + str(t1 - t0))
    for i in range(0,len(path_many),1):
        print("This is a path.")
        for j in range(0,len(path_many[i]),2):
            str_print = str(path_many[i][j]) + ', ' + str(path_many[i][j+1])
            print(str_print)
    # visualization (uncomment next line if you want to visualize a single path)
    Simulator.plot_many_path(path_many, agent_position, targets_position)
