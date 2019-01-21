#include "stdafx.h"
#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "Obfuscator.h"

namespace
{
	Application *gApp = nullptr;
}

// local callback functions declaration
void localKeyCallback		( GLFWwindow* window, int key, int scancode, int action, int mode );
void localMousePosCallback	( GLFWwindow* window, double xpos, double ypos					  );
void localMouseBtnCallback	( GLFWwindow* window, int btn, int action, int mods				  );
void localScrollCallback	( GLFWwindow* window, double xoffset, double yoffset			  );
void localResizingCallback	( GLFWwindow* window, int newWidth, int newHeight				  );

Application::Application()
{
	gApp = this;
}

Application::~Application()
{
	glfwTerminate();
	gApp = nullptr;
}

bool Application::initContext(void)
{
	if (!glfwInit())
	{
		ERROR_LOG(OBFUSCATE("GLFW initialization failed."));
		return false;
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4				  );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3				  );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_SAMPLES, 4								  );
	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE					  );

#ifdef __APPLE__ 
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_FORWARD_COMPAT);
#endif

	GLFWmonitor		  *glfwMonitor	= glfwGetPrimaryMonitor();
	GLFWvidmode const *glfwMode		= glfwGetVideoMode(glfwMonitor);

	glfwWindowHint( GLFW_RED_BITS, glfwMode->redBits		 );
	glfwWindowHint( GLFW_GREEN_BITS, glfwMode->greenBits	 );
	glfwWindowHint( GLFW_BLUE_BITS, glfwMode->blueBits		 );
	glfwWindowHint( GLFW_REFRESH_RATE, glfwMode->refreshRate );
	glfwWindowHint( GLFW_SRGB_CAPABLE, GLFW_TRUE			 );

#ifdef _DEBUG
	clientWidth  = 1600;
	clientHeight = 900;
	glfwMonitor  = nullptr;
#else
	clientWidth  = glfwMode->width;
	clientHeight = glfwMode->height;
#endif

	window = glfwCreateWindow(clientWidth, clientHeight, "Terrain Simulation", glfwMonitor, nullptr);

	if (!window)
	{
		glfwTerminate();
		ERROR_LOG(OBFUSCATE("GLFW Window Creating failed."));
		return false;
	}


	glfwMakeContextCurrent(window);

	int e = glewInit();
	if (e != GLEW_OK)
	{
		ERROR_LOG("Failed to init GLEW\nError{}", glewGetErrorString(e));
		return false;
	}

#define CHECK_EXTENSION(ext) if(!glewGetExtension("GL_ARB_"#ext)){ ERROR_LOG( "GLEW: GL_ARB_{} not supported.\n", #ext ); return false; }
	CHECK_EXTENSION(shading_language_100);	// check your platform supports GLSL
	CHECK_EXTENSION(vertex_buffer_object);	// BindBuffers, DeleteBuffers, GenBuffers, IsBuffer, BufferData, BufferSubData, GenBufferSubData, ...
	CHECK_EXTENSION(vertex_shader);			// functions related to vertex shaders
	CHECK_EXTENSION(fragment_shader);			// functions related to fragment shaders
	CHECK_EXTENSION(shader_objects);			// functions related to program and shaders
#undef CHECK_EXTENSION

	const GLubyte* vendor	= glGetString(GL_VENDOR	 );
	const GLubyte* renderer = glGetString(GL_RENDERER);

	INFO_LOG( OBFUSCATE("Vendor : {:<15}, Renderer : {:<15}"), vendor, renderer );

	registerCallback();

	return true;
}

void Application::registerCallback(void)
{
	glfwSetKeyCallback			  ( window, localKeyCallback				  );
	glfwSetMouseButtonCallback	  ( window, localMouseBtnCallback			  );
	glfwSetCursorPosCallback	  ( window, localMousePosCallback			  );
	glfwSetFramebufferSizeCallback( window, localResizingCallback			  );
	glfwSetScrollCallback		  ( window, localScrollCallback				  );
	glfwSetInputMode			  ( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
}

int Application::runApplicationLoop(void)
{
	//timer reset
	while (!glfwWindowShouldClose(window)) 
	{
		float dt = 0.03f; // timer.getDeltaTime();

		initialUpdate(dt);
		updateScene(dt);
		finalUpdate(dt);

		drawScene();
			   
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void Application::resizingCallback(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

void localKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	gApp->keyCallback(key, scancode, action, mode);
}

void localMousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	gApp->mousePosCallback(xpos, ypos);
}

void localMouseBtnCallback(GLFWwindow* window, int btn, int action, int mods)
{
	gApp->mouseBtnCallback(btn, action, mods);
}

void localScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	gApp->scrollCallback(xoffset, yoffset);
}

void localResizingCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	if (newWidth == 0)  newWidth  = 1;
	if (newHeight == 0) newHeight = 1;

	gApp->resizingCallback(newWidth, newHeight);
}