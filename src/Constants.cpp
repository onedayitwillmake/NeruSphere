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
		float DIRECTION;
	};

	namespace Defaults {
		int HEAD_COUNT;
		int HEAD_SIZE_MIN;
		int HEAD_SIZE_MAX;

		int windowWidth;
		int windowHeight;
		bool DEBUG_DRAW = true;
	};

	namespace Heads {
		int MIN_LIFETIME;
		int MAX_LIFETIME;

		float MAX_SPEED;
		float PERLIN_STRENGTH;

		float MIN_GRAVITY_DISTANCE;
		float ANTI_GRAVITY;

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

		float PARTICLE_SIZE_MIN;
		float PARTICLE_SIZE_MAX;

		float MIN_INITIAL_SPEED;
		float MAX_INITIAL_SPEED;
		float SPEED_DECAY;

		float ALPHA;
	}

	void init() {
		Constants::Forces::GRAVITY_FORCE = 40000.0f;
		Constants::Forces::DIRECTION = 1;

		Constants::Defaults::HEAD_COUNT = 300;
		Constants::Defaults::HEAD_SIZE_MIN = 6;
		Constants::Defaults::HEAD_SIZE_MAX = 42;
		Constants::Defaults::DEBUG_DRAW = false;

		Constants::Heads::MIN_LIFETIME = 10;
		Constants::Heads::MAX_LIFETIME = 100;
		Constants::Heads::MAX_SPEED = 1616.0f;
		Constants::Heads::PERLIN_STRENGTH = 4.1f;
		Constants::Heads::ANTI_GRAVITY = 5;
		Constants::Heads::MIN_GRAVITY_DISTANCE = 51.0f * 51.0f; // min distance Squared

		Constants::Planet::EASE_SPEED = 0.38f;
		Constants::Planet::VOLUME_RANGE = 28.0f;
		Constants::Planet::MIN_SIZE = 64.0f;

		Constants::Particles::MIN = 5;
		Constants::Particles::MAX = 6;

		Constants::Particles::PARTICLE_SIZE_MIN = 1.2;
		Constants::Particles::PARTICLE_SIZE_MAX = 3.4;

		Constants::Particles::MIN_INITIAL_SPEED = 5;
		Constants::Particles::MAX_INITIAL_SPEED = 5;
		Constants::Particles::SPEED_DECAY = 0.93;

		Constants::Particles::ALPHA = 0.99;

	}
}

