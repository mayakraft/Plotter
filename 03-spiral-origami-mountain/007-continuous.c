#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise1234.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "007-mountain.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

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

	float SCALE = 80;

	float pMag = 0.6;
	float pStep1 = 10;
	float pStep2 = 30;

	for(int i = 1; i < 4; i++){
		float circleResolution = 10 * 60;

		for(float a = 0; a <= TWOPI; a += TWOPI/circleResolution){
			float revolution = a/TWOPI;

			float curve1 = pMag * pnoise1(seed + revolution * pStep1, pStep1);// * (i)*.7;
			float curve2 = pMag * pnoise1(seed+8 + revolution * pStep2, pStep2);// * powf(i-2,2);
			if(i%2 == 0) 
				curve2 = pMag * pnoise1(seed+8 + revolution * pStep2*.5, pStep2*.5);// * powf(i-1.5,2);s

			float x = width*.5  + SCALE * cosf(a) * (i + curve1 + curve2);
			float y = height*.5 + SCALE * sinf(a) * (i + curve1 + curve2);

			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);

	printf("%f\n", seed);
	return 0;
}