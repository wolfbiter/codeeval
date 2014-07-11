#include <stdio.h>
#include <string.h>

#define LINE_SIZE 1024

struct stack {
  char symbols[LINE_SIZE];
  int curr;
};

typdef struct stack stack_struct;

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
    stack_struct symbols;
    symbols = make_stack();

    int i; bool b;
    for (i = 0; i < strlen(line); i++) {
      char symbol = line[i];
      switch (symbol) {
        // if open, push onto stack
        case "(": case "[": case "{":
          symbols.push(symbol); break;
        // if close, make sure it's valid
        case ")": case "]": case "}":
          b = (b and match(symbols.pop(), symbol));
          break;

        default:
          printf("ERROR, unknown symbol.\n");
          return 1;
      }

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

bool match(char a, char b) {
  if (*a == "(" and *b == ")") {
    return true;
  }
  if (*a == "[" and *b == "]") {
    return true;
  }
  if (*a == "{" and *b == "}") {
    return true;
  }
}

stack_struct make_stack() {
  stack_struct result;
  result.curr = -1;
  return result;
}

void push(stack s, char c) {
  int curr = s->curr;
  s->symbols[curr] = c;
  s.curr++;
}

char pop(stack s) {
  int curr = s->curr;
  if (curr == -1) {
    return NULL;
  } else {
    char result = s->symbols[curr--];
    s.curr--;
  }
}
