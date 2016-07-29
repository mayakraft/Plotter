#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "004-layered-sines.svg\0";
char path[128] = "out/\0";
// path[0] = '\0';

// document
int width = 1200;
int height = 900;

// groups
float NUM_GROUPS = 6;
float GROUP_SPACING = 200.0;
float GROUP_NUM_VERTICALS = 4.0;

// sine curve
float FREQUENCY = .018;
float AMPLITUDE = 10;

float phase0 = TWOPI*0.25 / 6.0;  // this needs to be a relation of PI / height

float freq1 = 0.003;
float freq2 = 0.005;
float freq3 = 0.015;
float freq4 = 0.0175;

float magnitude1 = 12;
float magnitude2 = 30;
float magnitude3 = 15;
float magnitude4 = 15;


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
	
	for(int i = 0; i < NUM_GROUPS; i++){
		float xGroup = GROUP_SPACING * i;  // the major X axis of each group

		// 4 sine waves in every group
		for(int j = 0; j < GROUP_NUM_VERTICALS; j++){
			// pattern: L L R R L L ...
			int direction = mod2PosNeg(j*.5);   // -1 or +1

			// spacing
			float percentOfGroup = (j / GROUP_NUM_VERTICALS);
			if(j == 0) percentOfGroup = .175;
			if(j == 1) percentOfGroup = .3;
			if(j == 2) percentOfGroup = .625;
			if(j == 3) percentOfGroup = .75;
			float xInternalSpacing = percentOfGroup * GROUP_SPACING;

			// affine scale
			float affine = 1.0;  // multiply to all
			if(j == 0 || j == GROUP_NUM_VERTICALS-1){ // multiply to outer curves
				// affine = 1.0 + 1.0 * (i/(NUM_GROUPS-1));
				affine = 1.75;
			}

            float phase = (i*4+j)*phase0;

			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
			for(float h = 0; h < height; h++){


				float wave1 = magnitude1 * sinf(h * freq1 + phase);
				float wave2 = magnitude2 * sinf(h * freq2 + phase);
				float wave3 = magnitude3 * sinf(h * freq3 + phase);
				float wave4 = magnitude4 * sinf(h * freq4 + phase);

				// wave1 = 0;
				wave2 = 0;
				wave3 = 0;
				wave4 = 0;

				float sine = sinf(h*FREQUENCY) * AMPLITUDE;
				float x = xGroup + xInternalSpacing + (sine + wave1 + wave2 + wave3 + wave4) * direction * affine;
				float y = h;

				fprintf(file, "%.2f,%.2f ", x, y);
			}
			fprintf(file, "\"/>\n"); // closing quote
		}
	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}