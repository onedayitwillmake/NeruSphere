/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "Planet.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Color.h"
#include "Constants.h"
#include "cinder/app/App.h"
#include "Resources.h"


Planet::~Planet() {
	std::cout << "Planet destructor" << std::endl;
}

void Planet::draw() {
	ci::gl::color( ci::ColorA(1.0f, 0.0, 0.2f, 0.5f ) );
	PhysicsObject::draw();
}
void Planet::update() {}
void Planet::setupTexture() {
	texture = *Constants::Textures::HEAD();
}
