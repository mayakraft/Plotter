#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../noise.c"

#define TWOPI 6.28318530718

int posNeg(int in){
	if(in == 0){
		return -1;
	}
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

	int width = 800;
	int height = 500;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "steps.svg");
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%d", width, height);
	fprintf(file, "px\" viewBox=\"0 0 %d %d\" xml:space=\"preserve\">\n", width, height);
	fprintf(file, "<g>\n");



	float COLUMNS = 12;

	int columnStart = 70;  // the start of each sine wave line, increments its way along the page

	float x, y;
	for(int i = 0; i < COLUMNS; i++){
		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote

		float waveMag = 10;

		for(float j = 0; j < height; j++){

			float freq = j*.05 + (2.0 - 0.5 * cos(j/(float)height*M_PI*2) );

			float xShift = 0;//30 * sinf(i);

			x = columnStart + waveMag*sinf( freq ) * posNeg((int)floor(i*.5)%2);
			y = j;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing quote



		int columnIncrement = 30;
		if(i%4 == 0) columnIncrement += 0 + arc4random()%50;
		if(i%4 == 1) columnIncrement += 15;  // mirror space
		if(i%4 == 2) columnIncrement += 0 + arc4random()%50;
		if(i%4 == 3) columnIncrement += 15;  // mirror space

		if(i%4 == 0 || i%4 == 2){
			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
			float randIncr = arc4random()%(int)(columnIncrement-waveMag*2) + waveMag;			
			fprintf(file, "%.2f,%.2f ", (float)columnStart + randIncr, 0.0);
			fprintf(file, "%.2f,%.2f ", (float)columnStart + randIncr, (float)height);
			fprintf(file, "\"/>\n"); // closing quote
		}
		
		columnStart += columnIncrement;

	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}