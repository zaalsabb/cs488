#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Quad.hpp"

using namespace glm;

Quad::Quad( const std::string& fname, double n_cols, double n_rows )
	: m_vertices()
	, m_faces(),
	  m_cols((float)n_cols),
	  m_rows((float)n_rows)
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3, s4;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3 >> s4;
			m_faces.push_back( QuadFace( s1 - 1, s2 - 1, s3 - 1, s4 - 1 ) );
		}
	}
	//std::cout << code << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Quad& quad)
{
  out << "quad {";
  /*

  for( size_t idx = 0; idx < quad.m_verts.size(); ++idx ) {
  	const QuadVertex& v = quad.m_verts[idx];
  	out << to_string( v.m_position );
	if( quad.m_have_norm ) {
  	  out << " / " << to_string( v.m_normal );
	}
	if( quad.m_have_uv ) {
  	  out << " / " << to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}

float Quad::intersect(vec3 origin, vec3 dir, vec3 &hit, vec3 &normal0,mat4 trans,mat4 invtrans){

	float t;
	float t0=0.0f;
	float U;
	float V;

	origin = origin-tol*dir;

	for (int i=0; i<m_faces.size(); i++){

		int U1 = (((int)m_faces[i].v1 % m_cols));
		int V1 = (((int)m_faces[i].v1 - (int)m_faces[i].v1 % m_cols)/m_cols);

		int U2 = (((int)m_faces[i].v2 % m_cols));
		int V2 = (((int)m_faces[i].v2 - (int)m_faces[i].v2 % m_cols)/m_cols);

		int U3 = (((int)m_faces[i].v3 % m_cols));
		int V3 = (((int)m_faces[i].v3 - (int)m_faces[i].v3 % m_cols)/m_cols);

		int U4 = (((int)m_faces[i].v4 % m_cols));
		int V4 = (((int)m_faces[i].v4 - (int)m_faces[i].v4 % m_cols)/m_cols);

		vec3 c0 = m_vertices[(int)m_faces[i].v1];
		vec3 c1 = m_vertices[(int)m_faces[i].v2];
		vec3 c2 = m_vertices[(int)m_faces[i].v3];
		vec3 c3 = m_vertices[(int)m_faces[i].v4];

		vec4 c0i = trans * vec4(c0.x,c0.y,c0.z,1.0f);
		vec4 c1i = trans * vec4(c1.x,c1.y,c1.z,1.0f);
		vec4 c2i = trans * vec4(c2.x,c2.y,c2.z,1.0f);
		vec4 c3i = trans * vec4(c3.x,c3.y,c3.z,1.0f);

		c0 = vec3(c0i.x,c0i.y,c0i.z)/c0i.w;
		c1 = vec3(c1i.x,c1i.y,c1i.z)/c1i.w;
		c2 = vec3(c2i.x,c2i.y,c2i.z)/c2i.w;
		c3 = vec3(c3i.x,c3i.y,c3i.z)/c3i.w;

		vec3 normal = normalize(cross(c1-c0,c2-c0));

		// c0 = c0 + normal*perlin.noise_function(U1,V1,m_rows,m_cols);
		// c1 = c1 + normal*perlin.noise_function(U2,V2,m_rows,m_cols);
		// c2 = c2 + normal*perlin.noise_function(U3,V3,m_rows,m_cols);
		// c3 = c3 + normal*perlin.noise_function(U4,V4,m_rows,m_cols);		

		t = dot((c0-origin),normal)/dot(normal,dir);
		hit = origin + t*dir;

		float u1;
		float v1;
		float u2;
		float v2;

		// check if hit is in quad subdivision 1 or 2
		if (checkSubdivision(hit,c0, c1, c2, u1, v1)) {
			if (t0==0.0f){
				t0 = t;
				normal0 = normal;
				U = (float)U1 + u1;
				V = (float)V1 + v1;
			} else if (t<t0) {
				t0 = t;
				normal0 = normal;
				U = (float)U1 + u1;
				V = (float)V1 + v1;
			}
		} else if (checkSubdivision(hit,c0, c2, c3, u2, v2)) {
			if (t0==0.0f){
				t0 = t;
				normal0 = normal;
				U = (float)U1 + u1;
				V = (float)V1 + v1;
			} else if (t<t0) {
				t0 = t;
				normal0 = normal;
				U = (float)U1 + u1;
				V = (float)V1 + v1;
			}
		}
	}
	
	hit = origin + t0*dir;
	// perlin.noise_normal(U,V,m_rows,m_cols,normal0);
	return t0;
}

bool Quad::checkSubdivision(vec3 hit, vec3 c0, vec3 c1, vec3 c2, float &u, float &v){

	u = dot(c1-c0,hit-c0)/dot(c1-c0,c1-c0);
	v = dot(c2-c0,hit-c0)/dot(c2-c0,c2-c0);
	
	return SameSide(hit,c0, c1,c2) & SameSide(hit,c1, c0,c2) & SameSide(hit,c2, c0,c1);
}

void Quad::TransformCoordinates(mat4 trans){
	for (int i=0; i<m_faces.size(); i++){

		vec3 c0 = m_vertices[(int)m_faces[i].v1];
		vec3 c1 = m_vertices[(int)m_faces[i].v2];
		vec3 c2 = m_vertices[(int)m_faces[i].v3];

		vec4 c0i = trans * vec4(c0.x,c0.y,c0.z,1.0f);
		vec4 c1i = trans * vec4(c1.x,c1.y,c1.z,1.0f);
		vec4 c2i = trans * vec4(c2.x,c2.y,c2.z,1.0f);

		m_vertices[(int)m_faces[i].v1] = vec3(c0i.x,c0i.y,c0i.z)/c0i.w;
		m_vertices[(int)m_faces[i].v2] = vec3(c1i.x,c1i.y,c1i.z)/c1i.w;
		m_vertices[(int)m_faces[i].v3] = vec3(c2i.x,c2i.y,c2i.z)/c2i.w;
	}
}

bool Quad::SameSide(vec3 p1,vec3 p2,vec3 a,vec3 b){
    vec3 cp1 = cross(b-a, p1-a);
    vec3 cp2 = cross(b-a, p2-a);
    if (dot(cp1, cp2) >= 0){ return true;}
    else { return false;}
}
