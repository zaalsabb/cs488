#include "A1.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include <iostream>

#include <sys/types.h>
#include <unistd.h>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

static const size_t DIM = 16;
<<<<<<< HEAD
Maze m(DIM);
=======
>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e

//----------------------------------------------------------------------------------------
// Constructor
A1::A1()
	: current_col( 0 )
{
	colour[0] = 0.0f;
	colour[1] = 0.0f;
	colour[2] = 0.0f;
}

//----------------------------------------------------------------------------------------
// Destructor
A1::~A1()
{}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A1::init()
{
	// Initialize random number generator
	int rseed=getpid();
	srandom(rseed);
	// Print random number seed in case we want to rerun with
	// same random numbers
	cout << "Random number seed = " << rseed << endl;
	
<<<<<<< HEAD
	avatar_x = (int)DIM/2+1;
	avatar_y = (int)DIM/2+1;
=======

	// DELETE FROM HERE...
	Maze m(DIM);
	m.digMaze();
	m.printMaze();
	// ...TO HERE
>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e
	
	// Set the background colour.
	glClearColor( 0.3, 0.5, 0.7, 1.0 );

	// Build the shader
	m_shader.generateProgramObject();
	m_shader.attachVertexShader(
		getAssetFilePath( "VertexShader.vs" ).c_str() );
	m_shader.attachFragmentShader(
		getAssetFilePath( "FragmentShader.fs" ).c_str() );
	m_shader.link();

	// Set up the uniforms
	P_uni = m_shader.getUniformLocation( "P" );
	V_uni = m_shader.getUniformLocation( "V" );
	M_uni = m_shader.getUniformLocation( "M" );
	col_uni = m_shader.getUniformLocation( "colour" );

	initGrid();

	// Set up initial view and projection matrices (need to do this here,
	// since it depends on the GLFW window being set up correctly).
	view = glm::lookAt( 
		glm::vec3( 0.0f, 2.*float(DIM)*2.0*M_SQRT1_2, float(DIM)*2.0*M_SQRT1_2 ),
		glm::vec3( 0.0f, 0.0f, 0.0f ),
		glm::vec3( 0.0f, 1.0f, 0.0f ) );

	proj = glm::perspective( 
		glm::radians( 30.0f ),
		float( m_framebufferWidth ) / float( m_framebufferHeight ),
		1.0f, 1000.0f );
}

void A1::initGrid()
{
	size_t sz = 3 * 2 * 2 * (DIM+3);

	float *verts = new float[ sz ];
	size_t ct = 0;
	for( int idx = 0; idx < DIM+3; ++idx ) {
		verts[ ct ] = -1;
		verts[ ct+1 ] = 0;
		verts[ ct+2 ] = idx-1;
		verts[ ct+3 ] = DIM+1;
		verts[ ct+4 ] = 0;
		verts[ ct+5 ] = idx-1;
		ct += 6;

		verts[ ct ] = idx-1;
		verts[ ct+1 ] = 0;
		verts[ ct+2 ] = -1;
		verts[ ct+3 ] = idx-1;
		verts[ ct+4 ] = 0;
		verts[ ct+5 ] = DIM+1;
		ct += 6;
	}

	// Create the vertex array to record buffer assignments.
	glGenVertexArrays( 1, &m_grid_vao );
	glBindVertexArray( m_grid_vao );

	// Create the cube vertex buffer
	glGenBuffers( 1, &m_grid_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, m_grid_vbo );
	glBufferData( GL_ARRAY_BUFFER, sz*sizeof(float),
		      verts, GL_STATIC_DRAW );

	// Specify the means of extracting the position values properly.
	GLint posAttrib = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr );


	static const GLfloat cube_vertices[] = {
	    -0.5f,-0.5f,-0.5f, 
	    -0.5f,-0.5f, 0.5f,
	    -0.5f, 0.5f, 0.5f, 
	    0.5f, 0.5f,-0.5f, 
	    -0.5f,-0.5f,-0.5f,
	    -0.5f, 0.5f,-0.5f, 
	    0.5f,-0.5f, 0.5f,
	    -0.5f,-0.5f,-0.5f,
	    0.5f,-0.5f,-0.5f,
	    0.5f, 0.5f,-0.5f,
	    0.5f,-0.5f,-0.5f,
	    -0.5f,-0.5f,-0.5f,
	    -0.5f,-0.5f,-0.5f,
	    -0.5f, 0.5f, 0.5f,
	    -0.5f, 0.5f,-0.5f,
	    0.5f,-0.5f, 0.5f,
	    -0.5f,-0.5f, 0.5f,
	    -0.5f,-0.5f,-0.5f,
	    -0.5f, 0.5f, 0.5f,
	    -0.5f,-0.5f, 0.5f,
	    0.5f,-0.5f, 0.5f,
	   0.5f, 0.5f, 0.5f,
	    0.5f,-0.5f,-0.5f,
	    0.5f, 0.5f,-0.5f,
	    0.5f,-0.5f,-0.5f,
	    0.5f, 0.5f, 0.5f,
	    0.5f,-0.5f, 0.5f,
	    0.5f, 0.5f, 0.5f,
	    0.5f, 0.5f,-0.5f,
	    -0.5f, 0.5f,-0.5f,
	    0.5f, 0.5f, 0.5f,
	    -0.5f, 0.5f,-0.5f,
	    -0.5f, 0.5f, 0.5f,
	    0.5f, 0.5f, 0.5f,
	    -0.5f, 0.5f, 0.5f,
	    0.5f,-0.5f, 0.5f
	};

	glGenVertexArrays( 1, &m_cube_vao );
	glBindVertexArray( m_cube_vao );

	glGenBuffers( 1, &m_cube_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, m_cube_vbo );
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// Reset state to prevent rogue code from messing with *my* 
	// stuff!
	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	// OpenGL has the buffer now, there's no need for us to keep a copy.
	delete [] verts;

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A1::appLogic()
{
	// Place per frame, application logic here ...
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A1::guiLogic()
{
	// We already know there's only going to be one window, so for 
	// simplicity we'll store button states in static local variables.
	// If there was ever a possibility of having multiple instances of
	// A1 running simultaneously, this would break; you'd want to make
	// this into instance fields of A1.
	static bool showTestWindow(false);
	static bool showDebugWindow(true);

	ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
	float opacity(0.5f);

	ImGui::Begin("Debug Window", &showDebugWindow, ImVec2(100,100), opacity, windowFlags);
		if( ImGui::Button( "Quit Application" ) ) {
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}

		// Eventually you'll create multiple colour widgets with
		// radio buttons.  If you use PushID/PopID to give them all
		// unique IDs, then ImGui will be able to keep them separate.
		// This is unnecessary with a single colour selector and
		// radio button, but I'm leaving it in as an example.

		// Prefixing a widget name with "##" keeps it from being
		// displayed.

		ImGui::PushID( 0 );
		ImGui::ColorEdit3( "##Colour", colour );
		ImGui::SameLine();
		if( ImGui::RadioButton( "##Col", &current_col, 0 ) ) {
			// Select this colour.
		}
		ImGui::PopID();

/*
		// For convenience, you can uncomment this to show ImGui's massive
		// demonstration window right in your application.  Very handy for
		// browsing around to get the widget you want.  Then look in 
		// shared/imgui/imgui_demo.cpp to see how it's done.
		if( ImGui::Button( "Test Window" ) ) {
			showTestWindow = !showTestWindow;
		}
*/

		ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );

	ImGui::End();

	if( showTestWindow ) {
		ImGui::ShowTestWindow( &showTestWindow );
	}
}

