#include "Constants.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "gl.h"
#include "Resources.h"
#include <vector>
#include <iostream>
#include <sstream>

namespace Constants {
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
					std::cout << "Loaded texture RES_HEAD " << std::endl;
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
					std::cout << "Loaded texture RES_PLANET " << std::endl;
				}
				return &texture;
			}

			static std::vector<ci::gl::Texture>* cache() {
				static std::vector<ci::gl::Texture> _internalcache;
				return &_internalcache;
			}

			static void loadTextures() {
				for( int i = 0; i <= 12; i++ ) {
					ci::gl::Texture::Format format;
					format.enableMipmapping( false );
					format.setMinFilter( GL_NEAREST );
					format.setMagFilter( GL_NEAREST );

					std::stringstream path;
					path << "../resources/circle-" << i << ".png";
					ci::gl::Texture texture = ci::gl::Texture( ci::loadImage( ci::app::App::get()->loadResource( path.str() ) ), format );

					cache()->push_back( texture );
					std::cout <<  cache()->size() << std::endl;
				}
			}

			static ci::gl::Texture* getRandomHeadTexture() {
				int index = ci::Rand::randInt( cache()->size() - 1 );
				std::cout <<  cache()->size() << std::endl;
				return &cache()->at( index );
			}
	};
}
