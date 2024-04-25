#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CART 100
#define MAX_PRODUCTS 100

// Declaration
struct Product;
struct Order {
    int idOrder;
    char customerName[50];
    char address[100];
    char phoneNumber[15];
    char purchaseDate[11];
    struct Product products[MAX_CART];
    int productCount;
    float totalPrice;
    char paymentMethod[20];
    char paymentStatus[20];
    float productPrice;
};
int validatePhoneNumber(const char *phoneNumber);
void read_cart_from_file(const char *filename, struct Order *order);
void read_order_from_file(const char *filename, struct Order *orders);
void write_order_to_file(const char *filename, struct Order *order);
void remove_newline(char *str);
int validate_phone_number(const char *phoneNumber);
int validate_date(const char *date);
void enter_bill_information(struct Order *x, int billID);
void create_bill(struct Order *numbers, int n);
void cancel_bill_by_idOrder(int idOrder);
void update_bill_by_idOrder(struct Order *count, int n, int id);
void display_all_bill_information(int n);
void display_bill_by_idOrder(int idOrder);

void read_cart_from_file(const char *filename, struct Order *order) {
    FILE *file = fopen("./src/data/cart.txt", "r");
    if (file == NULL) {
        printf("Can't open' %s.\n", filename);
        return;
    }

    struct Product product;
    int n = 0;
    while (fscanf(file, "%d %s %f %d", &product.id,
                  product.name,
                  &product.price,
                  &product.quantity) != EOF) {
        order->products[n] = product;
        printf("ID: %d \n Name: %s \n Price: %f \n Quantity: %d\n", order->products[n].id, order->products[n].name, order->products[n].price, order->products[n].quantity);
        n++;
    }
    order->productCount = n;
    fclose(file);
}

void read_order_from_file(const char *filename, struct Order *orders) {
    FILE *file = fopen("Bill.txt", "r");
    if (file == NULL) {
        printf("Can't open file '%s'.\n", filename);
        return;
    }

    int n = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%s,%s",
                  &orders[n].idOrder,
                  orders[n].purchaseDate,
                  orders[n].customerName,
                  orders[n].address,
                  orders[n].phoneNumber) != EOF) {
        printf("Bill ID: %d\n", orders[n].idOrder);
        printf("Purchase Date: %s\n", orders[n].purchaseDate);
        printf("Customer's Name: %s\n", orders[n].customerName);
        printf("Customer's Address: %s\n", orders[n].address);
        printf("Customer's Phone Number: %s\n", orders[n].phoneNumber);
        n++;
    }
    fclose(file);
    printf("Read %d orders from file '%s'.\n", n, filename);
}

void writeOrderToFile(const char *filename, struct Order *order, int n) {
    char fileName[100];
    sprintf(fileName, "BillNumber%d.txt", n);
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d,%s,%s,%s,%s\n", order->idOrder,
            order->purchaseDate,
            order->customerName,
            order->address,
            order->phoneNumber);

    for (int i = 0; i < order->productCount; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n", order->products[i].id,
                order->products[i].name,
                order->products[i].price,
                order->products[i].quantity);
    }

    fclose(file);
    printf("The data has been saved successfully.\n");
}

void removeNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0'; // Replace '\n' with '\0'
    }
}

void enter_Bill_Information(struct Order *x, int n, int billID) {
    x->idOrder = billID; 
    int check = 1;
    printf("Enter purchase date (DD/MM/YYYY): ");
    fgets(x->purchaseDate, sizeof(x->purchaseDate), stdin);
    fflush(stdin);
    while (check == 1) {
        if (!validate_date(x->purchaseDate)) {
            printf("Invalid date format. Please use DD/MM/YYYY.\n");
            printf("Rewrite purchase date.\n");
            fgets(x->purchaseDate, sizeof(x->purchaseDate), stdin);
            fflush(stdin);
        } else {
            check += 1;
        }
    }
    printf("Enter customer's name: ");
    fgets(x->customerName, sizeof(x->customerName), stdin);
    removeNewline(x->customerName);
    fflush(stdin);
    printf("Enter customer's address: ");
    fgets(x->address, sizeof(x->address), stdin);
    removeNewline(x->address);
    fflush(stdin);
    
    
    do {
        printf("Enter customer's phone number (10 digits): ");
        fgets(x->phoneNumber, sizeof(x->phoneNumber), stdin);
        removeNewline(x->phoneNumber);
        fflush(stdin);
    } while (!validatePhoneNumber(x->phoneNumber)); 
}

