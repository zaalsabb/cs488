#include <glm/ext.hpp>

#include "A5.hpp"
#include "GeometryNode.hpp"
#include "JointNode.hpp"
#include "PhongMaterial.hpp"
#include <math.h>
#include <iomanip>      // std::setprecision
#include "progressbar.hpp"
using namespace glm;

// parameters user can set
float N_SOLID = 6.0;
int MAX_RECURSION_DEPTH = 0;
bool SHADOWS_ON = true;
bool 	REFLECTIONS_ON = false;

//constants
float PI = 3.1415;

void A5_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const vec3 & eye,
		const vec3 & view,
		const vec3 & up,
		double fovy,

		// Lighting parameters
		const vec3 & ambient,
		const std::list<Light *> & lights,

		// Depth of Field Parameters
		float aperture,
		float focalLength,
		float screenPosition,

		// super sampling parameter
		int superSamplingScale
) {

	// recursively build hierarchical graph transformations
	root->BuildHierarchyGraph();
	// root->ApplyTransform();
	root->ApplyScales();

	LoadTextures(root);
	LoadBumps(root);

  vec3 wi = normalize(eye - view);
  vec3 ui = normalize(cross(up,wi));
  vec3 vi = cross(wi,ui);
  vec3 ei = eye;

  float film_z = 1.0f;
  float film_w  = 2*film_z*tan(fovy/2*PI/180);
  float film_h  = film_w;

  std::cout << "Calling A5_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << to_string(eye) << std::endl <<
		  "\t" << "view: " << to_string(view) << std::endl <<
		  "\t" << "up:   " << to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	size_t h = image.height()*superSamplingScale;
	size_t w = image.width()*superSamplingScale;

	Image depthBuffer = Image(w,h);
	Image image_original = Image(w,h);

	vec3 pixel_cam;
	vec3 pixel_world;
	vec3 dir;

	std::cout << "std::precision(10):    " << std::setprecision(10) << 1.2345678901234567890f << '\n';

	progressbar bar(h*w*2);
	float maxDepth=0;

	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {

			pixel_cam[0] = film_w*(w/2-(x+0.5f))/w;
			pixel_cam[1] = film_h*(y+0.5f-h/2)/h;
			pixel_cam[2] = film_z;

			pixel_world = pixel_cam[0]*ui + pixel_cam[1]*vi + pixel_cam[2]*wi + ei;

			dir = normalize(ei-pixel_world);
			vec4 L = shade(root, ei, dir, ambient, lights, 0);

			// Red:
			image_original(x, y, 0) = (double)L[0];
			// Green:
			image_original(x, y, 1) = (double)L[1];
			// Blue:
			image_original(x, y, 2) = (double)L[2];

			//Depth Buffer:
			depthBuffer(x,y,0) = (double)L[3];
			depthBuffer(x,y,1) = (double)L[3];
			depthBuffer(x,y,2) = (double)L[3];

			if (L[3] > maxDepth){
				maxDepth = L[3];
			}

			bar.update();

		}
	}
	Image image_original2 = Image(w,h);

	// float A = 3.0f;
	// float f = 15.0f;
	// float screenPosition = 15.0f;
	// depthBuffer = depthBuffer*(1/screenPos);

	// apply post-processing to image
	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {
				float d = depthBuffer(x,y,0)/screenPosition;
			if (d>0){
				float CoC = std::abs(aperture*(screenPosition*(1/focalLength-1/d)-1));
				// std::cout << CoC << std::endl;

				UniformDistribution(CoC,x,y, image_original, image_original2);
			}
			bar.update();
			// image(x,y,0) = depthBuffer(x,y,0)/maxDepth;
			// image(x,y,1) = depthBuffer(x,y,0)/maxDepth;
			// image(x,y,2) = depthBuffer(x,y,0)/maxDepth;
		}
	}
	superSampling(image_original2,image,superSamplingScale);

	std::cout <<" -> Rendering Finished!"<< '\n';
}

