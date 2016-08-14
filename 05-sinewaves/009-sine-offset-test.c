#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "009-sine-offset-test.svg\0";
char path[128] = "out/\0";

// document
int width = 1175;
int height = 825;
float MARGIN = 160;

// groups
float SINE_SPACING = 130.0;
float NUM_SINES = 4.0;

// sine curve
float FREQUENCY = .016;
float AMPLITUDE = 60;

float TILT = 0.0;//.05;

int mod2PosNeg(int iterator){
	if(iterator%2 == 0){ return -1; }
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%d", width, height);
	fprintf(file, "px\" viewBox=\"0 0 %d %d", width, height);
	fprintf(file, "\" xml:space=\"preserve\">\n<g>\n");
	

	// 4 sine waves in every group
	for(int i = 0; i < NUM_SINES; i++){

		float yGroup = SINE_SPACING * i;  // the major X axis of each group

		// pattern: L L R R L L ...
		int direction = mod2PosNeg(i);   // -1 or +1

		// spacing
		float percentOfGroup = (i / NUM_SINES);
		float yInternalSpacing = percentOfGroup * SINE_SPACING;

		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
		for(float w = 0; w < width; w++){

			float sine = cosf(w*FREQUENCY) * AMPLITUDE;
			float tilt = TILT * w;
			if(i%2 == 0)
				tilt = TILT * (width-w);
			float x = w;
			float y = ((MARGIN)) + yGroup + yInternalSpacing + tilt + sine;

			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing quote
	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}