/* File: A2Template2_ImageARM.c */
/* CSC367 Student */
/* Template in C for the program in ARM based on a subset of
the C program written for Assignment 1 */
/* The original program in C reads a 2D image from an input file, applies
to it some image processing transformation upon request and
prints the output both to the screen and to a file.
The 2D image is stored and handled as a 2D array of characters. */

/****** REVISED PSEUDO CODE FOR THE ARM PROGRAM  *******
Initialization:
	Open the input file
		if problems, print message and exit program
	Print a header message to screen
Obtain the input data:
	Read row size (Rsize1) and column size (Csize1) of image from the input file
	Read exactly (Rsize1)x(Csize1) integers as elements for an image,
		convert to characters, and store as 2D char array
	Print image as characters with headings to screen
Processing the image:
	Construct the Horizontal Mirror of the image into a second image
		and print the resulting image with headings to screen
	Construct the Vertical Mirror of the image into a second image
		and print the resulting image with headings to screen
BONUS: 	Construct the Diagonal Right of the image into a second image
		and print the resulting image with headings (note that this
		is the equivalent of constructing the transpose of a matrix)
Closure:
	Print a final message to screen
	Close the input file
	Exit the program */

/* Code for File I/O taken from IO_Example2a.s */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXROW 10
#define MAXCOL 10
#define	AP	'&'
#define	PL	'+'

/* global variables*/
FILE *fpin1;		/*pointer to file*/

/*************************************************************/
/*************************************************************/
int main() {

    int Rsize1, Csize1;	/*image sizes*/
	char IMchr1[MAXROW][MAXCOL]; /*original image*/
	char IMchr2[MAXROW][MAXCOL]; /*resulting image after processing*/
	int	ii,jj,temp,rr;

	fprintf(stdout, "Hello\n");		/*start of program*/
	/*open input file*/
	fpin1 = fopen("A2inF2.txt", "r");  /* open the file for reading */
	if (fpin1 == NULL) {
		fprintf(stdout, "Cannot open input file - Bye\n");
		return(0); /*if problem, exit program*/
	}

	fprintf(stdout, "\n James Tiberius Kirk - Student Number V00123456 \n");
	fprintf(stdout, "\n File = A2Template2.c \n");
	fprintf(stdout, "\n CSC 230, Assignment 2, Part 2 \n\n");
	fprintf(stdout,"Starting: \n");

	/*Read in the sizes for the image*/
	fscanf(fpin1,"%d",&Rsize1);  /* read row number */
	fscanf(fpin1,"%d",&Csize1);  /* read col number */

	/*Read in the image*/
	for (ii=0;ii<Rsize1;ii++) {
		for (jj=0;jj<Csize1;jj++) {
			fscanf(fpin1,"%d",&temp);  /* read element of image */
			if (temp==0) IMchr1[ii][jj]=PL;
			else IMchr1[ii][jj]=AP;
		}
	}

	/*Print the initial image*/
	fprintf(stdout, " IMchr1 contains: \n");
	for(ii = 0; ii < Rsize1; ii++) {
		for(jj = 0; jj < Csize1; jj++) {
			fprintf(stdout, " %2c", IMchr1[ii][jj]);
		}
		fprintf(stdout, "\n");
	}

	/*Construct the Horizontal Mirror image */
	jj=Rsize1-1;
	for(ii = 0; ii < Rsize1; ii++) { /*do for each row */
		/*copy row ii of Image1 to row jj of Image2*/
		for(rr = 0; rr < Csize1; rr++) { /*copy row*/
				IMchr2[jj][rr]=IMchr1[ii][rr];
		}
		jj--;
	}
	/*Print the transformed image*/
	fprintf(stdout, "\nHorizontal Mirroring \n");
	fprintf(stdout, "IMchr2 contains: \n\n");
	for(ii = 0; ii < Rsize1; ii++) {
		for(jj = 0; jj < Csize1; jj++) {
			fprintf(stdout, " %2c", IMchr2[ii][jj]);
		}
		fprintf(stdout, "\n");
	}

	/*Construct the Vertical Mirror image */
	jj=Csize1-1;
	for(ii = 0; ii < Csize1; ii++) { /*for each column*/
		/*copy column ii of Image1 to column jj of Image2*/
		for(rr = 0; rr < Rsize1; rr++) {
			IMchr2[rr][jj]=IMchr1[rr][ii];
		}
		jj--;
	}
	/*Print the transformed image*/
	fprintf(stdout, "\nVertical Mirroring \n");
	fprintf(stdout, "IMchr2 contains: \n\n");
	for(ii = 0; ii < Rsize1; ii++) {
		for(jj = 0; jj < Csize1; jj++) {
			fprintf(stdout, " %2c", IMchr2[ii][jj]);
		}
		fprintf(stdout, "\n");
	}

/* BONUS - OPTIONAL - NO NEED TO DO AT ALL   */
/*Construct the Transpose Diagonal Right image */

	fprintf(stdout, "\n All done - Bye! \n");

	fclose(fpin1);  /* close the file */

	return (0);
}