vec4 shade(SceneNode * root,
								const vec3 origin,
								const vec3 dir,
								const vec3 ambient,
								const std::list<Light *> & lights,
								const int recursionDepth)
{
	Hit hit;
	vec3 L;
	rayIntersection(root, origin, dir, hit);
	float d = -(hit.pos.z-origin.z);

	if (hit.t>0){

		L = hit.mat.m_kd * ambient;
		float p = hit.mat.m_shininess;

		for (Light * light : lights){
			// vec3 l = light->position - hit.pos;
			// float r = length(l);
			// vec3 I = light->colour/(light->falloff[0]+light->falloff[1]*r+light->falloff[2]*r*r);
			// l = l/r;

			// Hit shadow;
			// rayIntersection(root, hit.pos, l, shadow);
			// if (shadow.t==0 | !SHADOWS_ON){
			// 	// std::cout << dot(l,hit.normal) << std::endl;
			// 	//diffuse lighting
			// 	L = L + I*hit.mat.m_kd*std::max(0.0f,dot(l,hit.normal));

			// 	//specular Lighting
			// 	vec3 h = normalize(l-dir);
			// 	L = L + I*hit.mat.m_ks*pow(std::max(0.0f,dot(h,hit.normal)),p);
			// 	//std::cout << to_string(n) << std::endl;
			// } else {
			// 	// std::cout << "shadow" << std::endl;
			// }
			SoftShadows(root, dir, p, hit, light, L);
		}
		if (recursionDepth < MAX_RECURSION_DEPTH & REFLECTIONS_ON){
			vec3 R = hit.Reflection(dir);
			float n1;
			float n2;

			if (dot(dir,hit.normal) < 0){
				n1 = 1.0f;
				n2 = N_SOLID;
			} else {
				n1 = N_SOLID;
				n2 = 1.0f;
			}

			vec3 T;
			float F = Fresnel(n1,n2,dir,T,hit.normal);

			//std::cout << F << std::endl;
			vec3 refl = hit.mat.m_ks*F*vec3(shade(root, hit.pos, R, ambient, lights, recursionDepth+1));
			vec3 refr = hit.mat.m_ks/2*(1.0f-F)*vec3(shade(root, hit.pos, T, ambient, lights, recursionDepth+1));
			L = L +refl+refr;
		}
	} else {
		L = vec3(0.0f,0.0f,0.0f);
	}
	vec4 Ld = vec4(L,d);
	return Ld;
}

void rayIntersection(SceneNode * root, vec3 origin, vec3 dir,Hit &hit){
	Hit hit_temp;
	float t;
	float tol = 0.01f;

	const GeometryNode * geometryNode;

	for (SceneNode * node : root->children) {
		if (node->m_nodeType == NodeType::GeometryNode){
			geometryNode = static_cast<const GeometryNode *>(node);
			t = geometryNode->m_primitive->intersect(origin,dir,hit_temp,node->trans,node->invtrans);
			if (t > 2*tol){
				if (hit.t == 0.0f | t < hit.t ) {
					hit.t = t;
					hit.copy(hit_temp);
					PhongMaterial * mat = static_cast<PhongMaterial*>(geometryNode->m_material);
					hit.mat.m_ks = mat->m_ks;
					hit.mat.m_shininess = mat->m_shininess;
					if (geometryNode->m_texture != nullptr){
						float H = (float)geometryNode->m_texture->image->height();
						float W = (float)geometryNode->m_texture->image->width();
						uint U = hit.U*W;
						uint V = H-hit.V*H;
						// std::cout << hit.U << std::endl;
						hit.mat.m_kd = geometryNode->m_texture->getColor(U,V);
						hit.mat.m_ks=vec3(0,0,0);

					} else {
						hit.mat.m_kd = mat->m_kd;
					}

					if (geometryNode->m_bump != nullptr){
						float H = (float)geometryNode->m_bump->image->height();
						float W = (float)geometryNode->m_bump->image->width();
						uint U = hit.U*W;
						uint V = H-hit.V*H;
						// std::cout << hit.U << std::endl;
						geometryNode->m_bump->perturbNormal(U, V, hit);
					}
				}
			}
		}
		rayIntersection(node,origin,dir,hit_temp);
		if (hit.t==0 | (hit_temp.t>0 & hit_temp.t < hit.t)){
			// hit = hit_temp;
			hit.copy(hit_temp);
		}
	}
}

float Fresnel(float n1,float n2,vec3 V,vec3 &T, vec3 N){

	float r = n1/n2;
	float cos_i = std::max(abs(dot(V,N)),1.0f); //entering ray V
	float TIL = 1-r*r*(1-cos_i*cos_i);
	if (TIL>=0){
		T = normalize(r*V + (r*cos_i - sqrt(TIL))*N);

		float cos_o = std::max(abs(dot(T,N)),1.0f); //exiting ray T

		float ps = (n1*cos_i-n2*cos_o)/(n1*cos_i+n2*cos_o);
		float pt = (n1*cos_o-n2*cos_i)/(n1*cos_o+n2*cos_i);

		return 0.5f*(ps*ps + pt*pt);
	} else {
		return 1.0f;
	}
}

