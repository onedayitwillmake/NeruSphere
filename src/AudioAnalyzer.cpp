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

#include "fmod.h"
#include "fmod_errors.h"


/// Exit on error
void ERRCHECK(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        fprintf(stderr, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

AudioAnalyzer::AudioAnalyzer() {
	system  = NULL;
    sound	= NULL;
	channel = NULL;
	
	FMOD_RESULT   result        = FMOD_OK;
    unsigned int  version       = 0;
	
    /*
	 Create a System object and initialize
	 */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);
    
    result = system->getVersion(&version);
    ERRCHECK(result);
    
    if (version < FMOD_VERSION) {
        fprintf(stderr, "You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        exit(-1);
    }
    
    result = system->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL);
    ERRCHECK(result);
}

AudioAnalyzer::~AudioAnalyzer() {
	stop();
	sound->release();
	system->close();
	
	system = NULL;
	sound = NULL;
	channel = NULL;
}

// Runs update logic
void AudioAnalyzer::update() {
	
    FMOD_RESULT     result          = FMOD_OK;
    bool            playing         = false;
    bool            paused          = false;
    unsigned int    ms              = 0;
    unsigned int    lenms           = 0;
    int             channelsplaying = 0;
    
    if (channel != NULL) {
        FMOD::Sound *currentsound = NULL;
        
        result = channel->isPlaying(&playing);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
            ERRCHECK(result);
        }
        
        result = channel->getPaused(&paused);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
            ERRCHECK(result);
        }
        
        result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
            ERRCHECK(result);
        }
        
        result = channel->getCurrentSound(&currentsound);
		
		
        if (currentsound != NULL) {
            result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                ERRCHECK(result);
            }
        }
		
	}
	
    if (system != NULL ) {
        result = system->getChannelsPlaying(&channelsplaying);
        ERRCHECK(result);
        
        result = system->update();
        ERRCHECK(result);
    }
	
	_isPlaying = playing && !paused;
	_songTime = ms;
	_songDuration = lenms;
}

// Load and start strack
void AudioAnalyzer::load( std::string filePath ) {
	if( sound ) sound->release();
	
	// Load sound
	FMOD_RESULT   result        = FMOD_OK;
    result = system->createSound(filePath.c_str(), FMOD_SOFTWARE, NULL, &sound);
    ERRCHECK(result);
}

// Play sound
void AudioAnalyzer::play() {
	stop();

	FMOD_RESULT   result        = FMOD_OK;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	ERRCHECK(result);
}

// Stop track
void AudioAnalyzer::stop() {
	if( channel ) channel->stop();
}


void AudioAnalyzer::drawFFT() {
	ci::gl::clear( ci::ColorAf::black() );
	if ( channel ) {
		ci::gl::color( ci::ColorA(0, 1.0, 0.0, 1.0f ) );
		drawSpectrum( FMOD_DSP_FFT_WINDOW_RECT, -100 );
	}
}

void AudioAnalyzer::drawSpectrum( FMOD_DSP_FFT_WINDOW style, int yOffset ) {
	float windowHeight = (float)AppInfo::getInstance().getWindowHeight();
	
	// Get data in the frequency (transformed) and time domains
	int32_t specLen = 128;
	float* specData = (float*)malloc(specLen*sizeof(float));
	channel->getWaveData( specData, specLen, 0 );
	
	// Cast data size to float
	float specLenf = (float)specLen;
	
	// Get dimensions
	float scale = ( (float)AppInfo::getInstance().getWindowWidth() - 20.0f ) / specLenf;
	
	// Use polylines to depict time and frequency domains
	ci::PolyLine<ci::Vec2f> freqLine;
	
	/*
	 float* data = mFft->getData(); // Gets normalized input data
	 int32_t binSize = mFft->getBinSize();
	 float sum = 0.0f;
	 for ( int32_t i = 0; i < binSize; ++i ) {
	 sum += math<float>::pow( data[ i ], 2.0f );
	 }
	 float averageVolume = math<float>::sqrt( sum / (float)binSize );

	 */
	// Iterate through data
	double sum = 0;
	for ( int32_t i = 0; i < specLen; i++ ) {
		
		// Do logarithmic plotting for frequency domain
		float logSize = ci::math<float>::log( specLenf );
		float x = (float)( ( ci::math<float>::log( (float)i ) / logSize ) * specLenf );
		float y = ci::math<float>::clamp( specData[ i ] * ( x / specLenf ) * ( ci::math<float>::log( ( specLenf - (float)i ) ) ), 0.0f, 2.0f ) + yOffset;
		sum += ci::math<float>::pow( specData[ i ], 2.0f );
		
		// Plot points on lines for tme domain
		freqLine.push_back( ci::Vec2f(        x * scale + 10.0f,
									  -y * ( windowHeight - 20.0f ) * 0.25f + ( windowHeight - 10.0f ) + yOffset)  );
	}
	
	_averageVolume = ci::math<float>::sqrt( sum / specLenf );;
//	std::cout << "Volume:" << _averageVolume << std::endl;
	
	// Draw signals
	ci::gl::draw( freqLine );
}


