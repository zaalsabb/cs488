#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include <glm/glm.hpp>

#include <vector>

// Set a global maximum number of vertices in order to pre-allocate VBO data
// in one shot, rather than reallocating each frame.
const GLsizei kMaxVertices = 1000;


struct Line {
    glm::vec4 A;
    glm::vec4 B;
};

// Convenience class for storing vertex data in CPU memory.
// Data should be copied over to GPU memory via VBO storage before rendering.
class VertexData {
public:
	VertexData();

	std::vector<glm::vec2> positions;
	std::vector<glm::vec3> colours;
	GLuint index;
	GLsizei numVertices;
};


class A2 : public CS488Window {
public:
	A2();
	virtual ~A2();

protected:
	virtual void init() override;
	virtual void appLogic() override;
	virtual void guiLogic() override;
	virtual void draw() override;
	virtual void cleanup() override;

	virtual bool cursorEnterWindowEvent(int entered) override;
	virtual bool mouseMoveEvent(double xPos, double yPos) override;
	virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
	virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
	virtual bool windowResizeEvent(int width, int height) override;
	virtual bool keyInputEvent(int key, int action, int mods) override;

	void createShaderProgram();
	void enableVertexAttribIndices();
	void generateVertexBuffers();
	void mapVboDataToVertexAttributeLocation();
	void uploadVertexDataToVbos();

	void initLineData();

	void setLineColour(const glm::vec3 & colour);

	void drawLine (
			const glm::vec2 & v0,
			const glm::vec2 & v1
	);

	void Reset();

	Line CustomClip(glm::vec4 P, glm::vec4 n, Line l);

	ShaderProgram m_shader;

	GLuint m_vao;            // Vertex Array Object
	GLuint m_vbo_positions;  // Vertex Buffer Object
	GLuint m_vbo_colours;    // Vertex Buffer Object

	VertexData m_vertexData;

	glm::vec3 m_currentLineColour;

	int win_w;
	int win_h;
	
	int mode = 0;
	int rot_order_m = 0;
	int rot_order_v = 0;
	float fov=30;
	float far = 50.0f;
	float near = 1.0f;
	glm::vec4 v1 = glm::vec4(-0.9,-0.9,0,1);
	glm::vec4 v2 = glm::vec4(0.9,0.9,0,1);
	glm::mat4 rot_m;

	float tx_m = 0.0f;
	float ty_m = 0.0f;
	float tz_m = 0.0f;
	float alpha_m = 0.0f;
	float beta_m = 0.0f;
	float gamma_m = 0.0f;

	float tx_v = 0.0f;
	float ty_v = 0.0f;
	float tz_v = -15.0f;
	float alpha_v = 0.0f;
	float beta_v = 0.0f;
	float gamma_v = 0.0f;

	float sx = 1.0f;
	float sy = 1.0f;
	float sz = 1.0f;

	float xl0=0; float xm0=0; float xr0=0;
	float xl1=0; float xm1=0; float xr1=0;
	float dxl=0; float dxm=0; float dxr=0;

};
