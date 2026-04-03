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

## Building

To build this project, you need CMake and other build essentials. If you run windows, I recommend using WSL.

```bash
mkdir build && cd build

cmake -G Ninja ..
ninja build -j 8
```

### Acknowledgements

[ascii Art on startup](https://www.asciiart.eu/text-to-ascii-art) 
