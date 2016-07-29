#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "001-wave.svg\0";
char path[128] = "out/\0";

int width = 800;
int height = 800;

float SCALE = 26;
float ENDCAP = .4;
float ROUNDS = 11;//15.0;//18.0;

float divider = 5 * 60;

float wobbleFreq = 10.0;
float wobbleMag = 0.1;

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
	
	for(int i = 0; i < ROUNDS; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float x = width*.5  + SCALE * cos(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			float y = height*.5 + SCALE * sin(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	float turn = 0;
	for(int i = 0; i < ROUNDS; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float one = 1.0;
			if(i == 0)
				one = (a/TWOPI);
			float x = width*.5  + SCALE * cos(a-TWOPI*.5) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI)  ) + SCALE*.55 * one;
			float y = height*.5 + SCALE * sin(a-TWOPI*.5) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			fprintf(file, "%.2f,%.2f ", x, y);
			turn += TWOPI/divider;
		}
	}



	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote


	int i = 14;
		for(float a = 0; a <= TWOPI; a += TWOPI/divider){
			float x = width*.5  + SCALE * cos(a) * (i + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			float y = height*.5 + SCALE * sin(a) * (i + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			fprintf(file, "%.2f,%.2f ", x, y);
		}




	//+ cos(turn) * .2*sqrt(i + 2*a/TWOPI) 
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}