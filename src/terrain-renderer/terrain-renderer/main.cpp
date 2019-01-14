#include "stdafx.h"
#include "Logger.h"

#include "TerrainApplication.h"

int main(void) 
{
	INIT_LOGGER();

	TerrainApplication app;
	if (app.initApplication() == false)
	{
		ERROR_LOG("Failed to init opengl context");
		return -1;
	}

	return app.runApplicationLoop();
}