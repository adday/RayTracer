#ifndef RAY_H
#define RAY_H

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Ray: stores and manipulates relevant information about rays

class Ray{
   //constructor
   public:
	Ray(Vector3d p, Vector3d d){point=p;direction=d;}

	//accessors
	inline Vector3d get_pt() const{return point;}
	inline Vector3d get_dir() const{return direction;}
	
	//overloaded operators
	Ray & operator=(const Ray& rhs);

   private:
	//object data
	Vector3d point;
	Vector3d direction;
		
	
};

#endif
