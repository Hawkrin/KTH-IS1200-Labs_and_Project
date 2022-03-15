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
	int list[n]; //Creates a list with n size. 

	for (int i = 0; i < n; i++) { list[i] = 1; }

	for (int i = 2; i <= sqrt(n); i++) {
		if (list[i]) {                       // If the number has not been marked
			for (int j = i * i; j < n; j += i) {
				list[j] = 0;
			}
		}
	}

	for (int i = 2; i < n; i++) { 
		if (list[i]) { print_number(i); }
	}

	printf("\n");
}


