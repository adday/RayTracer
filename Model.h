#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Model: stores relevant information from .obj file
class Model{
   public:
      //constructors
	Model(string filename, Vector3d xyz, Vector4d aa_rot){
		name = filename;
		xyz_translation = xyz;
		axis_angle_rotation = aa_rot;
	}
	
	//accessors
	inline string get_name() const{return name;}
	inline int get_num_vertices() const{return vertices.size();}
	inline int get_num_faces() const{return num_faces;}
	inline vector<Vector3d> get_vertices() const{return vertices;}
	inline vector<Vector3i> get_faces() const{return faces;}
	inline int get_face_mtl_idx(int i) const{return face_mtl_idxs[i];}
	inline vector<VectorXd> get_intersect_vals() const{return intersect_vals;}
	inline VectorXd get_intersect_vals(int i) const{return intersect_vals[i];}
	inline Vector3d get_face_normal(int i) const{return face_normals[i];}

	//mutators
	inline void set_vertices(vector<Vector3d> v){vertices = v;}
	inline void set_num_vertices(int n){num_vertices = n;}
	inline void set_faces(vector<Vector3i> f){faces = f;}
	inline void set_num_faces(int n){num_faces = n;}
	inline void set_face_mtl_idxs(vector<int> fm){face_mtl_idxs = fm;}

	//methods
	void compute_intersect_vals(Vector3d ray_pt);
	void compute_face_normals(void);
	inline void print_model(void){
	cout<<"MODEL"<<endl;
	cout<<"Name: "<<name<<endl;
	cout<<"Num vertices: "<<num_vertices<<endl;
	cout<<"Num faces: "<<num_faces<<endl;
}

	//overloaded operators
	Model & operator=(const Model& rhs);

   private:
	//object data
	string name;
	int num_vertices,num_faces;
	Vector3d xyz_translation;
	Vector4d axis_angle_rotation;
	vector<Vector3d> vertices;
	vector<Vector3i> faces;
	vector<int> face_mtl_idxs;
	vector<VectorXd> intersect_vals;
	vector<Vector3d> face_normals;
	
};


#endif
