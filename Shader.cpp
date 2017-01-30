#include <Shader.h>




vector<vector<Array3i>> Shader::shade(){
	Vector4d sph_color, mdl_color;
	Vector3d color;
	vector<vector<Array3i>> pixels;
	for(int i=0;i<cam->get_resolution()[1];i++){
		vector<Array3i> row;
		for(int j=0;j<cam->get_resolution()[0];j++){
			Vector3d rgb_init, refatt_init;
			rgb_init << 0,0,0; refatt_init << 1,1,1;
			int recurse_lvl = 3;
			Ray ray = cam->pixel_ray(j,i);
			mdl_color = ray_model_rgb(ray, rgb_init, refatt_init, recurse_lvl);
			sph_color = ray_sphere_rgb(ray, rgb_init, refatt_init, recurse_lvl);
			if(sph_color[0] < mdl_color[0])
				color << sph_color[1],sph_color[2],sph_color[3];
			else
				color << mdl_color[1],mdl_color[2],mdl_color[3];
			Array3i pixel;
			pixel << max(0.0,min(255.0,round(255.0 * color[0]))),
					 max(0.0,min(255.0,round(255.0 * color[1]))), 
					 max(0.0,min(255.0,round(255.0 * color[2])));
			row.push_back(pixel);
		}
		pixels.push_back(row);
	}
	return pixels;
}


/* RAY SPHERE FUNCTIONS */

Vector4d Shader::ray_sphere_test(Ray ray, Sphere sphere)const{
	Vector4d ret_vec;
	Vector3d t_vec;
	t_vec << sphere.get_coords() - ray.get_pt();
	double v = t_vec.dot(ray.get_dir());
	double csq = t_vec.dot(t_vec);
	double disc = pow(sphere.get_radius(),2) - (csq - pow(v,2));
	if(disc < 0){
		ret_vec << INFINITY,INFINITY,INFINITY,INFINITY;
		return ret_vec;}
	else{
		double t = (v - pow(disc,0.5));
		Vector3d pt = ray.get_pt() + t * ray.get_dir();
		ret_vec << t, pt[0], pt[1], pt[2];
		return ret_vec;}
}

Vector4d Shader::ray_sphere_rgb(Ray ray, Vector3d accum, Vector3d refatt, int level)const{
	Vector3d color;
	color << 0,0,0;
	
	Vector4d best_hitp, hitp;
	best_hitp << INFINITY, INFINITY, INFINITY, INFINITY;
	unsigned best_sph_idx = 0;
	for(unsigned i=0;i<spheres.size();i++){
		hitp = ray_sphere_test(ray, spheres[i]);
		if(hitp[0] < best_hitp[0] && hitp[0] > 0){
			best_hitp = hitp;
			best_sph_idx = i;
		}
	}
	hitp = best_hitp;
	
	if(hitp[0] != INFINITY){
		Vector3d ptos, refl_const;
		refl_const << 0.3,0.3,0.3;
		ptos << hitp[1], hitp[2], hitp[3];
		Vector3d snrm = ptos - spheres[best_sph_idx].get_coords(); snrm.normalize();
		color = cam->get_ambient().cwiseProduct(spheres[best_sph_idx].get_rgb());
		for(unsigned i=0;i<lights.size();i++){
			Vector3d toL = lights[i].get_coords() - ptos; toL.normalize();
			if(snrm.dot(toL) > 0){
				color += spheres[best_sph_idx].get_rgb().cwiseProduct(lights[i].get_rgb()) * snrm.dot(toL);
				Vector3d toC = ray.get_pt() - ptos; toC.normalize();
				Vector3d spR = (2 * snrm.dot(toL) * snrm) - toL; spR.normalize();
				color += spheres[best_sph_idx].get_rgb().cwiseProduct(lights[i].get_rgb()) * pow(toC.dot(spR),sph_phong);
			}
		}
		accum += refatt.cwiseProduct(color);
        if (level > 0){
            Vector3d refR = (2 * snrm.dot(-ray.get_dir()) * snrm) + ray.get_dir(); 
            refR.normalize();
			Vector4d tmp_mdl, tmp_sph;
			const double ERR = 1e-12;
			tmp_mdl = ray_model_rgb(Ray(ptos+snrm*ERR, refR), accum, refl_const.cwiseProduct(refatt), (level - 1));
			tmp_sph = ray_sphere_rgb(Ray(ptos+snrm*ERR, refR), accum, refl_const.cwiseProduct(refatt), (level-1));
			if(tmp_mdl[0] < tmp_sph[0])
				accum << tmp_mdl[1],tmp_mdl[2],tmp_mdl[3];
			else
				accum << tmp_sph[1],tmp_sph[2],tmp_sph[3];
		}
	}
	//ret_vec = t value, color
	Vector4d ret_vec;
	ret_vec << hitp[0],accum[0], accum[1], accum[2];
	return ret_vec;
}



/* RAY MODEL FUNCTIONS */


