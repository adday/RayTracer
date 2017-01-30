#include <Camera.h>

/****************************************************************************************************************
 * Camera.cpp contains functions to manipulate camera models according to the specification
 * given in assignment 4 for CS410-Computer Graphics, FA2016 at Colorado State University
 * 
 *
 * http://www.cs.colostate.edu/~cs410/yr2016fa/more_assignments/assignment03.php
 ***************************************************************************************************************/

// member functions for Camera object as defined in Camera.h




Ray Camera::pixel_ray(int i, int j){
	double px = i * (bounds[2]-bounds[0])/(resolution[0]-1) + bounds[0];
	double py = j * (bounds[3]-bounds[1])/(resolution[1]-1) + bounds[1];
	
	Vector3d point = eye_pt + (-dist * W_vec) + (px * U_vec) + (py * V_vec);
	Vector3d direction = point - eye_pt; direction.normalize();
    return Ray(point,direction);
}

// convert camera to world coordinates
void Camera::camera_to_world(void){
	W_vec = eye_pt - look_at_pt;
	W_vec.normalize();
	U_vec = up_vec.cross(W_vec);
	U_vec.normalize();
	V_vec = W_vec.cross(U_vec);
}

Camera& Camera::operator=(const Camera& rhs){
  eye_pt = rhs.get_eye_pt();
  look_at_pt = rhs.get_look_at_pt();
  up_vec = rhs.get_up_vec();
  dist = rhs.get_dist();
  bounds = rhs.get_bounds();
  resolution = rhs.get_resolution();
  W_vec = rhs.get_W_vec();
  U_vec = rhs.get_U_vec();
  V_vec = rhs.get_V_vec();
  return *this;
}

// Print camera data
void Camera::print_camera(void)
{
	cout<<"CAMERA"<<endl;
	cout<<"Eye: "<<eye_pt<<endl;
	cout<<"Look At: "<<look_at_pt<<endl;
	cout<<"Up: "<<up_vec<<endl;
	cout<<"Dist: "<<dist<<endl;
	cout<<"Bounds: "<<bounds<<endl;
	cout<<"Resolution: "<<resolution<<endl;
	cout<<"W_vec: "<<W_vec<<endl;
	cout<<"U_vec: "<<U_vec<<endl;
	cout<<"V_vec: "<<V_vec<<endl;
	cout<<"Ambient: "<<ambient<<endl;


}//end input
