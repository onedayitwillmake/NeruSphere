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

void Planet::drawSphere() {
	
//	PhysicsObject::draw();

	// Draw 3D wireframe of planet
	ci::Vec2f pos2d = ci::box2d::Conversions::toScreen( _body->GetPosition() );
	ci::Vec3f pos3d(pos2d.x, pos2d.y, 0);

	static float rotationX = 0;
	static float rotationY = 0;
	static float rotationZ = 0;

	float scale = 2 * 0.01;
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
	
	
	
	//ci::Vec3f::zero(), _body->GetFixtureList()->GetShape()->m_radius * 0.99, 10
	int segments = 10;
	ci::Vec3f center = ci::Vec3f::zero();
	float radius = ci::box2d::Conversions::toScreen( _body->GetFixtureList()->GetShape()->m_radius ) * 1.1;
	
	float *verts = new float[(segments+1)*2*3];
	float *normals = new float[(segments+1)*2*3];
	float *texCoords = new float[(segments+1)*2*2];
	
	
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, verts );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, 0, texCoords );
	glEnableClientState( GL_NORMAL_ARRAY );
	glNormalPointer( GL_FLOAT, 0, normals );
	
	using namespace ci;
	for( int j = 0; j < segments / 2; j++ ) {
		float theta1 = j * 2 * 3.14159f / segments - ( 3.14159f / 2.0f );
		float theta2 = (j + 1) * 2 * 3.14159f / segments - ( 3.14159f / 2.0f );
		
		for( int i = 0; i <= segments; i++ ) {
			Vec3f e, p;
			float theta3 = i * 2 * 3.14159f / segments;
			
			e.x = math<float>::cos( theta1 ) * math<float>::cos( theta3 );
			e.y = math<float>::sin( theta1 );
			e.z = math<float>::cos( theta1 ) * math<float>::sin( theta3 );
			e.rotateX(rotationX);
			e.rotateY(rotationY);
			e.rotateZ(rotationZ);
			
			p = e * radius + center;
			normals[i*3*2+0] = e.x; normals[i*3*2+1] = e.y; normals[i*3*2+2] = e.z;
			texCoords[i*2*2+0] = 0.999f - i / (float)segments; texCoords[i*2*2+1] = 0.999f - 2 * j / (float)segments;
			verts[i*3*2+0] = p.x; verts[i*3*2+1] = p.y; verts[i*3*2+2] = p.z;
			
			e.x = math<float>::cos( theta2 ) * math<float>::cos( theta3 );
			e.y = math<float>::sin( theta2 );
			e.z = math<float>::cos( theta2 ) * math<float>::sin( theta3 );
			e.rotateX(rotationX);
			e.rotateY(rotationY);
			e.rotateZ(rotationZ);
			p = e * radius + center;
			normals[i*3*2+3] = e.x; normals[i*3*2+4] = e.y; normals[i*3*2+5] = e.z;
			texCoords[i*2*2+2] = 0.999f - i / (float)segments; texCoords[i*2*2+3] = 0.999f - 2 * ( j + 1 ) / (float)segments;
			verts[i*3*2+3] = p.x; verts[i*3*2+4] = p.y; verts[i*3*2+5] = p.z;
		}
		glDrawArrays( GL_LINE_STRIP, 0, (segments + 1)*2 );
	}
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	
	delete [] verts;
	delete [] normals;
	delete [] texCoords;
	
		ci::gl::popMatrices();
//	ci::gl::disableWireframe();


}
void Planet::update() {}
void Planet::setupTexture() {
	texture = *Constants::Textures::getPlanetTexture();
	_spriteSheetArea = texture.getBounds();
}
