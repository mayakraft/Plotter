#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "006-layered-nonsymmetrical-sines.svg\0";
char path[128] = "out/\0";
// path[0] = '\0';

// document
int width = 1600;
int height = 1200;

// groups
float NUM_GROUPS = 5;
float GROUP_SPACING = 240.0;
float GROUP_NUM_VERTICALS = 4.0;

// sine curve
float frequency1 = 0.005;
float frequency2 = 0.003;
float frequency3 = 0.015;
float frequency4 = 0.0175;

float amplitude1 = 8;
float amplitude2 = 8;
float amplitude3 = 15;
float amplitude4 = 15;

float phase0 = TWOPI*0.25 / 5.0;

float wanderingGroupX;
float WANDER = 75;

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
	
	wanderingGroupX = 0;
	for(int i = 0; i < NUM_GROUPS; i++){
		wanderingGroupX += WANDER;
		float xGroup = GROUP_SPACING * i + wanderingGroupX;  // the major X axis of each group

		// 4 sine waves in every group
		for(int j = 0; j < GROUP_NUM_VERTICALS; j++){
			// pattern: L L R R L L ...
			int direction = mod2PosNeg(j*.5);   // -1 or +1

			// spacing
			// float percentOfGroup = (j / (GROUP_NUM_VERTICALS));
			float percentOfGroup;
			if(j < (int)(GROUP_NUM_VERTICALS*.5))
				percentOfGroup = (j / (GROUP_NUM_VERTICALS+1));
			else if(j >= (int)(GROUP_NUM_VERTICALS*.5) )
				percentOfGroup = ((j+1) / (GROUP_NUM_VERTICALS+1));

			// if(j == 0) percentOfGroup = .175;
			// if(j == 1) percentOfGroup = .3;
			// if(j == 2) percentOfGroup = .625;
			// if(j == 3) percentOfGroup = .75;
			float xInternalSpacing = percentOfGroup * GROUP_SPACING;

			// affine scale
			float affine = 1.0;  // multiply to all
			if(j == 0 || j == GROUP_NUM_VERTICALS-1){ // multiply to outer curves
				// affine = 1.0 + 1.0 * (i/(NUM_GROUPS-1));
				// affine = 1.75;
				affine = 1.5;
			}

            float phase = 1.57 + (i*4+j) * phase0;

			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open polyline
			for(float h = 0; h < height; h++){

				float wave1 = amplitude1 * sinf(h * frequency1 + phase);
				float wave2 = amplitude2 * sinf(h * frequency2 + phase);
				float wave3 = amplitude3 * sinf(h * frequency3 + phase);
				float wave4 = amplitude4 * sinf(h * frequency4 + phase);

				float tilt = h*.1;
				tilt = 0;

				// wave1 = 0;
				// wave2 = 0;
				// wave3 = 0;
				wave4 = 0;

				float x = xGroup + xInternalSpacing + (wave1 + wave2 + wave3 + wave4) * direction * affine + tilt;
				float y = h;

				fprintf(file, "%.2f,%.2f ", x, y);
			}
			fprintf(file, "\"/>\n"); // closing polyline
		}
	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}