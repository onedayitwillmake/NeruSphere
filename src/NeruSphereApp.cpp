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
#include "cinder/Color.h"
#include "cinder/Display.h"
#include "cinder/Filesystem.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "cinder/DataTarget.h"
#include "cinder/gl/Texture.h"

#include "WorldController.h"
#include "Conversions.h"
#include "cinder/CinderMath.h"
#include "cinder/Perlin.h"
#include "cinder/gl/Fbo.h"
#include "AudioAnalyzer.h"
#include "Constants.h"
#include "Textures.h"
#include "PhysicsObject.h"
#include "Planet.h"
//#include "SimpleGUI.h"

#include <vector>

using namespace ci::box2d;
using namespace ci;


class NeruSphereApp : public ci::app::AppBasic {
public:
	WorldController _worldController;
	b2Body* _planetBody;
	Planet* _planetPhysicsObject;
//	AudioAnalyzer _audioAnalyzer;
//	mowa::sgui::SimpleGUI* _gui;

	void setup();
	void setupHeads();
	void setupGUI();
	void prepareSettings( ci::app::AppBasic::Settings *settings );
	void mouseDown( ci::app::MouseEvent event );
	void keyDown( ci::app::KeyEvent event );
	void resize( ci::app::ResizeEvent event );
	void update();
	void shutdown();

	void render();
	void draw();
	void drawParticles();

	bool restart( ci::app::MouseEvent event );

	void saveImage();
};


void NeruSphereApp::prepareSettings( ci::app::AppBasic::Settings *settings ) {
	settings->setWindowSize( 800, 600);
//	settings->set
//	settings->setDisplay( Display::getDisplays().at(1) );
//	settings->setFrameRate( 30 );
}

void NeruSphereApp::setup() {

	Constants::Textures::loadTextures();
	Constants::init();
	Constants::Defaults::setGravityPoint( getWindowCenter() );


	_planetBody = NULL;
	_planetPhysicsObject = NULL;
//
//	useFBO = false;
//	if( useFBO ) {
//		gl::Fbo::Format format;
//		mFbo = gl::Fbo( FBO_WIDTH, FBO_HEIGHT, format );
//		Constants::Defaults::windowWidth = FBO_WIDTH;
//		Constants::Defaults::windowHeight = FBO_HEIGHT;
//	}

	_worldController.init( 4, 2 );
	setupHeads();
	setupGUI();
}

void NeruSphereApp::setupGUI() {
//
//	using namespace  ci;
//	_gui = new mowa::sgui::SimpleGUI( this );
//	_gui->textColor = ci::ColorA(1,1,1,1);
//	_gui->lightColor = ci::ColorA(1, 0, 1, 1);
//	_gui->darkColor = ci::ColorA(0.05,0.05,0.05, 1);
//	_gui->bgColor = ci::ColorA(0.20, 0.20, 0.20, 0.5);
//	_gui->addColumn();
//	_gui->addLabel("DEFAULTS");
//	_gui->addParam("DRAW_SPECTRUM", &Constants::Defaults::DRAW_AUDIO_ANALYZER, Constants::Defaults::DRAW_AUDIO_ANALYZER);
//	_gui->addParam("HEAD_COUNT", &Constants::Defaults::HEAD_COUNT, 1, 300, Constants::Defaults::HEAD_COUNT );
//	_gui->addParam("HEAD_SIZE_MIN", &Constants::Defaults::HEAD_SIZE_MIN, 4, 256, Constants::Defaults::HEAD_SIZE_MIN );
//	_gui->addParam("HEAD_SIZE_MAX", &Constants::Defaults::HEAD_SIZE_MAX, 4, 256, Constants::Defaults::HEAD_SIZE_MAX );
//	mowa::sgui::ButtonControl* toggle = _gui->addButton("Restart");
//	toggle->registerClick( this, &NeruSphereApp::restart );
//
//	_gui->addColumn();
//	_gui->addLabel("HEADS");
//	_gui->addParam("MIN_LIFETIME", &Constants::Heads::MIN_LIFETIME, 400, 5000, Constants::Heads::MIN_LIFETIME );
//	_gui->addParam("MAX_LIFETIME", &Constants::Heads::MAX_LIFETIME, 400, 5000, Constants::Heads::MAX_LIFETIME );
//	_gui->addParam("MAX_SPEED", &Constants::Heads::MAX_SPEED, Constants::Heads::MAX_SPEED * 0.1, Constants::Heads::MAX_SPEED*Constants::Heads::MAX_SPEED, Constants::Heads::MAX_SPEED );
//	_gui->addParam("PERLIN_STRENGTH", &Constants::Heads::PERLIN_STRENGTH, 0, 20, Constants::Heads::PERLIN_STRENGTH );
//	_gui->addParam("GRAVITY_DISTANCE", &Constants::Heads::MIN_GRAVITY_DISTANCE, ci::math<float>::pow(50,2), ci::math<float>::pow(50.0,3), Constants::Heads::MIN_GRAVITY_DISTANCE );
//	_gui->addParam("ANTI_GRAVITY", &Constants::Heads::ANTI_GRAVITY, 0, 100, Constants::Heads::ANTI_GRAVITY );
//	_gui->addColumn();
//	_gui->addLabel("PLANET");
//	_gui->addParam("GROW_SPEED", &Constants::Planet::EASE_SPEED, 0.01f, 1.0f, Constants::Planet::EASE_SPEED );
//	_gui->addParam("VOLUME_RANGE", &Constants::Planet::VOLUME_RANGE, 15, 60, Constants::Planet::VOLUME_RANGE );
//	_gui->addParam("MIN_SIZE", &Constants::Planet::MIN_SIZE, 5, 300, Constants::Planet::MIN_SIZE );
//	_gui->addColumn();
//	_gui->addLabel("PARTICLES");
//	_gui->addParam("SIZE_MIN", &Constants::Particles::PARTICLE_SIZE_MIN, 1, 10, Constants::Particles::PARTICLE_SIZE_MIN );
//	_gui->addParam("SIZE_MAX", &Constants::Particles::PARTICLE_SIZE_MAX, 1, 10, Constants::Particles::PARTICLE_SIZE_MAX );
//	_gui->addSeparator();
//	_gui->addParam("COUNT_MIN", &Constants::Particles::MIN, 1, 32, Constants::Particles::MIN );
//	_gui->addParam("COUNT_MAX", &Constants::Particles::MAX, 1, 32, Constants::Particles::MAX );
//	_gui->addSeparator();
//	_gui->addParam("SPEED_MIN", &Constants::Particles::MIN_INITIAL_SPEED, 1, 10, Constants::Particles::MIN_INITIAL_SPEED );
//	_gui->addParam("SPEED_MAX", &Constants::Particles::MAX_INITIAL_SPEED, 1, 10, Constants::Particles::MAX_INITIAL_SPEED );
//	_gui->addParam("SPEED_DECAY", &Constants::Particles::SPEED_DECAY, 0.85, 0.999, Constants::Particles::SPEED_DECAY );
//	_gui->addParam("ALPHA", &Constants::Particles::ALPHA, 0, 1.0, Constants::Particles::ALPHA);
}

