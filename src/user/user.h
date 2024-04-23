

void userMenu() {
    int choice;
    do {
        printf("MENU: \n");
        printf("\t1. Shopping Cart Management\n");
        printf("\t2. Order Management\n");
        printf("\t0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

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
