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
#include "gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Rand.h"
#include "cinder/Display.h"
#include "WorldController.h"
#include "Conversions.h"
#include "cinder/CinderMath.h"
#include "cinder/Perlin.h"
#include "AudioAnalyzer.h"
#include "Constants.h"
#include "Textures.h"
#include "PhysicsObject.h"
#include "Planet.h"
#include <vector>

using namespace ci::box2d;
using namespace ci;


class NeruSphereApp : public ci::app::AppBasic {
public:
	WorldController _worldController;
	b2Body* _planetBody;
	Planet* _planetPhysicsObject;
	AudioAnalyzer _audioAnalyzer;

	void setup();
	void setupHeads();
	void prepareSettings( ci::app::AppBasic::Settings *settings );
	void mouseDown( ci::app::MouseEvent event );
	void update();
	void shutdown();
	void draw();
};

void NeruSphereApp::prepareSettings( ci::app::AppBasic::Settings *settings ) {
	settings->setWindowSize( 800, 600);
	settings->setDisplay( Display::getDisplays().at(1) );
//	settings->setFrameRate( 30 );
}

void NeruSphereApp::setup() {
	std::cout << "Setting application path: " << getAppPath() << std::endl;
	chdir( getAppPath().c_str( ) );

	Constants::Textures::loadTextures();

	_planetBody = NULL;
	_planetPhysicsObject = NULL;

	_worldController.init( 4, 2 );
	setupHeads();

	ci::gl::enableAdditiveBlending();
}

void NeruSphereApp::setupHeads() {
	ci::Vec2f pos = getWindowCenter();

	int count = Constants::Defaults::HEAD_COUNT;
	for(int i = 1; i <= count; i++) {
		pos.x = i * (float)getWindowSize().x/ (float)count;
		pos.y = ci::Rand::randFloat(-1000, 1000);

		b2Body* body = _worldController.createCircle( ci::Rand::randFloat(Constants::Defaults::HEAD_SIZE_MIN, Constants::Defaults::HEAD_SIZE_MAX), pos );
		PhysicsObject* physicsObject = new PhysicsObject( body );
		physicsObject->setupTexture();
		body->SetUserData( physicsObject );
	}
}

void NeruSphereApp::mouseDown( ci::app::MouseEvent event ) {
}


void NeruSphereApp::update() {
	_worldController.update();
	_audioAnalyzer.update();

	using namespace ci::box2d;
	if(_planetBody) {
		_worldController.getWorld()->DestroyBody(_planetBody);
	}

	// Shape definition
	b2CircleShape aShape;


	static float lastSize = 1;
	lastSize -= (lastSize - Conversions::toPhysics( Constants::Planet::MIN_SIZE + _audioAnalyzer.getAverageVolume() * Constants::Planet::VOLUME_RANGE ) ) * Constants::Planet::EASE_SPEED;
	aShape.m_radius = lastSize;

	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &aShape;
	mFixtureDef.friction = 1.0f;
	mFixtureDef.restitution = 0.0f;
	mFixtureDef.density = 1.0f;

	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_staticBody;
	mBodyDef.position = Conversions::toPhysics( getWindowCenter() );
	b2Body* body = _worldController.getWorld()->CreateBody( &mBodyDef );
	body->CreateFixture( &mFixtureDef );

	_planetBody = body;

	if( _planetPhysicsObject ) {
		_planetPhysicsObject->setBody( body );
	} else {
		_planetPhysicsObject = new Planet( body );
		_planetPhysicsObject->setupTexture();
	}

	body->SetUserData( _planetPhysicsObject );
}

void NeruSphereApp::draw() {
	ci::gl::clear( ci::Color(0,0,0) );
	ci::gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );

	_worldController.draw();
	_audioAnalyzer.draw();
}

void NeruSphereApp::shutdown() {
	std::cout << "Shutdown..." << std::endl;
	AppBasic::shutdown();
}

CINDER_APP_BASIC( NeruSphereApp, ci::app::RendererGl )
