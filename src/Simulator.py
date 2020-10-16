#!/usr/bin/env python3
import os
import sys
sys.path.append(os.getcwd()+'/src')
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from random import randint
import copy


class Simulator(object):
    resolution: int
    map_width: int
    map_height: int
    value_non_obs: int
    value_obs: int
    size_obs_width: int
    size_obs_height: int

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

        # a 2D list, each element is x and y coordinates of the obstacle's left top corner
        self.obs_left_top_corner_list = []


    def generate_random_obs(self, num_obs: int, size_obs: list):
        self.size_obs_width = round(size_obs[0] * self.resolution)
        self.size_obs_height = round(size_obs[1] * self.resolution)
        if num_obs > 0:
            for idx_obs in range(0, num_obs):
                # [width, height]
                obs_left_top_corner = [randint(1,self.map_width-self.size_obs_width-1), randint(1, self.map_height-self.size_obs_height-1)]

                self.obs_left_top_corner_list.append(obs_left_top_corner)

                obs_mat = self.map_array[obs_left_top_corner[1]:obs_left_top_corner[1]+self.size_obs_height+1][:, obs_left_top_corner[0]:obs_left_top_corner[0]+self.size_obs_width+1]
                print(obs_mat.shape)

                self.map_array[obs_left_top_corner[1]:obs_left_top_corner[1]+self.size_obs_height+1][:, obs_left_top_corner[0]:obs_left_top_corner[0]+self.size_obs_width+1] \
                    = self.value_obs * np.ones(obs_mat.shape)


    def plot_single_path(self, *arguments):
        """
        Simulator.visualize(path) # plot a path
        path is a list for the trajectory. [x[0], y[0], x[1], y[1], ...]
        """

        if len(arguments[0]) > 0:
            fig_map, ax_map = plt.subplots(1, 1)

            # plot retangle obstacles
            for idx in range(len(self.obs_left_top_corner_list)):
                # Create a Rectangle patch
                print(self.obs_left_top_corner_list[idx])
                rect = patches.Rectangle(self.obs_left_top_corner_list[idx], self.size_obs_width, self.size_obs_height, linewidth=1, edgecolor='k', facecolor='k')
                # Add the patch to the Axes
                ax_map.add_patch(rect)

            ax_map.scatter(arguments[0][0], arguments[0][1], label="start")
            ax_map.scatter(arguments[0][-2], arguments[0][-1], label="goal")
            ax_map.plot(arguments[0][0::2], arguments[0][1::2], label="path")
            ax_map.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
            ax_map.set_xlabel("x")
            ax_map.set_ylabel("y")
            ax_map.set_aspect('equal')
            ax_map.set_xlim([0, self.map_width])
            ax_map.set_ylim([0, self.map_height])
            plt.show()
        else:
            print("Lazy Theta Star didn't find a path!")


    def plot_many_path(self, path_many: list, agent_position: list, targets_position: list):
        """
        path_many is a list for the trajectory. [[x[0],y[0],x[1],y[1], ...], [x[0],y[0],x[1],y[1], ...], ...]
        """

        fig_map, ax_map = plt.subplots(1, 1)
        
        # plot retangle obstacles
        for idx in range(len(self.obs_left_top_corner_list)):
            # Create a Rectangle patch
            print(self.obs_left_top_corner_list[idx])
            rect = patches.Rectangle(self.obs_left_top_corner_list[idx], self.size_obs_width, self.size_obs_height, linewidth=1, edgecolor='k', facecolor='k')
            # Add the patch to the Axes
            ax_map.add_patch(rect)

        ax_map.scatter(agent_position[0], agent_position[1], label="start")
        for idx_target in range(0, int(len(targets_position)/2)):
            ax_map.scatter(targets_position[2*idx_target], targets_position[2*idx_target+1], label="goal")

        for idx_path in range(0, len(path_many)):
            ax_map.plot(path_many[idx_path][0::2], path_many[idx_path][1::2], label="path")

        ax_map.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
        ax_map.set_xlabel("x")
        ax_map.set_ylabel("y")
        ax_map.set_aspect('equal')
        ax_map.set_xlim([0, self.map_width])
        ax_map.set_ylim([0, self.map_height])
        plt.show()