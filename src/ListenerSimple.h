/*
 * ListenerSimple.h
 *
 *  Created on: Oct 27, 2011
 *      Author: onedayitwillmake
 */

#ifndef LISTENERSIMPLE_H_
#define LISTENERSIMPLE_H_

#include "OSC/include/OscListener.h"
#include "cinder/Cinder.h"
#include <iostream>
using namespace ci;
// We'll create a new Cinder Application by deriving from the BasicApp class
class ListenerSimple  {
 public:

	void setup();
	void update();
	void draw();


	osc::Listener listener;
	float positionX;
};

#endif /* LISTENERSIMPLE_H_ */
