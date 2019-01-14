#ifndef TERRAIN_APPLICATION_H
#define TERRAIN_APPLICATION_H

#include "Application.h"

class TerrainApplication : public Application
{
private:
protected:
	void initialUpdate(float dt) override;
	void updateScene(float dt)	 override;
	void drawScene(void) const	 override;
	void finalUpdate(float dt)	 override;

	void keyCallback(int key, int scancode, int action, int mode) override;
	void mousePosCallback(double xpos, double ypos)				  override;
	void mouseBtnCallback(int btn, int action, int mods)		  override;
	void scrollCallback(double xoffset, double yoffset)			  override;
public:
	TerrainApplication();
	~TerrainApplication();

	bool initApplication(void);
};

#endif