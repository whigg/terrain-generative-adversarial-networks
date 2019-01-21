#include "stdafx.h"
#include "Framebuffer.h"

bool Framebuffer::initFramebuffer(int width, int height)
{
	bufferSize = ivec2(width, height);


	return true;
}

void Framebuffer::attachColorTexture(int width, int height)
{
}

void Framebuffer::attachDepthTexture(int width, int height)
{
}

void Framebuffer::bindBuffer(void) const
{
}

void Framebuffer::unbindBuffer(void) const
{
}
