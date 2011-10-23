/*
 * Constants.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: mariogonzalez
 */
#include "Constants.h"
namespace Constants {
	namespace Forces {
		float GRAVITY_FORCE;
	};

	namespace Defaults {
		int HEAD_COUNT;
		int HEAD_SIZE_MIN;
		int HEAD_SIZE_MAX;
		bool DEBUG_DRAW = true;
	};

	namespace Heads {
		int MIN_LIFETIME;
		int MAX_LIFETIME;

		float MAX_SPEED;
		float PERLIN_STRENGTH;

		float MIN_GRAVITY_DISTANCE;

		int SINGLE_SPRITE_SIZE = 74;
		int NUM_SPRITES = 13;
	};

	namespace Planet {
		float EASE_SPEED;
		float VOLUME_RANGE;
		float MIN_SIZE;
	};

	void init() {
		Constants::Forces::GRAVITY_FORCE = 40000.0f;

		Constants::Defaults::HEAD_COUNT = 210;
		Constants::Defaults::HEAD_SIZE_MIN = 6;
		Constants::Defaults::HEAD_SIZE_MAX = 36;
		Constants::Defaults::DEBUG_DRAW = false;

		Constants::Heads::MIN_LIFETIME = 650;
		Constants::Heads::MAX_LIFETIME = 300;
		Constants::Heads::MAX_SPEED = 1616.0f;
		Constants::Heads::PERLIN_STRENGTH = 2.088f;
		Constants::Heads::MIN_GRAVITY_DISTANCE = 51.0f * 51.0f; // min distance Squared

		Constants::Planet::EASE_SPEED = 0.38f;
		Constants::Planet::VOLUME_RANGE = 28.0f;
		Constants::Planet::MIN_SIZE = 64.0f;
	}
}

