/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* List.c 
* Implementation for the Lex program 
*********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_LEN 1024

int main(int argc, char * argv[]){
  FILE *in, *out;
  int line_count;
  char line[MAX_LEN];
  
  // ARGUMENT PARSER ------------------------------------------------
  // NOTE: The command line procedures was taken from the FileIO.C file
  // Given to us by Prof. Tantalo

  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  in = fopen(argv[1], "r");
  if(in == NULL){
    printf("ERROR: Unable to open file: %s for reading\n",argv[1]);
    return EXIT_FAILURE;
  }

  out = fopen(argv[2], "w");
  if(out == NULL){
    printf("ERROR: Unable to open file: %s for writing\n",argv[2]);
    return EXIT_FAILURE;
  }
  
  // LINE COUNTER --------------------------------------------------
  line_count = 0;
  while( fgets(line, MAX_LEN, in) != NULL){
    line_count++; //count each line
  }
  
  // INPUT ARRAY ---------------------------------------------------
  fseek(in, 0, SEEK_SET); //resets file pointer

  char **file_lines = malloc(line_count * sizeof(char *)); //creates an array of char arrays.
                                                           //these char arrays are called a string
  if (file_lines == NULL){ //throw an error if we cannot create a heap-allocated array
    printf("ERROR: Unable to create an array for the input file\n");
    return EXIT_FAILURE;
  }

  for(int i = 0; i < line_count; ++i){ 
    char buffer[MAX_LEN];
    char* line;

    if(fgets(buffer, MAX_LEN, in) == NULL){ //we buffer the input into *buffer
      printf("ERROR: null at fgets()\n");
      return EXIT_FAILURE;
    }

    if((line = strtok(buffer, "\n")) == NULL){ //strtok returns NULL if a line is empty
      line = "";
    }

    file_lines[i] = malloc(strlen(line) + 1); //allocate memory for the string & make sure to ad extra memory for the string
    strcpy(file_lines[i], line); //send the buffered and formated string to an index in the array
  }
  

  // List Sorting ---------------------------------------------------

  List final_list = newList();
  prepend(final_list, 0);

  //list is being sorted by using inspiration from insertion sort
  for(int i = 1; i < line_count; ++i){
    int prev_list_len = length(final_list);
    for(moveFront(final_list); index(final_list) >= 0 && prev_list_len == length(final_list); moveNext(final_list)){
      if (strcmp(file_lines[i], file_lines[get(final_list)]) < 0){ // if the current input list element is lexographically smaller than the current 
                                                                   // element from the List, then it goes before the current element
        insertBefore(final_list, i);
      }
    }

    int updated_list_len = length(final_list);

    /*check if the current index is bigger than the last element of the list.
    * each element from the input list MUST be added to the list therefore,
    * if the current input element was not added from the procedure above,
    * this means that the current input element MUST be bigger than the last
    element of the list. */
    if(prev_list_len == updated_list_len && strcmp(file_lines[i], file_lines[back(final_list)]) > 0){ 
      append(final_list, i);
    }
  }

  // OUTPUTTING RESULTS --------------------------------------------

  //results get outputtued to the out pointer
  for(moveFront(final_list); index(final_list) >=0; moveNext(final_list)){
    fprintf(out, "%s\n", file_lines[get(final_list)]);
  }


  // CLOSING PROCEDURES --------------------------------------------

  for(int i = 0; i < line_count; i++){
    free(file_lines[i]);
    file_lines[i] = NULL;
  }

  free(file_lines);
  file_lines = NULL;

  freeList(&final_list);

  fclose(in);
  fclose(out);

  return EXIT_SUCCESS;
}