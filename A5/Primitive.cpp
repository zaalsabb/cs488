#include "Primitive.hpp"
#include "polyroots.hpp"
#include <iostream>
#include <vector>
#include <glm/ext.hpp>

using namespace glm;


Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

Cone::~Cone()
{
}

Cylinder::~Cylinder()
{
}

NonhierSphere::~NonhierSphere()
{
}

NonhierBox::~NonhierBox()
{
}

float NonhierSphere::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

	vec3 hit_pos;
	vec3 normal;

	origin = origin-tol*dir;

	origin = vec3(invtrans * vec4(origin,1.0f));
	dir = vec3(invtrans * vec4(dir,0.0f));


	double A = (double)dot(dir,dir);
	double B = (double)2*dot(dir,(origin-m_pos));
	double C = (double)dot(origin-m_pos,origin-m_pos)-m_radius*m_radius;

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
	hit_pos = origin + (float)t0*dir;
	normal = (hit_pos-m_pos)/(float)m_radius;

	hit_pos = vec3(trans * vec4(hit_pos,1.0f));
	normal = vec3(trans * vec4(normal,0.0f));
	// if (t0>=0){
	// 	t0 = length(hit_pos-origin);
	// } else {
	// 	t0 = -length(hit_pos-origin);
	// }
	hit.pos = hit_pos;
	hit.normal = normal;

	return t0;

}

float Cone::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

	//std::cout << m_height << std::endl;
	float PI = 3.1415;

	vec3 hit_pos;
	vec3 normal;
	float U;
	float V;

	origin = origin-tol*dir;

	origin = vec3(invtrans * vec4(origin,1.0f));
	dir = vec3(invtrans * vec4(dir,0.0f));

	double cos2_i = m_height*m_height/(m_height*m_height + m_radius*m_radius);

	vec3 q = vec3(0,-1,0);

	double A = (double)pow(dot(dir,q),2)-cos2_i;
	double B = (double)2*(dot(q,(origin-m_pos))*dot(q,dir)-dot(dir,origin-m_pos)*cos2_i);
	double C = (double)pow(dot(q,origin-m_pos),2)-dot(origin-m_pos,origin-m_pos)*cos2_i;

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

	vec3 hit_pos0 = origin + (float)t0*dir;
	if (hit_pos0[1]-m_pos[1]>0 | hit_pos0[1]-m_pos[1]<-m_height){
		return 0;
	}

	hit_pos = hit_pos0;
	vec3 n2 = cross(hit_pos-origin,hit_pos-m_pos);
	normal = normalize(cross(n2,hit_pos-m_pos));

	vec2 uv = (vec2(hit_pos[0],hit_pos[2])-vec2(m_pos[0],m_pos[2]))/m_radius;
	U = atan2((double)uv[1],(double)uv[0]) /(2 * PI);
	V = 1.0f+(hit_pos[1]-m_pos[1])/m_height;

	hit_pos = vec3(trans * vec4(hit_pos,1.0f));
	normal = vec3(trans * vec4(normal,0.0f));

	// if (t0>=0){
	// 	t0 = length(hit_pos-origin);
	// } else {
	// 	t0 = -length(hit_pos-origin);
	// }
	hit.pos = hit_pos;
	hit.normal = normal;
	hit.U = (float)clamp((double)U, 0.0, 1.0);
	hit.V = (float)clamp((double)V, 0.0, 1.0);
	return t0;

}


