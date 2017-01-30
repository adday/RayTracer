#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <iterator> 
#include <sstream>

#include <Model.h>
#include <Camera.h>
#include <Light.h>
#include <Sphere.h>
#include <Material.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Parser: parses relevant information from camera file and .obj file to initialize objects

class Parser{
   //constructor
   public:
	Parser(){}

	//accessors
	inline Camera get_camera() const{return camera;}
	inline vector<Light> get_lights() const{return lights;}
	inline vector<Sphere> get_spheres() const{return spheres;}
	inline vector<Model> get_models() const{return models;}
	inline vector<Material> get_materials() const{return materials;}

	//mutators

	//methods
	string parse(string filename);
	string parse_model(string filename, Vector3d xyz_translation, Vector4d axis_angle_rotation);
    string parse_material(string filename);

   private:
	//object data
	Camera camera;
	vector<Light> lights;
	vector<Sphere> spheres;
	vector<Model> models;
	vector<Material> materials;

};


#endif
