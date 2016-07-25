#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

// output
char filename[128] = "random-walker.svg\0";
char path[128] = "out/\0";

// document
int width = 640;
int height = 640;

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	// HEADER
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%dpx\" ", width, height);
	fprintf(file, "viewBox=\"0 0 %d %d\">\n", width, height);
	// BODY
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open polyline

	float x, y;
	x = width * .5;
	y = height * .5;
	unsigned char newPolyline = 0;
	for(int i = 0; i < 2000; i++){
		fprintf(file, "%.2f,%.2f ", x, y);
		x += (rand()%100 / 100.0 - .36)*10;
		y += (rand()%100 / 100.0 - .3)*10;
		// out of bounds, start a new line
		if(x < 0){      x += width;  newPolyline = 1; }
		if(y < 0){      y += height; newPolyline = 1; }
		if(x > width){  x -= width;  newPolyline = 1; }
		if(y > height){ y -= height; newPolyline = 1; }
		if(newPolyline){
			fprintf(file, "\"/>\n"); // closing polyline
			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open polyline
			newPolyline = 0;
		}
	}
	fprintf(file, "\"/>\n"); // closing polyline
	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}