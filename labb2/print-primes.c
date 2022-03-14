/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int counter;
void print_number(int n) {
  //when the counter gets to 6 we start on the next row and counter !=0 makes sure that we don't skip the first row
  if (counter%COLUMNS == 0 && counter != 0) {
	  printf("\n");
  }
  //%10d prints the numbers with 10 spaces between them to match the picture
	printf("%10d ", n);
	counter++;
}

//we check all conditions for a number not being a prime, if none is fulfilled the number is a prime.
int is_prime(int n){
  for(int i = 2; i <= n / 2; i++) {
    if(n % i == 0) {
      return 0;
    }
  }
  if(n <= 1) {
    return 0;
  }
  return 1;
}


void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  for(int i = 2; i <= n; i++) {
    if(is_prime(i)) {
      print_number(i);
    }
  }

  /*printf("%10d ", 2);
  printf("%10d ", 3);
  printf("%10d ", 5);
  printf("%10d ", 7);
  printf("%10d ", 11);
  printf("%10d ", 13);
  printf("\n");
  printf("%10d ", 17);
  printf("%10d ", 19);

  printf("\n");*/
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
