#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int frequency_counting(int * array, int n){
  int max_count = 0;
  for(int i=0;i<n;i++){
    if(array[i]>array[max_count]){
      max_count = i;
    }
  }
  return max_count;

}
int encrypt_key(FILE * f){
  int alphabet[26] = {0};
  int c;
  while((c = fgetc(f))!= EOF){
    if(isalpha(c)){
      c = tolower(c);
      int i = c - 'a';
      alphabet[i]++;
    }
  }
  int max = frequency_counting(alphabet,26);
  int key = (max+22)%26;
  return key;
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = encrypt_key(f);
  printf("%d\n",key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}