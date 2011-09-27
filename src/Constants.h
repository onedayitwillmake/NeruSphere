/*
 * Constants.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include "cinder/Perlin.h"
#include "cinder/ImageIo.h"
#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"


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

	struct Textures {
		static ci::gl::Texture* HEAD() {
			static bool initialized = false;
			static ci::gl::Texture texture;
			if( !initialized ) {
				initialized = true;

				ci::gl::Texture::Format format;
				format.enableMipmapping( false );
				format.setMinFilter( GL_NEAREST );
				format.setMagFilter( GL_NEAREST );

				texture = ci::gl::Texture( ci::loadImage( ci::app::App::get()->loadResource( RES_HEAD ) ), format );
			}
			return &texture;
		}

		static ci::gl::Texture* PLANET() {
			static bool initialized = false;
			static ci::gl::Texture texture;
			if( !initialized ) {
				initialized = true;

				ci::gl::Texture::Format format;
				format.enableMipmapping( false );
				format.setMinFilter( GL_NEAREST );
				format.setMagFilter( GL_NEAREST );

				texture = ci::gl::Texture( ci::loadImage( ci::app::App::get()->loadResource( RES_PLANET ) ), format );
			}
			return &texture;
		}
	};
}
#endif /* CONSTANTS_H_ */
