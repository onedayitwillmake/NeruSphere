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
#include "fmod.hpp"
#include "fmod_errors.h"


class AudioAnalyzer
{
public:
	AudioAnalyzer();
	~AudioAnalyzer();

	void	update();
	void	drawFFT();
	
	void	load( std::string filePath );
	void	play();
	void	stop();
	
	float	getAverageVolume() { return mAverageVolume; };

private:
	FMOD::System   *system;
    FMOD::Sound    *sound;
    FMOD::Channel  *channel;
	float			mAverageVolume;
	
	void	stopCurrentTrack();
	void	drawSpectrum( FMOD_DSP_FFT_WINDOW style, int yOffset );
};

#endif /* AUDIOANALYZER_H_ */
