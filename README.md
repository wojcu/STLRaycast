# STLRaycast
Raycasting engine written in pure C++ without external libraries.

# WIP
The rendered scenes and configuration are still hardcoded into the source.

# About
Static image renderer built without any external libraries.

# Features
- Multisampling
- Threaded / Single-core renderers
- PPM output format
- Reflections

# Example
The following scene can be rendered in 0.872 seconds with the number of reflections limited to 1 and without multisampling.

![alt text](http://i.imgur.com/C0o8XiW.png "Small example")

The same scene rendered in 50.260 seconds with 16 reflections and 8x multisampling.

![alt text](http://i.imgur.com/sZNgWqQ.png "Big example")
