#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./src/admin/admin.h"
#include "./src/user/user.h"
#include "./src/validation.h"
#include "./src/order.h"

void mainMenu(int choice) {
    char usernameUser[50];
    char passwordUser[50];
    char usernameAdmin[50];
    char passwordAdmin[50];

    do {
        printf("===MENU===\n");
        printf("\t1. User\n");
        printf("\t2. Admin\n");
        printf("\t0. Exit\n");
        choice = validate_choice(0, 2);

        if (choice == 1) { // USER LOGIN
            printf("Enter username: ");
            scanf("%s", usernameUser);
            printf("Enter password : ");
            scanf("%s", passwordUser);

            FILE *file_pointer;
            char line[100]; // Used to store each line in the file

            file_pointer = fopen("./src/data/account_user.txt", "r");
            if (file_pointer == NULL) {
                printf("Cannot open file.\n");
                return;
            }

            while (fgets(line, sizeof(line), file_pointer)) {
                char stored_username[50];
                char stored_password[50];
                char stored_userid[50];


               if (sscanf(line, "%49[^,],%49[^,],%49s", stored_userid, stored_username, stored_password) != 3) {
                  printf("Invalid file format.\n");
                  break;
                }



                stored_username[strcspn(stored_username, "\n")] = '\0';
                stored_password[strcspn(stored_password, "\n")] = '\0';

                if (strcmp(usernameUser, stored_username) == 0 && strcmp(passwordUser, stored_password) == 0) {
                    printf("Login successful.\n");
                    userMenu();
                    fclose(file_pointer);
                    return;
                }
            }

            printf("Incorrect username or password.\n");
            fclose(file_pointer);
            
        } else if (choice == 2) { // ADMIN LOGIN
            printf("Enter username: ");
            scanf("%s", usernameAdmin);
            printf("Enter password: ");
            scanf("%s", passwordAdmin);

            FILE *file_pointer;
            char line[100]; // Used to store each line in the file

            file_pointer = fopen("./src/data/account_admin.txt", "r");
            if (file_pointer == NULL) {
                printf("Cannot open file.\n");
                return;
            }

            while (fgets(line, sizeof(line), file_pointer)) {
                char stored_username[50];
                char stored_password[50];

                if (sscanf(line, "%49[^,], %49s", stored_username, stored_password) != 2) {
                    printf("Invalid file format.\n");
                    break;
                }

                stored_username[strcspn(stored_username, "\n")] = '\0';
                stored_password[strcspn(stored_password, "\n")] = '\0';

                if (strcmp(usernameAdmin, stored_username) == 0 && strcmp(passwordAdmin, stored_password) == 0) {
                    printf("Login successfully.\n");
                      adminMenu(choice);
                    fclose(file_pointer);
                    return;
                }
            }

            printf("Incorrect username or password.\n");
            fclose(file_pointer);
        } 
    } while (choice != 0);
 
    
}



int main() {
    int choice;
    do {
        mainMenu(choice);
    } while (choice != 0);
    return 0;
}
