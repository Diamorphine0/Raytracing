11/12/23
At this stage, computation of facing ratio at each hitpoint (for shading/Lambertian reflectance later) in Reflection Branch and computation of reflected ray.
Next step, recursively evaluate reflected rays up to reflection depth to determine pixel color.
After: Determine reflection parameters for materials, refraction, and optimize code (adapt to mesh structure.)


14/12/23
My previous Reflection Branch was quasi-useless after the engine-Raytracer merge, so hit reimplemented it, and at this stage have pretty naive shading algorithm implemented. Needs more work, interpolation methods, and then implementation of reflection. the facing ratio principle is based on Lambertian Reflectance. 

29/12/23
Diffuse Reflection, Metallic (mirrorlike reflection), color attenuation, material classes, transparent/translucent materials and basis for refraction in closed objects. 
Tudor helped fix a big issue I had with floating point rounding errors (a reflected ray kept hitting the reflecting surface because of rounding error on the intersection point. issue analogous to surface acne but much worse)

29/1/24
Wrote classes and edited ray_color in Camera.cpp to have lights accounted for when backtracing rays. Diffuse Lights and Collimated lights with the degree of collimation. Unfortunately, when merging, textures were the priority, and material classes as well as lights had to be removed. May not have time to reimplement them alongside textures.
