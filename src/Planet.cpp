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
#include "Conversions.h"



Planet::~Planet() {
	std::cout << "Planet destructor" << std::endl;
}

void Planet::drawImp( float volumeScale ) {

	if( !texture || ci::app::App::get()->getElapsedFrames() < 30 ) return;

	ci::gl::color( ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );

//	PhysicsObject::draw();

	// Draw 3D wireframe of planet
	ci::Vec2f pos2d = ci::box2d::Conversions::toScreen( _body->GetPosition() );
	ci::Vec3f pos3d(pos2d.x, pos2d.y, 0);

	static float rotationX = 0;
	static float rotationY = 0;
	static float rotationZ = 0;

	float scale = volumeScale * 0.01;
	rotationX += Constants::Instances::PERLIN_NOISE()->dfBm( (float)ci::app::App::get()->getElapsedFrames() / 100.0f, (float)ci::app::App::get()->getElapsedSeconds() / 10.0f).x * scale;
	rotationY += Constants::Instances::PERLIN_NOISE()->dfBm( (float)ci::app::App::get()->getElapsedFrames() / 100.0f, (float)ci::app::App::get()->getElapsedSeconds() / 10.0f).y * scale;
	rotationZ += Constants::Instances::PERLIN_NOISE()->dfBm( (float)ci::app::App::get()->getElapsedFrames() / 100.0f, (float)ci::app::App::get()->getElapsedSeconds() / 10.0f + 1000).x * scale;

//	std::cout << Constants::Instances::PERLIN_NOISE()->fBm( ci::app::App::get()->getElapsedFrames() / 10 ) << std::endl;
	static float red = 249.0f / 255.0f;
	static float green = 103.0f / 255.0f;
	static float blue = 166.0f / 255.0f;
	ci::gl::color( ci::ColorA(red, green, blue, 0.75 ) );
	ci::gl::enableWireframe();
		ci::gl::pushMatrices();
			ci::gl::translate(pos2d.x, pos2d.y);
			ci::gl::rotate( ci::Vec3f(rotationX, rotationY, rotationZ) );
			ci::gl::drawSphere(ci::Vec3f::zero(), this->_radius * 0.99, 10 );
			ci::gl::color( ci::ColorA(1, 0, 1, 0.5 ) );
			ci::gl::rotate( ci::Vec3f(-rotationX, -rotationY, -rotationZ) );
			ci::gl::drawSphere(ci::Vec3f::zero(), this->_radius * 0.6, 10 );
		ci::gl::popMatrices();
	ci::gl::disableWireframe();
	ci::gl::color( ci::ColorA::white() );


}
void Planet::update() {}
void Planet::setupTexture() {
	texture = *Constants::Textures::PLANET();
	_spriteSheetArea = texture.getBounds();
}
