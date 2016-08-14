#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "007-wave.svg\0";
char path[128] = "out/\0";

int width = 900;
int height = 900;

float SCALE = 26;
float ENDCAP = .4;
float ROUNDS = 11;//15.0;//18.0;

float divider = 10 * 60;

float wobbleFreq = 23.0;
float wobbleMag = 0.033;

float nudgeScale = 0.0333;

float pathGap = 0.33;

float SIDE_AMP = 0.017;

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

	for(int i = 0; i <= ROUNDS+1; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			if(i >= ROUNDS && a > TWOPI*.25)
				break;
			float one = 1.0;
			if(i == 0)
				one = (a/TWOPI);

			if(i == 0)
				nudgeScale = 0.1;
			else if(i == 2)
				nudgeScale = 0.1;
			else if(i == 4)
				nudgeScale = 0.06;
			else
				nudgeScale = 0.033;

			if(i == 0)
				wobbleMag = 0.03 + (0.04-0.03) * (1-a/TWOPI);
			else if(i == 2)
				wobbleMag = 0.02 + (0.03-0.02) * (1-a/TWOPI);
			else 
				wobbleMag = 0.02;

			// raise amplitude at just the sides 
			wobbleMag += SIDE_AMP * powf(sin(a), 2);

			float wobbleIncr = (i + 2*a/TWOPI);
			// if(cos(a) < 0)
			// 	wobbleIncr *= 1.5;
			wobbleIncr = (i + 2*a/TWOPI) * (1 + (-1*cos(a) + 1)*.25);

			// SCALE = 10 + .1 * powf((i+2*a/TWOPI), 2);


			float x = width*.5  + SCALE * cos(a - nudgeScale*sin(a)) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr ) - SCALE * pathGap * one;
			float y = height*.5 + SCALE * sin(a - nudgeScale*sin(a)) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );


			// the end of the line, ease these two lines together
			if(i >= ROUNDS ){
				float otherX = width*.5  + SCALE * cos(a-TWOPI*.5 - nudgeScale*sin(a)) * (i + 2*a/TWOPI - sin(a*wobbleFreq)*wobbleMag*wobbleIncr  ) + SCALE * pathGap * one;
				float otherY = height*.5 + SCALE * sin(a-TWOPI*.5 - nudgeScale*sin(a)) * (i + 2*a/TWOPI - sin(a*wobbleFreq)*wobbleMag*wobbleIncr );	
				x = (x+otherX) * .5;
				y = (y+otherY) * .5;
			}

			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}

	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#0000FF\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	for(int i = 0; i < ROUNDS; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			if(i == ROUNDS-1 && a > TWOPI*.75)
				break;

			float one = 1.0;
			if(i == 0)
				one = (a/TWOPI);
			// one = 0;

			if(i == 0)
				nudgeScale = 0.1;
			else if(i == 2)
				nudgeScale = 0.1;
			else if(i == 4)
				nudgeScale = 0.06;
			else
				nudgeScale = 0.033;


			if(i == 0)
				wobbleMag = 0.03 + (0.04-0.03) * (1-a/TWOPI);
			else if(i == 2)
				wobbleMag = 0.02 + (0.03-0.02) * (1-a/TWOPI);
			else
				wobbleMag = 0.02;

			// raise amplitude at just the sides 
			wobbleMag += SIDE_AMP * powf(sin(a), 2);

			float wobbleIncr = (i + 2*a/TWOPI);
			// if(cos(a) < 0)
			// 	wobbleIncr *= 1.5;
			wobbleIncr = (i + 2*a/TWOPI) * (1 + (-1*cos(a) + 1)*.25);

			// SCALE = 10 + .1* powf((i+2*a/TWOPI), 2);

			float x = width*.5  + SCALE * cos(a-TWOPI*.5 - nudgeScale*sin(a)) * (i + 2*a/TWOPI - sin(a*wobbleFreq)*wobbleMag*wobbleIncr  ) + SCALE * pathGap * one;
			float y = height*.5 + SCALE * sin(a-TWOPI*.5 - nudgeScale*sin(a)) * (i + 2*a/TWOPI - sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}



	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#999\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
	// for(int i = 0; i < ROUNDS; i+=2){
	// 	for(float a = 0; a < TWOPI; a += TWOPI/divider){
	// 		float one = 1.0;
	// 		if(i == 0)
	// 			one = (a/TWOPI);
	// 		float wobbleIncr = (i + 2*a/TWOPI);
	// 		x = width*.5  + SCALE * cos(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr ) - SCALE*.33 * one;
	// 		y = height*.5 + SCALE * sin(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
	// 		fprintf(file, "%.2f,%.2f ", x, y);
	// 	}
	// }
	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#999\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
	// for(int i = 0; i < ROUNDS; i+=2){
	// 	for(float a = 0; a < TWOPI; a += TWOPI/divider){
	// 		float one = 1.0;
	// 		if(i == 0)
	// 			one = (a/TWOPI);
	// 		float wobbleIncr = (i + 2*a/TWOPI);
	// 		x = width*.5  + SCALE * cos(a-TWOPI*.5) * (i + 2*a/TWOPI - sin(a*wobbleFreq)*wobbleMag*wobbleIncr  ) + SCALE*.33 * one;
	// 		y = height*.5 + SCALE * sin(a-TWOPI*.5) * (i + 2*a/TWOPI - sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
	// 		fprintf(file, "%.2f,%.2f ", x, y);
	// 	}
	// }








	wobbleMag = 0.025;


	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	// int i = 14;
	float i = 15.5;
		for(float a = 0; a <= TWOPI+.0001; a += TWOPI/divider){
			float wobbleIncr = (i + 2*a/TWOPI);
			// wobbleIncr = 1.0;
			float x = width*.5  + SCALE * cos(a) * (i + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			float y = height*.5 + SCALE * sin(a) * (i + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			fprintf(file, "%.2f,%.2f ", x, y);
		}




	//+ cos(turn) * .2*sqrt(i + 2*a/TWOPI) 
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}