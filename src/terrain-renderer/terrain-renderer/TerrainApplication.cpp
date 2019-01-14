#include "stdafx.h"
#include "TerrainApplication.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

TerrainApplication::TerrainApplication()
{
}

TerrainApplication::~TerrainApplication()
{
}

bool TerrainApplication::initApplication(void)
{
	if (Application::initContext() == false)
		return false;



	return true;
}

void TerrainApplication::initialUpdate(float dt)
{
}

void TerrainApplication::updateScene(float dt)
{
}

void TerrainApplication::drawScene(void) const
{
}

void TerrainApplication::finalUpdate(float dt)
{
}

void TerrainApplication::keyCallback(int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void TerrainApplication::mousePosCallback(double xpos, double ypos)
{
}

void TerrainApplication::mouseBtnCallback(int btn, int action, int mods)
{
}

void TerrainApplication::scrollCallback(double xoffset, double yoffset)
{
}