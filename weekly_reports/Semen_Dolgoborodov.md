11/12/2023. Build the project on the Ubuntu virtual machine. Working on the functionality to allow to load the external objects into the project.
17/12/2023. Created a basic class ObjectLoader that can load a limited range of .obj files. Further refinement of this functionality is needed. Additionally, the integration of this class in the main function is required. Created a "demo" folder to store obj. files.
21/12/2023. Object loading now works with files from demo folder (sometimes zoom out is required to see). Only vertices information is used at the moment, we could take advantage of other information in .obj file. Perhaps world creation could also be generalized. Added 2 more .obj examples in "demo" folder