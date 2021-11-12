#include "Primitive.hpp"
#include "polyroots.hpp"
#include <iostream>
#include <vector>
#include <glm/ext.hpp>


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

float NonhierSphere::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans){

	origin = origin-tol*dir;

	origin = glm::vec3(invtrans * glm::vec4(origin,1.0f));
	dir = glm::vec3(invtrans * glm::vec4(dir,0.0f));


	double A = (double)glm::dot(dir,dir);
	double B = (double)2*glm::dot(dir,(origin-m_pos));
	double C = (double)glm::dot(origin-m_pos,origin-m_pos)-m_radius*m_radius;

	double t[2];
	double t0;


	quadraticRoots(A, B, C, t);

	if (t[0]>0 & t[1]>0){
		t0 = std::min(t[0],t[1]);
	} else if (t[0]>0) {

		t0 = t[0];

	} else if (t[1]>0) {

		t0 = t[1];
	} else {

		t0 = 0;
	}
	hit = origin + (float)t0*dir;
	normal = (hit-m_pos)/(float)m_radius;

	hit = glm::vec3(trans * glm::vec4(hit,1.0f));
	normal = glm::vec3(trans * glm::vec4(normal,0.0f));
	// if (t0>=0){
	// 	t0 = glm::length(hit-origin);
	// } else {
	// 	t0 = -glm::length(hit-origin);
	// }

	return t0;

}

