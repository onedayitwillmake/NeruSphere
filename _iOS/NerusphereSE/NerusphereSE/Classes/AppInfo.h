//
//  AppInfo.h
//  NerusphereSE
//	This class acts as a shim for various methods that are usually retrieved from the ci::app instance
//
//  Created by Mario Gonzalez on 12/5/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#ifndef __NerusphereSE__AppInfo__
#define __NerusphereSE__AppInfo__
#include <iostream>
#include "cinder/Vector.h"
#include "cinder/Area.h"

class AppInfo {
public:
	static AppInfo& getInstance();
	
	//! width of the application's window specified in pixels
	int		getWindowWidth() const { return mWindowSizeX; }
	//! height of the application's window specified in pixels
	int		getWindowHeight() const { return mWindowSizeY; }
	
	//! width and height of the application's window specified in pixels
	void		setWindowSize( int x, int y ) { mWindowSizeX = x; mWindowSizeY = y;	};
	ci::Vec2i	getWindowSize() const { return ci::Vec2i( mWindowSizeX, mWindowSizeY ); }
	
	//! the size of the application's window specified in pixels. \return cinder::Area( 0, 0, width in pixels, height in pixels )
	ci::Area	getWindowBounds() const { return ci::Area( 0, 0, mWindowSizeX, mWindowSizeY ); }
	
	//! Returns the number of seconds which have elapsed since application launch
	void				setElapsedSeconds( double s ) { mEllapsedSeconds = s; }
	double				getElapsedSeconds() const { return mEllapsedSeconds; }
	//! Returns the number of animation frames which have elapsed since application launch
	void				setElapsedFrames( uint32_t f ) { mFrameCount = f; }
	uint32_t			getElapsedFrames() const { return mFrameCount; }
	
	//! Returns the center of the App's window or the screen in full-screen mode.
	ci::Vec2f			getWindowCenter() const { return ci::Vec2f( (float)getWindowWidth(), (float)getWindowHeight() ) * 0.5f; }
	//! Returns the aspect ratio of the App's window or the screen in full-screen mode
	float				getWindowAspectRatio() const { return getWindowWidth() / (float)getWindowHeight(); }
	
private:
	AppInfo();
	AppInfo(AppInfo const&);
	void operator=(AppInfo const&);
	
	int mWindowSizeX;
	int mWindowSizeY;
	double mEllapsedSeconds;
	uint32_t mFrameCount;
	
};

#endif /* defined(__NerusphereSE__AppInfo__) */
