#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_SIZE 1024

bool isRotation(char *word, char *rot, int i) {
  //printf("rotation, %s, %s, %d\n", word, rot, i);
  bool result = false;
  int length = strlen(rot) - i;
  // check first letter
  if (word[0] == rot[i]) {
    // check front of word
    //printf("front, %.*s, %.*s\n", length, word,
    //  length, rot + i);
    if (strncmp(word, rot + i, length) == 0) {
      // check back of word
      //printf("back, %.*s, %.*s\n", i, word + length, i, rot);
      if (strncmp(word + length, rot, i) == 0) {
        result = true;
      }
    }
  }
  return result;
}

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

    // parse words from line
    char *delim = ",";
    char *word = strtok(line, delim);
    char *rot = strtok(NULL, delim);

    // find start of rotation
    bool isRot = false;
    for (int i = 0; i <= strlen(rot); i++) {
      if (isRotation(word, rot, i)) {
        isRot = true;
        break;
      }
    }
    if (isRot) {
      printf("True\n");
    } else {
      printf("False\n");
    }
    /**************************/
    /*** /END DO LINE ***/
    /**************************/

  }


  if (ferror(f)) {
    perror("I/O Error");
  }

  return 0;
}