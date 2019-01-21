#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "NonCopyable.h"
#include <stdint.h>
#include <vector>
#include "cgmath.h"

class Framebuffer : public NonCopyable
{
protected:
	std::vector<uint32_t> colorTextures;
	ivec2			 bufferSize;
	uint32_t		 depthTexture;
public:
	Framebuffer() = default;

	virtual bool initFramebuffer(int width, int height);
	
	void attachColorTexture(int width, int height);
	void attachDepthTexture(int width, int height);
	void bindBuffer		   (void) const;
	void unbindBuffer	   (void) const;

	uint32_t getColorTexture(int index) const
	{
		return colorTextures[index];
	}
	uint32_t getDepthTexture(void) const
	{
		return depthTexture;
	}
	ivec2    getBufferSize  (void) const
	{
		return bufferSize;
	}
};

#endif