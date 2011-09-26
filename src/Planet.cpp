/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "Planet.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/CinderResources.h"
#include "cinder/ImageIo.h"
#include "cinder/app/App.h"
#include "Resources.h"


Planet::~Planet() {
	std::cout << "Planet created" << std::endl;
}

void Planet::update() {}
void Planet::setupTexture() {
	texture = ci::gl::Texture( ci::loadImage( ci::app::App::get()->loadResource( RES_PLANET ) ) );
}
