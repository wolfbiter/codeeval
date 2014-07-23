#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    char *delim = ",";

    // split line at semicolon
    int size = atoi(strtok(line, ";"));
    char *elements = strtok(NULL, ";");

    // parse integers into array
    int arr[size];
    char *token = strtok(elements, delim);
    int i = 0;
    while (token != NULL) {
      arr[i++] = atoi(token);
      token = strtok(NULL, delim);
    }

    // initialize seen
    bool encountered[size];
    for (i = 0; i < size; i++) {
      encountered[i] = false;
    }

    // find duplicate
    int curr = -1;
    for (i = 0; i < size; i++) {
      curr = arr[i];
      if (encountered[curr]) {
        break;
      } else {
        encountered[curr] = true;
      }
    }

    // print duplicate
    printf("%d\n", curr);

    /**************************/
    /*** /END DO LINE ***/
    /**************************/

  }


  if (ferror(f)) {
    perror("I/O Error");
  }

  return 0;
}