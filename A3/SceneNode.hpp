#pragma once

#include "Material.hpp"

#include <glm/glm.hpp>

#include <list>
#include <string>
#include <iostream>

enum class NodeType {
	SceneNode,
	GeometryNode,
	JointNode
};

class SceneNode {
public:
    SceneNode(const std::string & name);

	SceneNode(const SceneNode & other);

    virtual ~SceneNode();
    
	int totalSceneNodes() const;
    
    const glm::mat4& get_transform() const;
    const glm::mat4& get_inverse() const;
    
    void set_transform(const glm::mat4& m);
    void reset_transform();
    void ResetChildrenTransforms();

    void add_child(SceneNode* child);
    
    void remove_child(SceneNode* child);

	//-- Transformations:
    void rotate(char axis, float angle);
    void scale(const glm::vec3& amount);
    void translate(const glm::vec3& amount);
    void rotateLeft(char axis, float angle);

    void BuildHierarchyGraph();
    void ApplyScales();
    void ApplyMouseTranslation();
    void ApplyMouseRotation();
    void ApplyJointTransforms();

	friend std::ostream & operator << (std::ostream & os, const SceneNode & node);

	bool isSelected;
    
    // Transformations
    glm::mat4 trans;
    glm::mat4 trans_orig;
    glm::mat4 trans_unscaled;
    glm::vec3 s = glm::vec3(1.0,1.0,1.0);
    glm::mat4 invtrans;
    glm::vec3 total_trans;
    glm::vec3 mouse_trans;
    glm::vec3 mouse_rot;

    float jx=1;
    float jy=1;

    std::list<SceneNode*> children;

	NodeType m_nodeType;
	std::string m_name;
	unsigned int m_nodeId;


private:
	// The number of SceneNode instances.
	static unsigned int nodeInstanceCount;
};