void NeruSphereApp::setupHeads() {


	int count = Constants::Defaults::HEAD_COUNT;
	float spread = 0.4f;
	for(int i = 1; i <= count; i++) {
		ci::Vec2f pos = Constants::Defaults::getWindowCenter();
		pos.x += ci::Rand::randFloat(-Constants::Defaults::windowWidth*spread, Constants::Defaults::windowWidth*spread);
		pos.y += ci::Rand::randFloat(-Constants::Defaults::windowHeight*spread, Constants::Defaults::windowHeight*spread);

		b2Body* body = _worldController.createCircle( ci::Rand::randFloat(Constants::Defaults::HEAD_SIZE_MIN, Constants::Defaults::HEAD_SIZE_MAX), pos );
		PhysicsObject* physicsObject = new PhysicsObject( body );
		physicsObject->setupTexture();
		body->SetUserData( physicsObject );
	}
}

void NeruSphereApp::mouseDown( ci::app::MouseEvent event ) {
}

void NeruSphereApp::keyDown( ci::app::KeyEvent event ) {
	if( event.getChar() == ci::app::KeyEvent::KEY_o ) {
//		_gui->setEnabled( !_gui->isEnabled() );
	} else if( event.getChar() == ci::app::KeyEvent::KEY_s) {
		saveImage();
	} else if ( event.getChar() == ci::app::KeyEvent::KEY_f ) {
		setFullScreen( !isFullScreen() );
	}


	if( event.getChar() == ci::app::KeyEvent::KEY_1 ) {
		ci::Vec2f newGravityLocation( getWindowSize().x * 0.25, getWindowCenter().y );
		Constants::Defaults::setGravityPoint( newGravityLocation );
	} else if( event.getChar() == ci::app::KeyEvent::KEY_2 ) {
		ci::Vec2f newGravityLocation( getWindowSize().x * 0.5, getWindowCenter().y );
		Constants::Defaults::setGravityPoint( newGravityLocation );
	} else if( event.getChar() == ci::app::KeyEvent::KEY_3 ) {
		ci::Vec2f newGravityLocation( getWindowSize().x * 0.75, getWindowCenter().y );
		Constants::Defaults::setGravityPoint( newGravityLocation );
	}
}

