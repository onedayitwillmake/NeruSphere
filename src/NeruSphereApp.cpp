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
#include "cinder/Color.h"
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
#include "SimpleGUI.h"
#include <vector>



using namespace ci::box2d;
using namespace ci;


class NeruSphereApp : public ci::app::AppBasic {
public:
	WorldController _worldController;
	b2Body* _planetBody;
	Planet* _planetPhysicsObject;
	AudioAnalyzer _audioAnalyzer;
	mowa::sgui::SimpleGUI* _gui;

	void setup();
	void setupHeads();
	void setupGUI();
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

	Constants::init();
	Constants::Textures::loadTextures();

	_planetBody = NULL;
	_planetPhysicsObject = NULL;

	_worldController.init( 4, 2 );
	setupHeads();
	setupGUI();


}

void NeruSphereApp::setupGUI() {
	using namespace  ci;
	_gui = new mowa::sgui::SimpleGUI( this );
	_gui->textColor = ci::ColorA(1,1,1,1);
	_gui->lightColor = ci::ColorA(1, 0, 1, 1);
	_gui->darkColor = ci::ColorA(0.05,0.05,0.05, 1);
	_gui->bgColor = ci::ColorA(0.15, 0.15, 0.15, 1.0);
	_gui->addColumn();
	_gui->addLabel("DEFAULTS");
	_gui->addParam("HEAD_COUNT", &Constants::Defaults::HEAD_COUNT, 1, 300, Constants::Defaults::HEAD_COUNT );
	_gui->addParam("HEAD_SIZE_MIN", &Constants::Defaults::HEAD_SIZE_MIN, 4, 256, Constants::Defaults::HEAD_SIZE_MIN );
	_gui->addParam("HEAD_SIZE_MAX", &Constants::Defaults::HEAD_SIZE_MAX, 4, 256, Constants::Defaults::HEAD_SIZE_MAX );
	_gui->addButton("START");
	_gui->addColumn();
	_gui->addLabel("HEADS");
	_gui->addParam("MIN_LIFETIME", &Constants::Heads::MIN_LIFETIME, 400, 5000, Constants::Heads::MIN_LIFETIME );
	_gui->addParam("MAX_LIFETIME", &Constants::Heads::MAX_LIFETIME, 400, 5000, Constants::Heads::MAX_LIFETIME );
	_gui->addParam("MAX_SPEED", &Constants::Heads::MAX_SPEED, 500, 2000, Constants::Heads::MAX_SPEED );
	_gui->addParam("PERLIN_STRENGTH", &Constants::Heads::PERLIN_STRENGTH, 0, 3, Constants::Heads::PERLIN_STRENGTH );
	_gui->addParam("MIN_GRAVITY_DISTANCE", &Constants::Heads::MIN_GRAVITY_DISTANCE, 50.0f*50.0f * 0.5, 50.0f*50.0f * 2, Constants::Heads::MIN_GRAVITY_DISTANCE );
	_gui->addColumn();
	_gui->addLabel("PLANET");
	_gui->addParam("GROW_SPEED", &Constants::Planet::EASE_SPEED, 0.01f, 1.0f, Constants::Planet::EASE_SPEED );
	_gui->addParam("VOLUME_RANGE", &Constants::Planet::VOLUME_RANGE, 15, 30, Constants::Planet::VOLUME_RANGE );
	_gui->addParam("MIN_SIZE", &Constants::Planet::MIN_SIZE, 5, 300, Constants::Planet::MIN_SIZE );
	//_gui->addSeparator();
	//_toggle = _gui->addButton("START");
	//_toggle->registerClick( this, &UserStreamRecorder::onToggleRecordingClicked );
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

	ci::gl::enableAlphaBlending();
	_worldController.draw();
	_audioAnalyzer.draw();
	_gui->draw();
}

void NeruSphereApp::shutdown() {
	std::cout << "Shutdown..." << std::endl;
	AppBasic::shutdown();
}


CINDER_APP_BASIC( NeruSphereApp, ci::app::RendererGl )
