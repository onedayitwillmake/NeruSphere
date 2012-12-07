/*
 * Constants.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */
#pragma once
#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include "cinder/Perlin.h"
#include "cinder/Vector.h"

namespace Constants {
	struct Instances {
		static ci::Perlin* PERLIN_NOISE() {
			static ci::Perlin noise = ci::Perlin(4,2);
			return &noise;
		}
	};

	namespace Forces {
		extern float GRAVITY_FORCE;
		extern float DIRECTION;
	};

	namespace Defaults {
		extern int HEAD_COUNT;
		extern int HEAD_SIZE_MIN;
		extern int HEAD_SIZE_MAX;
		extern bool DEBUG_DRAW;
		extern bool DRAW_AUDIO_ANALYZER;
		
		extern ci::Vec2f GRAVITY_POINT;
		extern void setGravityPoint( ci::Vec2f newGravityPoint 	);
		extern ci::Vec2f getGravityPoint();
	};

	namespace Heads {
		extern int MIN_LIFETIME;
		extern int MAX_LIFETIME;

		extern float MAX_SPEED;
		extern float PERLIN_STRENGTH;

		extern float MIN_GRAVITY_DISTANCE;
		extern float ANTI_GRAVITY;

		extern int SINGLE_SPRITE_SIZE;
		extern int NUM_SPRITES;
	};

	namespace Planet {
		extern float EASE_SPEED;
		extern float VOLUME_RANGE;
		extern float MIN_SIZE;
	};

	namespace Particles {
		extern int MIN;
		extern int MAX;

		extern float PARTICLE_SIZE_MIN;
		extern float PARTICLE_SIZE_MAX;

		extern float MIN_INITIAL_SPEED;
		extern float MAX_INITIAL_SPEED;
		extern float SPEED_DECAY;

		extern float ALPHA;
	}

	void init();
}
#endif /* CONSTANTS_H_ */
