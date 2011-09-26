/*
 * PhysicsObject.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef PHYSICSOBJECT_H_
#define PHYSICSOBJECT_H_
#include <Box2D/Box2D.h>
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

class PhysicsObject
{
	public:
		PhysicsObject( b2Body* aBody );
		virtual ~PhysicsObject();


		// Updates thebody
		void update();
		// Draws the body
		void draw();
		void debugDraw();

		///// ACCESSORS
		b2Body*getBody() const { return _body; }
		void setBody( b2Body* aBody );
		bool isDead() { return false; };

	protected:
		void setupTexture();

		// Applies radial gravity - assumes center is in physics units
		void applyRadialGravity( b2Vec2 center );
		// Applies perlin noise to the bodies motion
		void applyNoise();
		// Limits linearvelocity of the object
		void limitSpeed();

		b2Body * _body;
		float _radius;
		int	_lifetime;
		int _age;
		float _agePer;

		ci::gl::Texture texture;
};

#endif /* PHYSICSOBJECT_H_ */