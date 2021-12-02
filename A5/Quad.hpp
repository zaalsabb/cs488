#pragma once

#include <vector>
#include <iosfwd>
#include <string>

#include <glm/glm.hpp>

#include "Primitive.hpp"
#include "Perlin.hpp"

using namespace glm;

// Use this #define to selectively compile your code to render the
// bounding boxes around your quad objects. Uncomment this option
// to turn it on.
//#define RENDER_BOUNDING_VOLUMES

struct QuadFace
{
	size_t v1;
	size_t v2;
	size_t v3;
	size_t v4;

	QuadFace( size_t pv1, size_t pv2, size_t pv3, size_t pv4 )
		: v1( pv1 )
		, v2( pv2 )
		, v3( pv3 )
		, v4( pv4 )
	{}
};

// A polygonal quad.
class Quad : public Primitive {
public:
  Quad( const std::string& fname, double n_cols, double n_rows);
  Perlin perlin = Perlin(1.0f);
  virtual float intersect(vec3 origin, vec3 dir, vec3 &hit, vec3 &normal,mat4 trans,mat4 invtrans);
	virtual bool SameSide(vec3 p1,vec3 p2,vec3 a,vec3 b);
	virtual void TransformCoordinates(mat4 trans);
	virtual bool checkSubdivision(vec3 hit, vec3 c0, vec3 c1, vec3 c2, float &u, float &v);

private:
	std::vector<vec3> m_vertices;
	std::vector<QuadFace> m_faces;
	int m_cols;
	int m_rows;
    friend std::ostream& operator<<(std::ostream& out, const Quad& quad);
};
