/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "Planet.h"
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include "cinder/app/App.h"
#include "Constants.h"
#include "Textures.h"


Planet::~Planet() {
	std::cout << "Planet destructor" << std::endl;
}
void Planet::drawImp() {
	ci::gl::color( ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );
	PhysicsObject::draw();
}
void Planet::update() {}
void Planet::setupTexture() {
	texture = *Constants::Textures::HEAD();
	_spriteSheetArea = texture.getBounds();
	_spriteSheetArea.expand( -texture.getWidth()*2 - 1, -texture.getHeight()*2 - 1 );
}
