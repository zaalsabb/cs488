#pragma once

#include "SceneNode.hpp"
#include "Primitive.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Bump.hpp"

class GeometryNode : public SceneNode {
public:
	GeometryNode( const std::string & name, Primitive *prim,
		Material *mat = nullptr );

	void setMaterial( Material *material );
	void setTexture( Texture *texture );
	void setBump( Bump *bump );

	Material *m_material;
	Primitive *m_primitive;
	Texture *m_texture = nullptr;
	Bump *m_bump = nullptr;
};
