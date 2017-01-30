#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <Ray.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Camera: stores and manipulates relevant information from camera file

class Camera{
   //constructor
   public:
	Camera(){}

	//accessors
	inline Vector3d get_eye_pt() const{return eye_pt;}
	inline Vector3d get_look_at_pt() const{return look_at_pt;}
	inline Vector3d get_up_vec() const{return up_vec;}
	inline double get_dist() const{return dist;}
	inline Array4d get_bounds() const{return bounds;}
	inline Array2i get_resolution() const{return resolution;}
	inline Vector3d get_W_vec() const{return W_vec;}
	inline Vector3d get_U_vec() const{return U_vec;}
	inline Vector3d get_V_vec() const{return V_vec;}
	inline Vector3d get_ambient() const{return ambient;}


	//mutators
	inline void set_eye_pt(double e1, double e2, double e3){eye_pt<<e1,e2,e3;}
	inline void set_look_at_pt(double l1, double l2, double l3){look_at_pt<<l1,l2,l3;}
	inline void set_up_vec(double u1, double u2, double u3){up_vec<<u1,u2,u3;}
	inline void set_dist(double d){dist = d;}
	inline void set_bounds(double l, double b, double r, double t){bounds<<l,b,r,t;}
	inline void set_resolution(int horiz, int vert){resolution<<horiz,vert;}
	inline void set_ambient(Vector3d a){ambient = a;}

	

	//methods
    string initialize(void);
	void camera_to_world(void);
	void print_camera(void);
	Ray pixel_ray(int i, int j);

	//overloaded operators
	Camera & operator=(const Camera& rhs);

   private:
	//object data
	string name;
	Vector3d eye_pt, look_at_pt, up_vec;
	double dist;
	Array4d bounds;
	Array2i resolution;
	Vector3d W_vec, U_vec, V_vec;
	Vector3d ambient;

};


#endif
