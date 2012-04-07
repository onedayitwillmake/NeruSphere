/*
 *  Utils.h
 *  BasicBox2D
 *
 *  Created by David Wicks on 6/7/10.
 *  Copyright 2010 David Wicks. All rights reserved.
 *
 */

#pragma once
#include "cinder/Vector.h"
#include "Box2D/Box2D.h"

namespace cinder
{

	namespace box2d
	{

		struct Conversions
		{

				const static int32_t SCALING = 300; //64 pixels per meter sounds reasonable

				static Vec2f toScreen(b2Vec2 fin) {
					return Vec2f(fin.x, fin.y) * (float) SCALING;
				}

				static b2Vec2 toPhysics(Vec2f fin) {
					return b2Vec2(fin.x / (float) SCALING,
					        fin.y / (float) SCALING);
				}

				static float toPhysics(float fin) {
					return fin / (float) SCALING;
				}

				static float toScreen(float fin) {
					return fin * (float) SCALING;
				}

				static float radiansToDegrees(float rad) {
					return rad * 180.0f / (float) M_PI;
				}
		};

	}

}
