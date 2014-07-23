#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 1024

int compare_function(const void *a, const void *b) {
  const char *stra = *(const char **) a;
  const char *strb = *(const char **) b;
  //printf("compare %s %s\n", stra, strb);
  return strlen(stra) - strlen(strb);
}

int main(int argc, char **argv) {
  FILE *f;
  char line[LINE_SIZE], *p;

  // open file passed as argument
  if (argc < 2 || !(f = fopen(argv[1], "r"))) {
    fprintf(stderr, "Unable to open file argument\n");
    return 1;
  }

  // parse first line specially
  fgets(line, LINE_SIZE, f);
  int n = atoi(line);
  char *longest[n];
  for (int i = 0; i < n; i++) {
    longest[i] = malloc(LINE_SIZE * sizeof(char));
  }

  // read rest of lines from file
  while (fgets(line, LINE_SIZE, f)) {
    // possibly remove the trailing '\n'
    if ((p = strchr(line, '\n'))) { *p = '\0'; }

    // skip empty lines
    if (line[0] == '\0') { continue; }

    /*********************/
    /*** DO LINE ***/
    /*********************/

    // if line is longer than longest, add to longest
    int len = strlen(line);
    //printf("%s %d %d\n", line, strlen(line), strlen(longest[0]));
    if (len > strlen(longest[0])) {
      strncpy(longest[0], line, LINE_SIZE);
    }

    // re-sort longest
    qsort(longest, n, sizeof(*longest), compare_function);

    /**************************/
    /*** /END DO LINE ***/
    /**************************/

  }

  // print longest n lines in descending order
  for (int i = n-1; i >= 0; i--) {
    printf("%s\n", longest[i]);
  }

  if (ferror(f)) {
    perror("I/O Error");
  }

  return 0;
}