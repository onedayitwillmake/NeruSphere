/*
 * AudioAnalyzer.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#include "AudioAnalyzer.h"
#include "cinder/app/AppBasic.h"
using namespace ci;

AudioAnalyzer::AudioAnalyzer() {
	// TODO Auto-generated constructor stub
	//iterate input devices and print their names to the console
	using namespace ci;
	const std::vector<audio::InputDeviceRef>& devices = audio::Input::getDevices();
	for( std::vector<audio::InputDeviceRef>::const_iterator iter = devices.begin(); iter != devices.end(); ++iter ) {
		std::cout << (*iter)->getName() << std::endl;
	}

	//initialize the audio Input, using the default input device
	mInput = audio::Input();

//	std::cout <<  mInput.getDefaultDevice() << std::endl;



	_averageVolume = 0;

	//tell the input to start capturing audio
	mInput.start();
}

void AudioAnalyzer::update()
{
	mPcmBuffer = mInput.getPcmBuffer();
	if( ! mPcmBuffer ) {
		return;
	}
	uint16_t bandCount = 512;
	//presently FFT only works on OS X, not iOS
	mFftDataRef = audio::calculateFft( mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT ), bandCount );
}

void AudioAnalyzer::draw()
{
	glPushMatrix();
		glTranslatef( 0.0f, ci::app::App::get()->getWindowHeight() -150, 0.0f );
		drawFft();
	glPopMatrix();
}

void AudioAnalyzer::drawWaveForm( float height )
{
	if( ! mPcmBuffer ) {
		return;
	}

	uint32_t bufferSamples = mPcmBuffer->getSampleCount();
	audio::Buffer32fRef leftBuffer = mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT );
	//audio::Buffer32fRef rightBuffer = mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_RIGHT );

	int displaySize = ci::app::App::get()->getWindowWidth();
	int endIdx = bufferSamples;

	//only draw the last 1024 samples or less
	int32_t startIdx = ( endIdx - 1024 );
	startIdx = math<int32_t>::clamp( startIdx, 0, endIdx );

	float scale = displaySize / (float)( endIdx - startIdx );

	PolyLine<Vec2f>	line;

	gl::color( Color( 1.0f, 0.5f, 0.25f ) );
	for( uint32_t i = startIdx, c = 0; i < endIdx; i++, c++ ) {
		float y = ( ( leftBuffer->mData[i] - 1 ) * - 100 );
		line.push_back( Vec2f( ( c * scale ), y ) );
	}
	gl::draw( line );
}

void AudioAnalyzer::drawFft()
{
	return;
	uint16_t bandCount = 512;
	float ht = 1000.0f;
	float bottom = 150.0f;

	if( ! mFftDataRef ) {
		return;
	}

	float * fftBuffer = mFftDataRef.get();


	float average = 0;
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, 0.0f );


//	int counter = 0;
	for( int i = 0; i < ( bandCount ); i++ ) {
		float barY = fftBuffer[i] / bandCount * ht;
		average += barY;
		float delta = bottom - barY;


	//	gl::rotate( i/(float)bandCount/360 );
		float size = 10;
		glBegin( GL_QUADS );
			glColor3f( 255.0f, 255.0f, 0.0f );
			glVertex2f( i * size, bottom );
			glVertex2f( i * size + size/2, bottom );
			glColor3f( 0.0f, 255.0f, 0.0f );
			glVertex2f( i * size + size/2, bottom - barY );
			glVertex2f( i * size, bottom - barY );
		glEnd();
	}
	glPopMatrix();
	_averageVolume = average/(bandCount/2);
}

AudioAnalyzer::~AudioAnalyzer() {
	// TODO Auto-generated destructor stub
}
