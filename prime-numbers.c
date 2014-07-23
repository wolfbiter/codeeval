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
    int n = atoi(line);
    bool primes[n];
    for (int i = 0; i < n; i++) {
      primes[i] = true;
    }
    int curr = 2;

    // compute sieve
    while (curr < n) {

      // if curr is in primes, mark off multiples
      if (primes[curr]) {
        int k = 2;
        while (curr * k < n) {
          primes[curr*(k++)] = false;
        }
      }

      curr++;
    }

    // print primes
    printf("2");
    for (int i = 3; i < n; i++) {
      if (primes[i]) {
        printf(",%d", i);
      }
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