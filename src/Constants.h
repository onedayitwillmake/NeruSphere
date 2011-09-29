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
		static float GRAVITY_FORCE;
	};

	struct Defaults {
		static int HEAD_COUNT;
		static int HEAD_SIZE_MIN;
		static int HEAD_SIZE_MAX;
		static bool DEBUG_DRAW;
	};

	struct Heads {
		static int MIN_LIFETIME;
		static int MAX_LIFETIME;

		static float MAX_SPEED;
		static float PERLIN_STRENGTH;

		static float MIN_GRAVITY_DISTANCE;
	};

	struct Planet {
		static float EASE_SPEED;
		static float VOLUME_RANGE;
		static float MIN_SIZE;
	};

	static void init() {
		Constants::Forces::GRAVITY_FORCE = 40000.0f;

		Constants::Defaults::HEAD_COUNT = 30;
		Constants::Defaults::HEAD_SIZE_MIN = 128;
		Constants::Defaults::HEAD_SIZE_MAX = 128;
		Constants::Defaults::DEBUG_DRAW = false;

		Constants::Heads::MIN_LIFETIME = 1200;
		Constants::Heads::MAX_LIFETIME = 3000;
		Constants::Heads::MAX_SPEED = 1075.0f;
		Constants::Heads::PERLIN_STRENGTH = 0.5f;
		Constants::Heads::MIN_GRAVITY_DISTANCE = 50.0f * 50.0f; // min distance Squared

		Constants::Planet::EASE_SPEED = 0.8f;
		Constants::Planet::VOLUME_RANGE = 15.0f;
		Constants::Planet::MIN_SIZE = 5.0f;
	}
}
#endif /* CONSTANTS_H_ */
