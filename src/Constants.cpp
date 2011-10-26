/*
 * Constants.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: mariogonzalez
 */
#include "Constants.h"
namespace Constants {
	namespace Forces {
		float PARTICLE_SPEED_DECAY;
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

		int NUM_PARTICLES_MIN = 2;
		int NUM_PARTICLES_MAX = 10;
	};

	namespace Planet {
		float EASE_SPEED;
		float VOLUME_RANGE;
		float MIN_SIZE;
	};

	namespace Particles {
		int MIN;
		int MAX;

		float SIZE;

		float MIN_INITIAL_SPEED;
		float MAX_INITIAL_SPEED;
		float SPEED_DECAY;
	}

	void init() {
		Constants::Forces::GRAVITY_FORCE = 40000.0f;

		Constants::Defaults::HEAD_COUNT = 210;
		Constants::Defaults::HEAD_SIZE_MIN = 6;
		Constants::Defaults::HEAD_SIZE_MAX = 36;
		Constants::Defaults::DEBUG_DRAW = false;

		Constants::Heads::MIN_LIFETIME = 250;
		Constants::Heads::MAX_LIFETIME = 600;
		Constants::Heads::MAX_SPEED = 1616.0f;
		Constants::Heads::PERLIN_STRENGTH = 2.088f;
		Constants::Heads::MIN_GRAVITY_DISTANCE = 51.0f * 51.0f; // min distance Squared

		Constants::Planet::EASE_SPEED = 0.38f;
		Constants::Planet::VOLUME_RANGE = 28.0f;
		Constants::Planet::MIN_SIZE = 64.0f;

		Constants::Particles::MIN = 2;
		Constants::Particles::MAX = 10;
		Constants::Particles::SIZE = 1;

		Constants::Particles::MIN_INITIAL_SPEED = 1;
		Constants::Particles::MAX_INITIAL_SPEED = 3;
		Constants::Particles::SPEED_DECAY = 0.99;

	}
}

