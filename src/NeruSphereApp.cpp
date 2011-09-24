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

class NeruSphereApp : public ci::app::AppBasic {
public:
	WorldController _worldController;
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

	_worldController.init( 6, 2 );
}

void NeruSphereApp::mouseDown( ci::app::MouseEvent event ) {
}

void NeruSphereApp::update() {
	_worldController.update();
}

void NeruSphereApp::draw() {
	ci::gl::clear( ci::Color(0,0,0) );
	_worldController.draw();
}

CINDER_APP_BASIC( NeruSphereApp, ci::app::RendererGl )
