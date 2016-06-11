#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));


	int width = 640;
	int height = 640;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "random_walker.svg");
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"");
	fprintf(file, "%d",width);
	fprintf(file, "px\" height=\"");
	fprintf(file, "%d",height);
	fprintf(file, "px\" viewBox=\"0 0 ");
	fprintf(file, "%d",width);
	fprintf(file, " ");
	fprintf(file, "%d",height);
	fprintf(file, "\" xml:space=\"preserve\">\n");

	// int fputc( int c, FILE *file );
	// char x[10]="ABCDEFGHIJ";
	// fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), file);
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
	float x, y;
	x = width * .5;
	y = height * .5;
	unsigned char newPolyline = 0;
	for(int i = 0; i < 2000; i++){
		fprintf(file, "%.2f,%.2f ", x, y);
		x += (rand()%100 / 100.0 - .36)*10;
		y += (rand()%100 / 100.0 - .3)*10;
		if(x < 0){   x += width; newPolyline = 1; }
		if(y < 0){   y += height; newPolyline = 1; }
		if(x > width){ x -= width; newPolyline = 1; }
		if(y > height){ y -= height; newPolyline = 1; }
		if(newPolyline){
			fprintf(file, "\"/>\n"); // closing quote
			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
			newPolyline = 0;
		}
	}
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}