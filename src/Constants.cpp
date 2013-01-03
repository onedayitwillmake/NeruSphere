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

		bool DEBUG_DRAW;
		bool DRAW_AUDIO_ANALYZER;

		ci::Vec2f GRAVITY_POINT;
		void setGravityPoint( ci::Vec2f newGravityPoint ) {
			GRAVITY_POINT = newGravityPoint;
		}
		ci::Vec2f getGravityPoint() {
			return GRAVITY_POINT;
		}
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

		Constants::Defaults::HEAD_COUNT = 200;
		Constants::Defaults::HEAD_SIZE_MIN = 10;
		Constants::Defaults::HEAD_SIZE_MAX = 28;
		Constants::Defaults::DEBUG_DRAW = false;
		Constants::Defaults::DRAW_AUDIO_ANALYZER = true;

		Constants::Heads::MIN_LIFETIME = 500;
		Constants::Heads::MAX_LIFETIME = 3500;
		Constants::Heads::MAX_SPEED = 1616.0f;
		Constants::Heads::PERLIN_STRENGTH = 6.1f;
		Constants::Heads::ANTI_GRAVITY = 2.1;
		Constants::Heads::MIN_GRAVITY_DISTANCE = 3000; // min distance Squared

		Constants::Planet::EASE_SPEED = 0.7f;
		Constants::Planet::VOLUME_RANGE = 30.0f;
		Constants::Planet::MIN_SIZE = 32.0f;

		Constants::Particles::MIN = 10;
		Constants::Particles::MAX = 30;

		Constants::Particles::PARTICLE_SIZE_MIN = 0.5f;
		Constants::Particles::PARTICLE_SIZE_MAX = 2.5f;

		Constants::Particles::MIN_INITIAL_SPEED = 1.5;
		Constants::Particles::MAX_INITIAL_SPEED = 9;
		Constants::Particles::SPEED_DECAY = 0.9;

		Constants::Particles::ALPHA = 1.0;

	}
}

