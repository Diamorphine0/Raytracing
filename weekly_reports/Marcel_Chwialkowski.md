# Weekly report:
* **25-30/11/2023** - First steps. With Alex, we were figuring out which libraries to use for graphics (we settled for OpenGL) and UI (settled for ImGUI). Reading a lot of OpenGL tutorials to get started and discussing the project structure.

* **11/12/2023** - rewritten the drawing system. Currently working on implementing the Entity Component System (ecs). Added mesh component, with the drawing functionality.

* **27/12/2023** - edited the Entity class heavily for improved readability and easier modifications in the future.

* **03/01/2024** - implemented the texture class and added it to the drawing process. also edited entity class further to add textures to entities. Wrote new slightly different shader variants which display texture instead of colour. Some bugs remain to be fixed.

* **13/01/2024** - textures fixed with Alex. Now can load any image onto an object correctly.

* **14-15/01/2024** - added ambient, diffuse, and specular lighting according to phong model. The user can add up to 20 lightsources. some minor bugs related to specular lighting remain, ambient and diffuse work perfectly well.

* **18/01/2024** - Added a grid to the engine which makes the layout in space more clear. The grid is customizable, the amount of lines and their setup can be changed, ~~in the future one will be able to toggle it on and off and change its colours more easily~~ (update: that was never implemented due to its low priority).

* **19-20/01/2024** - Added a window in the engine which allows one to add an object with a texture into the world. Connected the back end to the properties window in the UI - now one can apply translations and scaling to objects (for now just the root object, but with object picking implemented this can be applied to the object currently in focus). Minor quality of life changes - changed the camera movement system, ~~and added an optional zoom mode (not connected to the UI) which would enable slower zoom-like movement if needed~~ (update: it was deleted in a later commit).

* **28-30/01/2024** - Final touches. Fixed the menu on the left hand side of the screen which displays the object hierarchy. Now, any time an object gets added via the menu on the right, its tag shows up in the object hierarchy. Moreover, one can select an object in the object hierarchy and then the transformation applied via the transformation menu apply only to this object (that I couldn't get to run correctly so the final version of this feature was pushed by Alex Storozhenko). Added an ambience attribute to the objects - instead of a common ambient light in the scene, one can change the shades of selected objects via the properties menu now. Extremely minor UI changes.
