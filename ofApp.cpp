#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int deg_span = 12;
	int loc_span = 230;

	for (int x = -loc_span; x <= loc_span; x += loc_span) {

		for (int y = -loc_span; y <= loc_span; y += loc_span) {

			for (int deg = 0; deg < 360; deg += deg_span * 2) {

				for (int radius = 50; radius <= 100; radius += 50) {

					if (radius == 50) {

						auto noise_deg = ofMap(ofNoise(ofGetFrameNum() * 0.0075), 0, 1, deg - 1440, deg + 1440);

						this->mesh.addVertex(glm::vec3(x + radius * cos((noise_deg + deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((noise_deg + deg_span * 0.5) * DEG_TO_RAD), 0));
						this->mesh.addVertex(glm::vec3(x + radius * cos((noise_deg - deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((noise_deg - deg_span * 0.5) * DEG_TO_RAD), 0));

					}
					else {

						this->mesh.addVertex(glm::vec3(x + radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
						this->mesh.addVertex(glm::vec3(x + radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));

						this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
						this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}