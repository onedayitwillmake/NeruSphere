/*
 * WorldController.h
 *
 *  Created on: Sep 23, 2011
 *      Author: onedayitwillmake
 *
 *      A lot of this stuff is appreciatively taken from
 *      David Wicks' excellent Box2D Cinder Block: https://github.com/sansumbrella/sc-Box2D/
 */

#ifndef WORLDCONTROLLER_H_
#define WORLDCONTROLLER_H_
#include <Box2D/Box2D.h>
class WorldController
{
	public:
		WorldController();
		virtual ~WorldController();


		///// ACCESSORS
		b2World* getWorld() { return _world; };

		///// METHODS
		void init( int velocityIterations, int positionIterations );
		void update();
		void clear();
		void removeDeadElements();
		void debugDraw( bool drawBodies=true, bool drawContacts=true );
		void draw();

	private:
		b2World* _world;
};

#endif /* WORLDCONTROLLER_H_ */
