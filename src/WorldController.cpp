/*
 * WorldController.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: onedayitwillmake
 *
 *      A lot of this stuff is appreciatively taken from
 *      David Wicks' excellent Box2D Cinder Block: https://github.com/sansumbrella/sc-Box2D/
 */

#include "WorldController.h"
#include <iostream>
#include "cinder/Vector.h"
#include "cinder/Rect.h"
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include "cinder/app/App.h"
#include "Conversions.h"
#include "Constants.h"
#include "PhysicsObject.h"

using namespace ci::box2d;
WorldController::WorldController() {
	std::cout << "WorldController Constructor! " << std::endl;
}

WorldController::~WorldController() {
	std::cout << "WorldController Destructor! " << std::endl;
	if( _world) {
		b2Body* node = _world->GetBodyList();
		while( node ) {
			PhysicsObject* physicsObject = (PhysicsObject*) node->GetUserData();
			if( physicsObject ) {
				delete physicsObject;
			}
			node->SetUserData( NULL );
			node = node->GetNext();
		}
		delete _world;
	}
}

void WorldController::init( int positionIterations, int velocityIterations ) {
	b2Vec2 gravity(0.0f, 0.0f);
	_world = new b2World( gravity );
	_positionIterations = positionIterations;
	_velocityIterations = velocityIterations;
	_timeStep = 1.0f / 60.0f;
}

void WorldController::update( float dt ) {
	_world->Step( dt, _velocityIterations, _positionIterations );
	_world->ClearForces();

	b2Body* node = _world->GetBodyList();
	while( node ) {
		b2Body* b = node;
		node = node->GetNext();
		PhysicsObject* physicsObject = (PhysicsObject*) b->GetUserData();
		if( physicsObject ) {
			physicsObject->update();
			if( physicsObject->isDead() ) {

				// Destruct physics object
				PhysicsObject* physicsObject = (PhysicsObject*) b->GetUserData();
				if( physicsObject ) {
					delete physicsObject;
				}
				_world->DestroyBody( b );
			}
		}
	}
}

void WorldController::clear() {
	b2Body *node = _world->GetBodyList();
	while( node ) {
		b2Body* b = node;
		node = node->GetNext();

		// Destruct physics object
		PhysicsObject* physicsObject = (PhysicsObject*) b->GetUserData();
		if( physicsObject ) {
			delete physicsObject;
		}
		_world->DestroyBody( b );
	}

	b2Joint* joint = _world->GetJointList();
	while (joint) {
		b2Joint* j = joint;
		joint = joint->GetNext();
		_world->DestroyJoint(j);
	}
}

void WorldController::draw() {
	if( Constants::Defaults::DEBUG_DRAW ) {
		debugDraw();
		return;
	}


	b2Body* b = _world->GetBodyList();
	while( b ) {
		PhysicsObject* physicsElement = (PhysicsObject*) b->GetUserData();
		if( physicsElement ) {
			ci::gl::color( ci::ColorA(1.0f, 0.0, 0.1f, 0.5f ) );
			physicsElement->draw();
		}
		b = b->GetNext();
	}
}

void WorldController::debugDraw( bool drawBodies, bool drawContacts ) {
	using namespace cinder;
	if( drawBodies ) {
		gl::color( ColorA(1.0f, 0.0, 0.1f, 0.5f ) );

		b2Body* b = _world->GetBodyList();
		while( b != NULL ) {
			b2Vec2 pos = b->GetPosition();
			float angle = b->GetAngle();

			gl::pushMatrices();
			gl::translate( cinder::box2d::Conversions::toScreen( pos ) );
			gl::rotate( cinder::box2d::Conversions::radiansToDegrees( angle ) );

			// Draw every fixture
			b2Fixture* fixture = b->GetFixtureList();
			while( fixture != NULL ) {
				switch( fixture->GetType() ) {
					case b2Shape::e_polygon: {
						b2PolygonShape* shape = (b2PolygonShape*) fixture->GetShape();
						
						ci::PolyLine<Vec2f> polyLine;
						for(int i = 0; i != shape->GetVertexCount(); ++i) {
							polyLine.push_back( cinder::box2d::Conversions::toScreen( shape->GetVertex(i) ) );
						}
						gl::draw(polyLine);
					}
					break;
					case b2Shape::e_circle: {
						b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();
						gl::drawSolidCircle( cinder::box2d::Conversions::toScreen(shape->m_p), cinder::box2d::Conversions::toScreen( shape->m_radius ) );
					}
					break;
					default:
						break;
				}

				fixture = fixture->GetNext();
			}

			gl::popMatrices();
			b = b->GetNext();
		}

	}
}


b2Body* WorldController::createRect( ci::Vec2f size, ci::Vec2f pos ) {
	ci::app::App *appInstance = ci::app::App::get();

	// Shape definition
	b2PolygonShape mShape;
	mShape.SetAsBox(	Conversions::toPhysics( size.x/2.0f ), Conversions::toPhysics( size.y/2.0f ) );

	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mShape;
	mFixtureDef.friction = 0.3f;
	mFixtureDef.restitution = 0.0f;
	mFixtureDef.density = 1.0f;

	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set(	Conversions::toPhysics( pos.x ), Conversions::toPhysics( pos.y ) );

	b2Body* body = _world->CreateBody( &mBodyDef );
	body->CreateFixture( &mFixtureDef );

	return body;
}

b2Body* WorldController::createCircle( float radius, ci::Vec2f pos ) {

	// Shape definition
	b2CircleShape aShape;
	aShape.m_radius = Conversions::toPhysics( radius );

	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &aShape;
	mFixtureDef.friction = 0.1f;
	mFixtureDef.restitution = 0.2f;
	mFixtureDef.density = 1.0f;

	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set(	Conversions::toPhysics( pos.x ), Conversions::toPhysics( pos.y ) );

	b2Body* body = _world->CreateBody( &mBodyDef );
	body->CreateFixture( &mFixtureDef );


	return body;
}
