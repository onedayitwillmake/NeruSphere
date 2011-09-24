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
#include "Conversions.h"
#include "cinder/app/App.h"

using namespace ci::box2d;
WorldController::WorldController() {
	std::cout << "WorldController Constructor! " << std::endl;
}

WorldController::~WorldController() {
	delete _world;
}

void WorldController::init( int positionIterations, int velocityIterations ) {
	b2Vec2 gravity(0.0f, 1.0f);
	_world = new b2World( gravity );
	_positionIterations = positionIterations;
	_velocityIterations = velocityIterations;
	_timeStep = 1.0f / 60.0f;
}

void WorldController::update() {
	_world->Step( _timeStep, _velocityIterations, _positionIterations );
	_world->ClearForces();
}

void WorldController::clear() {

}

void WorldController::removeDeadElements() {

}

void WorldController::draw() {
	debugDraw();
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

						glBegin(GL_POLYGON);
						for(int i = 0; i != shape->GetVertexCount(); ++i) {
							gl::vertex( cinder::box2d::Conversions::toScreen( shape->GetVertex(i) ) );
						}
						glEnd();
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
	mFixtureDef.friction = 0.3f;
	mFixtureDef.restitution = 0.01f;
	mFixtureDef.density = 1.0f;

	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set(	Conversions::toPhysics( pos.x ), Conversions::toPhysics( pos.y ) );

	b2Body* body = _world->CreateBody( &mBodyDef );
	body->CreateFixture( &mFixtureDef );

	return body;
}
