#include <Parser.h>

/****************************************************************************************************************
 * Parser.cpp contains functions to parse files for graphics objects according to the specification
 * given in assignment 4 for CS410-Computer Graphics, FA2016 at Colorado State University
 * 
 *
 * http://www.cs.colostate.edu/~cs410/yr2016fa/more_assignments/assignment03.php
 ***************************************************************************************************************/

// member functions for Parser object as defined in Parser.h
 
// Parse files and store relevant data
string Parser::parse(string filename)
{
	//test file opening
	ifstream istr(filename.c_str());
	if (istr.fail()) 
		return "Failed to open file for read in main parse";
	string line;

	while (istr.eof() == false){	
		getline(istr, line);
		istringstream iss(line);	
		vector<string> words{istream_iterator<string>{iss},
							istream_iterator<string>{}};
		if(words.empty()) continue;	
		
		if(words.at(0) == "eye"){
			camera.set_eye_pt(stod(words.at(1)),stod(words.at(2)),stod(words.at(3)));
		}
		if(words.at(0) == "look"){
			camera.set_look_at_pt(stod(words.at(1)),stod(words.at(2)),stod(words.at(3)));
			}
		if(words.at(0) == "up"){
			camera.set_up_vec(stod(words.at(1)),stod(words.at(2)),stod(words.at(3)));
			camera.camera_to_world();
		}
		if(words.at(0) == "d"){
			camera.set_dist(stod(words.at(1)));
		}
		if(words.at(0) == "bounds"){
			camera.set_bounds(stod(words.at(1)),stod(words.at(2)),stod(words.at(3)),stod(words.at(4)));
		}
		if(words.at(0) == "res"){
			camera.set_resolution(stoi(words.at(1)),stoi(words.at(2)));
		}
		if(words.at(0) == "ambient"){
			Vector3d ambient;
			ambient << stod(words.at(1)), stod(words.at(2)), stod(words.at(3));
			camera.set_ambient(ambient);
		}
		if(words.at(0) == "light"){
			Vector3d coords;
			coords << stod(words.at(1)),stod(words.at(2)),stod(words.at(3));
			int w = stoi(words.at(4));
			Vector3d rgb;
			rgb << stod(words.at(5)),stod(words.at(6)),stod(words.at(7));
			Light light(coords,w,rgb);
			lights.push_back(light);
		}
		if(words.at(0) == "sphere"){
			Vector3d coords;
			coords << stod(words.at(1)),stod(words.at(2)),stod(words.at(3));
			double radius = stod(words.at(4));
			Vector3d rgb;
			rgb << stod(words.at(5)),stod(words.at(6)),stod(words.at(7));
			Sphere sphere(coords,radius,rgb);
			spheres.push_back(sphere);
		}
		if(words.at(0) == "model"){	
			Vector3d xyz_translation;
			xyz_translation << stod(words.at(1)),stod(words.at(2)),stod(words.at(3));
			Vector4d axis_angle_rotation;
			axis_angle_rotation << stod(words.at(4)),stod(words.at(5)),stod(words.at(6)),stod(words.at(7));
			string buf = parse_model(words.at(8),xyz_translation,axis_angle_rotation);
			if(buf != "success") return buf;
		}
	}
	return "success";
}//end initialize




// Parse .obj file and store relevant data in Model class

string Parser::parse_model(string filename, Vector3d xyz_translation, Vector4d axis_angle_rotation){
	//test file opening
	ifstream istr(filename.c_str());
	if (istr.fail()) 
		return "Failed to open file for read while parsing model";
	
	//temporary storage to set in initialized object
	vector<Vector3d> vertices;
	vector<Vector3i> faces;
	vector<int> face_mtl_idxs;
	int current_mtl_idx = -1;
	string current_mtl;
	int num_vertices = 0;
	int num_faces = 0;
	
	string line;
	while (istr.eof() == false){
		getline(istr, line);
		istringstream iss(line);	
		vector<string> words{istream_iterator<string>{iss},
							istream_iterator<string>{}};
		if(words.empty()) continue;	
		if(words.at(0) == "mtllib"){
			string buf = parse_material(words.at(1));
			if(buf != "success") return buf;
		}
		if(words.at(0) == "usemtl"){
			current_mtl = words.at(1);
		}
		if(words.at(0) == "v"){
			num_vertices++;
			Vector3d vertice;
			vertice << stod(words.at(1)),stod(words.at(2)),stod(words.at(3));
			vertices.push_back(vertice);
		}
		if(words.at(0) == "f"){
			num_faces++;
			Vector3i face;
			face << stoi(words.at(1))-1, stoi(words.at(2))-1, stod(words.at(3))-1;
			faces.push_back(face);
			for(unsigned i=0;i<materials.size();i++)
				if(materials[i].get_name() == current_mtl){
					current_mtl_idx = i;
					break;
					}
			face_mtl_idxs.push_back(current_mtl_idx);
		}
	}

	Model model(filename, xyz_translation, axis_angle_rotation);
	model.set_vertices(vertices);
	model.set_num_vertices(num_vertices);
	model.set_faces(faces);
	model.set_num_faces(num_faces);
	model.set_face_mtl_idxs(face_mtl_idxs);
	model.compute_face_normals();
	models.push_back(model);

	return "success";
}


string Parser::parse_material(string filename)
{
	//test file opening
	ifstream istr(filename.c_str());
	if (istr.fail()) 
		return "Failed to open file for read while parsing material";
	
	string line;
	while (istr.eof() == false){
		getline(istr, line);
		istringstream iss(line);	
		vector<string> words{istream_iterator<string>{iss},
							istream_iterator<string>{}};
		if(words.empty()) continue;
		if(words.at(0) == "newmtl"){
			string mtl_name = words.at(1);
			getline(istr, line);
			istringstream issa(line);	
			vector<string> wordsa{istream_iterator<string>{issa},
							istream_iterator<string>{}};
			Vector3d Ka, Kd, Ks;
			Ka << stod(wordsa.at(1)), stod(wordsa.at(2)), stod(wordsa.at(3));
			getline(istr, line);
			istringstream issb(line);	
			vector<string> wordsb{istream_iterator<string>{issb},
							istream_iterator<string>{}};
			Kd << stod(wordsb.at(1)), stod(wordsb.at(2)), stod(wordsb.at(3));
			getline(istr, line);
			istringstream issc(line);	
			vector<string> wordsc{istream_iterator<string>{issc},
							istream_iterator<string>{}};
			Ks << stod(wordsc.at(1)), stod(wordsc.at(2)), stod(wordsc.at(3));
			
			Material material(mtl_name, Ka, Kd, Ks);
			materials.push_back(material);
		}
	}

	return "success";
}