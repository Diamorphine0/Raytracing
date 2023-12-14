11/12/23
At this stage, computation of facing ratio at each hitpoint (for shading/Lambertian reflectance later) in Reflection Branch and computation of reflected ray.
Next step, recursively evaluate reflected rays up to reflection depth to determine pixel color.
After: Determine reflection paramters for materials, refraction, optimize code (adapt to mesh structure.)


14/12/23
My previous Reflection Branch is Quasi useless after the engine -Raytracer merge, so i reimplemented it, and at this shade have pretty naive shading algorithm implemented. Needs more work, interpolation methods, and then implementation of reflection. the facing ratio principle is based on Lambertian Reflectance. 
