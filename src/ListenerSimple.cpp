/*
 * ListenerSimple.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: onedayitwillmake
 */

#include "ListenerSimple.h"


void ListenerSimple::setup(){
	listener.setup(3000);
}

void ListenerSimple::update(){
	while (listener.hasWaitingMessages()) {
		osc::Message message;
		listener.getNextMessage(&message);

		std::cout << "New message received" << std::endl;
		std::cout << "Address: " << message.getAddress() << std::endl;
		std::cout << "Num Arg: " << message.getNumArgs() << std::endl;
		for (int i = 0; i < message.getNumArgs(); i++) {
			std::cout << "-- Argument " << i << std::endl;
			std::cout << "---- type: " << message.getArgTypeName(i) << std::endl;
			if (message.getArgType(i) == osc::TYPE_INT32){
				try {
					std::cout << "------ value: "<< message.getArgAsInt32(i) << std::endl;
				}
				catch (...) {
					std::cout << "Exception reading argument as int32" << std::endl;
				}

			}else if (message.getArgType(i) == osc::TYPE_FLOAT){
				try {
					std::cout << "------ value: " << message.getArgAsFloat(i) << std::endl;
				}
				catch (...) {
					std::cout << "Exception reading argument as float" << std::endl;
				}
			}else if (message.getArgType(i) == osc::TYPE_STRING){
				try {
					std::cout << "------ value: " << message.getArgAsString(i).c_str() << std::endl;
				}
				catch (...) {
					std::cout << "Exception reading argument as string" << std::endl;
				}

			}
		}

        if( message.getNumArgs() != 0 && message.getArgType( 0 ) == osc::TYPE_FLOAT )
        {
            positionX = message.getArgAsFloat(0);
        }

	}
}

void ListenerSimple::draw()
{
//	gl::clear(Color(0,0,0), true);
//	gl::color(Color(1, 1, 1));
//	gl::drawSolidRect(Rectf(Vec2f(0, 0), Vec2f(positionX * getWindowWidth(), getWindowHeight())));
}
