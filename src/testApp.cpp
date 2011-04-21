#include "testApp.h"

wstring wSearchstr;

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("日本語でTwitterSearch");
	setlocale( LC_ALL, "ja_JP.UTF-8" );
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	//searchStr = "helpforjapan";
	searchStr = "少女";
	twitterPage = 1;
	twitter.setup();
	twitter.setSearchDelegate(this);
	twitter.startTwitterQuery(searchStr, 10, twitterPage);
	millis = ofGetElapsedTimeMillis();
	
	font1.loadFont("AA.ttf", 20, true, true);
	font3.loadFont("AA.ttf", 80, true, true);
	font2.loadFont("NG.otf", 15, true, true);
	font4.loadFont("NG.otf", 10, true, true);
	X = ofGetWidth();
	
	const char*   c3 = searchStr.c_str();
	size_t     length3 = strlen( c3 );
	wchar_t*   wc3 = new wchar_t[ length3+1 ];
	length3 = mbstowcs( wc3, c3, length3+1 );

	setlocale( LC_ALL, "ja_JP.UTF-8" );
	wSearchstr = wc3;
	Count = 1;

}

//--------------------------------------------------------------
void testApp::update(){
	
	if ( ABS(ofGetElapsedTimeMillis()-millis) > 5000) {
		twitterPage = ++twitterPage % 10;
		twitter.startTwitterQuery(searchStr, 10, twitterPage);
		millis = ofGetElapsedTimeMillis();
	}
	
	X -= 5;
	
	if (X < -100) {
		if (wTweet.size() > Count && wName.size() > Count) {
			Count += 1;
			X = ofGetWidth();
		}
	}
	
	if (60 + Count * 15 > ofGetHeight()) {
		wTweet.clear();
		wName.clear();
		Count = 1;

	}
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(100, 100, 0, 100);
	ofRect(0, 0, ofGetWidth(), 50);
	
	
	
	

	
	if (wTweet.size() > 0 && wName.size() > 0) {
		ofSetColor(0x7fffff);
		font2.drawString(wSearchstr, X, 30);
		

		
		for(int i=0; i<wTweet.size(); i++) {
			
			/**
			ofRectangle rect = font2.getStringBoundingBox(wTweet[i], 0,0);
			ofSetColor(0xcccccc);	
			ofRect(rect.x + 20, rect.y + 80 + i * 40, rect.width, rect.height);
			**/
			ofSetColor(0x7fffff);	
			font4.drawString(wTweet[i], 20, 80 + i * 40 );
			ofSetColor(255,0,0);
			font4.drawString(wName[i], 20, 65 + i * 40);
		}
	}

	
	if (Count != 0) {
		ofSetColor(255, 255, 255, 100);
		//font3.drawString(ofToString(Count), 961, 210);
	} else {
		ofSetColor(255, 255, 255);
		font2.drawString(L"受信中", 961, 210);
	}

}

void testApp::searchResult(vector<Tweet> results) {

	tweets.clear();
	wTweet.clear();
	wName.clear();
	for(int i=0; i<results.size(); i++) {
		tweets.push_back(results[i]);
		
		setlocale( LC_ALL, "ja_JP.UTF-8" );
		const char*   c = tweets[i].title.c_str();
		size_t     length = strlen( c );
		wchar_t*   wc = new wchar_t[ length+1 ];
		length = mbstowcs( wc, c, length+1 );
		wTweet.push_back(wc);
		
		const char*   c2 = tweets[i].author.name.c_str();
		size_t     length2 = strlen( c2 );
		wchar_t*   wc2 = new wchar_t[ length2+1 ];
		length2 = mbstowcs( wc2, c2, length2+1 );
		wName.push_back(wc2);

	}	
	


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

