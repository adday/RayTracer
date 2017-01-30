/*-----------------------------------------------------------------------------------------------------
	CS 410P5 -  Reflecting
	Author: Alexander Day 830 523 317
-------------------------------------------------------------------------------------------------------*/
#include <Model.h>
#include <Camera.h>
#include <Ray.h>
#include <Shader.h>
#include <Image.h>
#include <Parser.h>
#include <string.h>

#include <Eigen/Dense>

int Usage(string message){    
	cerr << "Error: " <<message<< endl;       
	return -1;//error
}  
    
/*====================main====================*/
int main(int argc, char* argv[]){   

	//apply appropriate behavior for number of arguments
	string infile, outfile;
	if (argc == 1){
		infile = "masterwork.txt";
		outfile = "masterwork.ppm";}
	else if (argc == 3){
		infile = argv[1];
		outfile = argv[2];}
	else{
		return Usage("Wrong number of arguments");}
		
	Parser parser;
	parser.parse(infile);

	Camera camera = parser.get_camera();
	vector<Model> models = parser.get_models();
	vector<Light> lights = parser.get_lights();
	vector<Sphere> spheres = parser.get_spheres();
	vector<Material> materials = parser.get_materials();
	
	if(infile == "masterwork.txt"){	 
		// concentric circles
		for(int i=0;i<30;i++){
			for(int j=0;j<5;j++){
				Vector3d center, rgb;
				if(i%2==0)
					center << 70*cos(j*M_PI/4), 70*sin(j*M_PI/4), -75*i+100;
				else
					center << 70*cos(j*M_PI/4), 70*sin(j*M_PI/4), -75*i+100;
				double radius = 20-(i/2);
				if(i%2==0 && j%2==0)
					rgb << 0.53,0.16,0.05;
				else if(i%2==0 && j%2!=0)
					rgb << 0.91,0.98,0.18;
				else if(i%2==1 && j%2==0)
					rgb << 0.91,0.98,0.18;
				else //(i%2==1 && j%2!=0)
					rgb << 0.53,0.16,0.05;


				Sphere sph(center,radius,rgb);
				spheres.push_back(sph);
			}
		} 
	}
	/* 
	// print statements - toggle for debugging
	
	camera.print_camera();
	for(unsigned i=0;i<models.size();i++){models[i].print_model();}
	for(unsigned i=0;i<lights.size();i++){lights[i].print_light();}
	for(unsigned i=0;i<spheres.size();i++){spheres[i].print_sphere();}
	for(unsigned i=0;i<materials.size();i++){materials[i].print_material();} 
		 */

	// cast rays
	Shader shader(camera,lights,models,materials,spheres);
	vector<vector<Array3i>> pixels = shader.shade();

	// write output image
	Image image(pixels,camera.get_resolution());
	string buf = image.output(outfile);
	if(buf != "success")
		return Usage(buf);
	
	return 0;//success
}