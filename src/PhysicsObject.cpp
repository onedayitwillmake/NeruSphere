/*
 * PhysicsObject.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "PhysicsObject.h"
#include <iostream>
#include "cinder/Vector.h"
#include "cinder/CinderMath.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "Conversions.h"
#include "Constants.h"

using namespace ci;
PhysicsObject::PhysicsObject( b2Body* aBody ) {
	_body = aBody;
	std::cout << "PhysicsObject created!" << std::endl;
}

PhysicsObject::~PhysicsObject() {
	std::cout << "PhysicsObject destructor!" << std::endl;
	_body = NULL;
}

void PhysicsObject::update() {
	applyRadialGravity( ci::box2d::Conversions::toPhysics( ci::app::App::get()->getWindowCenter() ) );
	applyNoise();
	limitSpeed();
}

void PhysicsObject::applyRadialGravity( b2Vec2 center ) {
	using namespace ci::box2d;
	b2Vec2 pos = _body->GetPosition();
	b2Vec2 delta = center - pos;

	float lengthSQ = ci::math<float>::max( delta.LengthSquared(), ci::box2d::Conversions::toPhysics(75.0f) );
	float forceScale = ci::math<float>::max(0.2, Conversions::toPhysics( Constants::Forces::GRAVITY_FORCE ) / lengthSQ);
	delta.Normalize();

	b2Vec2 force = forceScale * delta;
	_body->ApplyForce( force, center );
}

void PhysicsObject::applyNoise( ) {
	b2Vec2 pos = _body->GetPosition();
	ci::Vec3f noise = Constants::Instances::PERLIN_NOISE()->dfBm( ci::Vec3f( pos.x*0.01, pos.y*0.01, (float)ci::app::App::get()->getElapsedFrames() * 0.001) ) * 0.3;
	b2Vec2 force = b2Vec2( noise.x, noise.y );
	_body->ApplyForce( force, _body->GetWorldCenter() );
}

void PhysicsObject::limitSpeed() {
	b2Vec2 velocity = _body->GetLinearVelocity();
	float speedSQ = velocity.LengthSquared();
	float maxSpeed = 15;
	if( speedSQ > maxSpeed * maxSpeed ) {
		velocity.Normalize();
		velocity *= maxSpeed;
		_body->SetLinearVelocity( velocity );
	}
}

void PhysicsObject::draw() {
	gl::color( ColorA(1.0f, 0.0, 0.1f, 0.2f ) );
	gl::pushMatrices(); // Store old matrix
	gl::translate( ci::box2d::Conversions::toScreen( _body->GetPosition() ) );
		b2Fixture* fixture = _body->GetFixtureList();
		while( fixture != NULL ) {
			switch( fixture->GetType() ) {
				case b2Shape::e_polygon: {
					b2PolygonShape* shape = (b2PolygonShape*) fixture->GetShape();

					glBegin(GL_POLYGON);
						for(int i = 0; i != shape->GetVertexCount(); ++i) {
							gl::vertex( ci::box2d::Conversions::toScreen( shape->GetVertex(i) ) );
						}
					glEnd();
				}
				break;
				case b2Shape::e_circle: {
					b2CircleShape* shape = (b2CircleShape*) fixture->GetShape();
					gl::drawSolidCircle( ci::box2d::Conversions::toScreen( shape->m_p ), ci::box2d::Conversions::toScreen( shape->m_radius ) );
				}
				break;
				default:
					break;
			}

			fixture = fixture->GetNext();
		}
	gl::popMatrices();
}
