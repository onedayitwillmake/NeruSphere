/*
 * AudioAnalyzer.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "AudioAnalyzer.h"
#include "cinder/gl/gl.h"
#include "cinder/PolyLine.h"
#include "cinder/Color.h"

#include "AppInfo.h"

AudioAnalyzer::AudioAnalyzer() {}
AudioAnalyzer::~AudioAnalyzer() {
	stopCurrentTrack();
}

// Runs update logic
void AudioAnalyzer::update() {
	// Check if track is playing and has a PCM buffer available
	if ( mTrack->isPlaying() && mTrack->isPcmBuffering() ) {
		
		// Get buffer
		mBuffer = mTrack->getPcmBuffer();
		if ( mBuffer && mBuffer->getInterleavedData() ) {
			
			// Get sample count
			uint32_t sampleCount = mBuffer->getInterleavedData()->mSampleCount;
			if ( sampleCount > 0 ) {
				
				// Initialize analyzer
				if ( !mFft ) {
					mFft = Kiss::create( sampleCount );
				}
				
				// Analyze data
				if ( mBuffer->getInterleavedData()->mData != 0 ) {
					mFft->setData( mBuffer->getInterleavedData()->mData );
				}
			}
		}
	}
}

void AudioAnalyzer::loadTrack( std::string filePath ) {
	stopCurrentTrack();
	
	// Load and play audio
	std::cout << filePath << std::endl;
	mAudioSource = ci::audio::load( filePath );
	mTrack = ci::audio::Output::addTrack( mAudioSource, false );
	mTrack->enablePcmBuffering( true );
	mTrack->play();
}

// Stop track
void AudioAnalyzer::stopCurrentTrack() {
	if( mTrack ) {
		mTrack->enablePcmBuffering( false );
		mTrack->stop();
	}
	
	if ( mFft ) {
		mFft->stop();
	}
}



void AudioAnalyzer::drawFFT() {
	// Clear screen
	ci::gl::clear( ci::ColorAf::black() );
	
	// Check init flag
	if ( mFft ) {
		
		// Get data in the frequency (transformed) and time domains
		float * freqData = mFft->getAmplitude();
		float * timeData = mFft->getData();
		int32_t dataSize = mFft->getBinSize();
		
		// Cast data size to float
		float dataSizef = (float)dataSize;
		
		// Get dimensions
		float scale = ( (float)AppInfo::getInstance().getWindowWidth() - 20.0f ) / dataSizef;
		float windowHeight = (float)AppInfo::getInstance().getWindowHeight();
		
		// Use polylines to depict time and frequency domains
		ci::PolyLine<ci::Vec2f> freqLine;
		ci::PolyLine<ci::Vec2f> timeLine;
		
		// Iterate through data
		for ( int32_t i = 0; i < dataSize; i++ ) {
			
			// Do logarithmic plotting for frequency domain
			float logSize = ci::math<float>::log( dataSizef );
			float x = (float)( ( ci::math<float>::log( (float)i ) / logSize ) * dataSizef );
			float y = ci::math<float>::clamp( freqData[ i ] * ( x / dataSizef ) * ( ci::math<float>::log( ( dataSizef - (float)i ) ) ), 0.0f, 2.0f );
			
			// Plot points on lines for tme domain
			freqLine.push_back( ci::Vec2f(        x * scale + 10.0f,            -y * ( windowHeight - 20.0f ) * 0.25f + ( windowHeight - 10.0f ) ) );
			timeLine.push_back( ci::Vec2f( (float)i * scale + 10.0f, timeData[ i ] * ( windowHeight - 20.0f ) * 0.25f + ( windowHeight * 0.25f + 10.0f ) ) );
			
		}
		
		// Draw signals
		ci::gl::draw( freqLine );
		ci::gl::draw( timeLine );
	}

}
