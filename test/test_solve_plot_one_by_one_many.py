#!/usr/bin/env python3
import os
import sys
sys.path.append(os.getcwd()+'/build')
sys.path.append(os.getcwd()+'/src')
import LazyThetaStarPython
import time
from math import sqrt
import matplotlib.pyplot as plt
from Simulator import Simulator


if __name__ == "__main__":
    # define the world
    map_width_meter = 30.0
    map_height_meter = 20.0
    map_resolution = 2
    value_non_obs = 0 # the cell is empty
    value_obs = 255 # the cell is blocked
    # create a simulator
    MySimulator = Simulator(map_width_meter, map_height_meter, map_resolution, value_non_obs, value_obs)
    # number of obstacles
    num_obs = 500
    # [width, length] size of each obstacle [meter]
    size_obs = [0.5, 0.5]
    # generate random obstacles
    MySimulator.generate_random_obs(num_obs, size_obs)
    # convert 2D numpy array to 1D list
    world_map = MySimulator.map_array.flatten().tolist()

    num_case = 20
    MySimulator.init_path_one_by_one_node_many()
    lastFlag = False
    for idx in range(num_case):
        if idx == num_case - 1:
            lastFlag = True

        # This is for a single start and goal
        num_targets = 1
        start, targets = MySimulator.generate_start_and_goals(num_targets)
        # solve it
        t0 = time.time()
        path_single, distance_single = LazyThetaStarPython.FindPath(start, targets, world_map, MySimulator.map_width, MySimulator.map_height)
        t1 = time.time()
        print("Time used for a single path is [sec]: " + str(t1-t0))
        print("This is the path.")
        print("Total distance: " + str(distance_single))
        distance_check = 0.0
        for idx in range(0,len(path_single),2):
            str_print = str(path_single[idx]) + ', ' + str(path_single[idx+1])
            print(str_print)
            if idx > 0:
                distance_check = distance_check + sqrt((path_single[idx]-path_single[idx-2])**2 + (path_single[idx+1]-path_single[idx-1])**2)
        print("Distance computed afterwards: " + str(distance_check))

        # visualization
        MySimulator.plot_path_one_by_one_node_many(path_single, (t1-t0)*1000, lastFlag)
