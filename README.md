# GraphAlgs! 

```
  ____                 _        _    _           
 / ___|_ __ __ _ _ __ | |__    / \  | | __ _ ___ 
| |  _| '__/ _ | '_ \| '_ \  / _ \ | |/ _ / __|
| |_| | | | (_| | |_) | | | |/ ___ \| | (_| \__ \
 \____|_|  \__,_| .__/|_| |_/_/   \_\_|\__, |___/
                |_|                    |___/     
```

This is a project that I am writing to help me memorise how to do all the different algorithms that I need to know for my exam.

It creates a graph that users can add and remove vertices to/from the graph and then run different traversal and pathfinding algorithms.

## Usage

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

### Acknowledgements

[ascii Art on startup](https://www.asciiart.eu/text-to-ascii-art) 
