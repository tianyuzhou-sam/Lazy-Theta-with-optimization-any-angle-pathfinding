# Lazy Theta* with optimization pathfinding
This is a customized version of Lazy-Theta-with-optimization-any-angle-pathfinding. Given a map and a set of starts and goals, this algorithm can return an optimal path. This repo has very easy-to-build-and-use C++ implementation and Python wrapper.


This repo has been tested with:
* GCC 9.3.0, CMake 3.16.3, Ubuntu 20.04.1 LTS
* Clang 12.0.0.0, CMake 3.18.3, macOS 10.15.7

Dependencies
============
For Python:
* [pybind11](https://github.com/pybind/pybind11) If you only install `pybind11` by `pip`, it's possible that CMake can't find it. But you can install it by `apt` or `brew`.
* [numpy](https://numpy.org/).
* [matplotlib](https://matplotlib.org/).


Build
=====
```
$ apt-get install pybind11 # For macOS: brew install pybind11
$ pip3 install numpy matplotlib
$ git clone https://github.com/zehuilu/Lazy-Theta-with-optimization-any-angle-pathfinding.git
$ cd <MAIN_DIRECTORY>
$ mkdir build
$ cd build
$ cmake ..
$ make
```


Usage
=====

For C++, the main file is `src/main_single_path.cpp`.
```
$ cd <MAIN_DIRECTORY>
$ build/main_single_path
```

For Python, the main file is `test/test_LazyThetaStarPython.py`.
```
$ cd <MAIN_DIRECTORY>
$ python3 test/test_LazyThetaStarPython.py
```

=========================================================================================





Files:

- pathfinding.hpp
  - The main file, the only one you need
  - Contain the algoritm 
- tileadaptor.hpp
  - To use the pathfinding class you'll need an adaptor, this is an exemple adaptor for tile grid
- utility.hpp
  - Dummy vector class and distance function used by tileadaptor
- main.cpp
  - Console based demo

```
######################################################################
#S   #              #                                                #
#    #              #                                                #
#    #              #                                                #
#    #              #                            3                  4#
#    #              #                             ################## #
#    #              #                                           #    #
#    #              #                                           #5   #
#    #              #                                           # ####
#    #              #                                           #    #
#    #              #                                           #    #
#    #              #                                           #    #
#    #              #                                           #    #
#    #              #                                           #    #
#   1               #                                           #    #
#                   #                                           #6   #
#                                 2                             #    #
#                                                               #    #
#                                                               #   E#
######################################################################
#  = walls
S  = start
E  = end
number = path nodes
```

Implementation of the algorithm described here: http://aigamedev.com/open/tutorial/lazy-theta-star/

At first I could find any code a part from this and honestly I had no idea of what line 37-38 means
![pseudo cat](http://aigamedev.com/wp-content/blogs.dir/5/files/2013/07/fig53-full.png)

After some amount of research I found this page http://idm-lab.org/project-o.html which provided me with some code.
I rewrote most of it because the code style dind't suite me and to take advantage of C++14.

I also made it more modular so that it can be used for grid, hexagonTile, polygon map, anything where you need to find a path between to point.

Also added the possibility to use weighted h-value as described in the first link, it make the search faster but may give slitghly longer path.
