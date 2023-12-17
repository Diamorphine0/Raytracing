17/12/2023:
Created a button and a slider in the GUI. The buttons are not functional for now, but will be used to toggle options and set parameters of the raytracer.
Moved the rendering process of the raytracer from ppm format to OpenGL.
For now the Raytracing button just opens a new OpenGL window.
In order to actually render the image resulting from the raytracing process, we would have to convert our 2D pixel_colors array into a OpenGL "texture", and in turn display this texture in our OpenGL window.
