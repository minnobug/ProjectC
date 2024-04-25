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
        scanf("%d", &number);
        if (number <= 0) {
            printf("Error! Please enter a positive number: ");
        } else {
            // Check characters 
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (!isspace(c) && !isdigit(c)) {
                    printf("Error! Please enter a positive number.\n");
                   
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
            }
        }
    } while (number <= 0);
    return number;
}

