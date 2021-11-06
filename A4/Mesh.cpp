#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"

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
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
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
  	out << glm::to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << glm::to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << glm::to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}

float Mesh::intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal0){

	float t;
	float t0=0.0f;
	float u;
	float v;
	glm::vec3 c0;
	glm::vec3 c1;
	glm::vec3 c2;
	glm::vec3 normal;

	for (int i=0; i<m_faces.size(); i++){

		c0 = m_vertices[(int)m_faces[i].v1];
		c1 = m_vertices[(int)m_faces[i].v2];
		c2 = m_vertices[(int)m_faces[i].v3];

		normal = glm::normalize(glm::cross(c1-c0,c2-c0));

		t = glm::dot((c0-origin),normal)/glm::dot(normal,dir);
		hit = origin + t*dir;

		u = glm::dot(c1-c0,hit-c0)/glm::dot(c1-c0,c1-c0);
		v = glm::dot(c2-c0,hit-c0)/glm::dot(c2-c0,c2-c0);
		if (SameSide(hit,c0, c1,c2) & SameSide(hit,c1, c0,c2)
				& SameSide(hit,c2, c0,c1)) {
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

bool Mesh::SameSide(glm::vec3 p1,glm::vec3 p2,glm::vec3 a,glm::vec3 b){
    glm::vec3 cp1 = glm::cross(b-a, p1-a);
    glm::vec3 cp2 = glm::cross(b-a, p2-a);
    if (glm::dot(cp1, cp2) >= 0){ return true;}
    else { return false;}
}
