//
//  ofxPlotter.cpp
//  Created by Robby on 10/15/16.
//

#include "ofxPlotter.h"

using namespace std;

void Plotter::setup(int width, int height, string filename){
	
//	file = fopen(filename.c_str(), "w");
	
	// navigate up to get out of the application package folder
	char path[128] = "../../../\0";
	strcat(path, filename.c_str());
	file = fopen(path, "w");

	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%d", width, height);
	fprintf(file, "px\" viewBox=\"0 0 %d %d", width, height);
	fprintf(file, "\" xml:space=\"preserve\">\n<g>\n");
}

void Plotter::close(){
	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
}

void Plotter::beginPolyline(){
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");
}

void Plotter::addPolylinePoint(float x, float y){
	fprintf(file, "%.2f,%.2f ", x, y);
}

void Plotter::endPolyline(){
	fprintf(file, "\"/>\n");
}

void Plotter::line(float x1, float y1, float x2, float y2){
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"%.2f,%.2f %.2f,%.2f\"/>\n", x1, y1, x2, y2);
}

