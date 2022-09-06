/* File: A1Final.c - Assignment 1  */
/* Name - Student Number V00123456  */
/* The program reads a 2D image from an input file, applies
to it some image processing transformation upon request and
prints the output both to the screen and to a file.
The 2D image is stored and handled as a 2D array of characters. */

/****** PSEUDO CODE: ******
	*Initialization:
		Open the input file
			if problems, print message and exit
		Open the output file
				if problems, print message and exit
		Print a header message to screen and to file

		*Obtain the input data:
		Read row size and column size of image
		Read elements of image as integers, convert to characters, and store as 2D char array
		Print image as characters with headings to screen and to file

		*Processing the image:
		Repeat until the end of file is reached:
			Read an integer k from the input file specifying a task for the image
				Case k of:
					If 1 then call Vertical Mirror Image routine
					If 2 then call Horizontal Mirror Image routine
					If 3 then call Diagonal Right Image routine
					If 4 then call Diagonal Left Image routine
					If 5 then call Rotate Right Image routine (BONUS)
				Print the new image generated with headings to screen and to file

		*Closure:
		When End of File is reached
			Print a final message to screen and to file
			Close input and output files
		Exit the program*/

/* Code for File I/O taken from FileIntegersArray2.c */

/* FINAL VERSION: Optional Task 5, Rotation Right by 90 degrees
	is not included */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXROW 50
#define MAXCOL 50
#define	AP	'&'
#define	PL	'+'

/* global variables*/
FILE *fpin1,*fpout1;	/*pointers to files*/

/*************************************************************/
/**** Function OpenInputFile: opens a given file for input****/
/*    returns file pointer */
FILE *OpenInputFile(char *fileName) {
	FILE	*result;
	result = fopen(fileName, "r");  /* open the file for reading */
	if (result == NULL)   			/* an error opening the file? */
		fprintf(stderr, "cannot read %s\n", fileName);
	return (result);
}
/*************************************************************/
/**** Function OpenOutputFile: opens a given file for output****/
/*    returns file pointer */
FILE *OpenOutputFile(char *fileName) {
	FILE	*result;
	result = fopen(fileName, "w");  /* open the file for writing */
	if (result == NULL)   			/* an error opening the file? */
		fprintf(stderr, "cannot write %s\n", fileName);
	return (result);
}
/*************************************************************/
/****** void PrImage(Image, Nrows,Ncols) ******/
/* This procedure prints a 2D char array row by row
	both to the screen and to an output file (global) */
void PrImage( char Image[MAXROW][MAXCOL], int Nrows, int Ncols)
{
	int ii, jj;
	for(ii = 0; ii < Nrows; ii++) {
		for(jj = 0; jj < Ncols; jj++) {
			fprintf(stdout, " %2c", Image[ii][jj]);
			fprintf(fpout1, " %2c", Image[ii][jj]);
		}
		fprintf(stdout, "\n");
		fprintf(fpout1, "\n");
	}
}/*End of PrImage*/
/*************************************************************/
/****** void CopyCol(Mat1,Mat2,Nrows,Coli,Colj) ******/
/* Copy Coli of Mat1 to Colj of Mat2 of the same dimensions */
void CopyCol( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Nrows, int Coli, int Colj)
{
	int ii;
	for(ii = 0; ii < Nrows; ii++) {
		Mat2[ii][Colj]=Mat1[ii][Coli];
	}

}/*End of CopyCol*/
/*************************************************************/
/****** void CopyRow(Mat1,Mat2,Ncols,Rowi,Rwoj) ******/
/* Copy row i of Mat1 to row j of Mat2 of the same dimensions */
void CopyRow( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Ncols, int Rowi, int Rowj)
{
	int ii;
	for(ii = 0; ii < Ncols; ii++) {
		Mat2[Rowj][ii]=Mat1[Rowi][ii];
	}

}/*End of CopyRow*/
/*************************************************************/
/****** void CopyColRow(Mat1,Mat2,Nrows,Coli,Rowj) ******/
/* Copy col i of Mat1 to row j of Mat2 */
void CopyColRow( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Nrows, int Ncols, int Coli, int Rowj)
{
	int ri;
	for (ri =0; ri < Nrows; ri++) {
		Mat2[Rowj][ri] = Mat1[ri][Coli];
	}

}/*End of CopyColRow*/
/*************************************************************/
/****** void CopyColrevRow(Mat1,Mat2,Nrows,Ncols,Coli,Rowj) ******/
/* Copy col i from (Nrows to 0) of Mat1 to row j of Mat2 from 0 to Ncols */
/* that is, copy the column, from bottom to top element,to the row */
/* 	copy column (Ncols-1) from (Nrows-1 element) to row (0) from (0) element
	copy column (Ncols-2) from (Nrows-1 element) to row (1) from (0) element
	copy column (0) from (Nrows-1 element) to row (Ncols-1) from (0) element*/