VectorXd Shader::ray_model_test(Ray ray, Model model)const{
	model.compute_intersect_vals(ray.get_pt());
	Vector2d t = get_model_t(ray,model);
	Vector3d pt = ray.get_pt() + t[0] * ray.get_dir();
	// ret_vec = t_val, sphere idx, intersection pt
	VectorXd ret_vec(5);
	ret_vec << t[0],t[1], pt[0], pt[1], pt[2];
	return ret_vec;
}




double Shader::intersect(Ray ray, VectorXd i_vals)const{
	// inverse method: Mx=y
	Matrix3d M;
	M << i_vals[0], i_vals[1], ray.get_dir()[0],
		 i_vals[2], i_vals[3], ray.get_dir()[1],
		 i_vals[4], i_vals[5], ray.get_dir()[2];
	Vector3d y;
	y << i_vals[6],i_vals[7],i_vals[8];
	Vector3d x = M.inverse() * y;
	if(x[0]<0 || x[1]<0 || x[2]<0 || (x[0]+x[1])>1)
		return INFINITY;
	return x[2];
}




Vector2d Shader::get_model_t(Ray ray, Model model)const{
	vector<double> tvals;
	int num_faces = model.get_num_faces();
	tvals.reserve(num_faces);
	for(int i=0;i<num_faces;i++){
		VectorXd intersect_vals = model.get_intersect_vals(i);
		tvals.push_back(intersect(ray,intersect_vals));
	}
	// ret_vec = min_t, associated face index
	Vector2d ret_vec;
	double min_t = *min_element(tvals.begin(),tvals.end());
	double face_idx = min_element(tvals.begin(),tvals.end()) - tvals.begin();;
	ret_vec << min_t, face_idx;
	return ret_vec;
}




Vector4d Shader::ray_model_rgb(Ray ray, Vector3d accum, Vector3d refatt, int level)const{

	Vector3d color;
	color << 0,0,0;
	
 	VectorXd best_hitp(5), hitp(5);
	best_hitp << INFINITY, INFINITY, INFINITY, INFINITY, INFINITY;
	unsigned best_mdl_idx = 0;
	for(unsigned i=0;i<models.size();i++){
		hitp = ray_model_test(ray, models[i]);
		if(hitp[0] < best_hitp[0]){
			best_hitp = hitp;
			best_mdl_idx = i;
		}
	}
	hitp = best_hitp;
	 
	if(hitp[0] != INFINITY){
		Vector3d ptom, refl_const;
		refl_const << 0.10,0.10,0.10;
		ptom << hitp[2], hitp[3], hitp[4];
		Vector3d snrm = models[best_mdl_idx].get_face_normal(hitp[1]);
		Vector3d toC = ray.get_pt() - ptom;	toC.normalize();
		if(snrm.dot(toC)<0) snrm = -snrm; 
		Vector3d Ka = materials[models[best_mdl_idx].get_face_mtl_idx(hitp[1])].get_Ka();
		color = cam->get_ambient().cwiseProduct(Ka);
		for(unsigned i=0;i<lights.size();i++){
			Vector3d toL = lights[i].get_coords() - ptom; toL.normalize();
			double l_dot_n = snrm.dot(toL); 
			if(l_dot_n < 0) l_dot_n = 0;
			Vector3d Kd = materials[models[best_mdl_idx].get_face_mtl_idx(hitp[1])].get_Kd();
			color += Kd.cwiseProduct(lights[i].get_rgb()) * l_dot_n;
			Vector3d spR = (2 * l_dot_n * snrm) - toL; spR.normalize();
			Vector3d Ks = materials[models[best_mdl_idx].get_face_mtl_idx(hitp[1])].get_Ks();
			double c_dot_r = toC.dot(spR); 
			if(c_dot_r < 0) c_dot_r = 0;
			color += Ks.cwiseProduct(lights[i].get_rgb()) * pow(c_dot_r,mdl_phong);
		}
		accum += refatt.cwiseProduct(color);
		if (level > 0){
            Vector3d refR = (2 * snrm.dot(-ray.get_dir()) * snrm) + ray.get_dir(); 
            refR.normalize();
			Vector4d tmp_mdl, tmp_sph;
			const double ERR = 1e-12;
			tmp_mdl = ray_model_rgb(Ray(ptom+snrm*ERR, refR), accum, refl_const.cwiseProduct(refatt), (level - 1));
			tmp_sph = ray_sphere_rgb(Ray(ptom+snrm*ERR, refR), accum, refl_const.cwiseProduct(refatt), (level-1));
			if(tmp_mdl[0] < tmp_sph[0])
				accum << tmp_mdl[1],tmp_mdl[2],tmp_mdl[3];
			else
				accum << tmp_sph[1],tmp_sph[2],tmp_sph[3];
		}	
	}
	//ret_vec = t value, color
	Vector4d ret_vec;
	ret_vec << hitp[0],accum[0], accum[1], accum[2];
	return ret_vec;
}

