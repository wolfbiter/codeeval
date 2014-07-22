#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_SIZE 1024
#define MAX_DIGITS 4

bool isPalindrome(int i) {
  char num[MAX_DIGITS + 1];
  sprintf(num, "%d", i);
  int len = strlen(num);
  for (int i = 0; i < len; i++) {
    if (num[i] != num[len - i - 1]) {
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv) {

  int n = 1000;
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

  // print largest prime palindrome
  for (int i = n-1; i >= 0; i--) {
    if (primes[i] && isPalindrome(i)) {
      printf("%d\n", i);
      return 0;
    }
  }

  return 0;
}