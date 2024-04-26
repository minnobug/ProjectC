#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define FILE_PATH "./src/data/product.txt"

// PRODUCT
struct Product {
    int id;
    char name[50];
    char manufacturer[50];
    float price;
    int quantity;
    int cartID;
};

struct Product products[MAX_PRODUCTS];
int numProducts = 0;

// Function prototypes
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
void displayAvailableProducts(struct Product products[], int numProducts);
void takeProductsFromFile(struct Product products[], int *numProducts);
int compareProducts(const void *a, const void *b);
int getLastProductIdFromFile(const char *filename);
int validate_positive_number();

// Create a new PRODUCT
struct Product createProduct(int id, char *name, float price, int quantity) {
    struct Product product;
    product.id = id;
    strcpy(product.name, name);
    product.price = price;
    product.quantity = quantity;
    return product;
}

// Add PRODUCT 
void addProduct(struct Product product) {
    int lastId = getLastProductIdFromFile(FILE_PATH);
    product.id = lastId + 1;

    if (numProducts < MAX_PRODUCTS) {
        products[numProducts++] = product;
        writeProductsToFile(FILE_PATH, products, numProducts);
        printf("Product added successfully with ID %d.\n", product.id);
    } else {
        printf("Cannot add more products. Product limit reached.\n");
    }
}

// Write products data to file 
void writeProductsToFile(const char *filename, struct Product products[], int numProducts) {
    FILE *file_pointer = fopen(filename, "w");
    if (file_pointer == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = numProducts - 1; i >= 0; i--) {
        fprintf(file_pointer, "%d,%s,%.0f,%d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
    fclose(file_pointer);
}

// Get the last product ID from the file
int getLastProductIdFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    int lastId = 0;
    while (fscanf(file, "%d,%*[^,],%*f,%*d\n", &lastId) == 1) {
        
    }
    fclose(file);
    return lastId;
}

// Remove PRODUCT 
void removeProduct(int id) {
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == id) {
            for (int j = i; j < numProducts - 1; j++) {
                products[j] = products[j + 1];
            }
            numProducts--;
            writeProductsToFile(FILE_PATH, products, numProducts);
            printf("Product removed successfully.\n");
            return;
        }
    }
    printf("ID of product not found.\n");
}

// Update PRODUCT
void updateProduct(int id, char *newName, float newPrice, int newQuantity) {
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == id) {
            printf("Old Information of Product with ID %d:\n", id);
            printf("Name: %s\n", products[i].name);
            printf("Price: %.0f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);

            char input[100]; 
            while (getchar() != '\n');
            printf("Enter new name (or press Enter to keep old name): ");
            fgets(input, sizeof(input), stdin);
            if (strlen(input) > 1) {
                input[strcspn(input, "\n")] = '\0'; 
                strcpy(products[i].name, input);
            } else {
                printf("The name of the product has been retained.\n");
            }

            printf("Enter new price (or press Enter to keep old price): ");
            fgets(input, sizeof(input), stdin);
            if (strlen(input) > 1) {
                sscanf(input, "%f", &newPrice);
                if (newPrice >= 0) {
                    products[i].price = newPrice;
                } else {
                    printf("Error! Please enter a positive number: ");
                    newPrice = validate_positive_number();
                    products[i].price = newPrice;
                }
            } else {
                printf("The price of the product has been retained.\n");
            }

            printf("Enter new quantity (or press Enter to keep old quantity): ");
            fgets(input, sizeof(input), stdin);
            if (strlen(input) > 1) {
                sscanf(input, "%d", &newQuantity);
                if (newQuantity >= 0) {
                    products[i].quantity = newQuantity;
                } else {
                    printf("Error! Please enter a positive number: ");
                    newQuantity = validate_positive_number();
                    products[i].quantity = newQuantity;
                }
            } else {
                printf("The quantity of the product has been retained.\n");
            }


            writeProductsToFile(FILE_PATH, products, numProducts);
            printf("Product updated successfully.\n");
            return;
        }
    }
    printf("ID of product not found.\n");
}


// Display list of products 
void displayProducts() {
    if (numProducts == 0) {
        printf("No products available.\n");
        return;
    }
    printf("List of Products:\n");
    printf("%-15s %-20s %-30s %-20s\n", "ID of Product", "Name", "Price", "Quantity");
    for (int i = numProducts - 1; i >= 0; i--) {
        printf("%-15d %-20s %-35.0f %-15d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

// Compare function for sorting products by ID in descending order
int compareProducts(const void *a, const void *b) {
    const struct Product *productA = (const struct Product *)a;
    const struct Product *productB = (const struct Product *)b;
    return productB->id - productA->id; 
}

// Sort products by ID in descending order
void sortProductsByID() {
    qsort(products, numProducts, sizeof(struct Product), compareProducts);
}

// Load products data from file at the beginning of the program
void loadProductsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (numProducts < MAX_PRODUCTS && fscanf(file, "%d,%49[^,],%f,%d\n", 
    &products[numProducts].id, products[numProducts].name, &products[numProducts].price, &products[numProducts].quantity) == 4) {
        numProducts++;
    }
    fclose(file);
    sortProductsByID();
}

// Reload products data from file
void reloadProductsData() {
    numProducts = 0;
    loadProductsFromFile(FILE_PATH);
}

// Display product
void displayProduct(struct Product product) {
    printf("ID of Product: %-5d | Name: %-15s | Price: %-15.0f | Quantity: %d\n", 
           product.id, product.name, product.price, product.quantity);
}

// Read products from text file
void displayProductsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open' %s.\n", filename);
        return;
    }
    struct Product product;
    while (fscanf(file, "%d %s %f %d", &product.id, product.name, &product.price, &product.quantity) != EOF) {
        displayProduct(product);
        printf("\n");
    }
    fclose(file);
}

void takeProductsFromFile(struct Product products[], int *numProducts) {
    FILE *file = fopen("./src/data/product.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Read data from the file
    while (fscanf(file, "%d,%49[^,],%f,%d\n", &products[*numProducts].id,products[*numProducts].name, &products[*numProducts].price, &products[*numProducts].quantity) == 4) {
        (*numProducts)++;
    }

    fclose(file);
}

// Display available products
void displayAvailableProducts(struct Product products[], int numProducts) {
    printf("Products available for purchase:\n");
    for (int i = 0; i < numProducts; i++) {
        displayProduct(products[i]);
    }
}
