#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise1234.c"

#define TWOPI 6.28318530718

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	float seed = rand()%100000/1000.0;

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
	float SCALE = 50;
	unsigned char newPolyline = 0;

	float pMag = 0.6;
	float pStep1 = 10;
	float pStep2 = 20;
	float pStep3 = 30;
	float pStep4 = 50;

	for(int i = 1; i < 8; i++){
		float divider = 10 * 60;

		for(float a = 0; a <= TWOPI; a += TWOPI/divider){
			float curve1 = pMag * pnoise1(seed    + a/TWOPI * pStep1, pStep1);
			float curve2 = pMag * pnoise1(seed+98 + a/TWOPI * pStep2, pStep2);
			float curve3 = pMag * pnoise1(seed+400+ a/TWOPI * pStep3, pStep3);
			float curve4 = pMag * pnoise1(seed+42 + a/TWOPI * pStep4, pStep4);

			if(i == 1){
				curve1 += .2;
				curve2 = 0;
				curve3 = 0;
				curve4 = 0;
			}
			else if (i == 2){
				curve1 += .4;
				curve3 = 0;
				curve4 = 0;
			}
			else if(i == 3){
				curve1 -= .4;
				curve4 = 0;
			}
			else if(i == 4){
				curve1 -= 1.2;
				curve4 = .2;
			}
			else if(i == 5){
				curve1 -= 1.7;
				curve4 *= .4;
			}
			else if(i == 6){
				curve1 -= 2.4;
				curve4 *= .7;
			}
			else if(i == 7){
				curve3 *= 3.0;
				curve1 -= 2.4;
				curve4 *= 3.0;
			}

			x = width*.5  + SCALE * cosf(a) * (i + curve1 + curve2 + curve3 + curve4);
			y = height*.5 + SCALE * sinf(a) * (i + curve1 + curve2 + curve3 + curve4);

			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);

	printf("%f\n", seed);
	return 0;
}