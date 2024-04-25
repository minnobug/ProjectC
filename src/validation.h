#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int validate_choice(int min, int max) {
    int choice;
    while (1) {
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1 || choice < min || choice > max) {
            printf("Invalid choice. Please enter a number between %d and %d.\n", min, max);
            int c; 
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            // Check characters 
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {

                if (!isspace(c) && !isdigit(c)) {
                    printf("Invalid choice. Please enter a number between %d and %d.\n", min, max);
                    
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
            }
            if (c == '\n' || c == EOF) {
                return choice;
            }
        }
    }
}


int validate_positive_number() {
    int number;
    do {
        if (scanf("%d", &number) != 1 || number <= 0) { 
            printf("Error! Please enter a positive number: "); 
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            // Check characters 
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (!isspace(c) && !isdigit(c)) {
                    printf("Invalid choice. Please enter a positive number.\n");
                    // Clear input buffer
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
            }
            // If valid input and end of line or end of file reached, return the number
            if (c == '\n' || c == EOF) {
                return number;
            } else {
                // If characters other than newline or EOF were found, prompt for input again
                printf("Invalid choice. Please enter a positive number.\n");
            }
        }
    } while (1); // Continue looping until valid input is provided
}


