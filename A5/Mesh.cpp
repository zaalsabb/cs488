#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"

using namespace glm;

Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
		}
	}
	//std::cout << code << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  /*

  for( size_t idx = 0; idx < mesh.m_verts.size(); ++idx ) {
  	const MeshVertex& v = mesh.m_verts[idx];
  	out << to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}

float Mesh::intersect(vec3 origin, vec3 dir, Hit &hit,mat4 trans,mat4 invtrans){

	float t;
	float t0=0.0f;
	float u;
	float v;
	vec3 hit_pos;
	vec3 normal0;

	origin = origin-tol*dir;

	for (int i=0; i<m_faces.size(); i++){

		vec3 c0 = m_vertices[(int)m_faces[i].v1];
		vec3 c1 = m_vertices[(int)m_faces[i].v2];
		vec3 c2 = m_vertices[(int)m_faces[i].v3];

		vec4 c0i = trans * vec4(c0.x,c0.y,c0.z,1.0f);
		vec4 c1i = trans * vec4(c1.x,c1.y,c1.z,1.0f);
		vec4 c2i = trans * vec4(c2.x,c2.y,c2.z,1.0f);

		c0 = vec3(c0i.x,c0i.y,c0i.z)/c0i.w;
		c1 = vec3(c1i.x,c1i.y,c1i.z)/c1i.w;
		c2 = vec3(c2i.x,c2i.y,c2i.z)/c2i.w;

		vec3 normal = normalize(cross(c1-c0,c2-c0));
		// if (dot(dir,normal)>0){
		// 	normal = -normal;
		// }

		t = dot((c0-origin),normal)/dot(normal,dir);
		hit_pos = origin + t*dir;

		u = dot(c1-c0,hit_pos-c0)/dot(c1-c0,c1-c0);
		v = dot(c2-c0,hit_pos-c0)/dot(c2-c0,c2-c0);
		
		if (SameSide(hit_pos,c0, c1,c2) & SameSide(hit_pos,c1, c0,c2)
				& SameSide(hit_pos,c2, c0,c1)) {
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
	hit.pos = hit_pos;
	hit.normal = normal0;	
	return t0;
}

void Mesh::TransformCoordinates(mat4 trans){
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

bool Mesh::SameSide(vec3 p1,vec3 p2,vec3 a,vec3 b){
    vec3 cp1 = cross(b-a, p1-a);
    vec3 cp2 = cross(b-a, p2-a);
    if (dot(cp1, cp2) >= 0){ return true;}
    else { return false;}
}