float NonhierBox::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal0,glm::mat4 trans,glm::mat4 invtrans){

	float t;
	float t0=0;
	float u;
	float v;
	glm::vec3 c0;
	glm::vec3 c1;
	glm::vec3 c2;
	glm::vec3 normal;

	origin = origin-tol*dir;

	origin = glm::vec3(invtrans * glm::vec4(origin,1.0f));
	dir = glm::vec3(invtrans * glm::vec4(dir,0.0f));
	// glm::vec4 origin2 = trans * glm::vec4(origin.x,origin.y,origin.z,1.0f);
	// glm::vec4 dir2 = trans * glm::vec4(dir.x,dir.y,dir.z,0.0f);
	//
	// origin.x = origin2.x/origin2.w;
	// origin.y = origin2.y/origin2.w;
	// origin.z = origin2.z/origin2.w;
	//
	// dir.x = dir2.x;
	// dir.y = dir2.y;
	// dir.z = dir2.z;
	// dir = glm::normalize(dir);


	for (int i=0; i<3; i++){

		if (i==0){
			c0 = glm::vec3(1,1,1)*(float)m_size+m_pos;
			c1 = glm::vec3( 0,1,1)*(float)m_size+m_pos;
			c2 = glm::vec3(1, 0,1)*(float)m_size+m_pos;
			normal = glm::vec3(0,0,1);
		} else if (i==1){
			c0 = glm::vec3(1, 1, 1)*(float)m_size+m_pos;
			c1 = glm::vec3( 1,0,1)*(float)m_size+m_pos;
			c2 = glm::vec3( 1, 1,0)*(float)m_size+m_pos;
			normal = glm::vec3(1,0,0);
		} else {
			c0 = glm::vec3(1, 1, 1)*(float)m_size+m_pos;
			c1 = glm::vec3( 1,1,0)*(float)m_size+m_pos;
			c2 = glm::vec3( 0,1,1)*(float)m_size+m_pos;
			normal = glm::vec3(0,1,0);
		}

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
		c0 = -c0+2.0f*m_pos+glm::vec3(m_size,m_size,m_size);
		c1 = -c1+2.0f*m_pos+glm::vec3(m_size,m_size,m_size);
		c2 = -c2+2.0f*m_pos+glm::vec3(m_size,m_size,m_size);

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

	hit = glm::vec3(trans * glm::vec4(hit,1.0f));
	normal0 = glm::vec3(trans * glm::vec4(normal0,0.0f));
	// if (t0>=0){
	// 	t0 = glm::length(hit-origin);
	// } else {
	// 	t0 = -glm::length(hit-origin);
	// }

	return t0;

}
float Cube::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal0,glm::mat4 trans,glm::mat4 invtrans){

		float t;
		float t0=0;
		float u;
		float v;

		origin = origin-tol*dir;

		origin = glm::vec3(invtrans * glm::vec4(origin,1.0f));
		dir = glm::vec3(invtrans * glm::vec4(dir,0.0f));

		// glm::vec4 origin2 = trans * glm::vec4(origin.x,origin.y,origin.z,1.0f);
		// glm::vec4 dir2 = trans * glm::vec4(dir.x,dir.y,dir.z,0.0f);
		//
		// origin.x = origin2.x/origin2.w;
		// origin.y = origin2.y/origin2.w;
		// origin.z = origin2.z/origin2.w;
		//
		// dir.x = dir2.x;
		// dir.y = dir2.y;
		// dir.z = dir2.z;
		// dir = glm::normalize(dir);

		// std::cout << glm::to_string(trans) << std::endl;

		for (int i=0; i<3; i++){

			glm::vec3 c0;
			glm::vec3 c1;
			glm::vec3 c2;
			glm::vec3 normal;

			if (i==0){
				c0 = glm::vec3( 1,1,1);
				c1 = glm::vec3( 0,1,1);
				c2 = glm::vec3( 1,0,1);
				normal = glm::vec3(0,0,1);
			} else if (i==1){
				c0 = glm::vec3( 1,1,1);
				c1 = glm::vec3( 1,0,1);
				c2 = glm::vec3( 1,1,0);
				normal = glm::vec3(1,0,0);
			} else {
				c0 = glm::vec3(1,1,1);
				c1 = glm::vec3(1,1,0);
				c2 = glm::vec3(0,1,1);
				normal = glm::vec3(0,1,0);
			}

			t = glm::dot((c0-origin),normal)/glm::dot(normal,dir);
			hit = origin + t*dir;

			float m_size1 = glm::length(c1-c0);
			float m_size2 = glm::length(c2-c0);

			u = glm::dot(c1-c0,hit-c0);
			v = glm::dot(c2-c0,hit-c0);
			if (u>0.0f & v>0.0f & u<1 & v<1) {
				if (t0==0.0f){
					t0 = t;
					normal0 = normal;
				} else if (t<t0) {
					t0 = t;
					normal0 = normal;
				}
			}

			normal = -normal;
			c0 = -c0+glm::vec3(1,1,1);
			c1 = -c1+glm::vec3(1,1,1);
			c2 = -c2+glm::vec3(1,1,1);

			t = glm::dot((c0-origin),normal)/glm::dot(normal,dir);
			hit = origin + t*dir;

			m_size1 = glm::length(c1-c0);
			m_size2 = glm::length(c2-c0);

			u = glm::dot(c1-c0,hit-c0);
			v = glm::dot(c2-c0,hit-c0);
			if (u>0.0f & v>0.0f & u<1 & v<1) {
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

		hit = glm::vec3(trans * glm::vec4(hit,1.0f));
		normal0 = glm::vec3(trans * glm::vec4(normal0,0.0f));
		// if (t0>=0){
		// 	t0 = glm::length(hit-origin);
		// } else {
		// 	t0 = -glm::length(hit-origin);
		// }

		return t0;

}
float Sphere::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans){

		// glm::vec4 m_posi = trans*glm::vec4(0,0,0,1);
		// glm::vec3 m_pos = glm::vec3(m_posi.x,m_posi.y,m_posi.z)/m_posi.w;

		origin = origin-tol*dir;

		origin = glm::vec3(invtrans * glm::vec4(origin,1.0f));
		dir = glm::vec3(invtrans * glm::vec4(dir,0.0f));

		glm::vec3 m_pos = glm::vec3(0,0,0);

		float m_radius = 1;

		double A = (double)glm::dot(dir,dir);
		double B = (double)2*glm::dot(dir,(origin-m_pos));
		double C = (double)glm::dot(origin-m_pos,origin-m_pos)-m_radius*m_radius;

		double t[2];
		double t0;

		// std::cout << glm::to_string(trans) << std::endl;

		quadraticRoots(A, B, C, t);

		if (t[0]>0 & t[1]>0){
			t0 = std::min(t[0],t[1]);
		} else if (t[0]>0) {

			t0 = t[0];

		} else if (t[1]>0) {

			t0 = t[1];
		} else {

			t0 = 0;
		}

		hit = origin + (float)t0*dir;
		normal = (hit-m_pos)/(float)m_radius;

		hit = glm::vec3(trans * glm::vec4(hit,1.0f));
		normal = glm::vec3(trans * glm::vec4(normal,0.0f));
		// if (t0>=0){
		// 	t0 = glm::length(hit-origin);
		// } else {
		// 	t0 = -glm::length(hit-origin);
		// }

		return t0;
}
