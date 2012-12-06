/*
 * Planet.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef PLANET_H_
#define PLANET_H_
#include "PhysicsObject.h"
#include <Box2D/Box2D.h>

class Planet : public PhysicsObject {
	public:
		Planet( b2Body* aBody ): PhysicsObject( aBody ) {};
		virtual ~Planet();
//		void draw();
		void drawImp( float volumeScale );
		void update();
		virtual void setupTexture();
};

#endif /* PLANET_H_ */