<<<<<<< HEAD

=======
>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e
//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A1::draw()
<<<<<<< HEAD
{	
	
	// Create a global transformation for the model (centre it).
	mat4 W;
=======
{
	// Create a global transformation for the model (centre it).
	mat4 W;
	float height = 0.5f;
>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e
	W = glm::translate( W, vec3( -float(DIM)/2.0f, 0, -float(DIM)/2.0f ) );

	m_shader.enable();
		glEnable( GL_DEPTH_TEST );

		glUniformMatrix4fv( P_uni, 1, GL_FALSE, value_ptr( proj ) );
		glUniformMatrix4fv( V_uni, 1, GL_FALSE, value_ptr( view ) );
		glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( W ) );

		// Just draw the grid for now.
		glBindVertexArray( m_grid_vao );
		glBindBuffer( GL_ARRAY_BUFFER, m_grid_vao );
		glEnableVertexAttribArray( posAttrib );
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glUniform3f( col_uni, 1, 1, 1 );
		glDrawArrays( GL_LINES, 0, (3+DIM)*4 );

		// Draw the cubes
<<<<<<< HEAD
		// setup buffers and color
=======
		// setup buffer
>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e
		glBindVertexArray( m_cube_vao );
		glBindBuffer( GL_ARRAY_BUFFER, m_cube_vbo );
		glEnableVertexAttribArray( posAttrib );
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
<<<<<<< HEAD
		GLint uniformLocation_colour = m_shader.getUniformLocation("colour");

		// Draw maze
	        for( int idy = 0; idy < DIM+2; ++idy )
		{
		    for( int idx = 0; idx < DIM+2; ++idx )
		    {
		        
		        float x = 0.5f-idx+DIM/2;
		        float y = 0.5f-idy+DIM/2;

		        int maze_value = m.getValue(DIM-idy, DIM-idx);

		        if (idx == avatar_x & idy == avatar_y) 
		        {
				mat4 avatar_model;
				glUniform3f(uniformLocation_colour, 0.0f, 1.0f, 0.0f);
			        avatar_model = glm::translate(avatar_model, glm::vec3(x, 0.5f, y));
			        avatar_model = glm::scale(
					avatar_model,
					glm::vec3( 1.0f, 1.0f, 1.0f )
					);
	      		        glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( avatar_model ) );
	   		        glDrawArrays(GL_TRIANGLES, 0, 12*3);				
			}
		        if (maze_value == 1 | (walls_enabled &
			    ( idx == 0 | idx == DIM+1 
		            | idy == 0 | idy == DIM+1))) 
		        {
				mat4 wall_model;
				glUniform3f(uniformLocation_colour, 1.0f, 1.0f, 1.0f);
			        wall_model = glm::translate(wall_model, glm::vec3(x, walls_height/2, y));
			        wall_model = glm::scale(
					wall_model,
					glm::vec3( 1.0f, walls_height, 1.0f )
					);
	      		        glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( wall_model ) );
	   		        glDrawArrays(GL_TRIANGLES, 0, 12*3);
		        } else {

				glUniform3f(uniformLocation_colour, 0.0f, 0.0f, 1.0f);
				mat4 floor_model;
			        floor_model = glm::translate(floor_model, glm::vec3(x, -0.01f, y));
				floor_model = glm::scale(
					floor_model,
					glm::vec3( 1.0f, 0.00001f, 1.0f )
					);
				glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( floor_model ) );
				glDrawArrays(GL_TRIANGLES, 0, 12*3);
}
		    }
		}

	// Highlight the active square.
