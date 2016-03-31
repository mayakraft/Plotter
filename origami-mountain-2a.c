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
	float SCALE = 13;
	float ENDCAP = .2;
	unsigned char newPolyline = 0;
	int count = 0;
	float ROUNDS = 24.0;
	for(int i = 2; i < ROUNDS; i++){
		float divider = 10 * 60;
		for(float a = 0; a < TWOPI; a += TWOPI/divider){
			float endCap = 1;
			if(a < ENDCAP)
				endCap = a/ENDCAP;
			if(a > TWOPI-ENDCAP)
				endCap = 1.0 - (a-TWOPI+ENDCAP)/ENDCAP;
			endCap = powf(endCap,2);

			float masterShape = noise1(seed + a) * (4 + i);
			float masterShape2 = noise1(seed + 6 + a*2) * (4 + i*.7);
			// float masterShape = noise1(seed + a*2) * 3;

			float shape2 = noise1(seed +  8+a*9) * .05 * powf(i,1.5);
			float shape3 = noise1(seed + 40+a*13) * .05 * powf(i,1.5);
			float shape4 = noise1(seed + 19+a*12) * .03 * powf(i,1.5);

			float weight2 = (1-cos(i/ROUNDS*M_PI*2+1))*.5;
			// float weight2 = (1+cos(i/ROUNDS*M_PI*2))*.5;
			if(i > ROUNDS*.8) weight2 = 0;
			float weight3 = (1-cos(i/ROUNDS*M_PI*2-M_PI+1))*.3;
			if(i < ROUNDS * .5) 
				weight3 = 0;
				// weight2 = 0;

			float weight4 = (1-cos(i/ROUNDS*M_PI*3-1.5))*.5;
			if(i < ROUNDS*.15 || i > ROUNDS * .82)
				weight4 = 0; 


			float mW1 = (1+cos(i/ROUNDS*M_PI))*.5;
			float mW2 = (1-cos(i/ROUNDS*M_PI))*.5;

			x = width*.5  + SCALE * cos(a) * (i + endCap*(masterShape * mW1 + masterShape2 * mW2 + shape2*weight2 + shape3*weight3 + shape4*weight4 ) );
			y = height*.5 + SCALE * sin(a) * (i + endCap*(masterShape * mW1 + masterShape2 * mW2 + shape2*weight2 + shape3*weight3 + shape4*weight4 ) );
			//  + a/TWOPI 


			//  + a/TWOPI * (1-(int)(count%2))
			//+ a/TWOPI * (1-(int)(count%2)*2) 


			fprintf(file, "%.2f,%.2f ", x, y);
		}
		count++;
		if(!(count%2))
			i++;
	}
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}