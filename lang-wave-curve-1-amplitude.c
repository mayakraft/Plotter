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
	float SCALE = 26;
	float ENDCAP = .4;
	float ROUNDS = 11;//15.0;//18.0;
	
	float divider = 5 * 60;

	float wobbleFreq = 10.0;
	float wobbleMag = 0.1;

	for(int i = 0; i < ROUNDS; i+=2){
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			x = width*.5  + SCALE * cos(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			y = height*.5 + SCALE * sin(a) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
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
			x = width*.5  + SCALE * cos(a-TWOPI*.5) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI)  ) + SCALE*.55 * one;
			y = height*.5 + SCALE * sin(a-TWOPI*.5) * (i + 2*a/TWOPI + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			fprintf(file, "%.2f,%.2f ", x, y);
			turn += TWOPI/divider;
		}
	}



	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote


	int i = 14;
		for(float a = 0; a <= TWOPI; a += TWOPI/divider){
			x = width*.5  + SCALE * cos(a) * (i + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			y = height*.5 + SCALE * sin(a) * (i + sin(a*wobbleFreq)*wobbleMag*(i + 2*a/TWOPI) );
			fprintf(file, "%.2f,%.2f ", x, y);
		}




	//+ cos(turn) * .2*sqrt(i + 2*a/TWOPI) 
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}