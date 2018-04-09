#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 300;
	int z_span = 150;
	int deg_span = 5;

	vector<vector<ofPoint>> points_list;

	this->cam.begin();
	ofRotateX(-90);

	for (int z = -300; z <= 300; z += z_span) {

		vector<ofPoint> points;
		int deg_start = ofNoise(z * 0.1, ofGetFrameNum() * 0.005) * 720;
		for (int deg = deg_start; deg < deg_start + 360; deg += deg_span) {

			points.push_back(ofPoint(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z));
		}
		points_list.push_back(points);
	}

	
	for (int list_index = 1; list_index < points_list.size(); list_index++) {

		for (int i = 0; i < points_list[list_index].size(); i++) {

			ofSetColor(239);
			ofDrawSphere(points_list[list_index][i], 2);

			if (list_index == 1) {

				ofDrawSphere(points_list[0][i], 2);
			}

			ofSetColor(239, ofMap(points_list[list_index][i].distance(points_list[list_index - 1][i]), 0, radius, 0, 255));
			ofDrawLine(points_list[list_index][i], points_list[list_index - 1][i]);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}