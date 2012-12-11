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
#include "fmod.hpp"


class AudioAnalyzer
{
public:
	AudioAnalyzer();
	~AudioAnalyzer();
	
	// Player actions
	void	load( std::string filePath );
	void	play();
	void	stop();
	
	// Updates information
	void	update();
	void	drawFFT();
	
	// Song properties
	float		getAverageVolume() { return _averageVolume; };
	uint32_t	getSongTime() { return _songTime; };
	uint32_t	getSongDuration() { return _songDuration; };
	bool		getIsPlaying() { return _isPlaying; };
	
private:
	FMOD::System   *system;
    FMOD::Sound    *sound;
    FMOD::Channel  *channel;
	
	float			_averageVolume;
	
	uint32_t		_songTime;
	uint32_t		_songDuration;
	bool			_isPlaying;
	
	void	stopCurrentTrack();
	void	drawSpectrum( FMOD_DSP_FFT_WINDOW style, int yOffset );
};

#endif /* AUDIOANALYZER_H_ */