void CopyColrevRow( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Nrows, int Ncols, int Coli, int Rowj)
{
	int rv,ri;
	ri = 0;  /*use for element order of Mat2 row*/
	for (rv = (Nrows-1); rv >= 0; rv--) {
		Mat2[Rowj][ri] = Mat1[rv][Coli];
		ri++;
	}

}/*End of CopyrevColRow*/
/*************************************************************/
/****** void VMirror(Image1, Image2, Nrows, Ncols) ******/
/* Given the 2D char array of Image1 and its dimensions,
	construct the vertical mirror image in Image 2 as in:
	copy columns (0,1,...,Ncols-1) of Image1 to
	columns (Ncols-1, Ncols-2, ..., 1, 0) respectively of Image2 */
void VMirror( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int ci,cj;
	cj=Ncols-1;

	for(ci = 0; ci < Ncols; ci++) {
		CopyCol(Image1,Image2,Nrows,ci,cj); /*copy column ci of
				Image1 to column cj of Image2*/
		cj--;
	}

}/*End of VMirror*/
/*************************************************************/
/****** void HMirror(Image1, Image2, Nrows, Ncols) ******/
/* Given the 2D char array of Image1 and its dimensions,
	construct the horizontal mirror image in Image 2 as in:
		copy rows (0,1,...,Nrows-1) of Image1
		to rows (Nrows-1,Nrows-2,...,1,0) respectively of Image2 */
void HMirror( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int ri,rj;
	rj=Nrows-1;
	for(ri = 0; ri < Nrows; ri++) {
			CopyRow(Image1,Image2,Ncols,ri,rj); /*copy row ri of
					Image1 to row rj of Image2*/
			rj--;
	}

}/*End of HMirror*/
/*************************************************************/
/****** void DiagR(Image1, Image2, Nrows, Ncols) ******/
/*Given the 2D char array of Image1 and its dimensions,
	construct the flipped image in Image2 along the top
	left to bottom right diagonal as in:
		 copy col 0 of Image1 -> row 0 of Image2
		 copy col 1 of Image1 -> row 1 of Image2
		......................................
		 copy col (Ncols-1) of Image1 to row (Ncols-1) of Image2
		 NOTE: sizes of Image2 are inverted from Image1 */
void DiagR( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int rc;
	for(rc = 0; rc < Ncols; rc++) {
		/*copy col rc of Image1 to row rc of Image2*/
		CopyColRow(Image1,Image2,Nrows,Ncols,rc,rc);
	}

}/*End of DiagR*/
/*************************************************************/
/****** void DiagL(Image1, Image2, Nrows, Ncols) ******/
/*Given the 2D char array of Image1 and its dimensions,
	construct the flipped image in Image2 along the top
	right to bottom left diagonal as in:
		copy col (Ncols-1) of Image1 -> row 0 of Image2
		copy col (Ncols-2) of Image1 -> row 1 of Image2
		......................................
		copy col 0 of Image1 -> row (Ncols-1) of Image2
		NOTE: sizes of Image2 are inverted from Image1 */
void DiagL( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int cc,rr;
	for(cc = (Ncols-1); cc >=0; cc--) {
		/*copy col cc of Image1 to row (Ncols-cc-1) of Image2,
		with column elements from bottom to top order*/
		rr = (Ncols - cc) - 1;
		CopyColrevRow(Image1,Image2,Nrows,Ncols,cc,rr);
	}

}/*End of DiagL*/
/*************************************************************/
/****** void RotR(Image1, Image2, Nrows, Ncols) ******/
/*Given the 2D char array of Image1 and its dimensions,
	construct the rotated by 90 degree image in Image2 */
void RotR( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	fprintf(stdout, "\n Optional task 5 - not implemented \n");
	fprintf(fpout1, "\n Optional task 5 - not implemented \n");

}/*End of RotR*/
/*************************************************************/
/****** void RdSize(FILE *fpi,*Nrows,*Ncols) ******/
/*Read from an input file two integers for the number of rows and
	number of columns of the image to be processed*/
void RdSize(FILE *fpi,int *Nrows, int *Ncols)
{
	int temp;
	fscanf(fpi,"%d",&temp);  /* read row number */
	*Nrows=temp;
	fscanf(fpi,"%d",&temp);  /* read col number */
	*Ncols=temp;

}/*End of RdSize*/
/*************************************************************/
/****** void RdImage(FILE *fpi,Image,Nrows,Ncols) ******/
/*Read from an input file the integers describing the image to
	be processed and store the corresponding character in the 2D array*/
