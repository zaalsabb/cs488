#pragma once

#include <glm/glm.hpp>

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include "maze.hpp"

class A1 : public CS488Window {
public:
	A1();
	virtual ~A1();

protected:
	virtual void init() override;
	virtual void appLogic() override;
	virtual void guiLogic() override;
	virtual void draw() override;
	virtual void cleanup() override;
	virtual void Reset();

	virtual bool cursorEnterWindowEvent(int entered) override;
	virtual bool mouseMoveEvent(double xPos, double yPos) override;
	virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
	virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
	virtual bool windowResizeEvent(int width, int height) override;
	virtual bool keyInputEvent(int key, int action, int mods) override;

private:
	void initGrid();

	// Fields related to the shader and uniforms.
	ShaderProgram m_shader;
	GLint P_uni; // Uniform location for Projection matrix.
	GLint V_uni; // Uniform location for View matrix.
	GLint M_uni; // Uniform location for Model matrix.
	GLint col_uni;   // Uniform location for cube colour.

	// Fields related to grid geometry.
	GLuint m_grid_vao; // Vertex Array Object
	GLuint m_grid_vbo; // Vertex Buffer Object

	GLuint m_cube_vao; // Vertex Array Object
	GLuint m_cube_vbo; // Vertex Buffer Object

	GLuint m_sphere_vao; // Vertex Array Object
	GLuint m_sphere_vbo; // Vertex Buffer Object
	int sphere_size;

	float walls_height = 1.0f;
	bool walls_enabled;
	int avatar_pos[2];

	GLint posAttrib;

	// Matrices controlling the camera and projection.
	glm::mat4 proj;
	glm::mat4 view;

	float colour[3];
	int current_col;

	float floor_color[3] = {0.0f,0.0f,0.0f};
	float wall_color[3] = {1.0f,1.0f,0.0f};
	float avatar_color[3] = {0.0f,1.0f,0.0f};

	float zoom = 1.0f;
	float rot = 0.0f;
	int xPos0 = 0;

};
