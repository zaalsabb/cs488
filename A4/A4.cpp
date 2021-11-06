#include <glm/ext.hpp>

#include "A4.hpp"
#include "GeometryNode.hpp"
#include "JointNode.hpp"
#include "PhongMaterial.hpp"
#include <math.h>

float PI = 3.1415;

void A4_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  glm::vec3 wi = glm::normalize(eye - view);
  glm::vec3 ui = glm::normalize(glm::cross(up,wi));
  glm::vec3 vi = glm::cross(wi,ui);
  glm::vec3 ei = eye;

  float film_z = 1.0f;
  float film_w  = 2*film_z*glm::tan(fovy/2*PI/180);
  float film_h  = film_w;

  std::cout << "Calling A4_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	size_t h = image.height();
	size_t w = image.width();

	glm::vec3 pixel_cam;
	glm::vec3 pixel_world;
	glm::vec3 dir;


	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {


			float t;
			float t0 = 0;

			Hit hit;

			pixel_cam[0] = film_w*(w/2-(x+0.5f))/w;
			pixel_cam[1] = film_h*(y+0.5f-h/2)/h;
			pixel_cam[2] = film_z;

			pixel_world = pixel_cam[0]*ui + pixel_cam[1]*vi + pixel_cam[2]*wi + ei;

			dir = glm::normalize(ei-pixel_world);

			bool hit_confirmed = rayIntersection(root, ei, dir, hit);

			if (hit_confirmed){

				//PhongMaterial* mat = static_cast<PhongMaterial*>(geometryNode0->m_material);
				//std::cout << glm::to_string(mat->m_ks ) << std::endl;
				glm::vec3 L = 1.2f*hit.mat.m_kd * ambient;
				float p = hit.mat.m_shininess;

				for (Light * light : lights){
					glm::vec3 l = light->position - hit.pos;
					float r = glm::length(l);
					glm::vec3 I = 120000.0*light->colour;
					l = l/r;

					Hit hit2;
					bool hit_confirmed2 = rayIntersection(root, hit.pos, l, hit2);
					if (!hit_confirmed2){
						//diffuse lighting
						L = L + I*hit.mat.m_kd/(r*r)*std::max(0.0f,glm::dot(l,hit.n));

						//specular Lighting
						glm::vec3 h = glm::normalize(l-dir);
						L = L + I*hit.mat.m_ks/(r*r)*pow(std::max(0.0f,glm::dot(h,hit.n)),p);
						//std::cout << glm::to_string(n) << std::endl;
					}
				}

				// Red:
				image(x, y, 0) = (double)L[0];
				// Green:
				image(x, y, 1) = (double)L[1];
				// Blue:
				image(x, y, 2) = (double)L[2];
			} else {

				// Red:
				image(x, y, 0) = (double)0.0;
				// Green:
				image(x, y, 1) = (double)0.0;
				// Blue:
				image(x, y, 2) = (double)0.0;
			}

		}
	}
}

bool rayIntersection(SceneNode * root, glm::vec3 origin, glm::vec3 dir,
												 Hit &hit){
	glm::vec3 normal;
	glm::vec3 hit_pos;
	float t;
	float t0 = 0.0f;
	float tol = 0.01f;

	const GeometryNode * geometryNode;
	const GeometryNode * geometryNode0;

	bool hit_confirmed = false;
	for (SceneNode * node : root->children) {
		if (node->m_nodeType == NodeType::GeometryNode){
			geometryNode = static_cast<const GeometryNode *>(node);
			t = geometryNode->m_primitive->intersect(origin,dir,hit_pos,normal);
			if (t > tol){
				hit_confirmed = true;
				if (t0 == 0 | t < t0 ) {
					t0 = t;
					geometryNode0 = geometryNode;
					hit.pos=hit_pos;
					hit.n=normal;
				}
			}
		}
	}

	if (hit_confirmed){
		PhongMaterial * mat = static_cast<PhongMaterial*>(geometryNode0->m_material);
		hit.mat.m_ks = mat->m_ks;
		hit.mat.m_kd = mat->m_kd;
		hit.mat.m_shininess = mat->m_shininess;
	}

	return hit_confirmed;
}
