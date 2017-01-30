#ifndef MATERIAL_H
#define MATERIAL_H

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Material: stores and manipulates relevant information for a material

class Material{
   //constructor
   public:
	Material(string filename, Vector3d ka, Vector3d kd, Vector3d ks){name = filename;Ka=ka;Kd=kd;Ks=ks;}

	//accessors
	inline string get_name() const{return name;}
	inline Vector3d get_Ka() const{return Ka;}
	inline Vector3d get_Kd() const{return Kd;}
	inline Vector3d get_Ks() const{return Ks;}

	//mutators
	
	//methods
	inline void print_material(void){
		cout<<"MATERIAL"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Ka: "<<Ka<<endl;
		cout<<"Kd: "<<Kd<<endl;
		cout<<"Ks: "<<Ks<<endl;
	}
	
	//overloaded operators

   private:
	//object data
	string name;
	Vector3d Ka, Kd, Ks;

};


#endif
