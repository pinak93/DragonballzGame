#include <iostream>
#include <cmath>
#include "explodingprojectile.h"



ExplodingProjectile::~ExplodingProjectile() { 
}

void ExplodingProjectile::draw() const { 
  Main[currentFrame]->draw(getX(), getY(), getScale());
}
void ExplodingProjectile::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;

		timeSinceLastFrame = 0;
	}
}
void ExplodingProjectile::update(Uint32 ticks) { 
advanceFrame(ticks);
	
	if(numberOfFrames-1==currentFrame)
	{
		DoneExploding=true;
	}
	
}