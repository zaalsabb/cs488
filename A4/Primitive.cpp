#include "Primitive.hpp"
#include "polyroots.hpp"
#include <iostream>
#include <vector>


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

float NonhierSphere::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal){


	double A = (double)glm::dot(dir,dir);
	double B = (double)2*glm::dot(dir,(origin-m_pos));
	double C = (double)glm::dot(origin-m_pos,origin-m_pos)-m_radius*m_radius;

	double t[2];
	double t_ans;

	quadraticRoots(A, B, C, t);

	if (t[0]>0 & t[1]>0){
		return std::min(t[0],t[1]);
	} else if (t[0]>0) {

		t_ans = t[0];

	} else if (t[1]>0) {

		t_ans = t[1];
	} else {

		t_ans = 0;
	}
	hit = origin + (float)t_ans*dir;
	normal = (hit-m_pos)/(float)m_radius;
	return t_ans;

}



float NonhierBox::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal0){

	std::vector<glm::vec3> c0_list;
	std::vector<glm::vec3> c1_list;
	std::vector<glm::vec3> c2_list;
	std::vector<glm::vec3> normal_list;


	c0_list.push_back(glm::vec3(1,1,1));
	c0_list.push_back(glm::vec3(1, 1, 1));
	c0_list.push_back(glm::vec3(1, 1, 1));

	c1_list.push_back(glm::vec3( 0,1,1));
	c1_list.push_back(glm::vec3( 1,0,1));
	c1_list.push_back(glm::vec3( 1,1,0));

	c2_list.push_back(glm::vec3(1, 0,1));
	c2_list.push_back(glm::vec3( 1, 1,0));
	c2_list.push_back(glm::vec3( 0,1,1));

	normal_list.push_back(glm::vec3(0,0,1));
	normal_list.push_back(glm::vec3(1,0,0));
	normal_list.push_back(glm::vec3(0,1,0));

	float t;
	float t0=0;
	float u;
	float v;

	for (int i=0; i<3; i++){

		glm::vec3 normal = normal_list[i];
		glm::vec3 c0 = c0_list[i]*(float)m_size+m_pos;
		glm::vec3 c1 = c1_list[i]*(float)m_size+m_pos;
		glm::vec3 c2 = c2_list[i]*(float)m_size+m_pos;

		t = glm::dot((c0-origin),normal)/glm::dot(normal,dir);
		hit = origin + t*dir;
		u = glm::dot(c1-c0,hit-c0)/(float)m_size;
		v = glm::dot(c2-c0,hit-c0)/(float)m_size;
		if (u>0.0f & v>0.0f & u<(float)m_size & v<(float)m_size) {
			if (t0==0.0f){
				t0 = t;
				normal0 = normal;
			} else if (t<t0) {
				t0 = t;
				normal0 = normal;
			}
		}

		normal = -normal;
		c0 = -c0_list[i]*(float)m_size+m_pos+glm::vec3(m_size,m_size,m_size);
		c1 = -c1_list[i]*(float)m_size+m_pos+glm::vec3(m_size,m_size,m_size);
		c2 = -c2_list[i]*(float)m_size+m_pos+glm::vec3(m_size,m_size,m_size);

		t = glm::dot((c0-origin),normal)/glm::dot(normal,dir);
		hit = origin + t*dir;
		u = glm::dot(c1-c0,hit-c0)/(float)m_size;
		v = glm::dot(c2-c0,hit-c0)/(float)m_size;
		if (u>0.0f & v>0.0f & u<(float)m_size & v<(float)m_size) {
			if (t0==0.0f){
				t0 = t;
				normal0 = normal;
			} else if (t<t0) {
				t0 = t;
				normal0 = normal;
			}
		}

	}

	hit = origin + t0*dir;
	return t0;

}
float Cube::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal){return 0;}
float Sphere::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 hit, glm::vec3 normal){return 0;}
