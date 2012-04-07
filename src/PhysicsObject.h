/*
 * PhysicsObject.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef PHYSICSOBJECT_H_
#define PHYSICSOBJECT_H_
#include <Box2D/Box2D.h>
#include "cinder/gl/Texture.h"
#include "cinder/Timeline.h"
#include "ParticleSystem.h"


#include "boost/function.hpp"

class PhysicsObject
{
	public:
		enum PhsyicsObjectState {
			ACTIVE,
			EXPLODING
		}
		;
		PhysicsObject( b2Body* aBody );
		virtual ~PhysicsObject();


		// Particles
		particle::ParticleSystem* emitter;

		// Updates thebody
		virtual void update();

		// Draws the body
		virtual void draw();
		virtual void setupTexture();
		void debugDraw();

		///// ACCESSORS
		b2Body*getBody() const { return _body; }
		void setBody( b2Body* aBody );

		void setState( PhsyicsObjectState aState, boost::function<void()>& updateFunction );
		PhsyicsObjectState getState() { return _state; };

		bool isDead() { return false; /*_age > _lifetime;*/ };


	protected:
		// Applies radial gravity - assumes center is in physics units
		void applyRadialGravity( b2Vec2 center );
		// Applies perlin noise to the bodies motion
		void applyNoise();
		// Limits linearvelocity of the object
		void limitSpeed();
		void faceCenter();
		void reset();

		// Death
		void beginDeath();

		b2Body * _body;
		float _radius;
		int	_lifetime;
		int _age;
		float _agePer;

		int _textureId;
		ci::gl::Texture texture;
		ci::Area _spriteSheetArea;

		PhsyicsObjectState _state;
		boost::function<void()> updateState;
		void updateActive();
		void updateExploding();

		// Death related vars
		ci::Anim<ci::Vec2f> _deathPosition; // Used to animate
};

#endif /* PHYSICSOBJECT_H_ */