void RdImage(FILE *fpi,char Image1[MAXROW][MAXCOL],int Nrows, int Ncols)
{
	int temp,ii,jj;
	for (ii=0;ii<Nrows;ii++) {
		for (jj=0;jj<Ncols;jj++) {
			fscanf(fpi,"%d",&temp);  /* read element of image */
			if (temp==0) Image1[ii][jj]=PL;
			else Image1[ii][jj]=AP;
		}
	}
}/*End of RdImage*/
/*************************************************************/
/****** void RdDoTask(FILE *fpi,FILE *fpi,Image1,Image2,Nrows,Ncols)***/
/*Read integers from an opened input file until EOF, and call
the appropriate stub routine for each task represented*/
int RdDoTask(FILE *fpi, FILE *fpo,char Image1[MAXROW][MAXCOL],
			char Image2[MAXROW][MAXCOL],int Nrows, int Ncols)
{
	int nir;
	int task;
	nir = fscanf(fpi,"%d",&task);  /* read 1st integer */
	while(nir == 1) {	/*if EOF, fscanf returns 0 int read*/
		switch (task) {
			case 1:
				VMirror(Image1,Image2,Nrows,Ncols);
				/*Print the transformed image*/
				fprintf(stdout, "\nTASK 1 = Vertical Mirroring \n");
				fprintf(fpout1, "\nTASK 1 = Vertical Mirroring\n");
				fprintf(stdout, "IMchr2 contains: \n\n");
				fprintf(fpout1, "IMchr2 contains: \n\n");
				PrImage(Image2,Nrows,Ncols);
				break;
			case 2:
				HMirror(Image1,Image2,Nrows,Ncols);
				/*Print the transformed image*/
				fprintf(stdout, "\nTASK 2 = Horizontal Mirroring \n");
				fprintf(fpout1, "\nTASK 2 = Horizontal Mirroring \n");
				fprintf(stdout, "IMchr2 contains: \n\n");
				fprintf(fpout1, "IMchr2 contains: \n\n");
				PrImage(Image2,Nrows,Ncols);
				break;
			case 3:
				DiagR(Image1,Image2,Nrows,Ncols);
				/*Print the transformed image*/
				fprintf(stdout, "\nTASK 3 = Diagonal Right \n");
				fprintf(fpout1, "\nTASK 3 = Diagonal Right \n");
				fprintf(stdout, "IMchr2 contains: \n\n");
				fprintf(fpout1, "IMchr2 contains: \n\n");
				PrImage(Image2,Ncols,Nrows);
				break;
			case 4:
				DiagL(Image1,Image2,Nrows,Ncols);
				/*Print the transformed image*/
				fprintf(stdout, "\nTASK 4 = Diagonal Left \n");
				fprintf(fpout1, "\nTASK 4 = Diagonal Left \n");
				fprintf(stdout, "IMchr2 contains: \n\n");
				fprintf(fpout1, "IMchr2 contains: \n\n");
				PrImage(Image2,Ncols,Nrows);
				break;
			case 5:
				/*Print the transformed image*/
				fprintf(stdout, "\nTASK 5 = Rotation Right \n");
				fprintf(fpout1, "\nTASK 5 = Rotation Right \n");
				/*fprintf(stdout, "IMchr2 contains: \n\n");
				  fprintf(fpout1, "IMchr2 contains: \n\n");
				  PrImage(Image2,Nrows,Ncols);*/
				RotR(Image1,Image2,Nrows,Ncols);
				break;
			}
		nir = fscanf(fpi,"%d",&task); /* read next*/
	}
	return (nir);	/* return EOF marker */
} /*End RdDoTask*/

/*************************************************************/
/*************************************************************/
int main() {

    int	eof;
    int Rsize1, Csize1;	/*image sizes*/
	char IMchr1[MAXROW][MAXCOL]; /*original image*/
	char IMchr2[MAXROW][MAXCOL]; /*resulting image after processing*/

	fprintf(stdout, "Hello:\n");		/*start of program*/
	/*open all input and output files*/
	fpin1 = OpenInputFile("A1inF.txt");
	if (fpin1 == NULL) {
		fprintf(stdout, "Cannot open input file - Bye\n");
		return(0); /*if problem, exit program*/
	}

	fpout1 = OpenOutputFile("A1outF.txt");
	if (fpout1 == NULL) {
		fprintf(stdout, "Cannot open output file - Bye\n");
		return(0); /*if problem, exit program*/
	}
	/*hello message to screen and output file*/
	fprintf(stdout, "\n Captain Picard - Student Number V00123456 \n");
	fprintf(stdout, "\n File = A1.c	- Fall 2011 \n");
	fprintf(stdout, "\n Assignment 1, Part 2 \n\n");
	fprintf(fpout1, "\n Captain Picard - Student Number V00123456 \n");
	fprintf(fpout1, "\n File = A1.c	- 2021 \n");
	fprintf(fpout1, "\n CSC 230, Assignment 1, Part 2 \n\n");
	fprintf(stdout,"Starting: \n");
	fprintf(fpout1,"Starting: \n");

	/*Read in the sizes for the image*/
	RdSize(fpin1,&Rsize1,&Csize1);
	/*Read in the image*/
	RdImage(fpin1,IMchr1,Rsize1,Csize1);

	/*Print the initial image*/
	fprintf(stdout, " Initial IMchr1 contains: \n");
	fprintf(fpout1, " Initial IMchr1 contains: \n");
	PrImage(IMchr1, Rsize1, Csize1);

	/* read all integers from file until EOF - for each call the
	required stub routine for the image processing task*/
	eof = RdDoTask(fpin1,fpout1,IMchr1,IMchr2,Rsize1,Csize1);

	/* Closure */
	fprintf(stdout, "\n The program is all done - Bye! \n");
	fprintf(fpout1, "\n The program is all done - Bye! \n");

	fclose(fpin1);  /* close the files */
	fclose(fpout1);

	return (0);
}/*End of Main*/
