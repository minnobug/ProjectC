#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Product
struct Product {
  int id;
  char name[50];
  char manufacturer[50];
  float price;
  int quantity;
};

struct Product products[MAX_PRODUCTS];
int numProducts = 0;


// Read products from text file
void displayProductsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open' %s.\n", filename);
        return;
    }

    struct Product product;
    // read product, show info
    while (fscanf(file, "%d %s %f %d", &product.id, product.name, &product.price, &product.quantity) != EOF) {
      displayProduct(product);
      printf("\n");
    }

  fclose(file);
}

