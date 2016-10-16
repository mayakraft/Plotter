//
//  ofxPlotter.h
//  Created by Robby on 10/15/16.
//

#ifndef ofxPlotter_h
#define ofxPlotter_h

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Plotter {
private:
	FILE *file;
	
public:
	// calling setup and close are requirements!
	// inbetween the two, call whatever draw functions you wish

	void setup(int width, int height, string filename);
	void close();
	
	// shapes
	
	void line(float x1, float y1, float x2, float y2);
	
	// polyline instructions:  1) beginPolyline   2) add points   3) endPolyline
	void beginPolyline();
	void addPolylinePoint(float x, float y);
	void endPolyline();

};

#endif /* ofxPlotter_h */
