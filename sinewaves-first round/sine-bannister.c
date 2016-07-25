#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../noise.c"

#define TWOPI 6.28318530718

int posNeg(int in){
	if(in == 0){
		return -1;
	}
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	float seed = rand()%1000/100.0;

	int width = 1200;
	int height = 1200;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "vertical-sines.svg");
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


	float x, y;

	float COLUMNS = 12;

	for(int i = 0; i < COLUMNS; i++){
		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
		for(float j = 0; j < height; j++){
			int halfI = floor(i*.5);
			int one = floor((i+0)*.25);
			int three = floor((i+2)*.25);

			// float vec[2];
			// vec[0] = i*.33;
			// vec[1] = j/(float)height*3;
			float waveMag = 22;
			float xShift = 0;//30 * sinf(i);

			// x = 70 + 66*(i+one+three)  +  waveMag * posNeg(halfI%2) * sinf(j*.0333 + sin(j*.02) );
			x = 70 + 66*(i+one+three)  +  waveMag * posNeg(halfI%2) * sinf(j*.04 + sin(j*.02) + cos(j*.01+ cos(j*.02)) );
			y = j;

			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing quote
	}
	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	// float turn = 0;
	// for(int i = 0; i < COLUMNS; i+=2){
	// 	for(float j = 0; j < TWOPI; j += TWOPI/divider){
	// 		x = 0;
	// 		y = 0;
	// 		fprintf(file, "%.2f,%.2f ", x, y);
	// 	}
	// }


	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}