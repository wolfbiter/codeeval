#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024
int main(int argc, char **argv) {
  FILE *f;
  char line[LINE_SIZE], *p;

  // open file passed as argument
  if (argc < 2 || !(f = fopen(argv[1], "r"))) {
    fprintf(stderr, "Unable to open file argument\n");
    return 1;
  }

  // read lines from file
  while (fgets(line, LINE_SIZE, f)) {
    // possibly remove the trailing '\n'
    if ((p = strchr(line, '\n'))) { *p = '\0'; }

    // skip empty lines
    if (line[0] == '\0') { continue; }

    /*********************/
    /*** DO LINE ***/
    /*********************/

    // get numbers
    double numbers[LINE_SIZE];
    char *token = strtok(line, " ");
    int length = 0;
    while (token != NULL) {
      numbers[length++] = atof(token);
      token = strtok(NULL, " ");
    }

    double min(double a, double b) {
      if (a < b) { return a; }
      else { return b; }
    }

    // selection sort
    int i, j;
    for (i = 0; i < length; i++) {
      double curr_min[] = {999999.0, -1.0};
      for (j = i; j < length; j++) {
        double num = numbers[j];
        if (num < curr_min[0]) {
          curr_min[0] = num;
          curr_min[1] = j;
        }
      }
      // swap
      numbers[(int) curr_min[1]] = numbers[i];
      numbers[i] = curr_min[0];
    }

    // print sorted numbers
    for (i = 0; i < length; i++) {
      printf("%g ", numbers[i]);
    }
    printf("\n");
    
    /**************************/
    /*** /END DO LINE ***/
    /**************************/

  }


  if (ferror(f)) {
    perror("I/O Error");
  }

  return 0;
}