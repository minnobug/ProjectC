#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "./src/product.h"

#define MAX_CART 100
#define MAX_PRODUCTS 100
#define CART_ID_LENGTH 10

int validate_choice(int min, int max);
struct Product;
struct Cart;
void displayProduct(struct Product product);
void displayProductsFromFile(const char *filename); 
void initCart( struct Cart *cart);
void displayCart(struct Cart *cart);
void addProductToCart(struct Cart *cart, struct Product product);
void removeProductFromCart(struct Cart *cart, int id);
void updateProductQuantity(struct Cart *cart, int id, int newQuantity);


// Cart
struct Cart {
  struct Product products[MAX_CART];
  int count;
};

struct Cart carts[MAX_PRODUCTS];
int numCarts = 0;

// Initialize cart
void initCart(struct Cart *cart) {
  cart->count = 0;
}

// Generate cart ID
char *generate_cart_id() {
    // Allocate memory for the cart ID string
    char *cart_id = (char *)malloc((CART_ID_LENGTH + 1) * sizeof(char));
    
    // Set seed for rand function based on current time
    srand(time(NULL));
    
    // Possible characters in the cart ID (letters and numbers)
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    // Random generate characters for the cart ID
    for (int i = 0; i < CART_ID_LENGTH; i++) {
        int index = rand() % (sizeof(charset) - 1);
        cart_id[i] = charset[index];
    }
    
    // End the string with a NULL character
    cart_id[CART_ID_LENGTH] = '\0';
    
    return cart_id;
}

// display cart
void displayCart(struct Cart *cart) {
  if (cart->count == 0) {
    printf("Cart is empty!\n");
    return;
  }

  printf("List of products in the shopping cart:\n");
  for (int i = 0; i < cart->count; i++) {
    displayProduct(cart->products[i]);
  }
}

// Add product to the cart
void addProductToCart(struct Cart *cart, struct Product product) {
  if (cart->count >= MAX_CART) {
    printf("Shopping cart is full! Unable to add product.\n");
    return;
  }

  cart->products[cart->count] = product;
  cart->count++;
  printf("Product added to cart successfully!\n");
}

// Remove product from cart
void removeProductFromCart(struct Cart *cart, int id) {
  int foundIndex = -1;

  for (int i = 0; i < cart->count; i++) {
    if (cart->products[i].id == id) {
      foundIndex = i;
      break;
    }
  }

  if (foundIndex == -1) {
    printf("The product does not exist in the shopping cart!\n");
    return;
  }

  // Move the following products to the previous position
  for (int i = foundIndex; i < cart->count - 1; i++) {
    cart->products[i] = cart->products[i + 1];
  }

  cart->count--;
  printf("Product successfully removed from cart!\n");
}

// Updates the number of products in the shopping cart
void updateProductQuantity(struct Cart *cart, int id, int newQuantity) {
  int foundIndex = -1;

  for (int i = 0; i < cart->count; i++) {
    if (cart->products[i].id == id) {
      foundIndex = i;
      break;
    }
  }

  if (foundIndex == -1) {
    printf("The product does not exist in the shopping cart!\n");
    return;
  }

  if (newQuantity <= 0) {
    printf("Product quantity must be greater than 0!\n");
    return;
  }

  cart->products[foundIndex].quantity = newQuantity;
  printf("Product quantity updated successfully!\n");
}

void userMenu() {
    int choice;
    do {
        printf("MENU: \n");
        printf("\t1. Shopping Cart Management\n");
        printf("\t2. Order Management\n");
        printf("\t0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        choice = validate_choice(0, 2);

        switch (choice) {
            case 1: {
                int cartChoice;
                do {
                    printf("\nMenu - Shopping Cart Management:\n");
                    printf("\t1. Displays all products available in the shop\n");
                    printf("\t2. Displays all products in cart\n");
                    printf("\t3. Add new product to cart\n");
                    printf("\t4. Remove product from cart\n");
                    printf("\t5. Update the number of products in the cart\n");
                    printf("\t0. Exit\n");
                    printf("Your choice: ");
                    scanf("%d", &cartChoice);
                    choice = validate_choice(0, 5);
                        switch (choice) {
                          case 1:
                              displayCart(&carts[0]); 
                              break;
                          case 2: {
                              // Enter new product information
                              struct Product newProduct;
                              printf("Enter the product ID: ");
                              scanf("%d", &newProduct.id);
                              printf("Enter the product quantity: ");
                              scanf("%d", &newProduct.quantity);

                              // Add product to the cart
                              addProductToCart(&carts[0], newProduct); 
                              break;
                          }
                          case 3: {
                              // Enter the product ID to delete
                              int productId;
                              printf("Enter the product ID to delete: ");
                              scanf("%d", &productId);

                              // remove product from cart
                              removeProductFromCart(&carts[0], productId); 
                              break;
                          }
                          case 4: {
                            // Enter the product ID whose quantity needs to be updated
                            int productId, newQuantity;
                            printf("Enter the product ID whose quantity needs to be updated: ");
                            scanf("%d", &productId);
                            printf("Enter the new quantity: ");
                            scanf("%d", &newQuantity);

                            // Update the number of products in the cart
                            updateProductQuantity(&carts[0], productId, newQuantity); 
                            break;
                          }
                          case 5:{
                          displayProductsFromFile("product.txt");
                          break;
                          }
                          case 0:
                          printf("Successfully exited the shopping cart management program.\n");
                          break;
                          default:
                          printf("Invalid selection! Please try again.\n");
                          }  
                       } while (cartChoice != 0);
                       break;
                      }

            case 2: {
                int orderChoice;
                do {
                  printf("\nMenu - Order Management:\n");
                  printf("\t1. Create order\n");
                  printf("\t2. Cancel order\n");
                  printf("\t3. Update order\n");
                  printf("\t4. Display information of order\n");
                  printf("\t0. Exit\n");
                  printf("Your choice: ");
                  scanf("%d", &orderChoice);
                  choice = validate_choice(0, 4);
                } while (orderChoice != 0);
                break;
              }

            case 0:{
              printf("Successfully exited.\n");
              break;
            }

            default:
                printf("Invalid selection! Please try again.\n");
        }
    } while (choice != 0);
}

#endif 