
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define FILE_PATH "./src/data/product.txt"

// PRODUCT
typedef struct Product {
    int id;
    char name[100];
    float price;
    int quantity;
} Product;

Product products[MAX_PRODUCTS];
int numProducts = 0;

// Create a new PRODUCT
Product createProduct(int id, char *name, float price, int quantity) {
    Product product;
    product.id = id;
    strcpy(product.name, name);
    product.price = price;
    product.quantity = quantity;
    return product;
}

// Add PRODUCT 
void addProduct(Product product) {
    if (numProducts < MAX_PRODUCTS) {
        
        for (int i = numProducts; i > 0; i--) {
            products[i] = products[i - 1];
        }
       
        products[0] = product;
        numProducts++;
        printf("Product added successfully.\n");
    } else {
        printf("Cannot add more products. Product limit reached.\n");
    }
}

// Write products data to file 
void writeProductsToFile(const char *filename, Product products[], int numProducts) {
    FILE *file_pointer;

    file_pointer = fopen(filename, "w");

    if (file_pointer == NULL) {
        printf("Error opening file.\n");
        return;
    }

  
    for (int i = numProducts - 1; i >= 0; i--) {
        fprintf(file_pointer, "%d,%s,%.0f,%d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }

    fclose(file_pointer);

    printf("The data has been saved successfully.\n");
}

// Remove PRODUCT 
void removeProduct(int id) {
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == id) {
            for (int j = i; j < numProducts - 1; j++) {
                products[j] = products[j + 1];
            }
            numProducts--;
            printf("Product removed successfully.\n");
            return;
        }
    }
    printf("Product with ID %d not found.\n", id);
}

// Update PRODUCT
void updateProduct(int id, char *newName, float newPrice, int newQuantity) {
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == id) {
            strcpy(products[i].name, newName);
            products[i].price = newPrice;
            products[i].quantity = newQuantity;
            printf("Product updated successfully.\n");
            return;
        }
    }
    printf("Product with ID %d not found.\n", id);
}

// Display list of products 
void displayProducts() {
    if (numProducts == 0) {
        printf("No products available.\n");
        return;
    }

    printf("List of Products:\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Quantity");
    for (int i = numProducts - 1; i >= 0; i--) {
        printf("%-5d %-20s %-10.0f %-10d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

// Compare for sorting products by ID in descending order
int compareProducts(const void *a, const void *b) {
    const Product *productA = (const Product *)a;
    const Product *productB = (const Product *)b;
    return productB->id - productA->id; // Compare in descending order
}

// Sort products by ID in descending order
void sortProductsByID() {
    qsort(products, numProducts, sizeof(Product), compareProducts);
}

// Load products data from file 
void loadProductsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Loop until either the end of file is reached or maximum products are loaded
    while (numProducts < MAX_PRODUCTS && fscanf(file, "%d,%99[^,],%f,%d\n", &products[numProducts].id, products[numProducts].name, &products[numProducts].price, &products[numProducts].quantity) == 4) {
        numProducts++;
    }

    fclose(file);
    
    // Sort products by ID in descending order after loading
    sortProductsByID();
}

// Reload products data from file
void reloadProductsData() {
    numProducts = 0; // Reset the number of products
    loadProductsFromFile(FILE_PATH); // Load products from file 
}


// ADMIN MENU
void adminMenu() {
    int choice;
    do {
        printf("MENU - Product Management: \n");
        printf("\t1. Add product \n");
        printf("\t2. Remove product \n");
        printf("\t3. Update product \n");
        printf("\t4. Display list of product \n");
        printf("\t0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // add product
            {
                int id, quantity;
                float price;
                char name[100];

                printf("Enter product ID: ");
                scanf("%d", &id);

                printf("Enter product name: ");
                scanf("%s", name);

                printf("Enter product price: ");
                scanf("%f", &price);

                printf("Enter product quantity: ");
                scanf("%d", &quantity);

                Product newProduct = createProduct(id, name, price, quantity);
                addProduct(newProduct);

                sortProductsByID();

                // Save products to file
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

                // Save products to file after removal
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

                printf("Enter new product name: ");
                scanf("%s", name);

                printf("Enter new product price: ");
                scanf("%f", &price);

                printf("Enter new product quantity: ");
                scanf("%d", &quantity);

                updateProduct(id, name, price, quantity);

                sortProductsByID();

                // Save products to file after update
                writeProductsToFile(FILE_PATH, products, numProducts);

                break;
            }
            case 4: // display list of product
            {
                displayProducts();

                break;
            }
            case 0:
                printf("Successfully exited the product management program.\n");
                
                // Reload products data from file before exiting
                reloadProductsData();
                break;
            default:
                printf("Invalid selection! Please try again.\n");
        }
    } while(choice != 0);
}
