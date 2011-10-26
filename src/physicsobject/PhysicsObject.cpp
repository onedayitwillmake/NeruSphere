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
#include "cinder/Utilities.h"
#include "cinder/CinderResources.h"
#include "Conversions.h"
#include "Constants.h"
#include "Textures.h"
#include "cinder/Rect.h"

#include "boost/function.hpp"

using namespace ci;
using namespace ci::box2d;


PhysicsObject::PhysicsObject( b2Body* aBody ) {
	_lifetime = ci::Rand::randInt( Constants::Heads::MIN_LIFETIME, Constants::Heads::MAX_LIFETIME );
	_age = 0;
	setBody( aBody );
	_body->SetAngularDamping(0.5);
	_body->SetLinearDamping(0.5);

	emitter = new particle::ParticleSystem();
	setState( ACTIVE, updateState );
}

PhysicsObject::~PhysicsObject() {
	_body = NULL;
	delete emitter; emitter = NULL;
}

void PhysicsObject::setupTexture() {
	texture = *Constants::Textures::getRandomHeadTexture();

	// Total sprites per row / column
	int rowCount = texture.getCleanWidth() / Constants::Heads::SINGLE_SPRITE_SIZE;
	int columnCount = texture.getCleanHeight() / Constants::Heads::SINGLE_SPRITE_SIZE;

	// Random sprite between [0, Constants::Heads::NUM_SPRITES]
	int spriteIndex = ci::Rand::randInt( Constants::Heads::NUM_SPRITES );
	int ix = spriteIndex / rowCount;
	int iy = spriteIndex % columnCount;

	// Determin sprite coords by using index, and adding 1 Constants::Heads::SINGLE_SPRITE_SIZE to the bounds X and then Y
	float ss = Constants::Heads::SINGLE_SPRITE_SIZE;
	_spriteSheetArea = ci::Area( ci::Vec2i(ix*ss, iy*ss), ci::Vec2i(ix*ss+ss, iy*ss+ss) );
//	std::cout << _spriteSheetArea << std::endl;
}

void PhysicsObject::update() {
	updateState();
}


void PhysicsObject::updateActive() {
	if(++_age == _lifetime) {
		beginDeath();
		return;
	}

	applyRadialGravity( ci::box2d::Conversions::toPhysics( ci::app::App::get()->getWindowCenter() ) );
	applyNoise();
	limitSpeed();
	faceCenter();
}

void PhysicsObject::updateExploding() {
	emitter->update();
	if( emitter->isDead ) {
		setState( ACTIVE, updateState );
		emitter->clear();
	}
}

void PhysicsObject::beginDeath() {

	ci::Vec2f screenPosition = ci::box2d::Conversions::toScreen( _body->GetPosition() ); // Store before resetting

	setState( EXPLODING, updateState );
	reset();
	emitter->isDead = false;

	const float scale = Constants::Particles::SIZE;//ci::Rand::randFloat(0.1, 1.5);
	const float halfWidth = 1 * scale;
	const float halfHeight = 1 * scale;



	int count = ci::Rand::randInt( Constants::Particles::MIN, Constants::Particles::MAX );
	for(size_t i = 0; i < count; ++i) {
		ci::Vec2f pos = screenPosition + ci::Vec2f( ci::Rand::randFloat(-_radius, _radius), ci::Rand::randFloat(-_radius, _radius) );

		const ci::Area srcArea = Area( 0, 0, halfWidth*2, halfHeight*2 );
		ci::Rectf destRect = ci::Rectf( pos.x-halfWidth, pos.y-halfHeight, pos.x + halfWidth, pos.y + halfHeight);
		const ci::Rectf srcCoords = ci::Rectf( srcArea );

		// Add a particle to any random emitter
		ci::Vec2f velocity = ci::Rand::randVec2f() * ci::Rand::randFloat( Constants::Particles::MAX_INITIAL_SPEED, Constants::Particles::MAX_INITIAL_SPEED );
		emitter->add( pos, velocity, srcCoords, destRect );
	}
}

void PhysicsObject::applyRadialGravity( b2Vec2 center ) {
	b2Vec2 pos = _body->GetPosition();
	b2Vec2 delta = center - pos;

	// Get the length squared - if too close use min distance
	float lengthSQ = ci::math<float>::max( delta.LengthSquared(), ci::box2d::Conversions::toPhysics( Constants::Heads::MIN_GRAVITY_DISTANCE  ) );
	// Scale inverse to lengthsq but always apply some gravity
	float forceScale = ci::math<float>::max(0.1, Conversions::toPhysics( Constants::Forces::GRAVITY_FORCE ) / lengthSQ);

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

void PhysicsObject::faceCenter() {
	b2Vec2 center = ci::box2d::Conversions::toPhysics( ci::app::App::get()->getWindowCenter() );
	b2Vec2 pos = _body->GetPosition();
	float angle = ci::math<float>::atan2( center.y - pos.y, center.x - pos.x ) - M_PI_2;
	_body->SetTransform( pos, angle );
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

	if( !texture || ci::app::App::get()->getElapsedFrames() < 30 ) return;


	float desiredRadius = _radius;
	ci::Vec2f pos = ci::box2d::Conversions::toScreen( _body->GetPosition() ) ;
	ci::Rectf rect = Rectf(-desiredRadius,
			-desiredRadius,
			desiredRadius,
			desiredRadius);

	gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f) );
	gl::pushMatrices();
		gl::translate( ci::box2d::Conversions::toScreen( _body->GetPosition() ) );
			gl::rotate( ci::box2d::Conversions::radiansToDegrees( _body->GetAngle() ) );
				gl::draw( texture, _spriteSheetArea, rect );
	gl::popMatrices();

//	debugDraw();
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
					gl::drawStrokedCircle( ci::box2d::Conversions::toScreen( shape->m_p ), ci::box2d::Conversions::toScreen( shape->m_radius ), 12 );
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
	float radius = ci::math<float>::sqrt( appWidth*appWidth + appHeight*appHeight ) + _radius;
	float angle = ci::Rand::randFloat(M_PI*2);

	float x = ci::app::App::get()->getWindowCenter().x + ci::math<float>::cos( angle ) * radius*0.5;
	float y = ci::app::App::get()->getWindowCenter().y + ci::math<float>::sin( angle ) * radius*0.5;
	ci::Vec2f position = ci::Vec2f(x, y);
	_body->SetTransform( Conversions::toPhysics(position), 0);

	_lifetime = ci::Rand::randInt( Constants::Heads::MIN_LIFETIME, Constants::Heads::MAX_LIFETIME );
	_age = 0;

	emitter->clear();
}

///// ACCESSORS
void PhysicsObject::setBody( b2Body* aBody ) {
	_body = aBody;
	_body->SetFixedRotation( true );
	_radius = ci::box2d::Conversions::toScreen( _body->GetFixtureList()->GetShape()->m_radius );
}

void PhysicsObject::setState( PhsyicsObjectState aState, boost::function<void()>& updateFunction ) {

	_state = aState;
	if( _state == ACTIVE ) {
		updateFunction = boost::bind( &PhysicsObject::updateActive, this );
	} else {
		updateFunction = boost::bind( &PhysicsObject::updateExploding, this );
	}
}
