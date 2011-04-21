/*
 *  TwitterDelegate.h
 *
 *  Created by Douglas Edric Stanley on 10/12/10
 *  cc-by-sa 2010 www.abstractmachine.net. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Paul Shen
 *  cf. http://in.somniac.me/2010/01/openframeworks-http-requests-xml-parser/
 *
 */

#pragma once

#include "ofMain.h"
#include "Tweet.h"

class TwitterDelegate {
public:
	virtual void searchResult(vector<Tweet> results) {}
};