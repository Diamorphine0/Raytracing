17/12/2023:
Created a button and a slider in the GUI. The buttons are not functional for now, but will be used to toggle options and set parameters of the raytracer.
Moved the rendering process of the raytracer from ppm format to OpenGL.
For now the Raytracing button just opens a new OpenGL window.
In order to actually render the image resulting from the raytracing process, we would have to convert our 2D pixel_colors array into a OpenGL "texture", and in turn display this texture in our OpenGL window.

07/01/2024:
Worked on GUI. Created multiple ImGui windows layered over the OpenGL scene. Created functions that initiliaze the buttons, sliders and menus that will be represented in these windows. Ultimately, we would like to have our OpenGL in a seperate ImGui window, so we don't have to layer the other windows over it.

08/01/2024:
In order to render our OpenGL scene in an ImGui window we created a FrameBuffer class.

11/01/2024:
Tried to Bind the framebuffer, but ran into some issues. Alex will now pick up the task of correctly binding the framebuffer and rendering it onto an ImGui window, while we will continue working on the other windows of the GUI.
