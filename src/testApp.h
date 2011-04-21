#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofTrueTypeFontWS.h"

class testApp : public ofBaseApp, public TwitterDelegate {
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	void searchResult(vector<Tweet> results);
	
	ofxTwitter twitter;
	ofTrueTypeFont font1;
	ofTrueTypeFont font3;
	ofTrueTypeFontWS font2;
	ofTrueTypeFontWS font4;
	
	int twitterPage;
	int millis;
	vector<Tweet> tweets;
	
	string searchStr;
	vector<wstring> wTweet;
	vector<wstring> wName;
	vector<wstring> wTime;
	float X;
	int Count;
	int timer;
	
};
