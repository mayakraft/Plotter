#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "006-mountain.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

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

	float SCALE = 20;
	float ENDCAP = .2;
	int count = 0;
	float ROUNDS = 12;//15.0;//18.0;
	float iRad = 5;
	for(int i = 5; i < ROUNDS; i++){
		float circleResolution = 10 * 60;
		for(float a = 0; a < TWOPI; a += TWOPI/circleResolution){
			float endCap = 1;
			if(a < ENDCAP)
				endCap = a/ENDCAP;
			if(a > TWOPI-ENDCAP)
				endCap = 1.0 - (a-TWOPI+ENDCAP)/ENDCAP;
			endCap = powf(endCap,2);

			float masterShape = noise1(seed + a) * (4 + i);
			float masterShape2 = noise1(seed + 6 + a*2) * (4 + i*.7);
			// float masterShape = noise1(seed + a*2) * 3;

			float shape2 = noise1(seed +  8+a*2) * .1 * powf(i,1.5);
			float shape4 = noise1(seed + 19+a*2.5) * .1 * powf(i,1.5);
			float shape3 = noise1(seed + 40+a*3) * .2 * powf(i,1.5);

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


			// weight3 = 0;
			// weight4 = 0;

			float mW1 = (1+cos(i/ROUNDS*M_PI))*.5;
			float mW2 = (1-cos(i/ROUNDS*M_PI))*.5;

			float x = width*.5  + SCALE * cos(a) * (iRad + endCap*(masterShape * mW1 + masterShape2 * mW2 + shape2*weight2 + shape3*weight3 + shape4*weight4 ) );
			float y = height*.5 + SCALE * sin(a) * (iRad + endCap*(masterShape * mW1 + masterShape2 * mW2 + shape2*weight2 + shape3*weight3 + shape4*weight4 ) );
			//  + a/TWOPI 


			//  + a/TWOPI * (1-(int)(count%2))
			//+ a/TWOPI * (1-(int)(count%2)*2) 


			fprintf(file, "%.2f,%.2f ", x, y);
		}
		count++;
		float rinc = 6*noise1(seed+5 + i*1)+2;
		iRad+=rinc;
		if(!(count%2)){
			i++;
			iRad-=rinc;
			// iRad += powf( (arc4random()%100/100.0)*2 + .8, 2);
			iRad += (1+noise1(seed+14 + i*.3)*12 ) +3;
		}
		// printf("%f\n", noise1(seed+14+i*.5));
	}
	fprintf(file, "\"/>\n"); // closing polyline

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}