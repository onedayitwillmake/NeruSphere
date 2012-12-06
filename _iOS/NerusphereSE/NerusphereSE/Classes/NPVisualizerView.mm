//
//  NPVisualizerView.m
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/4/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import "NPVisualizerView.h"
#import "Constants.h"
#import "Textures.h"
#import "cinder/Rand.h"
#import "cinder/ImageIo.h"
#import "AppInfo.h"

@implementation NPVisualizerView

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
		_planetBody = NULL;
		_planet = NULL;
    }
    return self;
}

-(void)dealloc {
	_planetBody = NULL;
	_planet = NULL;
}

-(void)prepareSettings {
	[self enableAntiAliasing];
}

-(void)setup {
	
	
	_elapsedFrames = 0;
	AppInfo::getInstance().setWindowSize(self.frame.size.width, self.frame.size.height);
	
	
	DataSourcePathRef ref = [self loadResource:"gromacirclepink.png"];
	ci::gl::Texture::Format format;
	format.enableMipmapping( false );
	format.setMinFilter( GL_NEAREST );
	format.setMagFilter( GL_NEAREST );
	ci::gl::Texture* texture = new ci::gl::Texture( ci::loadImage( ref ) , format );
	Constants::Textures::getPlanetTexture( texture );
	
	
	Constants::init();
	Constants::Defaults::setGravityPoint( [self getWindowCenter] );
	
	_worldController.init( 4, 2 );

	
	[super setup];
	
}

-(void)createHeads {
//	int count = Constants::Defaults::HEAD_COUNT;
//	float spread = 0.4f;
//	for(int i = 1; i <= count; i++) {
//		ci::Vec2f pos = Constants::Defaults::[self getWindowCenter];
//		pos.x += ci::Rand::randFloat(-Constants::Defaults::windowWidth*spread, Constants::Defaults::windowWidth*spread);
//		pos.y += ci::Rand::randFloat(-Constants::Defaults::windowHeight*spread, Constants::Defaults::windowHeight*spread);
//		
//		b2Body* body = _worldController.createCircle( ci::Rand::randFloat(Constants::Defaults::HEAD_SIZE_MIN, Constants::Defaults::HEAD_SIZE_MAX), pos );
//		PhysicsObject* physicsObject = new PhysicsObject( body );
//		physicsObject->setupTexture();
//		body->SetUserData( physicsObject );
//	}
}

-(void)update {
	
	// First run
	if(!_planet) {
		// Create planet b2Body
		b2CircleShape shape;
		shape.m_radius = 3;
		
		b2FixtureDef mFixtureDef;
		mFixtureDef.shape = &shape;
		b2BodyDef mBodyDef;
		mBodyDef.type = b2_staticBody;
		mBodyDef.position = cinder::box2d::Conversions::toPhysics( [self getWindowCenter]  );
		
		_planetBody = _worldController.getWorld()->CreateBody( &mBodyDef );
		_planetBody->CreateFixture( &mFixtureDef );
		_planet = new Planet( _planetBody );
		_planet->setupTexture();
		_planetBody->SetUserData( _planet );
	}
	
	
	AppInfo::getInstance().setElapsedSeconds([self getElapsedSeconds]);
	AppInfo::getInstance().setElapsedFrames( ++_elapsedFrames );
	
	_worldController.update();
	return;
	//	_audioAnalyzer.update();
	
	using namespace ci::box2d;
	if(_planetBody) {
		//_worldController.getWorld()->DestroyBody(_planetBody);
	}
	
	
	
	
	static float lastSize = 1;
	//	float newSize = Conversions::toPhysics( Constants::Planet::MIN_SIZE + _audioAnalyzer.getAverageVolume() * Constants::Planet::VOLUME_RANGE );
	float maxSize = [self getWindowWidth] < [self getWindowHeight] ? [self getWindowWidth]*0.49 : [self getWindowHeight]*0.49;
	float newSize = ci::Rand::randFloat() * maxSize;//ci::math<float>::min( newSize, Conversions::toPhysics( maxSize ) );
	
	
	// When the volume increases by a significant amount - push outward
	if( lastSize - newSize < -0.7 ) {
		
		Constants::Forces::DIRECTION = Constants::Heads::ANTI_GRAVITY * -1;
	} else {
		Constants::Forces::DIRECTION = 1;
	}
	
	lastSize -= (lastSize - newSize) * Constants::Planet::EASE_SPEED;
	static uint32_t i = 0;
	
	// Shape definition
	b2CircleShape aShape;
	aShape.m_radius = i++;
	
	
	// Fixture definition
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &aShape;
	mFixtureDef.friction = 1.0f;
	mFixtureDef.restitution = 0.0f;
	mFixtureDef.density = 1.0f;
	
	//Constants::Defaults::getGravityPoint()
	static ci::Vec2f currentPosition( 0, [self getWindowCenter].y * 0.5);
	
	currentPosition -= (currentPosition - Constants::Defaults::getGravityPoint() ) * 0.2f;
	// Body definition
	b2BodyDef mBodyDef;
	mBodyDef.type = b2_staticBody;
	mBodyDef.position = Conversions::toPhysics( currentPosition  );
	

	_planetBody->DestroyFixture( _planetBody->GetFixtureList() );
	_planetBody->CreateFixture( &mFixtureDef );
	_planetBody->SetTransform( mBodyDef.position, 0 );
}

-(void)draw {
	[self update];
	ci::gl::clear( ci::Color::black() );
	
//	ci::gl::draw( *(_planetPhysicsObject->getTexture()), [self getWindowCenter] );
//	return;
//	ci::gl::color( ColorA(ci::Rand::randFloat(), 1.0f, 1.0f, 1.0f ) );
//	
//	gl::setMatricesWindow([self getWindowWidth], [self getWindowHeight]);
	
//	gl::enableAlphaBlending();
//	gl::disableDepthRead();
//	gl::disableDepthWrite();
	
	//	if( Constants::Defaults::DRAW_AUDIO_ANALYZER ) _audioAnalyzer.draw();
	_worldController.draw();
	
//	gl::enableDepthRead();
//	gl::enableDepthWrite();
//	
//	if( _planetPhysicsObject )
//		_planetPhysicsObject->drawImp( cinder::Rand::randFloat() * Constants::Planet::VOLUME_RANGE);
	
	//	gl::enableWireframe();
}

-(void)drawParticles {
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

-(void)reset {
	_worldController.clear();
	[self createHeads];
	
	_planetBody = NULL;
	_planet = NULL;
}

-(ci::Vec2f)getWindowCenter {
	return ci::Vec2f([self getWindowWidth]*0.5, [self getWindowHeight]*0.5);
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
