#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char *delim = " ";

    // parse numbers from line
    int a = atoi(strtok(line, delim));
    int b = atoi(strtok(NULL, delim));
    int n = atoi(strtok(NULL, delim));

    // do count
    for (int i = 1; i <= n; i++) {
      if (i % a == 0 && i % b == 0) {
        printf("FB");
      }
      else if (i % a == 0) {
        printf("F");
      }
      else if (i % b == 0) {
        printf("B");
      }
      else {
        printf("%d", i);
      }
      printf(" ");
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