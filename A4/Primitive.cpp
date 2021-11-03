#include "Primitive.hpp"
#include "polyroots.hpp"
#include <iostream>


Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

NonhierBox::~NonhierBox()
{
}

float NonhierSphere::intersect(glm::vec3 origin, glm::vec3 dir){


	double A = (double)glm::dot(dir,dir);
	double B = (double)2*glm::dot(dir,(origin-m_pos));
	double C = (double)glm::dot(origin-m_pos,origin-m_pos)-m_radius*m_radius;

	double t[2];

	quadraticRoots(A, B, C, t);

	if (t[0]>0 & t[1]>0){
		return std::min(t[0],t[1]);
	} else if (t[0]>0) {

		return t[0];

	} else if (t[1]>0) {

		return t[1];
	} else {

		return 0;
	}

}



float NonhierBox::intersect(glm::vec3 origin, glm::vec3 dir){return 0;}
float Cube::intersect(glm::vec3 origin, glm::vec3 dir){return 0;}
float Sphere::intersect(glm::vec3 origin, glm::vec3 dir){return 0;}
