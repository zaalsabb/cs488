#include "A2.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include <iostream>
using namespace std;

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <math.h>
using namespace glm;
float PI = 3.1415;
//----------------------------------------------------------------------------------------
// Constructor
VertexData::VertexData()
	: numVertices(0),
	  index(0)
{
	positions.resize(kMaxVertices);
	colours.resize(kMaxVertices);
}


//----------------------------------------------------------------------------------------
// Constructor
A2::A2()
	: m_currentLineColour(vec3(0.0f))
{

}

//----------------------------------------------------------------------------------------
// Destructor
A2::~A2()
{

}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A2::init()
{
	// Set the background colour.
	glClearColor(0.3, 0.5, 0.7, 1.0);

	createShaderProgram();

	glGenVertexArrays(1, &m_vao);

	enableVertexAttribIndices();

	generateVertexBuffers();

	mapVboDataToVertexAttributeLocation();
}

//----------------------------------------------------------------------------------------
void A2::createShaderProgram()
{
	m_shader.generateProgramObject();
	m_shader.attachVertexShader( getAssetFilePath("VertexShader.vs").c_str() );
	m_shader.attachFragmentShader( getAssetFilePath("FragmentShader.fs").c_str() );
	m_shader.link();
}

//---------------------------------------------------------------------------------------- Spring 2020
void A2::enableVertexAttribIndices()
{
	glBindVertexArray(m_vao);

	// Enable the attribute index location for "position" when rendering.
	GLint positionAttribLocation = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray(positionAttribLocation);

	// Enable the attribute index location for "colour" when rendering.
	GLint colourAttribLocation = m_shader.getAttribLocation( "colour" );
	glEnableVertexAttribArray(colourAttribLocation);

	// Restore defaults
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
void A2::generateVertexBuffers()
{
	// Generate a vertex buffer to store line vertex positions
	{
		glGenBuffers(1, &m_vbo_positions);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);

		// Set to GL_DYNAMIC_DRAW because the data store will be modified frequently.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * kMaxVertices, nullptr,
				GL_DYNAMIC_DRAW);


		// Unbind the target GL_ARRAY_BUFFER, now that we are finished using it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}

	// Generate a vertex buffer to store line colors
	{
		glGenBuffers(1, &m_vbo_colours);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colours);

		// Set to GL_DYNAMIC_DRAW because the data store will be modified frequently.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * kMaxVertices, nullptr,
				GL_DYNAMIC_DRAW);


		// Unbind the target GL_ARRAY_BUFFER, now that we are finished using it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}
}

