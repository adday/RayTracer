#RayTracer
Recursive ray tracer implemented in C++.
Uses custom file format for input file, this format includes the names of any .OBJ files to be used in rendering a scene.

Commands following $ to be executed in Linux shell 

To compile program: $ make

To run executable: $ ./raytracer <cam.txt> <img.ppm> 
	where: 	<cam.txt> is a valid camera file as specified here://www.cs.colostate.edu/~cs410/yr2016fa/home_assignments.php.
			<img.ppm> is the name of the image to output
	OR to generate the default image use $ ./raytracer

To clean directory of compiled files: $ make clean
