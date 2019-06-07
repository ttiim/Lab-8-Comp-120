/*
 *  Comp120 - Lab 8:  Starter project -- Complete this code
 *    Sort Charcter Frequency analysis -- read a frequency analysis text file and sort the results.
 *
 *  Author: J. Fall
 *  Date: Feb. 2017
 */
 
#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>

// A simple data struct to record frequency data about one character
typedef struct frequency
{
   char ch;
   double freq;
} frequency;

// Function prototypes:
void construct_histogram(const int counts[], frequency histogram[], int length);
void sort_histogram(frequency histogram[], int length);
// LAB 7:
void init_array(int array[], int length);
int sum_array(const int array[], int length);
bool isPrintable(char c);
void compute_frequency(char* filename, int counts[], int length);
void write_histogram(char* filename, frequency histogram[], int length, char outputFormat);
char parse_command(int argc, char* argv[]);
FILE* openFileRead(char* filename);
FILE* openFileWrite(char* filename);

// Definition of printable character set 
#define FIRST_PRINTABLE ' '  // Space character code 32, see Etter 2016 text, pp. 418-420
#define LAST_PRINTABLE  '~'  // Tilde character code 126
#define NUM_PRINTABLE  (int) (LAST_PRINTABLE - FIRST_PRINTABLE + 1)

int main( int argc, char* argv[] )
{
   char outputFormat = parse_command(argc, argv);

   int counts[NUM_PRINTABLE];  // Array of counters -- one for each printible character
   frequency histogram[NUM_PRINTABLE];  // Array of frequencies -- one for each printible character
   
   compute_frequency(argv[1], counts, NUM_PRINTABLE);
   
   construct_histogram(counts, histogram, NUM_PRINTABLE);
   
   sort_histogram(histogram, NUM_PRINTABLE);
   
   write_histogram(argv[2], histogram, NUM_PRINTABLE, outputFormat);
   
   printf( "Program complete. Frequency histogram written to file %s \n", argv[2] );

   return 0                           ;
}

/**
 *   Convert an array of PRINTABLE character counts (zero-based, ASCII order)
 *   into an array of frequency structs:  (character, proportion) pairs
 *  Input:  counts[] -- an array of counts of given length
 *  Output: histogram[] -- an array of frequency structs
 */ 
void construct_histogram(const int counts[], frequency histogram[], int length)
{
  int total_count = sum_array(counts, length);
   
   int i;
   for (i=0; i<length; i++) {
      histogram[i].ch = (char) (i + (int) FIRST_PRINTABLE);
      if (counts[i] == 0)
         histogram[i].freq = 0.0;
      else
         histogram[i].freq = (double) counts[i] / (double) total_count;
   }   
}


/*
 * Sort the given frequency histogram in place
 * in frequency order
 */
void sort_histogram(frequency histogram[], int length)
{
  
  int k,j, m;
  frequency hold;
  
  for(k=0;k<length-1;k++)
  {
  
	  
	  m=k;
	  
  for(j=k+1;j<length;j++)
     
	  if ( histogram[j].freq > histogram[m].freq)
	  
		  m=j;
	  hold= histogram[m];
	 histogram[m]= histogram[k];
	 histogram[k]=hold;
  
  }
  
  return;
}

/***** LAB 7 Solution *****
/*
 * Initialize the array of integers of given length to all zeros
 */
void init_array(int array[], int length) 
{
   ;  // TODO: write function to assign 0 too every array element.
   // Solution:
   int i;
   for (i=0; i<length; i++) {
      array[i] = 0;
   }
}

/*
 * Return the sum of all items in the given array
 */
int sum_array(const int array[], int length)
{
   int sum = 0;
   int i;
   for (i=0; i<length; i++) {
      sum += array[i];
   }
   return sum;
}

/*
 * Return true iff the character is PRINTABLE
 */
bool isPrintable(char c)
{
   return FIRST_PRINTABLE <= c && c <= LAST_PRINTABLE;
}
 
/*
 * Compute the frequency (counts) for all PRINTABLE characters in the given file
 */
void compute_frequency(char* filename, int counts[], int length)
{
   FILE* inputFile = openFileRead(filename);
   
   init_array(counts, length);
   
   char c = getc(inputFile);
   while (c != EOF) {
      if (isPrintable(c)) {
         int i = (int) (c - FIRST_PRINTABLE);
         if (0 <= i && i < length)
            counts[i]++;
      }
      c = getc(inputFile);   
   }
}


/*
 * Write the frequency histogram out to the given file
 */
void write_histogram(char* filename, frequency histogram[], int length, char outputFormat)
{
   FILE* outputFile = openFileWrite(filename);
   int i;
   if (outputFormat == 'c') {  // character list output, for easy reading by another program
      for (i=0; i<length; i++) {
         fprintf(outputFile, "%c", histogram[i].ch);
      }      
      fprintf(outputFile, "\n");
   }
   else { // human readable output
      fprintf(outputFile, "Sorted Frequency Analysis. \n");
      fprintf(outputFile, "Char | Frequency \n");
      fprintf(outputFile, "____ | _________ \n");
      for (i=0; i<length; i++) {
         if (histogram[i].freq > 0) {
            fprintf(outputFile, "%3c  | %9.3f%% \n", histogram[i].ch, histogram[i].freq*100);
         }
         else
            fprintf(outputFile, "%3c  | %9d%% \n", histogram[i].ch, 0);
      }
   }
}

/**
 * Validate the input arguments and return the optional output format flag
 */
char parse_command(int argc, char* argv[])
{
   char outputFormat = 'h';  // default to human readable output
   if (argc < 3 || (argv[1][0] == '-' && argc < 4)) {
      printf("Usage: freq [-h/c] inputFile outputFile\n");
      exit(-1);
   }
   else if (argv[1][0] == '-') {  // process optional flag.
      outputFormat = argv[1][1];
      argv[1] = argv[2];
      argv[2] = argv[3];
   }
   printf("Output Format: %c \n", outputFormat);
   return outputFormat;
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

/*
 * Attempt to open the file for write access.
 * Peforms error check and exits if file is not accessible
 */
FILE* openFileWrite(char* filename)
{
   FILE* outFile = fopen(filename, "w" );
   if( outFile == NULL) {
      printf( "Error opening output file %s, program terminating!\n", filename);
      exit(EXIT_FAILURE);
   }
   return outFile;
}
