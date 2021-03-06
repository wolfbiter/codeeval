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

    // split line at pipe
    char *letters = strtok(line, "|");
    char *hints = strtok(NULL, "|");
    //printf("%s\n", letters);
    //printf("%s\n", hints);

    // tokenize hints
    char *hintsTokens[LINE_SIZE];
    char *token = strtok(hints, delim);
    int length = 0;
    while (token != NULL) {
      hintsTokens[length] = token;
      length++;
      token = strtok(NULL, delim);
    }

    // decode writer
    char sentence[length];
    int i;
    for (i = 0; i < length; i++) {
      int hint = atoi(hintsTokens[i]);
      sentence[i] = letters[hint-1];
    }

    // print sentence
    printf("%s\n", sentence);

    /**************************/
    /*** /END DO LINE ***/
    /**************************/

  }


  if (ferror(f)) {
    perror("I/O Error");
  }

  return 0;
}