void LoadTextures(SceneNode * root){
	const GeometryNode * geometryNode;
	for (SceneNode * node : root->children) {
		if (node->m_nodeType == NodeType::GeometryNode){
			geometryNode = static_cast<const GeometryNode *>(node);
			if (geometryNode->m_texture != nullptr){
				geometryNode->m_texture->loadTexture();
			}
			LoadTextures(node);
		}
	}
}

void LoadBumps(SceneNode * root){
	const GeometryNode * geometryNode;
	for (SceneNode * node : root->children) {
		if (node->m_nodeType == NodeType::GeometryNode){
			geometryNode = static_cast<const GeometryNode *>(node);
			if (geometryNode->m_bump != nullptr){
				geometryNode->m_bump->loadBump();
			}
			LoadBumps(node);
		}
	}
}

void UniformDistribution(float c,int x,int y, Image &image1, Image &image2){
	float r = c/2;
	float a;
	if (r<1){
		r=1;
		a=1;
	} else {
		a = PI*r*r;
	}

	vec3 i = vec3(image1(x,y,0),image1(x,y,1),image1(x,y,2))/a;
	// for (uint yi = y-(int)r; yi < y+(int)r; ++y) {
	// 	for (uint xi = x-(int)r; xi < x+(int)r; ++x) {
	for (int xi=x-(int)r;xi<=x+(int)r;++xi){
		for (int yi=y-(int)r;yi<=y+(int)r;++yi){
			if (xi>0 & xi<image1.width() & yi>0 & yi<image2.height()){
				if (std::sqrt((xi-x)*(xi-x)+(yi-y)*(yi-y))<r)
				{
					image2(xi,yi,0) += i[0];
					image2(xi,yi,1) += i[1];
					image2(xi,yi,2) += i[2];
				}
			}
		}
	}
}

void superSampling(Image &image1, Image &image2, int scale){

	for (uint y = 0; y < image2.height(); ++y) {
		for (uint x = 0; x < image2.width(); ++x) {
			for (int s1 = 0; s1<scale; s1++){
				for (int s2 = 0; s2<scale; s2++){
					int x2 = x*scale+s1;
					int y2 = y*scale+s2;
					if (x2>=image1.width()){
						x2 = image1.width()-1;
					}
					if (y2>=image1.height()){
						y2 = image1.height()-1;
					}
					image2(x,y,0) += image1(x2,y2,0)/(scale*scale);
					image2(x,y,1) += image1(x2,y2,1)/(scale*scale);
					image2(x,y,2) += image1(x2,y2,2)/(scale*scale);
				}
			}
		}
	}
}

void SoftShadows(SceneNode * root, vec3 dir, float p, Hit hit, Light* light, vec3 &L){

	Hit shadow[light->samples];
	// vec3 L_total = vec3(0,0,0);
	vec3 L_list[light->samples];

	for (int i=0; i<light->samples; i++){
		vec3 l_rand = vec3((float)rand()/RAND_MAX-0.5f,(float)rand()/RAND_MAX-0.5f,(float)rand()/RAND_MAX-0.5f);
		l_rand = normalize(l_rand);
		vec3 l_sample = light->position+light->radius*l_rand;
		vec3 l = l_sample - hit.pos;
		float r = length(l);
		vec3 I = light->colour/(light->falloff[0]+light->falloff[1]*r+light->falloff[2]*r*r);
		l = l/r;	
		L_list[i] = vec3(0,0,0);	
		rayIntersection(root, hit.pos, l, shadow[i]);
		if (shadow[i].t==0 | !SHADOWS_ON){
			
			//diffuse lighting
			L_list[i] = L_list[i] + I*hit.mat.m_kd*std::max(0.0f,dot(l,hit.normal));

			//specular Lighting
			vec3 h = normalize(l-dir);
			L_list[i] = L_list[i] + I*hit.mat.m_ks*pow(std::max(0.0f,dot(h,hit.normal)),p);
			// L_total += L_list[i];
		} else {}
	}

	// std::cout << to_string(L_total) << std::endl;
	// std::cout << to_string(L_list[0]) << "\n" << std::endl;

	for (int i=0; i<light->samples; i++){
		if (shadow[i].t==0 | !SHADOWS_ON){
			L += L_list[i]/light->samples;
		} else {}	
	}
}
