/*
 * ParticleSystem.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: onedayitwillmake
 */

#include "ParticleSystem.h"
#include "cinder/Rand.h"

namespace particle {

ParticleSystem::ParticleSystem() {
	_debugColor = ci::Rand::randFloat();
}

ParticleSystem::~ParticleSystem() {
	// TODO Auto-generated destructor stub
}

void ParticleSystem::add( ci::Vec2f pos, ci::Vec2f velocity, ci::Rectf srcCoords, ci::Rectf destRect ) {
	Particle p = { verts.size(), velocity, pos, pos };
	particles.push_back( p );

	// Vertices
	verts.push_back( destRect.getX1() ); verts.push_back( destRect.getY2() );
	verts.push_back( destRect.getX2() ); verts.push_back( destRect.getY2() );
	verts.push_back( destRect.getX2() ); verts.push_back( destRect.getY1() );
	verts.push_back( destRect.getX1() ); verts.push_back( destRect.getY2() );
	verts.push_back( destRect.getX2() ); verts.push_back( destRect.getY1() );
	verts.push_back( destRect.getX1() ); verts.push_back( destRect.getY1() );;

	// Texture coords
	texCoords.push_back( srcCoords.getX1() ); texCoords.push_back( srcCoords.getY2() );
	texCoords.push_back( srcCoords.getX2() ); texCoords.push_back( srcCoords.getY2() );
	texCoords.push_back( srcCoords.getX2() ); texCoords.push_back( srcCoords.getY1() );
	texCoords.push_back( srcCoords.getX1() ); texCoords.push_back( srcCoords.getY2() );
	texCoords.push_back( srcCoords.getX2() ); texCoords.push_back( srcCoords.getY1() );
	texCoords.push_back( srcCoords.getX1() ); texCoords.push_back( srcCoords.getY1() );

	// Colors
	ci::ColorA color = ci::ColorA(ci::CM_HSV, _debugColor, 1.0, 0.4, 1.0);
	colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color );
}
void ParticleSystem::update() {
	for( std::vector<Particle>::iterator itr = particles.begin(); itr != particles.end(); ++itr ) {
		ci::Vec2f delta = itr->speed;//itr->originalPosition - itr->currentPosition;

		for(size_t x = 0; x < 12; x += 2)
			verts[ itr->index+x ] += delta.x;
		for(size_t y = 1; y < 12; y += 2)
			verts[ itr->index+y ] += delta.y;

		itr->speed *= 0.998f;
	}
}

void ParticleSystem::draw() {

}
void ParticleSystem::clear() {
	verts.clear();
	texCoords.clear();
	particles.clear();
	colors.clear();
}

} /* namespace particle */
