/*
 *  Comp120 - Lab 8:  Starter project -- Complete this code
 *    Code Breaking - use a 'natural' FOCL to break the encryption on a file.
 *
 *  Author: J. Fall
 *  Date: Feb. 2017
 */
 
#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>

// Function prototypes:
void read_focl(char* filename, char focl[], int length);
void print_focl(char focl[], int length);
int find(char c, char list[], int length);
// provided:
char translate(char c, char focl[], char natural_focl[], int length);
void decode_file(char* filename, char focl[], char natural_focl[], int length);
FILE* openFileRead(char* filename);

// Definition of printable character set 
#define FIRST_PRINTABLE ' '  // Space character code 32, see Etter 2016 text, pp. 418-420
#define LAST_PRINTABLE  '~'  // Tilde character code 126
#define NUM_PRINTABLE  (int) (LAST_PRINTABLE - FIRST_PRINTABLE + 1)

int main( int argc, char* argv[] )
{
   if (argc < 4) {
      printf("Usage: breakcode cipherTextFile focl natural_focl\n");
      exit(-1);
   }
   char* cipherFile = argv[1];
   char* foclFile = argv[2];
   char* naturalFoclFile = argv[3];

   char focl[NUM_PRINTABLE];
   char natural[NUM_PRINTABLE];

   printf( "Decoding Input File: %s \n", argv[1]);
   printf( "---------------------------------------------------\n\n ");
   
   read_focl(foclFile, focl, NUM_PRINTABLE);
   read_focl(naturalFoclFile, natural, NUM_PRINTABLE);
   // print_focl(focl, NUM_PRINTABLE);  // debug!
   // print_focl(natural, NUM_PRINTABLE);  // debug!
   decode_file(cipherFile, focl, natural, NUM_PRINTABLE);

   printf( "\n\n---------------------------------------------------\n Decode Compelete \n");

   return 0                           ;
}

/**
 *  Read up to length characters from the given filename into the focl array.
 * Input:  filename -- name of the file to read
 * Output: focl -- an array of characters up to given length
 */
void read_focl(char* filename, char focl[], int length) 

{
    
	FILE* myfile =openFileRead(filename);
	
	char c = fgetc(myfile);
	 int i;
	
	for(i=0;i<length; i++)
	 {
      focl[i]=c;
	  c=fgetc(myfile);
	 }
	 
	 

	
}

	
  
  


/**
 *   Find a given charachter in the list.
 * Input:  c -- the character to find;  list -- this array to find it in
 * Returns: i such that list[i] == c, or -1 if no such i exists.
 */
int find(char c, char list[], int length)
 {
	 int i;
	 for(i=0; i<length; i++)
	 {
		 if (list[i]==c)
		 return i;
	 }
	 
     
       return -1; 
}

void print_focl(char focl[], int length)
{
	int i;
	for(i=0;i<length; i++)
		printf("%c",focl[i]);
}







// *******  The main decipher algorithm is provided below:
/**
 *  Translate char c from the given focl using the natural_focl
 * Input: c -- the character from focl to be translated; 
 *        focl, natural_focl -- Freq. Ordereed Character Lists of given length
 * Returns: the matching character from the natural_focl
 */
char translate(char c, char focl[], char natural_focl[], int length) {
   int i = find(c, focl, length);
   if (i >= 0)
      return natural_focl[i];
   else
      return c;
}

/**
 *  Attempt to decode the given file using the 2 frequency arrays
 * Input: filname -- the file to be decoded, which has given focl[]
 *        natural_focl -- a natural frequency ordering for plain text
 * Output: the decoded file, printed to stdout.
 */
void decode_file(char* filename, char focl[], char natural_focl[], int length) {
   FILE* f = openFileRead(filename);
   char c;
   while ((c = fgetc(f)) != EOF) {
      printf("%c", translate(c, focl, natural_focl, length));
   }
}


/*
 * Attempt to open the file for read access.
 * Peforms error check and exits if file is not accessible
 */
FILE* openFileRead(char* filename)
{
   FILE* inFile = fopen(filename, "r" );
   if( inFile == NULL) {
      printf( "Error opening input file %s, program terminating!\n", filename);
      exit(EXIT_FAILURE);
   }
   return inFile;
}

