#include <stdio.h>
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
    char *delim = " ";

    // tokenize line
    char *last, *word;
    char *token = strtok(line, delim);
    while (token != NULL) {
      last = word;
      word = token;
      token = strtok(NULL, delim);
    }

    // print penultimate
    printf("%s\n", last);

    /**************************/
    /*** /END DO LINE ***/
    /**************************/

  }


  if (ferror(f)) {
    perror("I/O Error");
  }

  return 0;
}