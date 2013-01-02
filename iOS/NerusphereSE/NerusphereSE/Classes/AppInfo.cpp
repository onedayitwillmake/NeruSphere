//
//  AppInfo.cpp
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/5/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#include "AppInfo.h"

AppInfo::AppInfo(){};
AppInfo& AppInfo::getInstance() {
	static AppInfo instance;
	return instance;
}