void NeruSphereApp::saveImage() {
//	std::string _saveDirectory = ci::getHomeDirectory() + "Desktop/NeruSphere/";
//	ci::createDirectories( _saveDirectory );
//
//	std::stringstream filename;
//	filename << _saveDirectory << "Image_" << ci::Rand::randInt( 100000000 ) << ".png";
//
//	ci::writeImage( filename.str(), useFBO ? mFbo.getTexture(0) : copyWindowSurface() );
}
void NeruSphereApp::update() {
	_worldController.update();
//	_audioAnalyzer.update();

	using namespace ci::box2d;
	if(_planetBody) {
//		_worldController.getWorld()->DestroyBody(_planetBody);
	}

	// Shape definition
	b2CircleShape aShape;


	static float lastSize = 1;
//	float newSize = Conversions::toPhysics( Constants::Planet::MIN_SIZE + _audioAnalyzer.getAverageVolume() * Constants::Planet::VOLUME_RANGE );
	float maxSize = getWindowWidth() < getWindowHeight() ? getWindowWidth()*0.49 : getWindowHeight()*0.49;
	float newSize = ci::Rand::randFloat() * maxSize;//ci::math<float>::min( newSize, Conversions::toPhysics( maxSize ) );


	// When the volume increases by a significant amount - push outward
	if( lastSize - newSize < -0.7 ) {

		Constants::Forces::DIRECTION = Constants::Heads::ANTI_GRAVITY * -1;
	} else {
		Constants::Forces::DIRECTION = 1;
	}

	lastSize -= (lastSize - newSize) * Constants::Planet::EASE_SPEED;
	aShape.m_radius = lastSize;


	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &aShape;
	mFixtureDef.friction = 1.0f;
	mFixtureDef.restitution = 0.0f;
	mFixtureDef.density = 1.0f;

	//Constants::Defaults::getGravityPoint()
	static ci::Vec2f currentPosition( 0, getWindowCenter().y * 0.5);

	currentPosition -= (currentPosition - Constants::Defaults::getGravityPoint() ) * 0.2f;
	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_staticBody;
	mBodyDef.position = Conversions::toPhysics( currentPosition  );


//	if( _planetBody )



	if( _planetPhysicsObject ) {
		_planetBody->DestroyFixture( _planetBody->GetFixtureList() );
		_planetBody->CreateFixture( &mFixtureDef );
		_planetBody->SetTransform( mBodyDef.position, 0 );
		_planetPhysicsObject->setBody( _planetBody );
	} else {
		_planetBody = _worldController.getWorld()->CreateBody( &mBodyDef );
		_planetBody->CreateFixture( &mFixtureDef );
		_planetBody->SetUserData( _planetPhysicsObject );

		_planetPhysicsObject = new Planet( _planetBody );
		_planetPhysicsObject->setupTexture();
	}

//	body->SetActive( false );

}

void NeruSphereApp::render() {
	ci::gl::clear( ci::Color(0.05,0.05,0.05) );
	ci::gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );


	gl::enableAlphaBlending();
	gl::disableDepthRead();
	gl::disableDepthWrite();

//	if( Constants::Defaults::DRAW_AUDIO_ANALYZER ) _audioAnalyzer.draw();
	_worldController.draw();

	gl::enableDepthRead();
	gl::enableDepthWrite();
//	if( _planetPhysicsObject ) _planetPhysicsObject->drawImp( _audioAnalyzer.getAverageVolume() * Constants::Planet::VOLUME_RANGE);

//	gl::enableWireframe();
	drawParticles();
}
void NeruSphereApp::draw() {
	render();
}

void NeruSphereApp::drawParticles() {
	ci::gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );
//	texture.enableAndBind();
		glEnableClientState( GL_VERTEX_ARRAY );
//		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
		b2Body* node = _worldController.getWorld()->GetBodyList();
		while( node ) {
			PhysicsObject* physicsObject = (PhysicsObject*) node->GetUserData();
			if( physicsObject && physicsObject->getState() == PhysicsObject::EXPLODING ) {
				glVertexPointer( 3, GL_FLOAT, 0, &(physicsObject->emitter->verts)[0] );
				glTexCoordPointer( 2, GL_FLOAT, 0, &(physicsObject->emitter->texCoords)[0] );
				glColorPointer( 4, GL_FLOAT, 0, &(physicsObject->emitter->colors)[0].r );
				glDrawArrays( GL_TRIANGLES, 0, physicsObject->emitter->verts.size() / 2 );
			}
			node = node->GetNext();
		}
		glDisableClientState( GL_VERTEX_ARRAY );
//		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_COLOR_ARRAY );
//	texture.disable();
}

bool NeruSphereApp::restart( ci::app::MouseEvent event ) {
	_worldController.clear();
	setupHeads();
	setupGUI();

	_planetBody = NULL;
	_planetPhysicsObject = NULL;

	return true;
}

void NeruSphereApp::resize( ci::app::ResizeEvent event ) {
//	if( !useFBO ) {
//		Constants::Defaults::windowWidth = event.getWidth();
//		Constants::Defaults::windowHeight = event.getHeight();
//
//		ci::Vec2f newGravityLocation( getWindowSize().x * 0.5, getWindowCenter().y );
//		Constants::Defaults::setGravityPoint( newGravityLocation );
//	}
}

void NeruSphereApp::shutdown() {
	std::cout << "Shutdown..." << std::endl;
	AppBasic::shutdown();
}