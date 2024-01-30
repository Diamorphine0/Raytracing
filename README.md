# Raytracer and Engine

## Introduction
- CSE201 project on the topic of ray tracing, engine graphics, and animations. The goal was to
  program a GLFW OpenGL application capable of handling animations and implementing a simple ray tracer
  that can view different objects imported inside of the engine.

## Index

- [About](#about)
- [Usage](#usage)
- [Development](#development)
- [Contribution](#contribution)
- [Resources](#resources)

## About
- The application in question serves as a tool to implement different object entities inside of a scene and view them.
  The scene is inside of an engine that is capable of animating these objects, as well as determining their position in 3D and 
  positioning the camera which views them. These objects can then further be manipulated inside of the engine, modifying their position, color,
  texture, size etc. Finally, the scene can then be captured through a ray tracer that performs complex algorithms and uses optics to make the 
  rendering more efficient.

## Usage
### Add Object
- We start with adding objects. Here we can initialize different shapes and give them different textures and tags so that later we can access them and change
  their properties. The added objects will appear at the center of the 3D axis. Once the object is not needed anymore, we can use the 'DELETE' button to remove it from the scene.
### Hierarchy
- An important data structure used in this project is the scene graph. Here, it is presented and we can visualize how the objects are sorted in memory, as well as access specific objects
  and modify them. The structure works like a tree with entities that are presented on the screen.
### Properties
- Here all of the different properties of the object can be changed.
### Animation
- This part of the application handles the animations as well as different keyframes.
### Raytracing 
- Image is generated inside the build folder
### Raytracing animation
- Video generated inside the root folder
### Settings 
  Here you can see basic data and stats related to the engine, camera, and the ray tracer like FPS and CPU usage. Additionally, this is where the button for ray tracing is located.

## Development
...

## Contribution
The contributors to the project are the following individuals (in no particular order):
- Alexander Storozhenko [**Project Leader**]
- Tudor Ivan
- Marcel Chwialkowski
- Luka Barovic [**Git Leader**]
- Ryan Sfeila
- David Kraus
- Ena Stefic
- Akira Roman Barros Griffiths Sugeno
- Joseph Weizsacker
- Simon Dolgoborodov
- Anca Sfia [**Trello Leader**]
- Jana Zlatic

## Dependencies (Everything is run with the CMAKE file)
- GLFW
- OpenGL
- GLM
- ImGUI 
- ffmpeg
- stb_image
- QT

## Example of how to build (on LINUX): 

clone repo into folder
...
mkdir build
cd cuild
cmake .. -DCMAKE_PREFIX_PATH=/home/tudor/Qt/6.6.1/gcc_64
make
./Raytracing
