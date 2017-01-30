#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;  

class Image{
   public:
	Image(vector<vector<Array3i>> p, Array2i resolution){pixels = p;width = resolution[0];height = resolution[1];}

	//accessors
	inline int get_width() const{return width;}
	inline int get_height() const{return height;}
	inline vector<vector<Array3i>> get_pixels() const{return pixels;}

	//mutators
	inline void set_width(double w){width = w;}
	inline void set_height(double h){height = h;}
	inline void set_pixels(vector<vector<Array3i>> p){pixels = p;}

	//methods
	string output(string outfile);
	
	//overloaded operators
	Image & operator=(const Image& rhs);

   private:
    int width,height;
	vector<vector<Array3i>> pixels;
};

#endif
