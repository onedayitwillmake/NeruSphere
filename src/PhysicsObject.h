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
#include "ParticleSystem.h"

#include "boost/function.hpp"
#include "boost/bind.hpp"

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

		ci::gl::Texture* getTexture() { return &texture; };
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
};

#endif /* PHYSICSOBJECT_H_ */
