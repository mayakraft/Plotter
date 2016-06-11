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
	float SCALE = 60;
	unsigned char newPolyline = 0;
	for(int i = 1; i < 6; i++){
		float divider = 10 * 60;
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float bend1 = noise1(seed + a*2)*3;
			float bend2 = noise1(seed + 8+a*3) * powf(i-3,1.5) * 1.5;
			if(i < 3) 
				bend2 = 0;
			// 	bend2 = noise1(seed + 8+a*10) * powf(i-1.5,2);
				// bend2 = 0;
			// float bend3 = noise1(-seed - a*40) * (i-2) * 0.2;
			// if(i < 3) 
				// bend3 = 0;

			float weight1 = (1+cos(i/4.0*M_PI))*.5;
			float weight2 = (1-cos(i/4.0*M_PI))*.5;

			x = width*.5  + SCALE * cos(a) * (i + bend1*weight1 + bend2*weight2);// * (i + bend1)+ cos(a) * bend2 - sin(a) * bend3;
			y = height*.5 + SCALE * sin(a) * (i + bend1*weight1 + bend2*weight2);// * (i + bend1)+ sin(a) * bend2 - cos(a) * bend3;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}