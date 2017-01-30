#include <Image.h>

Image& Image::operator=(const Image& rhs){
  height = rhs.get_height();
  width = rhs.get_width();
  pixels = rhs.get_pixels();
  return *this;
}

//writes image to a ppm file
string Image::output(string outfile){
	ofstream ostr(outfile.c_str());
	if(ostr.fail()){//ensure the file is valid to write 
    		return "Failure to open file for output";
	}
	ostr<<"P3\n"<<width<<" "<<height<<" 255"<<endl;
	for(int i=height-1;i>=0;i--){
		for(int j=0;j<width;j++){
			ostr<<pixels.at(i).at(j)[0]<<" "<<pixels.at(i).at(j)[1]<<" "<<pixels.at(i).at(j)[2]<<" ";
		}
		ostr<<endl;
	}
	ostr<<endl;
  	return "success";
}//end output
