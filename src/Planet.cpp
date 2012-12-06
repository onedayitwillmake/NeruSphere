/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "Planet.h"
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include "Constants.h"
#include "Textures.h"
#include "Conversions.h"
#include "AppInfo.h"


Planet::~Planet() {
	std::cout << "Planet destructor" << std::endl;
}

void Planet::drawImp( float volumeScale ) {

	if( !texture || AppInfo::getInstance().getElapsedFrames() < 30 ) return;

	ci::gl::color( ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );
	PhysicsObject::draw();

	// Draw 3D wireframe of planet
	ci::Vec2f pos2d = ci::box2d::Conversions::toScreen( _body->GetPosition() );
	ci::Vec3f pos3d(pos2d.x, pos2d.y, 0);

	static float rotationX = 0;
	static float rotationY = 0;
	static float rotationZ = 0;

	float scale = volumeScale * 0.01;
	rotationX += Constants::Instances::PERLIN_NOISE()->dfBm( AppInfo::getInstance().getElapsedFrames() / 100, AppInfo::getInstance().getElapsedSeconds() / 10).x * scale;
	rotationY += Constants::Instances::PERLIN_NOISE()->dfBm( AppInfo::getInstance().getElapsedFrames() / 100, AppInfo::getInstance().getElapsedSeconds() / 10).y * scale;
	rotationZ += Constants::Instances::PERLIN_NOISE()->dfBm( AppInfo::getInstance().getElapsedFrames() / 100, AppInfo::getInstance().getElapsedSeconds() / 10 + 1000).x * scale;

	static float red = 249.0f / 255.0f;
	static float green = 103.0f / 255.0f;
	static float blue = 166.0f / 255.0f;
	ci::gl::color( ci::ColorA(red, green, blue, 0.75 ) );
//	ci::gl::enableWireframe();
		ci::gl::pushMatrices();
			ci::gl::translate(pos2d.x, pos2d.y);
			ci::gl::rotate( ci::Vec3f(rotationX, rotationY, rotationZ) );
			ci::gl::drawSphere(ci::Vec3f::zero(), _radius * 0.99, 10 );
		ci::gl::popMatrices();
//	ci::gl::disableWireframe();


}
void Planet::update() {}
void Planet::setupTexture() {
	texture = *Constants::Textures::getPlanetTexture();
	_spriteSheetArea = texture.getBounds();
}
