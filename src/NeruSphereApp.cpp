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

void NeruSphereApp::setup() {
	std::cout << "Setting application path: " << getAppPath() << std::endl;
	chdir( getAppPath().c_str( ) );

	_worldController.init( 4, 2 );

	ci::Vec2f size = ci::Vec2f( 10, 10 );
	ci::Vec2f pos = getWindowCenter();

	int count = 400;
	for(int i = 1; i < count; i++) {
		pos.x = i * (float)getWindowSize().x/ (float)count;
		pos.y = ci::Rand::randFloat(-1000, 1000);
		_heads.push_back( _worldController.createCircle( ci::Rand::randFloat(size.x*0.8, size.x*1.5), pos ) );
	}

	using namespace ci::box2d;

	// Shape definition
	b2CircleShape aShape;
	aShape.m_radius = Conversions::toPhysics( 100 );

	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &aShape;
	mFixtureDef.friction = 0.3f;
	mFixtureDef.restitution = 0.8f;
	mFixtureDef.density = 1.0f;

	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_staticBody;
	mBodyDef.position = Conversions::toPhysics( getWindowCenter() );
	b2Body* body = _worldController.getWorld()->CreateBody( &mBodyDef );
	body->CreateFixture( &mFixtureDef );
	_planet = body;

	_perlin = Perlin(4, ci::Rand::randInt(999));

	for(uint32_t j = 0; j < 60 * 30; j++) {
		_worldController.update();
		doGravity(j);
	}

}

void NeruSphereApp::mouseDown( ci::app::MouseEvent event ) {
}

void NeruSphereApp::update() {
	_worldController.update();
	doGravity( getElapsedFrames() );
}

void NeruSphereApp::doGravity( uint32_t noiseZ ) {

	float GRAVITY_FORCE = 700.0f;


	Vec3f noise = _perlin.dfBm( Vec3f( 15.0f, 15.0f, noiseZ * 0.007) ) * 0.45;


	for(std::vector<b2Body*>::const_iterator i = _heads.begin(); i != _heads.end(); ++i) {
		b2Body* body = *i;
		b2Vec2 center = Conversions::toPhysics( getWindowCenter() );
		b2Vec2 pos = body->GetPosition();
		b2Vec2 delta = center - pos;

		float lengthSQ = ci::math<float>::max( delta.LengthSquared(), Conversions::toPhysics(50.0f) );
		float forceScale = ci::math<float>::max(0.6, Conversions::toPhysics( GRAVITY_FORCE ) / lengthSQ);
		delta.Normalize();

		b2Vec2 force = forceScale * delta;
		force.x += noise.x;
		force.y += noise.y;
		body->ApplyForce( force, center );
	}

	_planet->SetTransform( Conversions::toPhysics( getWindowCenter() ), _planet->GetAngle() );
}

void NeruSphereApp::draw() {
	ci::gl::clear( ci::Color(0,0,0) );
	_worldController.draw();
}

CINDER_APP_BASIC( NeruSphereApp, ci::app::RendererGl )
