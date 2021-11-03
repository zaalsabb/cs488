#include "SceneNode.hpp"

#include "cs488-framework/MathUtils.hpp"

#include <iostream>
#include <sstream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

using namespace glm;


// Static class variable
unsigned int SceneNode::nodeInstanceCount = 0;


//---------------------------------------------------------------------------------------
SceneNode::SceneNode(const std::string& name)
  : m_name(name),
	m_nodeType(NodeType::SceneNode),
	trans(mat4()),
	isSelected(false),
	m_nodeId(nodeInstanceCount++)
{

}

//---------------------------------------------------------------------------------------
// Deep copy
SceneNode::SceneNode(const SceneNode & other)
	: m_nodeType(other.m_nodeType),
	  m_name(other.m_name),
	  trans(other.trans),
	  invtrans(other.invtrans)
{
	for(SceneNode * child : other.children) {
		this->children.push_front(new SceneNode(*child));
	}
}

//---------------------------------------------------------------------------------------
SceneNode::~SceneNode() {
	for(SceneNode * child : children) {
		delete child;
	}
}

//---------------------------------------------------------------------------------------
void SceneNode::set_transform(const glm::mat4& m) {
	trans = m;
	invtrans = m;
}
//---------------------------------------------------------------------------------------
void SceneNode::reset_transform() {
	trans = trans_orig;
	invtrans = trans_orig;
}
//---------------------------------------------------------------------------------------
const glm::mat4& SceneNode::get_transform() const {
	return trans;
}

//---------------------------------------------------------------------------------------
const glm::mat4& SceneNode::get_inverse() const {
	return invtrans;
}

//---------------------------------------------------------------------------------------
void SceneNode::add_child(SceneNode* child) {
	children.push_back(child);
}

//---------------------------------------------------------------------------------------
void SceneNode::remove_child(SceneNode* child) {
	children.remove(child);
}

//---------------------------------------------------------------------------------------
void SceneNode::rotate(char axis, float angle) {
	vec3 rot_axis;

	switch (axis) {
		case 'x':
			rot_axis = vec3(1,0,0);
			break;
		case 'y':
			rot_axis = vec3(0,1,0);
	        break;
		case 'z':
			rot_axis = vec3(0,0,1);
	        break;
		default:
			break;
	}
	mat4 rot_matrix = glm::rotate(degreesToRadians(angle), rot_axis);
	trans = rot_matrix * trans;
	trans_unscaled = rot_matrix * trans_unscaled;
	trans_orig = trans;
}
//---------------------------------------------------------------------------------------
void SceneNode::rotateLeft(char axis, float angle) {
	vec3 rot_axis;

	switch (axis) {
		case 'x':
			rot_axis = vec3(1,0,0);
			break;
		case 'y':
			rot_axis = vec3(0,1,0);
	        break;
		case 'z':
			rot_axis = vec3(0,0,1);
	        break;
		default:
			break;
	}
	vec4 rot_axis1 = glm::inverse(trans)*glm::vec4(rot_axis, 0.0f);
	mat4 rot_matrix = glm::rotate(degreesToRadians(angle), vec3(rot_axis1[0],rot_axis1[1],rot_axis1[2]));
	trans =  trans * rot_matrix;
	trans_unscaled = trans_unscaled * rot_matrix;
	trans_orig = trans;
}

//---------------------------------------------------------------------------------------
void SceneNode::scale(const glm::vec3 & amount) {
	//trans = glm::scale(amount) * trans;
	//trans_orig = trans;
	s = amount;
}

//---------------------------------------------------------------------------------------
void SceneNode::translate(const glm::vec3& amount) {
	trans = glm::translate(amount) * trans;
	trans_unscaled = glm::translate(amount) * trans_unscaled;
	trans_orig = trans;
	total_trans = amount;
}

//---------------------------------------------------------------------------------------
void SceneNode::BuildHierarchyGraph(){

	for (SceneNode * node : children) {
		node->set_transform(trans*node->trans);
		node->BuildHierarchyGraph();
	}
}

//---------------------------------------------------------------------------------------
void SceneNode::ApplyJointTransforms(){

	for (SceneNode * node : children) {
		if (node->m_nodeType == NodeType::JointNode) {
			node->rotateLeft('x',node->jx);
			node->rotateLeft('y',node->jy);
		}
		node->ApplyJointTransforms();
	}
}


//---------------------------------------------------------------------------------------
void SceneNode::ApplyScales(){

	for (SceneNode * node : children) {
		node->set_transform(node->trans*glm::scale(node->s));
		node->ApplyScales();
	}
}

//---------------------------------------------------------------------------------------
void SceneNode::ResetChildrenTransforms(){

	for (SceneNode * node : children) {
		node->reset_transform();
		node->ResetChildrenTransforms();
	}
}
//---------------------------------------------------------------------------------------
void SceneNode::ApplyMouseTranslation(){

	translate(mouse_trans);
}
//---------------------------------------------------------------------------------------
void SceneNode::ApplyMouseRotation(){


	rotateLeft('x', mouse_rot.x);
	rotateLeft('y', mouse_rot.y);
	rotateLeft('z', mouse_rot.z);


}

//---------------------------------------------------------------------------------------
int SceneNode::totalSceneNodes() const {
	return nodeInstanceCount;
}

//---------------------------------------------------------------------------------------
std::ostream & operator << (std::ostream & os, const SceneNode & node) {

	//os << "SceneNode:[NodeType: ___, name: ____, id: ____, isSelected: ____, transform: ____"
	switch (node.m_nodeType) {
		case NodeType::SceneNode:
			os << "SceneNode";
			break;
		case NodeType::GeometryNode:
			os << "GeometryNode";
			break;
		case NodeType::JointNode:
			os << "JointNode";
			break;
	}
	os << ":[";

	os << "name:" << node.m_name << ", ";
	os << "id:" << node.m_nodeId;
	os << "]";

	return os;
}
