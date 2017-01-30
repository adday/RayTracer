#ifndef SHADER_H
#define SHADER_H

#include <Camera.h>
#include <Model.h>
#include <Sphere.h>
#include <Light.h>
#include <Material.h>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Shader: stores and manipulates relevant information about rays

#define sph_phong 16
#define mdl_phong 16

class Shader{
   //constructor
   public:
	Shader(Camera & c, vector<Light> l, vector<Model> & mod, 
			vector<Material> & mat, vector<Sphere> & s){
				   cam = &c; 
				   lights = l;
				   models = mod;
				   materials = mat;
				   spheres = s;
				}

	//methods
	// void cast_rays(void);
	double intersect(Ray ray, VectorXd i_vals)const;
	Vector2d get_model_t(Ray ray, Model model)const; 
	VectorXd ray_model_test(Ray ray, Model model)const;
	Vector4d ray_model_rgb(Ray ray, Vector3d accum, Vector3d refatt, int level)const;
	Vector4d ray_sphere_test(Ray ray, Sphere sphere)const;
	Vector4d ray_sphere_rgb(Ray ray,  Vector3d accum, Vector3d refatt, int level)const;
	VectorXd find_hitp(Ray ray)const;
	vector<vector<Array3i>> shade();

	//overloaded operators
	Shader & operator=(const Shader& rhs);

   private:
	//object data
	vector<vector<double>> tvalues;
	Camera * cam;
	vector<Light> lights;
	vector<Model> models;
	vector<Sphere> spheres;
	vector<Material> materials;

};


#endif
