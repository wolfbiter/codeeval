#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_SIZE 1024

struct stack {
  char symbols[LINE_SIZE];
  int curr;
};

typedef struct stack stack_struct;

bool open(char a) {
  if (a == '(' || a == '[' || a == '{') {
    return true;
  }
  else {
    return false;
  }
}

bool close(char a) {
  if (a == ')' || a == ']' || a == '}') {
    return true;
  }
  else {
    return false;
  }
}

bool match(char a, char b) {
  //printf("CHECKING MATCH %c %c\n", a, b);
  if (a == '(' && b == ')') {
    return true;
  }
  if (a == '[' && b == ']') {
    return true;
  }
  if (a == '{' && b == '}') {
    return true;
  }
  return false;
}

stack_struct* make_stack() {
  stack_struct* result = malloc(sizeof(*result));
  result->curr = -1;
  return result;
}

void push(stack_struct* s, char c) {
  int curr = s->curr;
  //printf("PUSHING %d %c\n", curr, c);
  if (curr == -1) {
    curr = 0;
  }
  s->symbols[curr] = c;
  s->curr = ++curr;
}

char pop(stack_struct* s) {
  if (s->curr == -1) {
    return 'X';
  } else {
    char result = s->symbols[--(s->curr)];
    //printf("POPPING %d %c\n", s->curr, result);
    return result;
  }
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

    // keep stack of encountered symbols
    stack_struct* symbols = make_stack();

    int i; bool b = true;
    for (i = 0; i < strlen(line); i++) {
      char symbol = line[i];
      //printf("SYMBOL %c\n", symbol);
      if (open(symbol)) {
        // if open, push onto stack
        push(symbols, symbol);
      }
      else if (close(symbol)) {
        // if close, make sure it's valid
        b = (b && match(pop(symbols), symbol));
        // if invalid, exit loop
        if (!b) {
          break;
        }
      }
      else {
        printf("ERROR, unknown symbol.\n");
        return 1;
      }
    }

    if (b && (symbols->curr == 0)) {
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