void create_bill(struct Order *numbers, int n) {
  
    int billID = 1;
    while (1) {
        char fileName[100];
        sprintf(fileName, "BillNumber%d.txt", billID);
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
           
            fclose(file);
            break;
        } else {
           
            fclose(file);
            billID++;
        }
    }
    char fileName[100];
    sprintf(fileName, "BillNumber%d.txt", billID);
    printf("Your ID bill is: %d\n", billID);
    enter_Bill_Information(&numbers[billID], n, billID); 
    writeOrderToFile(fileName, &numbers[billID], billID);
}

void cancel_bill_by_idOrder(int idOrder) {
    char fileName[100];
    sprintf(fileName, "BillNumber%d.txt", idOrder);
    if (remove(fileName) == 0) {
        printf("File 'BillNumber%d.txt' deleted successfully.\n", idOrder);
    } else {
        printf("Error deleting file 'BillNumber%d.txt': File not found.\n", idOrder);
    }
}

void update_bill_by_idOrder(struct Order *count, int n, int id) {
    char fileName[20];
    sprintf(fileName, "BillNumber%d.txt", id);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: File '%s' not found.\n", fileName);
        return;
    }

    struct Order order;
    fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", &order.idOrder,
           order.purchaseDate,
           order.customerName,
           order.address,
           order.phoneNumber,
           &order.productCount);

    printf("\nCurrent Bill Information:\n");
    printf("Bill ID: %d\n", order.idOrder);
    printf("Purchase Date: %s\n", order.purchaseDate);
    printf("Customer's Name: %s\n", order.customerName);
    printf("Customer's Address: %s\n", order.address);
    printf("Customer's Phone Number: %s\n", order.phoneNumber);
    
    fclose(file);

    
    printf("\nEnter new information:\n");
    enter_Bill_Information(&count[id], n, id);

    
    writeOrderToFile(fileName, &count[id], id);
}

void display_all_bill_information(int n) {
    for (int i = 1; i < MAX_PRODUCTS; i++) {
        char fileName[100];
        sprintf(fileName, "BillNumber%d.txt", i);
        FILE *file = fopen(fileName, "r");
        if (file != NULL) {
            struct Order order;
            fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", &order.idOrder,
                   order.purchaseDate,
                   order.customerName,
                   order.address,
                   order.phoneNumber,
                   &order.productCount);

            printf("\n----- Bill %d -----\n", i);
            printf("Bill ID: %d\n", order.idOrder);
            printf("Purchase Date: %s\n", order.purchaseDate);
            printf("Customer's Name: %s\n", order.customerName);
            printf("Customer's Address: %s\n", order.address);
            printf("Customer's Phone Number: %s\n", order.phoneNumber);

            for (int j = 0; j < order.productCount; j++) {
                fscanf(file, "%d,%[^,],%f,%d\n", &order.products[j].id,
                       order.products[j].name,
                       &order.products[j].price,
                       &order.products[j].quantity);
                printf("Product ID: %d\n", order.products[j].id);
                printf("Product Name: %s\n", order.products[j].name);
                printf("Product Price: %.2f\n", order.products[j].price);
                printf("Product Quantity: %d\n", order.products[j].quantity);
            }
            fclose(file);
        }
    }
}

void display_bill_by_idOrder(int idOrder) {
    char fileName[100];
    sprintf(fileName, "BillNumber%d.txt", idOrder);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: File '%s' not found.\n", fileName);
        return;
    }

    struct Order order;
    fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d\n", &order.idOrder,
           order.purchaseDate,
           order.customerName,
           order.address,
           order.phoneNumber,
           &order.productCount);

    printf("\n----- Bill %d -----\n", idOrder);
    printf("Bill ID: %d\n", order.idOrder);
    printf("Purchase Date: %s\n", order.purchaseDate);
    printf("Customer's Name: %s\n", order.customerName);
    printf("Customer's Address: %s\n", order.address);
    printf("Customer's Phone Number: %s\n", order.phoneNumber);

    for (int j = 0; j < order.productCount; j++) {
        fscanf(file, "%d,%[^,],%f,%d\n", &order.products[j].id,
               order.products[j].name,
               &order.products[j].price,
               &order.products[j].quantity);
        printf("Product ID: %d\n", order.products[j].id);
        printf("Product Name: %s\n", order.products[j].name);
        printf("Product Price: %.2f\n", order.products[j].price);
        printf("Product Quantity: %d\n", order.products[j].quantity);
    }
    fclose(file);
}








