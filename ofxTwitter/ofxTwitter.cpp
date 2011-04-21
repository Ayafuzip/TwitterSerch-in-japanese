/*
 *  ofxTwitter.cpp
 *
 *  Created by Douglas Edric Stanley on 10/12/10
 *  cc-by-sa 2010 www.abstractmachine.net. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Paul Shen
 *  cf. http://in.somniac.me/2010/01/openframeworks-http-requests-xml-parser/
 *
 */

#include "ofxTwitter.h"

void ofxTwitter::setup() {
	
	// listen to http events
	ofxHttpEvents.addListener(this);
	// use dummy data in case we've lost web connection
	data.push_back( Tweet("...") );
	
	delegate = NULL;
	
	
	
}

void ofxTwitter::startTwitterQuery(string keywords, int repliesPerPage, int pageIndex) {
	
	string query = "http://search.twitter.com/search.atom?q=";
	query += keywords;
	query += "&rpp=" + ofToString(repliesPerPage);
	query += "&page=" + ofToString(pageIndex);
	
	startQuery(query);
	
}

void ofxTwitter::startQuery(string query) {
	// load data from web
	ofxHttpUtil.addUrl(query);
}

void ofxTwitter::newResponse(ofxHttpResponse &response) {
    // printf("%s\n", response.responseBody.c_str());
	
    xml.loadFromBuffer(response.responseBody); // parse string
    xml.pushTag("feed"); // change relative root to <feed>
	
	// get current count of data
	int xmlDataCount = data.size();
	
    int nombreDeTweets = xml.getNumTags("entry");
    // iterate through <entry> tags
    for (int i = 0; i < nombreDeTweets; i++) {
		
		xml.pushTag("entry", i);
		
		Tweet tweet;
		tweet.id = xml.getValue("id", "", 0).c_str();
		tweet.title = xml.getValue("title", "", 0).c_str();
		tweet.updated = xml.getValue("updated", "", 0).c_str();
		tweet.published = xml.getValue("published", "", 0).c_str();
		tweet.author.uri  = xml.getValue("author:uri", "", 0).c_str();
		tweet.author.name = xml.getValue("author:name", "", 0).c_str();
		
		//tweet.language = xml.getValue("twitter:lang", "", 0).c_str();
		
		for(int j=0; j<xml.getNumTags("link"); j++) {
			
			string type = xml.getAttribute("link", "type", "", j);
			string rel  = xml.getAttribute("link", "rel", "", j);
			string href = xml.getAttribute("link", "href", "", j);
			
			if (rel == "image")
				tweet.author.imageUri = href;
			else if (rel == "alternate")
				tweet.link = href;
		}
		
		data.push_back( tweet );
		
		xml.popTag();
		
    }
    xml.popTag(); // move out of <feed>
	
	// remove previous data
	for (int i=0; i<xmlDataCount; i++) {
		data.erase(data.begin());
	}
	
	// ok, send back results
	if (delegate) {
		delegate->searchResult(data);
	}
	
}

vector<Tweet> ofxTwitter::getLatestResponse() {
	return data;
}
