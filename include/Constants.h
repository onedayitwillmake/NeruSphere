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
#include "cinder/app/App.h"

namespace Constants {
	struct Instances {
		static ci::Perlin* PERLIN_NOISE() {
			static ci::Perlin noise = ci::Perlin(4,2);
			return &noise;
		}
	};

	namespace Forces {
		extern float GRAVITY_FORCE;
	};

	namespace Defaults {
		extern int HEAD_COUNT;
		extern int HEAD_SIZE_MIN;
		extern int HEAD_SIZE_MAX;
		extern bool DEBUG_DRAW;
	};

	namespace Heads {
		extern int MIN_LIFETIME;
		extern int MAX_LIFETIME;

		extern float MAX_SPEED;
		extern float PERLIN_STRENGTH;

		extern float MIN_GRAVITY_DISTANCE;
	};

	namespace Planet {
		extern float EASE_SPEED;
		extern float VOLUME_RANGE;
		extern float MIN_SIZE;
	};

	void init();
}
#endif /* CONSTANTS_H_ */
