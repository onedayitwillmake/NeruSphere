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
			static ci::Perlin noise = ci::Perlin(4,2);
			return &noise;
		}
	};

	struct Forces {
		const static float GRAVITY_FORCE = 800.0f;
	};

	struct Defaults {
		const static int HEAD_COUNT = 400;
		const static bool DEBUG_DRAW = false;
	};
}
#endif /* CONSTANTS_H_ */
