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
#include "cinder/app/Event.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Rand.h"
#include "gl.h"
#include "WorldController.h"
#include "Conversions.h"
#include "cinder/CinderMath.h"
#include "cinder/Perlin.h"
#include <vector>

using namespace ci::box2d;
using namespace ci;
class NeruSphereApp : public ci::app::AppBasic {
public:
	WorldController _worldController;
	std::vector<b2Body*> _heads;
	b2Body* _planet;
	Perlin _perlin;

	void setup();
	void prepareSettings( ci::app::AppBasic::Settings *settings );
	void mouseDown( ci::app::MouseEvent event );
	void update();
	void doGravity(uint32_t noiseZ);
	void draw();
};

void NeruSphereApp::prepareSettings( ci::app::AppBasic::Settings *settings ) {
	settings->setWindowSize( 800, 600 );
}


static float planetsize = 200;
void NeruSphereApp::mouseDown( ci::app::MouseEvent event ) {


	if(_planet) {
		_worldController.getWorld()->DestroyBody( _planet );
	}

	Vec3f noise = _perlin.dfBm( Vec3f(getWindowCenter().y, getWindowCenter().x, getElapsedFrames() * 0.3) );
	float amount = 5;
	float delta = noise.x > 0 ? -amount : amount*1.01;

	planetsize = ci::math<float>::clamp( delta + planetsize, 50, 300 );

	// Shape definition
	b2CircleShape aShape;
	aShape.m_radius = Conversions::toPhysics( planetsize );

	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &aShape;
	mFixtureDef.friction = 1.0f;
	mFixtureDef.restitution = 1.0f;
	mFixtureDef.density = 1.0f;

	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_kinematicBody;
	mBodyDef.position = Conversions::toPhysics( getWindowCenter() );
	b2Body* body = _worldController.getWorld()->CreateBody( &mBodyDef );
	body->CreateFixture( &mFixtureDef );
	_planet = body;

}

void NeruSphereApp::setup() {
	std::cout << "Setting application path: " << getAppPath() << std::endl;
	chdir( getAppPath().c_str( ) );

	_worldController.init( 4, 2 );

	ci::Vec2f size = ci::Vec2f( 15, 15 );
	ci::Vec2f pos = getWindowCenter();

	int count = 200;
	for(int i = 1; i < count; i++) {
		pos.x = i * (float)getWindowSize().x/ (float)count;
		pos.y = ci::Rand::randFloat(-1000, 1000);
		_heads.push_back( _worldController.createCircle( ci::Rand::randFloat(size.x*0.8, size.x*1.5), pos ) );
	}


	_perlin = Perlin(4, ci::Rand::randInt(999));
	_planet = NULL;

	for(uint32_t j = 0; j < 60 * 10; j++) {
		_worldController.update();
		doGravity(j);
	}

}

void NeruSphereApp::update() {
	_worldController.update();

	ci::app::MouseEvent fakeEvent;
	mouseDown( fakeEvent );
	doGravity( getElapsedFrames() );
}

void NeruSphereApp::doGravity( uint32_t noiseZ ) {

	float GRAVITY_FORCE = 400.0f;


	Vec3f noise = _perlin.dfBm( Vec3f(getWindowCenter().x, getWindowCenter().y, noiseZ * 0.007) ) * 0.45;
	GRAVITY_FORCE =  noise.x < -0.2 ? GRAVITY_FORCE*-0.1 : GRAVITY_FORCE;
//	noise *= 0.25;
	for(std::vector<b2Body*>::const_iterator i = _heads.begin(); i != _heads.end(); ++i) {
		b2Body* body = *i;
		b2Vec2 center = Conversions::toPhysics( getWindowCenter() );
		b2Vec2 pos = body->GetPosition();
		b2Vec2 delta = center - pos;

		float lengthSQ = ci::math<float>::max( delta.LengthSquared(), Conversions::toPhysics(100.0f) );

		float forceScale;
		if(GRAVITY_FORCE > 0)
			 forceScale = ci::math<float>::max(0.6, Conversions::toPhysics( GRAVITY_FORCE ) / lengthSQ);
		else
			forceScale = ci::math<float>::max(-0.6, Conversions::toPhysics( GRAVITY_FORCE ) / lengthSQ);
		delta.Normalize();

		Vec3f noise = _perlin.dfBm( Vec3f(pos.x, pos.y, noiseZ * 0.007) ) * 0.45;
		b2Vec2 force = forceScale * delta;
		force.x += -noise.x;
		force.y += noise.y;
		body->ApplyForce( force, center );
	}

	if(_planet)
		_planet->SetTransform( Conversions::toPhysics( getWindowCenter() ), _planet->GetAngle() );
}

void NeruSphereApp::draw() {
	ci::gl::clear( ci::Color(0,0,0) );
	_worldController.draw();
}

CINDER_APP_BASIC( NeruSphereApp, ci::app::RendererGl(0) )
