/*
 *  ofxTwitter.h
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

#include "ofxHttpEvents.h"
#include "ofxXmlSettings.h"

#include "TwitterDelegate.h"
#include "Tweet.h"

class ofxTwitter : public ofxHttpEventListener {

public:
	
	void setup();
	void setSearchDelegate(TwitterDelegate *_delegate) { delegate = _delegate; }
	
	void startQuery(string query);
	void startTwitterQuery(string keywords, int repliesPerPage=10, int pageIndex=1);
	
	vector<Tweet> getLatestResponse();
	void newResponse(ofxHttpResponse &response);
	
private:
	
	TwitterDelegate *delegate;
	
	ofxXmlSettings xml;
	vector<Tweet> data;
	
};