Weekly report:

11/12/2023 - rewritten the drawing system. Currently working on implementing the Entity Component System (ecs). Added mesh component, with the drawing functionality.

27/12/2023 - edited the Entity class heavily for improved readability and easier modifications in the future.

03/01/2024 - implemented the texture class and added it to the drawing process. also edited entity class further to add textures to entities. Wrote new slightly different shader variants which display texture instead of colour. Some bugs remain to be fixed.

13/01/2024 - textures fixed with Alex. Now can load any image onto an object correctly.

14-15/01/2024 - added ambient, diffuse, and specular lighting according to phong model. The user can add up to 20 lightsources. some minor bugs related to specular lighting remain, ambient and diffuse work perfectly well.

18/01/2024 - Added a grid to the engine which makes the layout in space more clear. The grid is customizable, the amount of lines and their setup can be changed, in the future one will be able to toggle it on and off and change its colours more easily.
