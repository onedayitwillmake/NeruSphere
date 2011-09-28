/*
 * Constants.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

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

	struct Forces {
		const static float GRAVITY_FORCE = 40000.0f;
	};

	struct Defaults {
		const static int HEAD_COUNT = 30;
		const static int HEAD_SIZE_MIN = 128;
		const static int HEAD_SIZE_MAX = 128;
		const static bool DEBUG_DRAW = false;
	};

	struct Heads {
		const static int MIN_LIFETIME = 1200;
		const static int MAX_LIFETIME = 3000;

		const static float MAX_SPEED = 1075.0f;
		const static float PERLIN_STRENGTH = 0.5f;

		const static float MIN_GRAVITY_DISTANCE = 50.0f * 50.0f; // min distance Squared
	};

	struct Planet {
		const static float EASE_SPEED = 0.8f;
		const static float VOLUME_RANGE = 15.0f;
		const static float MIN_SIZE = 5.0f;
	};
}
#endif /* CONSTANTS_H_ */
