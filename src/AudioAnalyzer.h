///*
// * AudioAnalyzer.h
// *
// *  Created on: Sep 25, 2011
// *      Author: onedayitwillmake
// */
//
//#include "cinder/gl/gl.h"
//#include "cinder/audio/Io.h"
//#include "cinder/audio/Input.h"
//#include "cinder/audio/Output.h"
//#include "cinder/audio/FftProcessor.h"
//#include "cinder/audio/PcmBuffer.h"
//
//#ifndef AUDIOANALYZER_H_
//#define AUDIOANALYZER_H_
//
//class AudioAnalyzer
//{
//	public:
//		AudioAnalyzer();
//		virtual ~AudioAnalyzer();
//
//
//		void update();
//		void draw();
//
//		////// ACCESSORS
//		float getAverageVolume() { return _averageVolume; };
//
//	private:
//		void drawFft();
//		void drawWaveForm( float height );
//
//		float _averageVolume;
//		ci::audio::Input mInput;
//		std::shared_ptr<float> mFftDataRef;
//		ci::audio::PcmBuffer32fRef mPcmBuffer;
//};
//
//#endif /* AUDIOANALYZER_H_ */
