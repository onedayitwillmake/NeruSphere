/*
 * Constants.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include "cinder/Perlin.h"


namespace Constants {
	struct Instances {
		static ci::Perlin* PERLIN_NOISE() {
			static ci::Perlin noise = ci::Perlin(4,9);
			return &noise;
		}
	};

	struct Forces {
		const static float GRAVITY_FORCE = 800.0f;
	};

	struct Defaults {
		const static int HEAD_COUNT = 350;
		const static bool DEBUG_DRAW = false;
	};

	struct Heads {
		const static int MIN_LIFETIME = 1000;
		const static int MAX_LIFETIME = 3400;

		const static float MAX_SPEED = 27.0f;
		const static float PERLIN_STRENGTH = 0.2f;

		const static float MIN_GRAVITY_DISTANCE = 150.0f;
	};
}
#endif /* CONSTANTS_H_ */
