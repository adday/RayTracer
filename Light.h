#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Light: stores and manipulates relevant information for a light

class Light{
    //constructor
   public:
	Light(Vector3d c, int W, Vector3d RGB){coords=c;w=W;rgb=RGB;}

	//accessors
	inline int get_w() const{return w;}
	inline Vector3d get_coords() const{return coords;}
	inline Vector3d get_rgb() const{return rgb;}

	//mutators

	//methods
	inline void print_light(void){
		cout<<"LIGHT"<<endl;
		cout<<"Coords: "<<coords<<endl;
		cout<<"RGB: "<<rgb<<endl;
	}
	
	//overloaded operators

   private:
	//object data
	int w;
	Vector3d coords, rgb;


};


#endif
