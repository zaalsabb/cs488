#pragma once

#include <vector>
#include <iosfwd>
#include <string>

#include <glm/glm.hpp>

#include "Primitive.hpp"

// Use this #define to selectively compile your code to render the
// bounding boxes around your mesh objects. Uncomment this option
// to turn it on.
//#define RENDER_BOUNDING_VOLUMES

struct Triangle
{
	size_t v1;
	size_t v2;
	size_t v3;

	Triangle( size_t pv1, size_t pv2, size_t pv3 )
		: v1( pv1 )
		, v2( pv2 )
		, v3( pv3 )
	{}
};

// A polygonal mesh.
class Mesh : public Primitive {
public:
  Mesh( const std::string& fname );
  virtual float intersect(glm::vec3 origin, glm::vec3 dir, glm::vec3 &hit, glm::vec3 &normal,glm::mat4 trans,glm::mat4 invtrans);
	virtual bool SameSide(glm::vec3 p1,glm::vec3 p2,glm::vec3 a,glm::vec3 b);
	virtual void TransformCoordinates(glm::mat4 trans);

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<Triangle> m_faces;


    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};
