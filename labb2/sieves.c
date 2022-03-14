#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// main 10

#define COLUMN 6 

void print_number(int);
void print_sieves(int);

int main(int argc, char *argv[]) {
	if (argc == 2) {
		print_sieves(atoi(argv[1]));
	} else { printf("Please state an integer number.\n"); }
	
	return 0;
}

int counter;
void print_number(int n) {
	if (counter%COLUMN == 0 && counter != 0) {
		printf("\n");
	}

	printf("%10d ", n);
	counter++;

}


void print_sieves(int n) {
	char list[n]; //Creates a list with n size. 

	//marking all numbers as possible primes
	//for (int i = 0; i < n; i++) { list[i] = 1; }

	//we are checking all numbers between 2 and sqrt(n)
	for (int i = 2; i < n; i++) {
		if (!list[i]) {                       // checks if the current number is marked as a prime
			for (int j = i; j < n; j += i) { //marks every number that is dividable with "i"
				list[j] = 1;
			}
		}
	}

	for (int i = 2; i < n; i++) {  //we print the rest of the numbers that's still marked as 1
		if (!(int)list[i]) { print_number(i); }
	}

	printf("\n");
}


