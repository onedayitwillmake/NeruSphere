//
//  MyCCGLView.mm
//  CCGLTouchBasic example
//
//  Created by Matthieu Savary on 09/09/11.
//  Copyright (c) 2011 SMALLAB.ORG. All rights reserved.
//
//  More info on the CCGLTouch project >> http://cocoacid.org/ios/
//  License & disclaimer >> see license.txt file included in the distribution package
//
//  Latest revision on 10/06/12.
//

#import "MyCCGLView.h"

@implementation MyCCGLView

/**
 *	The prepareSettings & setup method
 */

- (void)prepareSettings {
    [self enableAntiAliasing];
//    frameRate = 30;
}

- (void)setup
{
    // Comment the following line to simply override, if you want to not animate
    // automatically, to change the default viewport, to not use CCGLTouch's OpenGLES
    // default params... Check this method in the super class implementation for
    //  more details on what happens.
//    [super setup];
//
//    // setup the camera
//	mCam.lookAt( Vec3f(-100.0f, 20.0f, 10.0f), Vec3f::zero() );
//	mCam.setPerspective( 60.0f, [self getWindowAspectRatio], 1.0f, 1000.0f );
//	
//    // init value
//    mCubeSize = 10;
	
	
	Constants::Textures::loadTextures();
	Constants::init();
	Constants::Defaults::setGravityPoint( getWindowCenter() );
	
	
	_planetBody = NULL;
	_planetPhysicsObject = NULL;
	
	_worldController.init( 4, 2 );
	[self setupHeads];
}

-(void)setupHeads {
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

-(void)update {
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
}

- (void)draw {
	[self update];
	
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

-(void)restart {
	_worldController.clear();
	[self setupHeads];
	
	_planetBody = NULL;
	_planetPhysicsObject = NULL;
}

-(void)setCubeSize:(float)size {
}


-(void)mouseDown:( ci::app::MouseEvent )event {
	
}


@end
