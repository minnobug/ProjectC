#ifndef ADMIN_H
#define ADMIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../product.h"


struct Product createProduct(int id, char *name, float price, int quantity);
void addProduct(struct Product product);
void writeProductsToFile(const char *filename, struct Product products[], int numProducts);
void removeProduct(int id);
void updateProduct(int id, char *newName, float newPrice, int newQuantity);
void displayProducts();
void sortProductsByID();
void loadProductsFromFile(const char *filename);
void reloadProductsData();
void displayProduct(struct Product product);
void displayProductsFromFile(const char *filename);
int compareProducts(const void *a, const void *b);
int validate_choice(int min, int max);
int validate_positive_number();


// ADMIN MENU
void adminMenu(int choice) {
    do {
        printf("MENU - Product Management: \n");
        printf("\t1. Add product \n");
        printf("\t2. Remove product \n");
        printf("\t3. Update product \n");
        printf("\t4. Display list of product \n");
        printf("\t0. Exit\n");
        choice = validate_choice(0, 4);


        switch (choice) {
            case 1: // add product
            {
                int id, quantity;
                float price;
                char name[100];
                int is_valid = 0; 
                while (!is_valid) {
                    printf("Enter product name: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    if (strlen(name) == 0) {
                         printf("Product name cannot be empty. Please try again.\n");
                    }
                    else {
                           int i, all_spaces = 1;
                           for (i = 0; i < strlen(name); i++) {
                               if (name[i] != ' ') {
                                   all_spaces = 0;
                                  break;
                                }
                           }

                          if (all_spaces) {
                               printf("Product name cannot consist of only spaces. Please try again.\n");
                           } 
                           else {
                               is_valid = 1; 
                           }
                    }
                }
                printf("Enter product price: ");
                price = validate_positive_number();
                printf("Enter product quantity: ");
                quantity = validate_positive_number();
                struct Product newProduct = createProduct(id, name, price, quantity);
                addProduct(newProduct);
                sortProductsByID();
                writeProductsToFile(FILE_PATH, products, numProducts);

                break;
            }


            case 2: // remove product
            {
                int id;
                printf("Enter ID of the product to remove: ");
                scanf("%d", &id);
                removeProduct(id);
                sortProductsByID();
                writeProductsToFile(FILE_PATH, products, numProducts);
                break;
            }

            case 3: // update product
           {
               int id, quantity;
               float price;
               char name[100];
               printf("Enter product ID to update: ");
               scanf("%d", &id);
               updateProduct(id, name, price, quantity);
               sortProductsByID();
               writeProductsToFile(FILE_PATH, products, numProducts);

               break;
           }
            case 4: // display list of product
            {
                reloadProductsData();
                displayProducts();

                break;
            }
            case 0:
                printf("Successfully exited the product management program.\n");
                reloadProductsData();
                break;
            default:
                printf("Invalid selection! Please try again.\n");
        }
    } while(choice != 0);
}

#endif 