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
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "cinder/CinderResources.h"
#include "Conversions.h"
#include "Constants.h"
#include "Resources.h"
#include "cinder/Rect.h"

using namespace ci;
using namespace ci::box2d;

PhysicsObject::PhysicsObject( b2Body* aBody ) {
	std::cout << "PhysicsObject created!" << std::endl;

	setBody( aBody );
	texture = gl::Texture( loadImage( ci::app::App::get()->loadResource( RES_PLANET ) ) );;
}

PhysicsObject::~PhysicsObject() {
	std::cout << "PhysicsObject destructor!" << std::endl;
	_body = NULL;
}

void PhysicsObject::setupTexture() {
	texture = gl::Texture( loadImage( ci::app::App::get()->loadResource( RES_PLANET ) ) );
}

void PhysicsObject::update() {
	applyRadialGravity( ci::box2d::Conversions::toPhysics( ci::app::App::get()->getWindowCenter() ) );
	applyNoise();
	limitSpeed();
}

void PhysicsObject::applyRadialGravity( b2Vec2 center ) {
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


	if( !texture ) return;

	gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f) );
	gl::pushMatrices();
		gl::translate( ci::box2d::Conversions::toScreen( _body->GetPosition() ) );
			gl::rotate( ci::box2d::Conversions::radiansToDegrees( _body->GetAngle() ) );
				float desiredRadius = _radius;
				ci::Vec2f pos = ci::box2d::Conversions::toScreen( _body->GetPosition() ) ;
				ci::Rectf rect = Rectf(desiredRadius*-0.5,
						desiredRadius*-0.5,
						desiredRadius,
						desiredRadius );
				gl::draw( texture, rect );
	gl::popMatrices();
}

void PhysicsObject::debugDraw() {

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
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


///// ACCESSORS
void PhysicsObject::setBody( b2Body* aBody ) {
	_body = aBody;
	_radius = ci::box2d::Conversions::toScreen( _body->GetFixtureList()->GetShape()->m_radius );
}