float Cylinder::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

	float PI = 3.1415;

	vec3 hit_pos;
	vec3 normal;
	float U;
	float V;

	origin = origin-tol*dir;

	origin = vec3(invtrans * vec4(origin,1.0f));
	dir = vec3(invtrans * vec4(dir,0.0f));

	vec2 dir2d = vec2(dir[0],dir[2]);
	vec2 origin2d = vec2(origin[0],origin[2]);
	vec2 m_pos2d = vec2(m_pos[0],m_pos[2]);

	double A = (double)dot(dir2d,dir2d);
	double B = (double)2*dot(dir2d,(origin2d-m_pos2d));
	double C = (double)dot(origin2d-m_pos2d,origin2d-m_pos2d)-m_radius*m_radius;

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

	vec3 hit_pos0 = origin + (float)t0*dir;
	vec3 normal0;
	if (hit_pos0[1]-m_pos[1]<0){
		// bottom face
		vec3 p = m_pos;
		normal0 = vec3(0,-1,0);
		t0 = dot((p-origin),normal0)/dot(normal0,dir);
		hit_pos0 = origin + (float)t0*dir;
		vec2 uv = (vec2(hit_pos0[0],hit_pos0[2])-vec2(p[0],p[2]))/m_radius;
		if (length(uv)<1){
			hit_pos = hit_pos0;
			normal = normal0;
			U = (uv[0]+1)/2;
			V = (uv[1]+1)/2;
		} else {
			return 0;
		}
	} else if (hit_pos0[1]-m_pos[1]>m_height){
		// top face
		vec3 p = m_pos+vec3(0,m_height,0);
		normal0 = vec3(0,1,0);
		t0 = dot((p-origin),normal0)/dot(normal0,dir);
		hit_pos0 = origin + (float)t0*dir;
		vec2 uv = (vec2(hit_pos0[0],hit_pos0[2])-vec2(p[0],p[2]))/m_radius;
		if (length(uv)<1){
			hit_pos = hit_pos0;
			normal = normal0;
			U = (uv[0]+1)/2;
			V = (uv[1]+1)/2;
		} else {
			return 0;
		}

	} else {
		// cylinderical side
		hit_pos = hit_pos0;
		normal = normalize(hit_pos - vec3(m_pos[0],hit_pos[1],m_pos[2]));
		vec2 uv = (vec2(hit_pos0[0],hit_pos0[2])-vec2(m_pos[0],m_pos[2]))/m_radius;
		U = atan2((double)uv[1],(double)uv[0]) /(2 * PI);
		V = (hit_pos[1]-m_pos[1])/m_height;
		// std::cout << "stop here\n" << std::endl;
	}

	hit_pos = vec3(trans * vec4(hit_pos,1.0f));
	normal = vec3(trans * vec4(normal,0.0f));
	// if (t0>=0){
	// 	t0 = length(hit_pos-origin);
	// } else {
	// 	t0 = -length(hit_pos-origin);
	// }
	hit.pos = hit_pos;
	hit.normal = normal;
	hit.U = (float)clamp((double)U, 0.0, 1.0);
	hit.V = (float)clamp((double)V, 0.0, 1.0);
	return t0;

}


