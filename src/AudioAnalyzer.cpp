///*
// * AudioAnalyzer.cpp
// *
// *  Created on: Sep 25, 2011
// *      Author: onedayitwillmake
// */
//
//#include "AudioAnalyzer.h"
//#include "cinder/app/AppBasic.h"
//#include "cinder/Utilities.h"
//using namespace ci;
//
//AudioAnalyzer::AudioAnalyzer() {
//	// TODO Auto-generated constructor stub
//	//iterate input devices and print their names to the console
//	std::string inputDeviceNames[] = {"4PR909", "Built-in Microphone", "Built-in Input"};
//
//
//	//iterate input devices and print their names to the console
////	const std::vector<audio::InputDeviceRef>& devices = audio::Input::getDevices();
////	for( std::vector<audio::InputDeviceRef>::const_iterator iter = devices.begin(); iter != devices.end(); ++iter ) {
////		std::cout << (*iter)->getName() << std::endl;
////	}
//
//	//initialize the audio Input, using the default input device
//	mInput = audio::Input();
//	ci::sleep( 3000 );
//
//
////	mInput = audio::Input::getDefaultDevice();
////	std::cout <<  mInput.getDefaultDevice()->getName() << std::endl;
//
//
//
//	_averageVolume = 0;
//
//	//tell the input to start capturing audio
//	mInput.start();
//}
//
//void AudioAnalyzer::update()
//{
//	mPcmBuffer = mInput.getPcmBuffer();
//	if( ! mPcmBuffer ) {
//		return;
//	}
//
//	uint16_t bandCount = 512;
//	//presently FFT only works on OS X, not iOS
//	mFftDataRef = audio::calculateFft( mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT ), bandCount );
//	if( ! mFftDataRef ) {
//		return;
//	}
//
//	float * fftBuffer = mFftDataRef.get();
//
//	float average = 0;
//	float ht = 1000.0f;
//	for( int i = 0; i < ( bandCount ); i++ ) {
//		average += fftBuffer[i] / bandCount * ht;
//	}
//	_averageVolume = average/(bandCount/2);
//}
//
//void AudioAnalyzer::draw() {
//	glPushMatrix();
//		glTranslatef( 0.0f, ci::app::App::get()->getWindowHeight() -150, 0.0f );
//		drawFft();
//	glPopMatrix();
//}
//
//void AudioAnalyzer::drawFft()
//{
//	uint16_t bandCount = 512;
//	float ht = 1000.0f;
//	float bottom = 150.0f;
//
//	if( ! mFftDataRef ) {
//		return;
//	}
//
//	float * fftBuffer = mFftDataRef.get();
//
//
//
//	glPushMatrix();
//	glTranslatef( 0.0f, 0.0f, 0.0f );
//
//
//	float bandColor = 1.0 / 6.0f;
//	float halfBandColor = bandColor * 0.5f;
//
//	for( int i = 0; i < ( bandCount ); i++ ) {
//		float barY = fftBuffer[i] / bandCount * ht;
//		float delta = bottom - barY;
//
//		float size = 10;
//		glBegin( GL_QUADS );
//			glColor3f( halfBandColor, halfBandColor, halfBandColor );
//			glVertex2f( i * size, bottom );
//			glVertex2f( i * size + size/2, bottom );
//			glColor3f( bandColor, bandColor, bandColor );
//			glVertex2f( i * size + size/2, bottom - barY );
//			glVertex2f( i * size, bottom - barY );
//		glEnd();
//	}
//	glPopMatrix();
//}
//
//AudioAnalyzer::~AudioAnalyzer() {
//	// TODO Auto-generated destructor stub
//}
