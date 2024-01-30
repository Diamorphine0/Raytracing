Week 1:
-
- Organized first team meeting; As a result, we have adopted a 2 team approach (members evenly split between the Engine and the Raytracing Component).
  - Outlined the project objectives:
    - An engine to set up scenes; Define objects (Textures, Materials, Positions);
    - Animation functionality in the engine (Load .obj files and be able to move them around the scene);
    - A parallel raytracing engine to render the objects with photo realism;
    - Ability to raytrace the animations constructed in the engine.
- Implemented a simple OpenGL window with ability to render verticies 
- Implemented a simple camera to navigate the scene

Week 2:
-
- The first encountered challenge stemmed from issues of platform compatibility, as we had to synchronize library loading across 3 different operating systems. To resolve the issue, we have set up 3 installation workshop sessions outside of TD hours to help members build the project. Unfortunately, numerous members disregarded the proposed request. 
- In conjunction with Tudor.I wrote the list of tasks to be implemented for the week (first come first serve principle)
- Installed the ImGUI library locally - fixed bugs in the original file (adressed the present incompatibilities between our stack and the library)
  (Pushed to github from Ryan.S. account);
- Added a minimal viable UI display and designated a UI team;

Week 3:
- 
- Discussed the problem of members not being able to set up the libraries with Julien Tierny. Based on the results of the discussion, we promptly adopted the proposed recommendations - organizing another installation session for the Linux Virtual machine (using the CLion IDE).
- Multiple tasks remain unfinished from last week. We have, hence, adopted an alternative approach of explicitly assigning tasks during the Monday sessions, agreeing members would commit the chosen task by the end of the week.  Unfortunately, multiple members consistently failed to attend the Monday sessions, and ignored messages.
- Implemented a simple ECS class for the engine (Idea eventually dropped, in favor of strictly OOP approach)
- Simple object transformations added
- To adress the issue of unfinished tasks Tudor, Ryan, Marcel and I have split the additional workload between us to stay on track with the weekly goals.

Week 4:
- 
- Example excerpt (from the raytracing group chat) of intended task distribution for the team (Each member chose their own task and promised to finish by the end of the week):
  Tasks for the week - (Add your task / Ask for a task if you are not on the list)
  
  Engine Team:
    ECS system + Code Refactoring (Marcel & Alex)
    UI ( with the described functionality) (Akira)
    UI & Engine System Logging (Joseph)
    Camera Movement (Jana)
    Loading Objects (Semen)
    Batch Rendering / Displaying multiple objects( Anca + Dimitar )
    Passing information to the raytracing camera ( Cannot be added for now - The ECS code will look different from the way it's currently implemented)
    
  Raytracing Team:
    Connect the raytracing camera with engine (Alex & Tudor)
    Positionable Camera (Ena)
    Shading , Reflection, Refraction (Ryan)
    Möller–Trumbore and optimization of rendering using bounding volume hierarchies (Luka)
    Moving the raytracing display to opengl - Associate to it a simple UI (using ImGUI, which would allow to toggle betwen the different raytracing improvements to be added) ( David )
  
 - The ECS approach was dropped at the end of the week due to the relative similarity of the considered objects, making an OOP based approach sufficiently efficient.
 - At the end of the week, we held another session to track the general progress of the team - multiple tasks remain undone, due to cited reasons of overwhelming course work. We reached an agreement that tasks would be completed over
the Christmas break.
 - Assigned new set of tasks (See Trello).
 - Helped merge the engine entity representation to the raytracing component. 

Week 5:
- 
- Abstraction of rendering event loop (Completed the engine camera class)
- Abstracton of the openGL library code (Through the definition of Vertex, VB, VA, & Entity classes)
- Created the Scene Graph Class (Refer to the node class)
- Added simple animation functionality
- Merged with raytracing part (Task completed with Tudor Ivan - leader of the raytracing team)
- Had to take on multiple taks such as object loading, camera movement, textures which have now been on hold for 2-3 weeks, as members were unable to implement them.
- Correspondingly assigned simpler tasks to the aforementioned members (UI tasks, Connection of UI functionality to the implemented backend).
- List of proposed UI tasks:
  - When we select an object in the GUI (by hovering over it and left-clicking it), we have a dedicated portion of the window where its properties are shown. These properties include color, size, texture, coordinates. Each of these properties can be modified within the dedicated window.
  - When hovering over and left-clicking an object, arrows appear (like in blenders gizmos) that allow us to move, rotate and scale our object.
  - When holding shift, we can select multiple objects and modify, move, rotate and scale them simulataneously.
  - Another portion of the GUI window is dedicated to a displaying and modifying the hierarchy of objects. The hierarchy is ultimately another property of each object, defined in relation to the other objects.
  - When the raytracing button is clicked, another OpenGL window opens that renders the result of the raytracer. The result of the raytracer is stored in a 2D array containing the RGB codes of each individual pixel. This array needs to be rendered. Make sure the window opens closes without affecting the rest of the GUI. After clicking the raytrace button, a “save raytrace” button becomes clickable (it was there already, however, not clickable). When this button is clicked the result of the raytracer is written to a dedicated file. This can be in ppm format, but would ideally be in jpeg format.
  - For ease of debugging and future development, add a logging function to the engine. This logging function should report messages of the types; debug, info, warning, error and critical. Each log message should include the type of log the message, a timestamp and an appropriate message.
    
Week 6:
-
- Further improved the scene graph (Fixed hanging pointer issues)
- Animation through linear interpolation between keyframes
- Implementation of Textures and Lighting (Helping Marcel to fix the bugs and connect it to the engine functionality) + (Rewrote the code to fit the codebase style - abstracted textures into classes, etc ...).
- Object picking
- Frame buffer loading
- Previous tasks + UI tasks remain undone. I, individually, spoke to the responsible members to find out what problems they are facing. We managed to fix multiple issues and create the GUI branch. UI should be improved over the next 10 days.

Week 7:
- 
- Connected engine and raytracing functionality to the UI
- Implemented the animation functionality in the UI (Ability to create, modify, and edit keyframes; Run the engine animation with an animation bar; etc)
- Assisted in the final merge with the raytracing part (Task completed with Tudor Ivan - Leader of the raytracing team).
- Merged across multiple engine side branches, connecting the implemented functionality (i.e object loading and transforms) ( Task completed with Marcel Chwialkowski ).
- Fixed multiple bugs found in the code (hanging nullptrs, inconsistent naming, circular library loading)
- Fixed Matrix Multiplication issues (Task completed with Tudor Ivan) - There was a vector space change of basis inconsistency between raytracing and the engine.
- Animation Further Improved (i.e fixed lack of adjustment for scaling in the linear interpolation function)
- Converted to unique_ptrs and shader_ptrs for reasons of memory efficiency
