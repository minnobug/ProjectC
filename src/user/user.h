#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_CART 100
#define MAX_PRODUCTS 100
#define CART_ID_LENGTH 10

int validate_choice(int min, int max);
struct Order;
struct Product;
struct Cart;
void displayProduct(struct Product product);
void displayProductsFromFile(const char *filename); 
void initCart( struct Cart *cart);
void displayCart(struct Cart cart);
void addProductToCart(struct Cart *cart, struct Product product);
void removeProductFromCart(struct Cart *cart, int id);
void updateProductQuantity(struct Cart *cart, int id, int newQuantity);
char *generate_cart_id();
void readDataFromFile(struct Product *products, int *numProducts);
void saveCartToFile(struct Cart *cart);
void loadCartFromFile(struct Cart *cart);
void loadProductsFromFile(const char *filename, struct Product *products, int *numProducts);
void create_bill(struct Order *numbers, int n);
void cancel_bill_by_idOrder(int idOrder);
void update_bill_by_idOrder(struct Order *count, int n, int id);
void display_all_bill_information(int n);
void display_bill_by_idOrder(int idOrder);
struct Product listProduct[1001];

          
typedef struct Cart {
    char cart_id[CART_ID_LENGTH + 1];
    struct Product products[MAX_CART];
    int count;
} Cart;

struct Cart cart;
int numCarts = 0;

// Initialize cart
void initCart(Cart *cart) {
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

//Read data from file product.txt
void readDataFromFile(struct Product products[], int *numProducts) {
    FILE *file = fopen("./src/data/product.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    while (*numProducts < MAX_CART &&
           fscanf(file, "%d,%49[^,],%f,%d\n",
                  &products[*numProducts].id,
                  products[*numProducts].name,
                  &products[*numProducts].price,
                  &products[*numProducts].quantity) == 4) {
        (*numProducts)++;
    }

    if (*numProducts == MAX_CART) {
        printf("Warning: Maximum number of products reached. Some products might not have been loaded.\n");
    }

    fclose(file);
}


// Save cart data to file // them CARD ID vao day
void saveCartToFile(struct Cart *cart) {
    FILE *file = fopen("./src/data/cart.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    // Ghi cart ID vai file
    fprintf(file, "Cart ID: %s\n", cart->cart_id);

    for (int i = 0; i < cart->count; i++) {
        fprintf(file, "%d,%d\n", cart->products[i].id, cart->products[i].quantity);
    }

    fclose(file);
 }

// Load cart data from file
void loadCartFromFile(Cart *cart) {
    FILE *file = fopen("cart.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // read id from file
    fscanf(file, "%s", cart->cart_id);

    // read data product from file and save cart
	    while (fscanf(file, "%d %s %f %d", &cart->products[cart->count].id, cart->products[cart->count].name, &cart->products[cart->count].price, &cart->products[cart->count].quantity) == 4) {
        cart->count++;
     }
}
// display cart
void displayCart(struct Cart cart) {
  if (cart.count == 0) {
    printf("Cart is empty!\n");
    return;
  }

  printf("List of products in the shopping cart:\n");
  for (int i = 0; i < cart.count; i++) {
    displayProduct(cart.products[i]);
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
    // Save cart data to file after adding product
    saveCartToFile(cart);
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
        choice = validate_choice(0, 2);

        switch (choice) {
            case 1: {
                initCart(&cart);
                
                // Take product data from the file
                takeProductsFromFile(products, &numProducts);
    
                // Load cart data from file
                loadCartFromFile(&cart);

                int cartChoice;
                do {
                    printf("\nMenu - Shopping Cart Management:\n");
                    printf("1. Display all products in cart\n");
                    printf("2. Add new product to cart\n");
                    printf("3. Remove product from cart\n");
                    printf("4. Update product quantity in cart\n");
                    printf("5. Display all available products\n");
                    printf("0. Exit\n");
                    cartChoice = validate_choice(0, 5); // Use cartChoice here

                    switch (cartChoice) { // Use cartChoice here instead of choice
                        case 1:
                            displayCart(cart);
                            break;
                        case 2: {
                            // Add product to cart
                            struct Product newProduct;
                            printf("Enter the product ID: ");
                            scanf("%d", &newProduct.id);
                            

                            printf("Enter the quantity of the product: ");
                            scanf("%d", &newProduct.quantity);
                            

                            for (int i = 0; i < numProducts; i++) {
                              if(newProduct.id == products[i].id) {
                                if (newProduct.quantity > products[i].quantity) {
                                  printf("Error!!! Over quantity");
                                  break;
                                }
                                strcpy(newProduct.name, products[i].name);
                                newProduct.price = products[i].price;
                                addProductToCart(&cart, newProduct);
                                break;
                              }
                            }
                            break;
                        }
                        case 3: {
                            int productId;
                            printf("Enter the product ID to delete: ");
                            scanf("%d", &productId);
                            removeProductFromCart(&cart, productId);
                            break;
                        }
                        case 4: {
                            int productId, newQuantity;
                            printf("Enter the product ID to update quantity: ");
                            scanf("%d", &productId);
                            printf("Enter the new quantity: ");
                            scanf("%d", &newQuantity);
                            updateProductQuantity(&cart, productId, newQuantity);
                            break;
                        }
                        case 5:
                            // Display available products
                            displayAvailableProducts(products, numProducts);
                            break;
                        case 0:
                            printf("Successfully exited the shopping cart management program.\n");
                            break;
                        default:
                            printf("Invalid selection! Please try again.\n");
                    }
                      } while (cartChoice != 0); // Use cartChoice here instead of choice

                       // Generate and display the cart ID
                       char *cart_id = generate_cart_id();
                       printf("Cart ID: %s\n", cart_id);
                       free(cart_id); // Free memory allocated for the cart ID
                       break;
                      }

            case 2: {
                int orderChoice;
                int n = 1;
                int ID;
                struct Order order;
                do {
                  printf("\nMenu - Order Management:\n");
                  printf("\t1. Create order\n");
                  printf("\t2. Cancel order\n");
                  printf("\t3. Update order\n");
                  printf("\t4. Display information of order\n");
                  printf("\t0. Exit\n");
                  orderChoice = validate_choice(0, 4);

                  switch (orderChoice) {
                     case 1:
                        if (n < 100) {
                          create_bill(&order, n);
                          n++;
                        } else {
                          printf("Maximum number of orders reached.\n");
                        }
                     break;
                     case 2:
                         if (n > 0) {
                             printf("Enter file ID of Bill to cancel: ");
                             scanf("%d", &ID);
                             getchar();
                             cancel_bill_by_idOrder(ID);
                         } else {
                             printf("No orders to cancel.\n");
                         }
                        break;
                        case 3:
                            printf("Enter file ID of Bill to update: ");
                            scanf("%d", &ID);
                            getchar();
                            update_bill_by_idOrder(&order, n, ID);
                         break;
                         case 4:
                            display_all_bill_information(n);
                         break;
                        case 5:
                            printf("Enter the file ID of the bill to display: ");
                            scanf("%d", &ID);
                            getchar();
                            display_bill_by_idOrder(ID);
                        break;
            
                        default:
                        printf("Invalid choice.\n");
                        break;
                      }
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