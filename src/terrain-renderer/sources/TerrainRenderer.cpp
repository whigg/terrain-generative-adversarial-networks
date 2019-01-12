#include "TerrainRenderer.h"
#include "FileSystem.hpp"
#include "Obfuscator.hpp"

TerrainRenderer::TerrainRenderer() {
}

TerrainRenderer::~TerrainRenderer() {
}

bool TerrainRenderer::initApplication(void)
{
	if (!Application::initContext())
		return false;

	auto& fs = FileSystem::getMutableInstance();
	fs.setRootPath(OBFUSCATE("./"));
	fs.addTable(OBFUSCATE("Material"), OBFUSCATE("resources/texture/"));
	fs.addTable(OBFUSCATE("Resource"), OBFUSCATE("resources/resource/"));
	
	return true;
}

void TerrainRenderer::updateScene(float dt) {
}

void TerrainRenderer::drawScene(void) const {
}

void TerrainRenderer::keyCallback(int key, int scancode, int action, int mode) {
}

void TerrainRenderer::mousePosCallback(double xpos, double ypos) {
}

void TerrainRenderer::mouseBtnCallback(int btn, int action, int mods) {
}

void TerrainRenderer::scrollCallback(double xoffset, double yoffset) {
}

void TerrainRenderer::resizingCallback(int newWidth, int newHeight) {
}
