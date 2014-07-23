#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    // split line at comma
    int n = atoi(strtok(line, ","));
    int m = atoi(strtok(NULL, ","));

    int next = m-1;
    int killed = 0;
    bool executed[n];
    for (int i = 0; i < n; i++) {
      executed[i] = false;
    }

    while (true) {
      // do execution
      printf("%d ", next);
      executed[next] = true;
      if (++killed >= n) {
        break;
      }
      // advance pointer
      for (int i = 0; i < m; i++) {
        next = (next + 1) % n;
        if (executed[next]) {
          i--;
        }
      }
      //printf("NEXT %d\n", next);
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