float NonhierBox::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

	float t;
	float t0=0;
	float u;
	float v;
	vec3 c0;
	vec3 c1;
	vec3 c2;
	vec3 normal;
	vec3 hit_pos;
	vec3 normal0;

	origin = origin-tol*dir;

	origin = vec3(invtrans * vec4(origin,1.0f));
	dir = vec3(invtrans * vec4(dir,0.0f));
	// vec4 origin2 = trans * vec4(origin.x,origin.y,origin.z,1.0f);
	// vec4 dir2 = trans * vec4(dir.x,dir.y,dir.z,0.0f);
	//
	// origin.x = origin2.x/origin2.w;
	// origin.y = origin2.y/origin2.w;
	// origin.z = origin2.z/origin2.w;
	//
	// dir.x = dir2.x;
	// dir.y = dir2.y;
	// dir.z = dir2.z;
	// dir = normalize(dir);


	for (int i=0; i<3; i++){

		if (i==0){
			c0 = vec3(1,1,1)*(float)m_size+m_pos;
			c1 = vec3( 0,1,1)*(float)m_size+m_pos;
			c2 = vec3(1, 0,1)*(float)m_size+m_pos;
			normal = vec3(0,0,1);
		} else if (i==1){
			c0 = vec3(1, 1, 1)*(float)m_size+m_pos;
			c1 = vec3( 1,0,1)*(float)m_size+m_pos;
			c2 = vec3( 1, 1,0)*(float)m_size+m_pos;
			normal = vec3(1,0,0);
		} else {
			c0 = vec3(1, 1, 1)*(float)m_size+m_pos;
			c1 = vec3( 1,1,0)*(float)m_size+m_pos;
			c2 = vec3( 0,1,1)*(float)m_size+m_pos;
			normal = vec3(0,1,0);
		}

		t = dot((c0-origin),normal)/dot(normal,dir);
		hit_pos = origin + t*dir;
		u = dot(c1-c0,hit_pos-c0)/(float)m_size;
		v = dot(c2-c0,hit_pos-c0)/(float)m_size;
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
		c0 = -c0+2.0f*m_pos+vec3(m_size,m_size,m_size);
		c1 = -c1+2.0f*m_pos+vec3(m_size,m_size,m_size);
		c2 = -c2+2.0f*m_pos+vec3(m_size,m_size,m_size);

		t = dot((c0-origin),normal)/dot(normal,dir);
		hit_pos = origin + t*dir;
		u = dot(c1-c0,hit_pos-c0)/(float)m_size;
		v = dot(c2-c0,hit_pos-c0)/(float)m_size;
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

	hit_pos = origin + t0*dir;

	hit_pos = vec3(trans * vec4(hit_pos,1.0f));
	normal0 = vec3(trans * vec4(normal0,0.0f));
	// if (t0>=0){
	// 	t0 = length(hit_pos-origin);
	// } else {
	// 	t0 = -length(hit_pos-origin);
	// }
	hit.pos = hit_pos;
	hit.normal = normal0;
	return t0;

}
float Cube::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

		float t;
		float t0=0;
		float u;
		float v;
		vec3 hit_pos;
		vec3 normal0;

		origin = origin-tol*dir;

		origin = vec3(invtrans * vec4(origin,1.0f));
		dir = vec3(invtrans * vec4(dir,0.0f));

		// vec4 origin2 = trans * vec4(origin.x,origin.y,origin.z,1.0f);
		// vec4 dir2 = trans * vec4(dir.x,dir.y,dir.z,0.0f);
		//
		// origin.x = origin2.x/origin2.w;
		// origin.y = origin2.y/origin2.w;
		// origin.z = origin2.z/origin2.w;
		//
		// dir.x = dir2.x;
		// dir.y = dir2.y;
		// dir.z = dir2.z;
		// dir = normalize(dir);

		// std::cout << to_string(trans) << std::endl;

		for (int i=0; i<3; i++){

			vec3 c0;
			vec3 c1;
			vec3 c2;
			vec3 normal;

			if (i==0){
				c0 = vec3( 1,1,1);
				c1 = vec3( 0,1,1);
				c2 = vec3( 1,0,1);
				normal = vec3(0,0,1);
			} else if (i==1){
				c0 = vec3( 1,1,1);
				c1 = vec3( 1,0,1);
				c2 = vec3( 1,1,0);
				normal = vec3(1,0,0);
			} else {
				c0 = vec3(1,1,1);
				c1 = vec3(1,1,0);
				c2 = vec3(0,1,1);
				normal = vec3(0,1,0);
			}

			t = dot((c0-origin),normal)/dot(normal,dir);
			hit_pos = origin + t*dir;

			float m_size1 = length(c1-c0);
			float m_size2 = length(c2-c0);

			u = dot(c1-c0,hit_pos-c0);
			v = dot(c2-c0,hit_pos-c0);
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
			c0 = -c0+vec3(1,1,1);
			c1 = -c1+vec3(1,1,1);
			c2 = -c2+vec3(1,1,1);

			t = dot((c0-origin),normal)/dot(normal,dir);
			hit_pos = origin + t*dir;

			m_size1 = length(c1-c0);
			m_size2 = length(c2-c0);

			u = dot(c1-c0,hit_pos-c0);
			v = dot(c2-c0,hit_pos-c0);
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

		hit_pos = origin + t0*dir;

		hit_pos = vec3(trans * vec4(hit_pos,1.0f));
		normal0 = vec3(trans * vec4(normal0,0.0f));
		// if (t0>=0){
		// 	t0 = length(hit_pos-origin);
		// } else {
		// 	t0 = -length(hit_pos-origin);
		// }
		hit.pos = hit_pos;
		hit.normal = normal0;
		return t0;

}
float Sphere::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

		// vec4 m_posi = trans*vec4(0,0,0,1);
		// vec3 m_pos = vec3(m_posi.x,m_posi.y,m_posi.z)/m_posi.w;
		vec3 hit_pos;
		vec3 normal;

		origin = origin-tol*dir;

		origin = vec3(invtrans * vec4(origin,1.0f));
		dir = vec3(invtrans * vec4(dir,0.0f));

		vec3 m_pos = vec3(0,0,0);

		float m_radius = 1;

		double A = (double)dot(dir,dir);
		double B = (double)2*dot(dir,(origin-m_pos));
		double C = (double)dot(origin-m_pos,origin-m_pos)-m_radius*m_radius;

		double t[2];
		double t0;

		// std::cout << to_string(trans) << std::endl;

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

		hit_pos = origin + (float)t0*dir;
		normal = (hit_pos-m_pos)/(float)m_radius;

		hit_pos = vec3(trans * vec4(hit_pos,1.0f));
		normal = vec3(trans * vec4(normal,0.0f));
		// if (t0>=0){
		// 	t0 = length(hit_pos-origin);
		// } else {
		// 	t0 = -length(hit_pos-origin);
		// }
		hit.pos = hit_pos;
		hit.normal = normal;
		return t0;
}
