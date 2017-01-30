#include <Model.h>
#include <iostream>
#include <iterator> 
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

/****************************************************************************************************************
 * Model.cpp contains functions to manipulate object models given as .ply files according to the specification
 * given in assignment 4 for CS410-Computer Graphics, FA2016 at Colorado State University
 * 
 *
 * http://www.cs.colostate.edu/~cs410/yr2016fa/more_assignments/assignment01.php
 ***************************************************************************************************************/


Model& Model::operator=(const Model& rhs){
  name = rhs.get_name(); 
  num_vertices = rhs.get_num_vertices(); 
  num_faces = rhs.get_num_faces(); 
  vertices = rhs.get_vertices(); 
  faces = rhs.get_faces(); 
  intersect_vals = rhs.get_intersect_vals();
  return *this;
}

void Model::compute_intersect_vals(Vector3d ray_pt){
	Vector3i face;
	Vector3d a,b,c; // vertices of triangle
	VectorXd i_val(9);
	intersect_vals.reserve(num_faces);
	for(int i=0;i<num_faces;i++){
		face = faces[i];
		a = vertices[face[0]];
		b = vertices[face[1]];
		c = vertices[face[2]];
		i_val << (a[0]-b[0]), (a[0]-c[0]),
				 (a[1]-b[1]), (a[1]-c[1]),
				 (a[2]-b[2]), (a[2]-c[2]),
				 (a[0]-ray_pt[0]),(a[1]-ray_pt[1]),(a[2]-ray_pt[2]);
		intersect_vals.push_back(i_val);
	}
}

void Model::compute_face_normals(void){
	Vector3i face;
	Vector3d a,b,c,v,w,normal; // vertices of triangle
	
	face_normals.reserve(num_faces);
	for(int i=0;i<num_faces;i++){
		face = faces[i];
		a = vertices[face[0]];
		b = vertices[face[1]];
		c = vertices[face[2]];
		v = b - a;
		w = c - a;
		normal << (v[1]*w[2]-v[2]*w[1]),(v[2]*w[0]-v[0]*w[2]),(v[0]*w[1]-v[1]*w[0]);
		normal.normalize();
		face_normals.push_back(normal);
	}
}
