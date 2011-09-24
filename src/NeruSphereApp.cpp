/**
 * EclipseLovesCinder example application
 *
 * * On first run, run Project -> Clean...
 * * If you change your project name go into debug configurations (arrow next to bug icon), and modify where the debug application will run from
 *
 * This project is released under public domain, do whatever with it.
 *
 *
 * Mario Gonzalez
 * http://onedayitwillmake
 */


#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Rand.h"
#include "gl.h"
#include "WorldController.h"
#include "Conversions.h"
#include "cinder/CinderMath.h"

#include <vector>

class NeruSphereApp : public ci::app::AppBasic {
public:
	WorldController _worldController;
	std::vector<b2Body*> _heads;

	void setup();
	void prepareSettings( ci::app::AppBasic::Settings *settings );
	void mouseDown( ci::app::MouseEvent event );
	void update();
	void draw();
};

void NeruSphereApp::prepareSettings( ci::app::AppBasic::Settings *settings ) {
	settings->setWindowSize( 800, 600 );
}

void NeruSphereApp::setup() {
	std::cout << "Setting application path: " << getAppPath() << std::endl;
	chdir( getAppPath().c_str( ) );

	_worldController.init( 2, 1 );

	ci::Vec2f size = ci::Vec2f( 10, 10 );
	ci::Vec2f pos = getWindowCenter();

	int count = 800;
	for(int i = 1; i < count; i++) {
		pos.x = i * (float)getWindowSize().x/ (float)count;
		_heads.push_back( _worldController.createCircle( size.x, pos ) );
	}
}

void NeruSphereApp::mouseDown( ci::app::MouseEvent event ) {
}

void NeruSphereApp::update() {
	_worldController.update();

	using namespace ci::box2d;

	float GRAVITY_FORCE = 500.0f;
	for(std::vector<b2Body*>::const_iterator i = _heads.begin(); i != _heads.end(); ++i) {
		b2Body* body = *i;
		b2Vec2 center = Conversions::toPhysics( getWindowCenter() );
		b2Vec2 pos = body->GetPosition();
		b2Vec2 delta = center - pos;

		float lengthSQ = ci::math<float>::max( delta.LengthSquared(), Conversions::toPhysics(100.0f) );
		float forceScale = ci::math<float>::max(0.5, Conversions::toPhysics( GRAVITY_FORCE ) / lengthSQ);
		delta.Normalize();

		b2Vec2 force = forceScale * delta;
		body->ApplyForce( force, center );
	}
}

void NeruSphereApp::draw() {
	ci::gl::clear( ci::Color(0,0,0) );
	_worldController.draw();
}

CINDER_APP_BASIC( NeruSphereApp, ci::app::RendererGl )
