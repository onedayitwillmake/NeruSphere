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
#include "TargetConditionals.h"
typedef std::pair< int, ci::Surface8u* > TintSurfacePair;

namespace Constants {
		ci::gl::Texture Textures::_planetTexture;
	
	
		ci::gl::Texture* Textures::getPlanetTexture() {
			return &_planetTexture;
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
		void Textures::loadTextures( std::string resourcePath ) {
			ci::gl::Texture::Format format;
			format.enableMipmapping( false );
			format.setMinFilter( GL_NEAREST );
			format.setMagFilter( GL_NEAREST );
			
			for( int i = 0; i < 3; i++ ) {
				std::stringstream path; // create a new 'string stream' so we can append to a string
				path << resourcePath << "/" << "heads_" << (i+1) << ".png"; // Build out a string that has the file path, assumes images are called head_#.png

				// Create a 'surface' - key part is
				// ci::loadImage( ci::app::App::get()->loadResource( path.str() ) )
				// Passes the file path, to a function loadResource which returns whatever loadImage wants
				ci::Surface8u* surface = new ci::Surface8u( ci::loadImage( path.str()  ) );
				ci::gl::Texture texture = ci::gl::Texture( *surface , format );

				surfaceMap()->insert( TintSurfacePair( i, surface) );
				cache()->push_back( texture );
			}
			
			// Load the head texture
			std::string path = resourcePath + "/" + "gromacirclepink.png";
			std::cout << "Loaded texture HEAD '" << path << "'" << std::endl;
			Textures::_planetTexture = ci::gl::Texture( ci::loadImage( path ) , format );
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
