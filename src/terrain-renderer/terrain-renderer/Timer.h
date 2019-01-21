#ifndef TIMER_H
#define TIMER_H

#include "NonCopyable.h"

class Timer : public NonCopyable
{
private:
	bool bPaused;
public:
	Timer();

	void tick (void);
	void start(void);
	void reset(void);
	void pause(void);
	
	bool isOnGoing(void) const;
	bool isPaused (void) const;

	float getDeltaTime(void) const;
	float getTotalTime(void) const;
};

#endif