//----------------------------------------------------------------------------------------
void A2::mapVboDataToVertexAttributeLocation()
{
	// Bind VAO in order to record the data mapping.
	glBindVertexArray(m_vao);

	// Tell GL how to map data from the vertex buffer "m_vbo_positions" into the
	// "position" vertex attribute index for any bound shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
	GLint positionAttribLocation = m_shader.getAttribLocation( "position" );
	glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Tell GL how to map data from the vertex buffer "m_vbo_colours" into the
	// "colour" vertex attribute index for any bound shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colours);
	GLint colorAttribLocation = m_shader.getAttribLocation( "colour" );
	glVertexAttribPointer(colorAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//---------------------------------------------------------------------------------------
void A2::initLineData()
{
	m_vertexData.numVertices = 0;
	m_vertexData.index = 0;
}

//---------------------------------------------------------------------------------------
void A2::setLineColour (
		const glm::vec3 & colour
) {
	m_currentLineColour = colour;
}

//---------------------------------------------------------------------------------------
void A2::drawLine(
		const glm::vec2 & V0,   // Line Start (NDC coordinate)
		const glm::vec2 & V1    // Line End (NDC coordinate)
) {

	m_vertexData.positions[m_vertexData.index] = V0;
	m_vertexData.colours[m_vertexData.index] = m_currentLineColour;
	++m_vertexData.index;
	m_vertexData.positions[m_vertexData.index] = V1;
	m_vertexData.colours[m_vertexData.index] = m_currentLineColour;
	++m_vertexData.index;

	m_vertexData.numVertices += 2;
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A2::appLogic()
{
	// Place per frame, application logic here ...

	// Call at the beginning of frame, before drawing lines:
	initLineData();

	// Draw outer square:
	//setLineColour(vec3(1.0f, 0.7f, 0.8f));
	//drawLine(vec2(-0.75f, -0.75f), vec2(0.75f, -0.75f));
	//drawLine(vec2(0.75f, -0.75f), vec2(0.75f, 0.75f));
	//drawLine(vec2(0.75f, 0.75f), vec2(-0.75f, 0.75f));
	//drawLine(vec2(-0.75f, 0.75f), vec2(-0.75f, -0.75f));


	//Define generic rotation matrices and a translation matrix
    	glm::mat4 Rx = glm::mat4( 1.0 );
    	glm::mat4 Ry = glm::mat4( 1.0 );
    	glm::mat4 Rz = glm::mat4( 1.0 );
	glm::mat4 rot = glm::mat4( 1.0 );
    	glm::mat4 transl = glm::mat4( 1.0 );
    	glm::mat4 scale = glm::mat4( 1.0 );

	// define lookat transformation
    	Rx[ 1 ] = glm::vec4(0.0f,  cos(alpha_v), sin(alpha_v), 0.0f);
    	Rx[ 2 ] = glm::vec4(0.0f, -sin(alpha_v), cos(alpha_v), 0.0f);

    	Ry[ 0 ] = glm::vec4(cos(beta_v), 0.0f, -sin(beta_v), 0.0f);
    	Ry[ 2 ] = glm::vec4(sin(beta_v), 0.0f,  cos(beta_v), 0.0f);

    	Rz[ 0 ] = glm::vec4( cos(gamma_v), sin(gamma_v), 0.0f, 0.0f);
    	Rz[ 1 ] = glm::vec4(-sin(gamma_v), cos(gamma_v), 0.0f, 0.0f);

	if (rot_order_v==0)
	{
	    	rot = Rz*Ry*Rx;
	} else if (rot_order_v==1)
	{
	    	rot = Rx*Rz*Ry;
	} else if (rot_order_v==2)
	{
	    	rot = Ry*Rx*Rz;
	}
	rot[2] = -1.0f*rot[2];
	rot = glm::transpose(rot);
    	transl[ 3 ] = glm::vec4(-tx_v, -ty_v, -tz_v, 1.0f);

    	glm::mat4 L = rot*transl;

	// define model transformation
    	transl[ 3 ] = glm::vec4( tx_m, ty_m, tz_m, 1.0f );

    	Rx[ 1 ] = glm::vec4(0.0f,  cos(alpha_m), sin(alpha_m), 0.0f);
    	Rx[ 2 ] = glm::vec4(0.0f, -sin(alpha_m), cos(alpha_m), 0.0f);

    	Ry[ 0 ] = glm::vec4(cos(beta_m), 0.0f, -sin(beta_m), 0.0f);
    	Ry[ 2 ] = glm::vec4(sin(beta_m), 0.0f,  cos(beta_m), 0.0f);

    	Rz[ 0 ] = glm::vec4(cos(gamma_m),  sin(gamma_m), 0.0f, 0.0f);
    	Rz[ 1 ] = glm::vec4(-sin(gamma_m), cos(gamma_m), 0.0f, 0.0f);

	scale[0][0] = sx*scale[0][0];
	scale[1][1] = sy*scale[1][1];
	scale[2][2] = sz*scale[2][2];

	if (rot_order_m==0)
	{
	    	rot = Rz*Ry*Rx;
	} else if (rot_order_m==1)
	{
	    	rot = Rx*Rz*Ry;
	} else if (rot_order_m==2)
	{
	    	rot = Ry*Rx*Rz;
	}

	rot_m = rot;
	//transl[3]=rot*transl[3];

	glm::mat4 T = transl*rot; 

    	glm::mat4 P = glm::mat4( 1.0 );

	float S = 1/tan(fov/2*PI/180); 
    	P[ 0 ] = glm::vec4(S, 0.0f, 0.0f, 0.0f);
    	P[ 1 ] = glm::vec4(0.0f, S, 0.0f, 0.0f);
    	P[ 2 ] = glm::vec4(0.0f, 0.0f, -1.0f*(far+near)/(far-near), -1.0f);
    	P[ 3 ] = glm::vec4(0.0f, 0.0f, -2.0f*far*near/(far-near),    0.0f);

	//combine transformations
	glm::mat4 LTS = L*T*scale;
	glm::mat4 LT = L*T;

	// Draw cube	
	std::vector<glm::vec4> vert;
	vert.push_back(glm::vec4(1,1,1,1));
	vert.push_back(glm::vec4(-1,1,1,1));
	vert.push_back(glm::vec4(-1,1,1,1));
	vert.push_back(glm::vec4(-1,-1,1,1));
	vert.push_back(glm::vec4(-1,-1,1,1));
	vert.push_back(glm::vec4(1,-1,1,1));
	vert.push_back(glm::vec4(1,-1,1,1));
	vert.push_back(glm::vec4(1,1,1,1));	

	vert.push_back(glm::vec4(1,1,-1,1));
	vert.push_back(glm::vec4(-1,1,-1,1));
	vert.push_back(glm::vec4(-1,1,-1,1));
	vert.push_back(glm::vec4(-1,-1,-1,1));
	vert.push_back(glm::vec4(-1,-1,-1,1));
	vert.push_back(glm::vec4(1,-1,-1,1));
	vert.push_back(glm::vec4(1,-1,-1,1));
	vert.push_back(glm::vec4(1,1,-1,1));

	vert.push_back(glm::vec4(1,1,1,1));
	vert.push_back(glm::vec4(1,1,-1,1));
	vert.push_back(glm::vec4(-1,1,1,1));
	vert.push_back(glm::vec4(-1,1,-1,1));
	vert.push_back(glm::vec4(-1,-1,1,1));
	vert.push_back(glm::vec4(-1,-1,-1,1));
	vert.push_back(glm::vec4(1,-1,1,1));
	vert.push_back(glm::vec4(1,-1,-1,1));

	for (int i=0; i<vert.size(); i++) {
	  vert[i] = LTS*vert[i];	 
	  vert[i] = vert[i]/vert[i].w;
	}

	setLineColour(vec3(1.0f, 1.0f, 1.0f));

	for (int i=0; i<vert.size()/2; i++) {
	  Line line;
	  line.A = vert[i*2];
	  line.B = vert[i*2+1];

    	  //std::cout << line.A.z << ' ';

	  line = CustomClip(vec4(0,0,-near,1), vec4(0,0,-1,0), line);
	  line = CustomClip(vec4(0,0,-far,1), vec4(0,0,1,0), line);

	  line.A = P*line.A;
	  line.A = line.A/line.A.w;
	  line.B = P*line.B;
	  line.B = line.B/line.B.w;

	  line = CustomClip(vec4(-1,-1,0,1), vec4(1,0,0,0), line);
	  line = CustomClip(vec4(-1,-1,0,1), vec4(0,1,0,0), line);
	  line = CustomClip(vec4( 1, 1,0,1), vec4(-1,0,0,0), line);
	  line = CustomClip(vec4( 1, 1,0,1), vec4(0,-1,0,0), line);

	  line.A = line.A*(v2-v1)/2.0f+(v1+v2)/2.0f;
	  line.B = line.B*(v2-v1)/2.0f+(v1+v2)/2.0f;

	  drawLine(vec2(line.A.x, line.A.y), vec2(line.B.x, line.B.y)); 

	}

	// Draw cube local axes	
	vert[0]=glm::vec4(0,0,0,1);
	vert[1]=glm::vec4(1,0,0,1);
	vert[2]=glm::vec4(0,0,0,1);
	vert[3]=glm::vec4(0,1,0,1);
	vert[4]=glm::vec4(0,0,0,1);
	vert[5]=glm::vec4(0,0,1,1);

	for (int i=0; i<6; i++) {
	  vert[i] = LT*vert[i];	 
	  vert[i] = vert[i]/vert[i].w;
	}

	Line line;

	
	for (int i=0; i<3; i++) {
	
	  if (i == 0) {
	    setLineColour(vec3(1.0f, 0.0f, 0.0f));
	  } else if (i==1) {
	    setLineColour(vec3(0.0f, 1.0f, 0.0f));
	  } else if (i==2) {
	    setLineColour(vec3(0.0f, 0.0f, 1.0f));
	  }
	  Line line;
	  line.A = vert[i*2];
	  line.B = vert[i*2+1];

    	  //std::cout << line.A.z << ' ';

	  line = CustomClip(vec4(0,0,-near,1), vec4(0,0,-1,0), line);
	  line = CustomClip(vec4(0,0,-far,1), vec4(0,0,1,0), line);

	  line.A = P*line.A;
	  line.A = line.A/line.A.w;
	  line.B = P*line.B;
	  line.B = line.B/line.B.w;

	  line = CustomClip(vec4(-1,-1,0,1), vec4(1,0,0,0), line);
	  line = CustomClip(vec4(-1,-1,0,1), vec4(0,1,0,0), line);
	  line = CustomClip(vec4( 1, 1,0,1), vec4(-1,0,0,0), line);
	  line = CustomClip(vec4( 1, 1,0,1), vec4(0,-1,0,0), line);

	  line.A = line.A*(v2-v1)/2.0f+(v1+v2)/2.0f;
	  line.B = line.B*(v2-v1)/2.0f+(v1+v2)/2.0f;

	  drawLine(vec2(line.A.x, line.A.y), vec2(line.B.x, line.B.y)); 

	}

	// Draw world axes	
	vert[0]=glm::vec4(0,0,0,1);
	vert[1]=glm::vec4(1,0,0,1);
	vert[2]=glm::vec4(0,0,0,1);
	vert[3]=glm::vec4(0,1,0,1);
	vert[4]=glm::vec4(0,0,0,1);
	vert[5]=glm::vec4(0,0,1,1);

	for (int i=0; i<6; i++) {
	  vert[i] = L*vert[i];	 
	  vert[i] = vert[i]/vert[i].w;
	}

	for (int i=0; i<3; i++) {
	
	  if (i == 0) {
	    setLineColour(vec3(1.0f, 1.0f, 0.0f));
	  } else if (i==1) {
	    setLineColour(vec3(1.0f, 0.0f, 1.0f));
	  } else if (i==2) {
	    setLineColour(vec3(0.0f, 1.0f, 1.0f));
	  }
	  Line line;
	  line.A = vert[i*2];
	  line.B = vert[i*2+1];

    	  //std::cout << line.A.z << ' ';

	  line = CustomClip(vec4(0,0,-near,1), vec4(0,0,-1,0), line);
	  line = CustomClip(vec4(0,0,-far, 1), vec4(0,0, 1,0), line);

	  line.A = P*line.A;
	  line.A = line.A/line.A.w;
	  line.B = P*line.B;
	  line.B = line.B/line.B.w;

	  line = CustomClip(vec4(-1,-1,0,1), vec4(1,0,0,0), line);
	  line = CustomClip(vec4(-1,-1,0,1), vec4(0,1,0,0), line);
	  line = CustomClip(vec4( 1, 1,0,1), vec4(-1,0,0,0), line);
	  line = CustomClip(vec4( 1, 1,0,1), vec4(0,-1,0,0), line);

	  line.A = line.A*(v2-v1)/2.0f+(v1+v2)/2.0f;
	  line.B = line.B*(v2-v1)/2.0f+(v1+v2)/2.0f;

	  drawLine(vec2(line.A.x, line.A.y), vec2(line.B.x, line.B.y)); 
	}

	setLineColour(vec3(1.0f, 0.0f, 1.0f));
	drawLine(vec2(v1.x, v1.y), vec2(v2.x, v1.y)); 
	drawLine(vec2(v2.x, v1.y), vec2(v2.x, v2.y)); 
	drawLine(vec2(v2.x, v2.y), vec2(v1.x, v2.y)); 
	drawLine(vec2(v1.x, v2.y), vec2(v1.x, v1.y)); 
}

Line A2::CustomClip(glm::vec4 P, glm::vec4 n, Line l)
{	
	float t;

	if (glm::dot(l.A-P,n) < 0 & glm::dot(l.B-P,n) < 0){
	  l.A= glm::vec4(0,0,0,1);
	  l.B= glm::vec4(0,0,0,1);
	}

	else if (glm::dot(l.A-P,n) > 0 & glm::dot(l.B-P,n) < 0){
	  t = glm::dot(l.A-P,n) / glm::dot(l.A-l.B,n);
	  l.B = l.A+(l.B-l.A)*t;
	}

	else if (glm::dot(l.A-P,n) < 0 & glm::dot(l.B-P,n) > 0){
	  t = glm::dot(l.B-P,n) / glm::dot(l.B-l.A,n);
	  l.A = l.B+(l.A-l.B)*t;
	}
	return l;
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A2::guiLogic()
{
	static bool firstRun(true);
	if (firstRun) {
		ImGui::SetNextWindowPos(ImVec2(50, 50));
		firstRun = false;
	}

	static bool showDebugWindow(true);
	ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
	float opacity(0.5f);

	ImGui::Begin("Properties", &showDebugWindow, ImVec2(100,100), opacity,
			windowFlags);


		if( ImGui::RadioButton( "Rotate View      (O)", &mode, 0 ) ) {}
		if( ImGui::RadioButton( "Translate View   (E)", &mode, 1 ) ) {}
		if( ImGui::RadioButton( "Perspective      (P)", &mode, 2 ) ) {}
		if( ImGui::RadioButton( "Rotate Model     (R)", &mode, 3 ) ) {}
		if( ImGui::RadioButton( "Translate Model  (T)", &mode, 4 ) ) {}
		if( ImGui::RadioButton( "Scale Model      (S)", &mode, 5 ) ) {}
		if( ImGui::RadioButton( "Viewport         (V)", &mode, 6 ) ) {}
				      
		// Create Button, and check if it was clicked:
		if( ImGui::Button( "Reset              (A)" ) ) {
			Reset();
		}
		if( ImGui::Button( "Quit Application   (Q)" ) ) {
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}


		ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );
		ImGui::Text( "Near: %.1f, Far: %.1f", near, far );
		ImGui::Text( "fov: %.1f deg", fov );

	ImGui::End();
}

//----------------------------------------------------------------------------------------
void A2::uploadVertexDataToVbos() {

	//-- Copy vertex position data into VBO, m_vbo_positions:
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec2) * m_vertexData.numVertices,
				m_vertexData.positions.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}

	//-- Copy vertex colour data into VBO, m_vbo_colours:
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colours);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * m_vertexData.numVertices,
				m_vertexData.colours.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A2::draw()
{
	uploadVertexDataToVbos();

	glBindVertexArray(m_vao);

	m_shader.enable();
		glDrawArrays(GL_LINES, 0, m_vertexData.numVertices);
	m_shader.disable();

	// Restore defaults
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A2::cleanup()
{

}

void A2::Reset(){

	mode=0;
	rot_order_m = 0;
	rot_order_v = 0;
	fov=30;
	far = 50.0f;
	near = 1.0f;
	v1 = glm::vec4(-0.9,-0.9,0,1);
	v2 = glm::vec4(0.9,0.9,0,1);

	tx_m = 0.0f;
	ty_m = 0.0f;
	tz_m = 0.0f;
	alpha_m = 0.0f;
	beta_m = 0.0f;
	gamma_m = 0.0f;

	tx_v = 0.0f;
	ty_v = 0.0f;
	tz_v = -15.0f;
	alpha_v = 0.0f;
	beta_v = 0.0f;
	gamma_v = 0.0f;

	sx = 1.0f;
	sy = 1.0f;
	sz = 1.0f;

}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A2::cursorEnterWindowEvent (
		int entered
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse cursor movement events.
 */
bool A2::mouseMoveEvent (
		double xPos,
		double yPos
) {
	bool eventHandled(false);

	if (!ImGui::IsMouseHoveringAnyWindow()) {
		xl1=xPos;
		xm1=xPos;
		xr1=xPos;
		if (ImGui::IsMouseDragging(0))
		{
			dxl = xl1-xl0;
			xl0 = xl1;
			if (mode == 0) {rot_order_v=0;}			
			if (mode == 3) {rot_order_m=0;}			
		} else if (ImGui::IsMouseDown(0))
		{
			xl0 = xl1;
		} else {dxl = 0;}

		if (ImGui::IsMouseDragging(2))
		{
			dxm = xm1-xm0;
			xm0 = xm1;
			if (mode == 0) {rot_order_v=1;}			
			if (mode == 3) {rot_order_m=1;}
		} else if (ImGui::IsMouseDown(2))
		{
			xm0 = xm1;
			dxm=0;
		} else {dxm = 0;}

		if (ImGui::IsMouseDragging(1))
		{
			dxr = xr1-xr0;
			xr0 = xr1;
			if (mode == 0) {rot_order_v=2;}			
			if (mode == 3) {rot_order_m=2;}
		} else if (ImGui::IsMouseDown(1))
		{
			xr0 = xr1;
			dxr = 0;
		} else {dxr = 0;}
	}

	if (mode == 0){
		alpha_v += dxl/1500;
		beta_v += dxm/1500;
		gamma_v += dxr/500;

	} else if (mode == 1){
		tx_v += dxl/200;
		ty_v += dxm/200;
		tz_v += dxr/200;

	} else if (mode == 2) {
		fov += dxl/20;
		near += dxm/100;
		far += dxr/100;
		if (near <= 0){near=0.01f;}
		if (far  <= 0){far =0.02f;}

		if (fov  < 5){fov =5;}
		if (fov  > 160){fov =160;}

	} else if (mode == 3) {
		alpha_m += dxl/100;
		beta_m += dxm/100;
		gamma_m += dxr/100;

	} else if (mode == 4) {
		vec4 d = vec4(dxl/200,dxm/200,dxr/200,1);
		d = rot_m*d;
		tx_m += d.x;
		ty_m += d.y;
		tz_m += d.z;

	} else if (mode == 5) {
		sx += dxl/100;
		sy += dxm/100;
		sz += dxr/100;

	} else if (mode == 6) {

		if (!ImGui::IsMouseHoveringAnyWindow()) {
			if (ImGui::IsMouseDragging(0))
			{
				v2 = vec4(xPos/win_w*2-1,1-yPos/win_h*2,0,1);
				if (v2.x < -1){v2.x=-1;}
				if (v2.y < -1){v2.y=-1;}
				if (v2.x >  1){v2.x=1;}
				if (v2.y >  1){v2.y=1;}
			} else if (ImGui::IsMouseDown(0))
			{
				v1 = vec4(xPos/win_w*2-1,1-yPos/win_h*2,0,1);
				if (v1.x < -1){v1.x=-1;}
				if (v1.y < -1){v1.y=-1;}
				if (v1.x >  1){v1.x=1;}
				if (v1.y >  1){v1.y=1;}

			}
		}
	}
	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A2::mouseButtonInputEvent (
		int button,
		int actions,
		int mods
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A2::mouseScrollEvent (
		double xOffSet,
		double yOffSet
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool A2::windowResizeEvent (
		int width,
		int height
) {
	bool eventHandled(false);

	win_w = width;
	win_h = height;

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A2::keyInputEvent (
		int key,
		int action,
		int mods
) {
	bool eventHandled(false);

	if (key == GLFW_KEY_O) {
		cout << "O key pressed" << endl;
		mode = 0;
		eventHandled = true;
	} else if (key == GLFW_KEY_E) {
		cout << "E key pressed" << endl;
		mode=1;
		eventHandled = true;
	} else if (key == GLFW_KEY_P) {
		cout << "P key pressed" << endl;
		mode=2;
		eventHandled = true;
	} else if (key == GLFW_KEY_R) {
		cout << "R key pressed" << endl;
		mode=3;
		eventHandled = true;
	} else if (key == GLFW_KEY_T) {
		cout << "T key pressed" << endl;
		mode=4;
		eventHandled = true;
	} else if (key == GLFW_KEY_S) {
		cout << "S key pressed" << endl;
		mode=5;
		eventHandled = true;
	} else if (key == GLFW_KEY_V) {
		cout << "V key pressed" << endl;
		mode=6;
		eventHandled = true;
	} else if (key == GLFW_KEY_A) {
		cout << "A key pressed" << endl;
		Reset();
		eventHandled = true;
	} else if (key == GLFW_KEY_Q) {
		cout << "Q key pressed" << endl;
		glfwSetWindowShouldClose(m_window, GL_TRUE);
		eventHandled = true;
	}

	return eventHandled;
}
