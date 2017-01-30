#ifndef SPHERE_H
#define SPHERE_H

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Spherre: stores and manipulates relevant information for a sphere

class Sphere{
    //constructor
   public:
	Sphere(Vector3d c, double r, Vector3d RGB){coords=c;radius=r;rgb=RGB;}
	
	//accessors
	inline int get_radius() const{return radius;}
	inline Vector3d get_coords() const{return coords;}
	inline Vector3d get_rgb() const{return rgb;}

	//mutators
	
	//methods
	inline void print_sphere(void){
		cout<<"SPHERE"<<endl;
		cout<<"Coords: "<<coords<<endl;
		cout<<"RGB: "<<rgb<<endl;
		cout<<"radius: "<<radius<<endl;
	}
	
	//overloaded operators

   private:
	//object data
	double radius;
	Vector3d coords, rgb;


};

#endif