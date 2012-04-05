#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "gl.h"
#include "Resources.h"
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include "Constants.h"

typedef std::pair< int, ci::Surface8u* > TintSurfacePair;
namespace Constants {
	struct Textures {
		static ci::gl::Texture* HEAD() {
				static bool initialized = false;
				static ci::gl::Texture texture;
				if( !initialized ) {
					initialized = true;

					ci::gl::Texture::Format format;
					format.enableMipmapping( true );
//					format.setMinFilter( GL_NEAREST );
//					format.setMagFilter( GL_NEAREST );

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

			/**
			 * Stores and retrieves the static texture cache for the app
			 */
			static std::vector<ci::gl::Texture>* cache() {
				static std::vector<ci::gl::Texture> _internalcache;
				return &_internalcache;
			}

			static std::map< int, ci::Surface* >* surfaceMap() {
				static std::map< int, ci::Surface* > _internalSurfaceMap;
				return &_internalSurfaceMap;
			}

			/**
			 * Naive texture loader for app - circle_x_.png
			 */
			static void loadTextures() {
				for( int i = 0; i < 3; i++ ) {
					ci::gl::Texture::Format format;
					format.enableMipmapping( false );
					format.setMinFilter( GL_NEAREST );
					format.setMagFilter( GL_NEAREST );

					std::stringstream path; // create a new 'string stream' so we can append to a string
					path << "../resources/heads_" << (i+1) << ".png"; // Build out a string that has the file path, assumes images are called head_#.png

					// Create a 'surface' - key part is
					// ci::loadImage( ci::app::App::get()->loadResource( path.str() ) )
					// Passes the file path, to a function loadResource which returns whatever loadImage wants
					ci::Surface8u* surface = new ci::Surface8u( ci::loadImage( ci::app::App::get()->loadResource( path.str() ) ) );
					
					
					ci::gl::Texture texture = ci::gl::Texture( *surface , format );

					surfaceMap()->insert( TintSurfacePair( i, surface) );
					cache()->push_back( texture );
				}
			}

			/**
			 * Retrieves a random index from between 0 and textureCache size
			 */
			static int getRandomHeadTextureId() {
				return ci::Rand::randInt( cache()->size() );
			}
			static ci::gl::Texture* getHeadTextureAtIndex( int anIndex ) {
				return &cache()->at( anIndex );
			}

			// Retrieves the surface mapped to a specific texture
			static ci::Surface8u* getSurfaceForTextureId( int anID ) {
				std::map< int, ci::Surface* >::iterator itr;
				itr = surfaceMap()->find( anID );
				return itr->second;
			}
	};
}
