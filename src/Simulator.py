#!/usr/bin/env python3
import os
import sys
sys.path.append(os.getcwd()+'/src')
import numpy as np
import matplotlib.pyplot as plt
from random import randint


class Simulator(object):
    resolution: int
    map_width: int
    map_height: int
    obs_size: float
    value_non_obs: int
    value_obs: int


    def __init__(self, 
        map_width_meter: float, 
        map_height_meter: float, 
        resolution: int,
        value_non_obs: int,
        value_obs: int):
        """
        Constructor

        the cell is empty if value_non_obs, the cell is blocked if value_obs.
        """

        # map resolution, how many cells per meter
        self.resolution = resolution
        # how many cells for width and height
        map_width = map_width_meter * resolution
        map_height = map_height_meter * resolution

        # check if these are integers
        assert (map_width.is_integer() == True)
        assert (map_height.is_integer() == True)

        self.map_width = int(map_width)
        self.map_height = int(map_height)

        self.value_non_obs = value_non_obs
        self.value_obs = value_obs

        # create an empty map
        self.map_array = np.array([self.value_non_obs]*(self.map_width*self.map_height)).reshape(-1, self.map_width)

        # the length [meter] of box obstacles
        self.obs_size = 0.5 * self.resolution


    def generate_random_obs(self, num_obs: int):
        obs_half_size = round(self.obs_size/2)
        if num_obs > 0:
            for idx_obs in range(0, num_obs):
                # [width, height]
                obs_center = [randint(1+obs_half_size,self.map_width-obs_half_size), randint(1+obs_half_size, self.map_height-obs_half_size)]
            
                obs_mat = self.map_array[obs_center[1]-obs_half_size : obs_center[1]+obs_half_size+1][:, obs_center[0]-obs_half_size : obs_center[0]+obs_half_size+1]
                self.map_array[obs_center[1]-obs_half_size : obs_center[1]+obs_half_size+1][:, obs_center[0]-obs_half_size : obs_center[0]+obs_half_size+1] = \
                    self.value_obs * np.ones(obs_mat.shape)


    def plot_single_path(self, *arguments):
        """
        Simulator.visualize(path) # plot a path
        path is a list for the trajectory. [x[0], y[0], x[1], y[1], ...]
        """

        if len(arguments[0]) > 0:
            fig_map, ax_map = plt.subplots(1, 1)
            ax_map.imshow(self.map_array, cmap='binary')
            ax_map.scatter(arguments[0][0], arguments[0][1], label="start")
            ax_map.scatter(arguments[0][-2], arguments[0][-1], label="goal")
            ax_map.plot(arguments[0][0::2], arguments[0][1::2], label="path")
            ax_map.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
            ax_map.set_xlabel("x")
            ax_map.set_ylabel("y")
            plt.show()
        else:
            print("Lazy Theta Star didn't find a path!")


    def plot_many_path(self, path_many: list, agent_position: list, targets_position: list):
        """
        path_many is a list for the trajectory. [[x[0],y[0],x[1],y[1], ...], [x[0],y[0],x[1],y[1], ...], ...]
        """

        fig_map, ax_map = plt.subplots(1, 1)
        ax_map.imshow(self.map_array, cmap='binary')
        ax_map.scatter(agent_position[0], agent_position[1], label="start")
        for idx_target in range(0, int(len(targets_position)/2)):
            ax_map.scatter(targets_position[2*idx_target], targets_position[2*idx_target+1], label="goal")

        for idx_path in range(0, len(path_many)):
            ax_map.plot(path_many[idx_path][0::2], path_many[idx_path][1::2], label="path")

        ax_map.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
        ax_map.set_xlabel("x")
        ax_map.set_ylabel("y")
        plt.show()