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

    // split line at comma
    char *a = strtok(line, ",");
    char *b = strtok(NULL, ",");
    //printf("%s\n", a);
    //printf("%s\n", b);

    // check if b is at end of a
    int len_a = strlen(a);
    int len_b = strlen(b);
    //printf("%d, %d\n", len_a, len_b);
    if (*(a + len_a - len_b) == *b) {
      printf("1\n");
    } else {
      printf("0\n");
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