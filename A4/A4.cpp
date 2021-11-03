#include <glm/ext.hpp>

#include "A4.hpp"
#include "GeometryNode.hpp"
#include "JointNode.hpp"

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
	glm::vec3 di;
	float t;
	const GeometryNode * geometryNode;

	bool hit;

	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {

			hit = false;

			pixel_cam[0] = film_w*(x+0.5f-w/2)/w;
			pixel_cam[1] = film_h*(y+0.5f-h/2)/h;
			pixel_cam[2] = film_z;

			pixel_world = pixel_cam[0]*ui + pixel_cam[1]*vi + pixel_cam[2]*wi + ei;
			
			di = glm::normalize(ei-pixel_world);

			for (SceneNode * node : root->children) {
				if (node->m_nodeType == NodeType::GeometryNode)
					geometryNode = static_cast<const GeometryNode *>(node);
					t = geometryNode->m_primitive->intersect(ei,di);
					if (t != 0){
						hit = true;
					}

					//std::cout << geometryNode->m_primitive->intersect(ei,di) << std::endl;
			}

			if (hit){

				// Red: 
				image(x, y, 0) = (double)0.0;
				// Green: 
				image(x, y, 1) = (double)0.0;
				// Blue: 
				image(x, y, 2) = (double)0.0;
			} else {

				// Red: 
				image(x, y, 0) = (double)1.0;
				// Green: 
				image(x, y, 1) = (double)1.0;
				// Blue: 
				image(x, y, 2) = (double)1.0;
			}

		}
	}

}
