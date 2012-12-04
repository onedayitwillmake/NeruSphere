#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
//#include "gl.h"
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

#include "Constants.h"
#include "Textures.h"

typedef std::pair< int, ci::Surface8u* > TintSurfacePair;

namespace Constants {
		ci::gl::Texture* Textures::PLANET() {
			static bool initialized = false;
			static ci::gl::Texture texture;
			if( !initialized ) {
				initialized = true;

				ci::gl::Texture::Format format;
				format.enableMipmapping( false );
				format.setMinFilter( GL_NEAREST );
				format.setMagFilter( GL_NEAREST );

				std::string path = "godofthieves.png";//ci::app::App::get()->getResourcePath().string() + "/" + "godofthieves.png"; // TODO: move magic string to variable in constants

				std::cout << "Loaded texture HEAD '" << path << "'" << std::endl;

				texture = ci::gl::Texture( ci::loadImage( path ) , format );
			}
			return &texture;
		}

		/**
		 * Stores and retrieves the static texture cache for the app
		 */
		std::vector<ci::gl::Texture>* Textures::cache() {
			static std::vector<ci::gl::Texture> _internalcache;
			return &_internalcache;
		}

		std::map< int, ci::Surface* >* Textures::surfaceMap() {
			static std::map< int, ci::Surface* > _internalSurfaceMap;
			return &_internalSurfaceMap;
		}

		/**
		 * Naive texture loader for app - circle_x_.png
		 */
		void Textures::loadTextures() {
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
				//godofthieves
				ci::Surface8u* surface = new ci::Surface8u( ci::loadImage( ci::app::App::get()->loadResource( path.str() ) ) );


				ci::gl::Texture texture = ci::gl::Texture( *surface , format );

				surfaceMap()->insert( TintSurfacePair( i, surface) );
				cache()->push_back( texture );
			}
		}

		// Retrieves a random index from between 0 and textureCache size
		int Textures::getRandomHeadTextureId() {
			return ci::Rand::randInt( cache()->size() );
		}

		// Retrieves the surface mapped to a specific texture
		ci::Surface8u* Textures::getSurfaceForTextureId( int anID ) {
			std::map< int, ci::Surface* >::iterator itr;
			itr = surfaceMap()->find( anID );
			return itr->second;
		}
} /** Constants**/
