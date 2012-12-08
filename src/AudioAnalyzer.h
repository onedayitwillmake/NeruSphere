/*
 * AudioAnalyzer.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef AUDIOANALYZER_H_
#define AUDIOANALYZER_H_

#include "cinder/audio/Io.h"
#include "cinder/audio/Output.h"
#include "cinder/CinderMath.h"
#include "KissFFT.h"


class AudioAnalyzer
{
public:
	AudioAnalyzer();
	~AudioAnalyzer();

	void update();
	void drawFFT();
	void loadTrack( std::string filePath );
	
	KissRef	getFFT() { return mFft; };
	
private:
	// Audio file
	ci::audio::SourceRef		mAudioSource;
	ci::audio::PcmBuffer32fRef	mBuffer;
	ci::audio::TrackRef			mTrack;
	
	// Analyzer
	KissRef						mFft;
	
	void stopCurrentTrack();
};

#endif /* AUDIOANALYZER_H_ */
