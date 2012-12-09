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
	
	float getAverageVolume() { return mAverageVolume; };
	
private:
	// Audio file
	ci::audio::SourceRef		mAudioSource;
	ci::audio::PcmBuffer32fRef	mBuffer;
	ci::audio::TrackRef			mTrack;
	std::shared_ptr<float>		mFftDataRef;
	
	// Analyzer
	KissRef						mFft;
	float						mAverageVolume;
	
	void stopCurrentTrack();
};

#endif /* AUDIOANALYZER_H_ */