=======

		// draw vertical edges
	        for( int idx = 0; idx < DIM+2; ++idx )
		{
	            mat4 cube_model;

		    cube_model = glm::translate(cube_model, glm::vec3(-0.5f-DIM/2, 0.0f, 0.5f-idx+DIM/2));
		    cube_model = glm::scale(
				cube_model,
				glm::vec3( 1.0f, height, 1.0f )
				);
      		    glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( cube_model ) );
   		    glDrawArrays(GL_TRIANGLES, 0, 12*3);

		    cube_model = glm::translate(cube_model, glm::vec3(DIM+1, 0.0f, 0.0f));
      		    glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( cube_model ) );
   		    glDrawArrays(GL_TRIANGLES, 0, 12*3);
		}
		// draw horizontal edges
	        for( int idx = 0; idx < DIM+2; ++idx )
		{
	            mat4 cube_model;

		    cube_model = glm::translate(cube_model, glm::vec3(0.5f-idx+DIM/2, 0.0f, -0.5f-DIM/2));
		    cube_model = glm::scale(
				cube_model,
				glm::vec3( 1.0f, height, 1.0f )
				);
      		    glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( cube_model ) );
   		    glDrawArrays(GL_TRIANGLES, 0, 12*3);

		    cube_model = glm::translate(cube_model, glm::vec3(0.0f, 0.0f, DIM+1));
      		    glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( cube_model ) );
   		    glDrawArrays(GL_TRIANGLES, 0, 12*3);
		}

		// Highlight the active square.
>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e
	m_shader.disable();

	// Restore defaults
	glBindVertexArray( 0 );

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A1::cleanup()
{}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A1::cursorEnterWindowEvent (
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
bool A1::mouseMoveEvent(double xPos, double yPos) 
{
	bool eventHandled(false);

	if (!ImGui::IsMouseHoveringAnyWindow()) {
		// Put some code here to handle rotations.  Probably need to
		// check whether we're *dragging*, not just moving the mouse.
		// Probably need some instance variables to track the current
		// rotation amount, and maybe the previous X position (so 
		// that you can rotate relative to the *change* in X.
	}

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A1::mouseButtonInputEvent(int button, int actions, int mods) {
	bool eventHandled(false);

	if (!ImGui::IsMouseHoveringAnyWindow()) {
		// The user clicked in the window.  If it's the left
		// mouse button, initiate a rotation.
	}

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A1::mouseScrollEvent(double xOffSet, double yOffSet) {
	bool eventHandled(false);

	// Zoom in or out.

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool A1::windowResizeEvent(int width, int height) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A1::keyInputEvent(int key, int action, int mods) {
	bool eventHandled(false);

	// Fill in with event handling code...
	if( action == GLFW_PRESS ) {
<<<<<<< HEAD
		if (key == GLFW_KEY_SPACE) {
			cout << "space key pressed" << endl;

			// Increase wall height by 0.5.
			walls_height += 0.5f;

			eventHandled = true;
		} else if (key == GLFW_KEY_BACKSPACE) {
			cout << "backspace key pressed" << endl;

			// decrease wall height by 0.5.
			walls_height -= 0.5f;
			if (walls_height < 0) {walls_height = 0.001f;};

			eventHandled = true;
		} else if (key == GLFW_KEY_D) {
			cout << "D key pressed" << endl;

			walls_enabled = true;
			m.digMaze();
			m.printMaze();
		    	for( int idx = 1; idx < DIM+1; ++idx ) 
			{
			   if (m.getValue(0, DIM-idx)==0){
				avatar_x = idx;
				avatar_y = DIM;
			   }
			}

			eventHandled = true;

		} else if (key == GLFW_KEY_R) {
			cout << "R key pressed" << endl;

			m.reset();
			walls_enabled = false;
			avatar_x = (int)DIM/2+1;
			avatar_y = (int)DIM/2+1;			

			eventHandled = true;
		}
	}



=======
		// Respond to some key events.
	}

>>>>>>> 4a6d78dac86d2e6c8541d35fda7fec12cfe3246e
	return eventHandled;
}
