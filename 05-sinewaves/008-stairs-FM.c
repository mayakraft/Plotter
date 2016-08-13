#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "008-stairs.svg\0";
char path[128] = "out/\0";

// document
int width = 600;
int height = 800;

// groups
float NUM_GROUPS = 2;
float GROUP_SPACING = 300.0;
float GROUP_NUM_VERTICALS = 6.0;

// sine curve
float FREQUENCY = .05;
float AMPLITUDE = 12;

float LARGE_FREQUENCY = .015;

float LARGE_STRETCH = .5;

int MASTER_INDEX = 0;


int mod2PosNeg(int iterator){
	if(iterator%2 == 0){ return -1; }
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%d", width, height);
	fprintf(file, "px\" viewBox=\"0 0 %d %d", width, height);
	fprintf(file, "\" xml:space=\"preserve\">\n<g>\n");

	for(int i = 0; i < NUM_GROUPS; i++){
		float xGroup = GROUP_SPACING * i;  // the major X axis of each group

		// 4 sine waves in every group
		for(int j = 0; j < GROUP_NUM_VERTICALS; j++){
			// pattern: L L R R L L ...
			int direction = 1;//mod2PosNeg(j*.5);   // -1 or +1
			if(j > GROUP_NUM_VERTICALS * 0.5)
				direction = -1;

			// spacing
			float percentOfGroup = (j / GROUP_NUM_VERTICALS);
			float xInternalSpacing = percentOfGroup * GROUP_SPACING;

			float PHASE_OFFSET = 0; // reset every height round

			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
			for(float h = 0; h < height; h++){

				float freq_increase = 0; 

				if(h > height*(.5-LARGE_STRETCH*.5) && h < height*(.5+LARGE_STRETCH*.5) ){
					float start = height*(.5-LARGE_STRETCH*.5);
					float phase = (h-start)/(height*LARGE_STRETCH); // 0 to 1
					freq_increase = powf(cos(phase*TWOPI*.5 + TWOPI*.25), 2);
				}
				PHASE_OFFSET += freq_increase * LARGE_FREQUENCY;

				float sine = sinf(h*FREQUENCY + PHASE_OFFSET) * AMPLITUDE;
				float x;

				if(MASTER_INDEX%6 == 0 || MASTER_INDEX % 6 == 3){
					x = xGroup + xInternalSpacing + 0 + AMPLITUDE;
					fprintf(file, "%.2f,%.2f ", x, 0.0);
					fprintf(file, "%.2f,%.2f ", x, (float)height);
					break;
				}
				else if(MASTER_INDEX%6 == 1 || MASTER_INDEX % 6 == 4)
					x = xGroup + xInternalSpacing + sine * direction;
				else if(MASTER_INDEX%6 == 2 || MASTER_INDEX % 6 == 5)
					x = xGroup + xInternalSpacing - sine * direction;
				float y = h;

				fprintf(file, "%.2f,%.2f ", x, y);
			}
			fprintf(file, "\"/>\n"); // closing quote

			MASTER_INDEX++;
		}
	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}