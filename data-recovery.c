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

    // split line at semicolon
    char *words = strtok(line, ";");
    char *hints = strtok(NULL, ";");
    //printf("%s\n", words);
    //printf("%s\n", hints);

    // tokenize words
    char *wordsTokens[LINE_SIZE];
    char *token = strtok(words, delim);
    int length = 0;
    while (token != NULL) {
      wordsTokens[length] = token;
      length++;
      token = strtok(NULL, delim);
    }

    // tokenize hints
    char *hintsTokens[length-1];
    token = strtok(hints, delim);
    int i = 0;
    while (token != NULL) {
      hintsTokens[i++] = token;
      token = strtok(NULL, delim);
    }

    // reconstruct sentence
    char *sentence[length];
    for (i = 0; i < length - 1; i++) {
      int hint = atoi(hintsTokens[i]);
      char *word = wordsTokens[i];
      sentence[hint-1] = word;
    }
    // search for null and replace with last word
    for (i = 0; i < length; i++) {
      if (sentence[i] == NULL) {
        sentence[i] = wordsTokens[length-1];
        break;
      }
    }


    // print sentence
    for (i = 0; i < length; i++) {
      printf("%s ", sentence[i]);
      //printf("%i ", atoi(hintsTokens[i]));
    }
    //printf("%s\n", sentence[i]);
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