#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "noise.c"

#define TWOPI 6.28318530718

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	float seed = rand()%1000/100.0;

	int width = 800;
	int height = 800;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "homemade.svg");
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"");
	fprintf(file, "%d",width);
	fprintf(file, "px\" height=\"");
	fprintf(file, "%d",height);
	fprintf(file, "px\" viewBox=\"0 0 ");
	fprintf(file, "%d ",width);
	fprintf(file, "%d",height);
	fprintf(file, "\" xml:space=\"preserve\">\n");

	// int fputc( int c, FILE *file );
	// char x[10]="ABCDEFGHIJ";
	// fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), file);
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote


	float x, y;

	float divider = 10 * 60;

	float SCALE = 20;
	float ROUNDS = 17;
	float wobbleFreq = 23.0;
	float wobbleMag = 1;
	// float SCALE = 45;
	// float ROUNDS = 7;
	// float wobbleFreq = 7.0;
	// float wobbleMag = 0.33;

	for(int i = 0; i < ROUNDS; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float wobbleIncr = 5*sqrt(i + 2*a/TWOPI);
			wobbleIncr = 1.0;

			SCALE = 1 * pow((i + 2*a/TWOPI), 1);

			x = width*.5  + SCALE * cos(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			y = height*.5 + SCALE * sin(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	float turn = 0;
	for(int i = 0; i < ROUNDS; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float one = 1.0;
			// if(i == 0)
			// 	one = (a/TWOPI);
			one = 0;
			float wobbleIncr = 5*sqrt(i + 2*a/TWOPI);
			wobbleIncr = 1.0;

			SCALE = 1 * pow((i + 2*a/TWOPI), 1);

			x = width*.5  + SCALE * cos(a-TWOPI*.5) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr  ) + SCALE*.55 * one;
			y = height*.5 + SCALE * sin(a-TWOPI*.5) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			fprintf(file, "%.2f,%.2f ", x, y);
			turn += TWOPI/divider;
		}
	}

	//+ cos(turn) * .2*sqrt(i + 2*a/TWOPI) 
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}