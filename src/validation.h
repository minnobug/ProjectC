#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate_choice(int min, int max) {
    int choice;
    while (1) {
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1 || choice < min || choice > max) {
            printf("Invalid choice. Please enter a number between %d and %d.\n", min, max);
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            return choice;
        }
    }
}

int validate_positive_number() {
    int number;
    do {
        scanf("%d", &number);
        if (number <= 0) {
            printf("Please enter a positive number: ");
        }
    } while (number <= 0);
    return number;
}
