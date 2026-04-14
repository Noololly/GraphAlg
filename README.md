# GraphAlgs! 

```
  ____                 _        _    _           
 / ___|_ __ __ _ _ __ | |__    / \  | | __ _ ___ 
| |  _| '__/ _ | '_ \| '_ \  / _ \ | |/ _ / __|
| |_| | | | (_| | |_) | | | |/ ___ \| | (_| \__ \
 \____|_|  \__,_| .__/|_| |_/_/   \_\_|\__, |___/
                |_|                    |___/     
```

This is a project that I started writing to help me memorise how to do all the different algorithms that I need to know for my exam. It ended up being so much more! :D

It creates a graph that users can add and remove vertices to/from the graph and then run different traversal and pathfinding algorithms.

## Some context

A graph is a data structure that shows relationships. In computer science, we are taught how they work with abstract numbers, but they can be represented as anything really!

Cities, people and their friendships, family trees (although that's more a tree, which is a subtype of graph), etc.

A node is an object, in my code I refer to them as vertices a lot; and an edge is the connection between the object.

Dijkstra's algorithm is an algorithm find the shortest path between two vertices (nodes). The path length is the sum of the weights, which in my application, are the magenta numbers.

Breadth first search is a traversal algorithm, which is just an algorithm that goes around and finds all the nodes in order. Depth first search is the same thing, but it goes about it in a different way.

## Usage

If you download the zip file containing the executable and font file, just make sure the font file stays in a folder called assets. Unfortunately, the graphics library I use has no way of accessing system fonts.

Click and drag on a node to move it around, you can reposition the graph with it!
Press 'Space' to pause the physics, you can still drag the nodes around while paused.
Press 'r' to reset the display, the nodes will be places randomly around the window.

## Building

To build this project, you need CMake and other build essentials. If you run windows, I recommend using WSL.
I use SFML to run the GUI. The CMake system will automatically clone and build SFML, but its dependencies need to be downloaded manually.

```bash
# Install required dependencies (only required if building the project from source)
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype-dev
```

```bash
mkdir build && cd build

cmake -G Ninja ..
ninja build -j 8
```

## Some photos
|                                                                              |                                                                              |
|------------------------------------------------------------------------------|------------------------------------------------------------------------------|
| ![](https://cdn.hackclub.com/019d8d10-8f95-73fb-9d92-b4c192520608/image.png) | ![](https://cdn.hackclub.com/019d8d11-1b5f-770d-8da7-cdb37d808b3a/image.png) |
| ![](https://cdn.hackclub.com/019d8d2d-b0b9-791d-bbef-7ac2fc8cbc17/image.png) | ![](https://cdn.hackclub.com/019d8d51-ab57-706b-9097-a5425b9f83f0/image.png) |


### Acknowledgements

[ascii Art on startup](https://www.asciiart.eu/text-to-ascii-art) 

The only fully AI generated part of the project is the GitHub actions that builds the executable
