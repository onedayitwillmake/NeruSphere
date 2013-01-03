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
#import "NPAudioConverter.h"
#import "NPConstants.h"
#include <time.h>

@implementation NPVisualizerView

-(void)prepareSettings {
	[self enableAntiAliasing];
	[super prepareSettings];
}

-(void)setup {
	_lastElapsedSeconds = [self getElapsedSeconds];
	
	// Load textures
	std::string bundlePath = std::string( [NPkConstants bundlePathAsCString] );
	
	// Initialize constants
	AppInfo::getInstance().setWindowSize(self.frame.size.width, self.frame.size.height);
	AppInfo::getInstance().setElapsedFrames( 0 );
	
	Constants::init();
	Constants::Defaults::setGravityPoint( AppInfo::getInstance().getWindowCenter() );
	Constants::Textures::loadTextures( bundlePath );
	
	// Start Box2D
	_worldController.init( 4, 2 );
	_worldController.createHeads( Constants::Defaults::HEAD_COUNT );
	
	[super setup];
//	[self startQueue];
}

-(void)startQueue {
	dispatch_queue_t aQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
	dispatch_async(aQueue, ^{
		while(true) {
			int milisec = 16; // length of time to sleep, in miliseconds
			struct timespec req = {0};
			req.tv_sec = 0;
			req.tv_nsec = milisec * 1000000L;
//			nanosleep(&req, (struct timespec *)NULL);
//			NSLog(@"Wake up!");
			
		}
    });
	
	
}
-(void)startAudioAnalyzer {
	std::string bundlePath = std::string( [NPkConstants bundlePathAsCString] );
	
	// Load last file written if exist, if not use FOG during dev
	if( [[NPAudioConverter sharedConverter] lastFileWritten] ) {
		_audioAnalyzer.load( std::string([[[NPAudioConverter sharedConverter] lastFileWritten] cStringUsingEncoding:NSUTF8StringEncoding]));
		_audioAnalyzer.play();
	} else {
		_audioAnalyzer.load( bundlePath + "/2-Fog.mp3");
	}
}
-(void)update {
	AppInfo::getInstance().setElapsedSeconds([self getElapsedSeconds]);
	AppInfo::getInstance().setElapsedFrames( AppInfo::getInstance().getElapsedFrames() + 1 );
	
	double delta = [self getElapsedSeconds] - _lastElapsedSeconds;
	_worldController.update( delta );
	_audioAnalyzer.update();
	
	// Update planet size to match volume
	static float lastSize = 1;
	float scale = _audioAnalyzer.getAverageVolume() / 0.05;
	float newSize = 0;
//	NSLog(@"%0.2f", scale);
	
	// Scale based on audio average volume, if no audio is playing use perlin noise
	if( _audioAnalyzer.getIsPlaying() ){
		newSize = cinder::box2d::Conversions::toPhysics( Constants::Defaults::HEAD_SIZE_MAX * scale );//
	} else {
		newSize = fabs( cinder::box2d::Conversions::toPhysics( Constants::Instances::PERLIN_NOISE()->noise( AppInfo::getInstance().getWindowCenter().x, AppInfo::getInstance().getElapsedFrames() * 0.02) + 0.1 ) * 1024 );
	}
	
	float maxSize = [self getWindowWidth] < [self getWindowHeight] ? [self getWindowWidth]*0.49 : [self getWindowHeight]*0.49;
	newSize = ci::math<float>::min( newSize, cinder::box2d::Conversions::toPhysics( maxSize ) );
	_worldController.setPlanetSize( newSize );
	
	_lastElapsedSeconds = [self getElapsedSeconds];
}

-(void)draw {
	[self update];
//	ci::gl::clear( ci::Color::black() );
	_audioAnalyzer.drawFFT();
	
	gl::enableAlphaBlending();
	
	//if( Constants::Defaults::DRAW_AUDIO_ANALYZER ) _audioAnalyzer.draw();
	_worldController.draw();
	
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAdditiveBlending();
	[self drawParticles];
	_worldController.getPlanet()->drawSphere();
	gl::disableDepthRead();
	gl::disableDepthWrite();
}

-(void)drawParticles {
	ci::gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f ) );

	glEnableClientState( GL_VERTEX_ARRAY );
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
	glDisableClientState( GL_COLOR_ARRAY );
}

-(void)reset {
	_worldController.clear();
	_worldController.createHeads( Constants::Defaults::HEAD_COUNT );
}

@end
