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
#include "cinder/Rand.h"
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
	_lifetime = ci::Rand::randInt( Constants::Heads::MIN_LIFETIME, Constants::Heads::MAX_LIFETIME );
	_age = 0;
	setBody( aBody );
}

PhysicsObject::~PhysicsObject() {
//	std::cout << "PhysicsObject destructor!" << std::endl;
	_body = NULL;
}

void PhysicsObject::setupTexture() {
	texture = *Constants::Textures::HEAD();
}

void PhysicsObject::update() {

	if(++_age > _lifetime) {
		reset();
		return;
	}

	applyRadialGravity( ci::box2d::Conversions::toPhysics( ci::app::App::get()->getWindowCenter() ) );
	applyNoise();
	limitSpeed();
}

void PhysicsObject::applyRadialGravity( b2Vec2 center ) {
	b2Vec2 pos = _body->GetPosition();
	b2Vec2 delta = center - pos;

	float lengthSQ = ci::math<float>::max( delta.LengthSquared(), ci::box2d::Conversions::toPhysics( Constants::Heads::MIN_GRAVITY_DISTANCE  ) );
//	std::cout << lengthSQ << std::endl;

	float forceScale = ci::math<float>::max(0.7, Conversions::toPhysics( Constants::Forces::GRAVITY_FORCE ) / lengthSQ);
	delta.Normalize();

	b2Vec2 force = forceScale * delta;
	_body->ApplyForce( _body->GetMass() * force, _body->GetWorldCenter() );
}

void PhysicsObject::applyNoise( ) {
	b2Vec2 pos = _body->GetPosition();
	ci::Vec3f noise = Constants::Instances::PERLIN_NOISE()->dfBm( ci::Vec3f( pos.x, pos.y, (float)ci::app::App::get()->getElapsedFrames() * 0.001) ) * Constants::Heads::PERLIN_STRENGTH;
	b2Vec2 force = b2Vec2( noise.x, noise.y );


	_body->ApplyForce( _body->GetMass() * force, _body->GetWorldCenter() );
}

void PhysicsObject::limitSpeed() {
	b2Vec2 velocity = _body->GetLinearVelocity();
	float speedSQ = velocity.LengthSquared();
	float maxSpeed = Conversions::toPhysics( Constants::Heads::MAX_SPEED );
	if( speedSQ > maxSpeed * maxSpeed ) {
		velocity.Normalize();
		velocity *= maxSpeed;
		_body->SetLinearVelocity( velocity );
	}
}

void PhysicsObject::draw() {

	if( !texture ) return;
//	debugDraw();
//	return;

	gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f) );
	gl::pushMatrices();
		gl::translate( ci::box2d::Conversions::toScreen( _body->GetPosition() ) );
			gl::rotate( ci::box2d::Conversions::radiansToDegrees( _body->GetAngle() ) );
				float desiredRadius = _radius*2.5;
				ci::Vec2f pos = ci::box2d::Conversions::toScreen( _body->GetPosition() ) ;
				ci::Rectf rect = Rectf(-desiredRadius,
						-desiredRadius,
						desiredRadius,
						desiredRadius);
				gl::draw( texture, rect );
	gl::popMatrices();
}

void PhysicsObject::debugDraw() {

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
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


void PhysicsObject::reset() {
	_body->SetLinearVelocity( b2Vec2(0,0) );
	_body->SetAngularVelocity( 0 );

	float appWidth = (float)ci::app::App::get()->getWindowWidth();
	float appHeight = (float)ci::app::App::get()->getWindowHeight();
	float radius = ci::math<float>::sqrt( appWidth*appWidth + appHeight*appHeight );
	float angle = ci::Rand::randFloat(M_PI*2);

	float x = ci::app::App::get()->getWindowCenter().x + ci::math<float>::cos( angle ) * radius*0.5;
	float y = ci::app::App::get()->getWindowCenter().y + ci::math<float>::sin( angle ) * radius*0.5;
	ci::Vec2f position = ci::Vec2f(x, y);
	_body->SetTransform( Conversions::toPhysics(position), 0);

	_lifetime = ci::Rand::randInt( Constants::Heads::MIN_LIFETIME, Constants::Heads::MAX_LIFETIME );
	_age = 0;
}

///// ACCESSORS
void PhysicsObject::setBody( b2Body* aBody ) {
	_body = aBody;
	_radius = ci::box2d::Conversions::toScreen( _body->GetFixtureList()->GetShape()->m_radius );
}
