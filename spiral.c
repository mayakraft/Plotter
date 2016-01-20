#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "noise.c"

#define TWOPI 6.28318530718

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	float seed = rand()%100/100.0;

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
	const int REVS = 20;
	unsigned char newPolyline = 0;
	for(int i = 1; i < REVS; i++){
		float divider = i * 30;
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float bend1 = noise1(seed + a*3)*(i-1)*.7;
			float bend2 = noise1(seed + 8+a*10) * powf(i-(REVS*.4),2)*.8;
			if(i < (REVS*.4)) bend2 = 0;
			float bend3 = noise1(-seed - a*10) * (i-(REVS*.6))*5;
			if(i < (REVS*.6)) bend3 = 0;
			x = width*.5  + cos(a) * (i + a/TWOPI + bend1) * 15 + cos(a) * bend2 - sin(a+i*.1) * bend3;
			y = height*.5 + sin(a) * (i + a/TWOPI + bend1) * 15 + sin(a) * bend2 - cos(a+i*.1) * bend3;
			fprintf(file, "%.1f,%.1f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}