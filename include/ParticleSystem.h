/*
 * ParticleSystem.h
 *
 *  Created on: Oct 23, 2011
 *      Author: onedayitwillmake
 */

#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_


#include <vector>
#include <gl.h>
#include "cinder/Area.h"
#include "cinder/Rect.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"

namespace particle {

struct Particle {
	size_t index;
	ci::Vec2f speed;
	ci::Vec2f originalPosition;
	ci::Vec2f currentPosition;
};

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();

	void add( ci::Vec2f pos, ci::Vec2f velocity, ci::Rectf srcCoords, ci::Rectf destRect );
	void draw();
	void update();
	void clear();

	std::vector<GLfloat> verts;
	std::vector<GLfloat> texCoords;
	std::vector<ci::ColorA> colors;
	std::vector<Particle> particles;

	// DEBUG
	float _debugColor;
};

} /* namespace particle */
#endif /* PARTICLESYSTEM_H_ */
