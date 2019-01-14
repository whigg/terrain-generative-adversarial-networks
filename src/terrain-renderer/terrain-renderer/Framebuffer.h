#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "NonCopyable.h"

template <typename Type>
class Framebuffer : public Noncopyable
{
private:
public:
public:
	Framebuffer() = default;

	Type& operator~() noexcept 
	{
		return *static_cast<Type *>(this);
	}
	Type const& operator~() const noexcept 
	{
		return *static_cast<Type const *>(this);
	}
};

#endif