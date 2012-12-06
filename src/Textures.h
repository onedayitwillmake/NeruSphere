/*
 * Planet.h
 *
 *  Created on: Sep 25, 2011
 *      Author: onedayitwillmake
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <map>
namespace Constants {
	class Textures {
	public:
			// Returns the PLANET texture used by the center planet object
			static ci::gl::Texture* getPlanetTexture( ci::gl::Texture* aTexture = NULL );

			// Naive texture loader for app - circle_x_.png
			static void loadTextures();

			// Retrieves a random index from between 0 and textureCache size
			static int getRandomHeadTextureId();

			// Retrieves the texture at a specific index
			static ci::gl::Texture* getHeadTextureAtIndex( int anIndex ) { return &cache()->at( anIndex ); }

			// Retrieves the surface mapped to a specific texture
			static ci::Surface8u* getSurfaceForTextureId( int anID );

//	private:
			// Stores and retrieves the static texture cache for the app
			static std::vector<ci::gl::Texture>* cache();

			// Stores a map of [indexId,surface] pairs
			static std::map< int, ci::Surface* >* surfaceMap();
	};
}

#endif /* TEXTURE_H_ */

