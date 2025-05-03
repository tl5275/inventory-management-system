#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    int stock;
    float price;
} Product;

Product inventory[MAX];
int count = 0;
const char *filename = "inventory.txt";

// Function prototypes
void loadFromFile();
void saveToFile();
void addProduct();
void editProduct();
void deleteProduct();
void displayProducts();
void sortByStock();
void sortByPrice();
int findProductByID(int id);

int main() {
    int choice;

    loadFromFile();

    do {
        printf("\nInventory Management System\n");
        printf("1. Add Product\n");
        printf("2. Edit Product\n");
        printf("3. Delete Product\n");
        printf("4. Display Products\n");
        printf("5. Sort by Stock\n");
        printf("6. Sort by Price\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: addProduct(); break;
            case 2: editProduct(); break;
            case 3: deleteProduct(); break;
            case 4: displayProducts(); break;
            case 5: sortByStock(); displayProducts(); break;
            case 6: sortByPrice(); displayProducts(); break;
            case 0: saveToFile(); printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

void loadFromFile() {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%d %s %d %f", &inventory[count].id, inventory[count].name,
                  &inventory[count].stock, &inventory[count].price) != EOF) {
        count++;
    }
    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %.2f\n", inventory[i].id, inventory[i].name,
                inventory[i].stock, inventory[i].price);
    }
    fclose(fp);
}

void addProduct() {
    if (count >= MAX) {
        printf("Inventory full!\n");
        return;
    }

    Product p;
    printf("Enter product ID: ");
    scanf("%d", &p.id);
    getchar();

    if (findProductByID(p.id) != -1) {
        printf("Product with ID %d already exists!\n", p.id);
        return;
    }

    printf("Enter product name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0'; // remove newline

    printf("Enter stock: ");
    scanf("%d", &p.stock);
    printf("Enter price: ");
    scanf("%f", &p.price);

    inventory[count++] = p;
    printf("Product added!\n");
}

void editProduct() {
    int id;
    printf("Enter product ID to edit: ");
    scanf("%d", &id);

    int idx = findProductByID(id);
    if (idx == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter new name: ");
    getchar();
    fgets(inventory[idx].name, sizeof(inventory[idx].name), stdin);
    inventory[idx].name[strcspn(inventory[idx].name, "\n")] = '\0';

    printf("Enter new stock: ");
    scanf("%d", &inventory[idx].stock);
    printf("Enter new price: ");
    scanf("%f", &inventory[idx].price);
    printf("Product updated!\n");
}

void deleteProduct() {
    int id;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    int idx = findProductByID(id);
    if (idx == -1) {
        printf("Product not found!\n");
        return;
    }

    for (int i = idx; i < count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    count--;
    printf("Product deleted!\n");
}

void displayProducts() {
    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "Name", "Stock", "Price");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10d %-10.2f\n", inventory[i].id, inventory[i].name,
               inventory[i].stock, inventory[i].price);
    }
}

void sortByStock() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (inventory[i].stock > inventory[j].stock) {
                Product temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }
    printf("Sorted by stock.\n");
}

void sortByPrice() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (inventory[i].price > inventory[j].price) {
                Product temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }
    printf("Sorted by price.\n");
}

int findProductByID(int id) {
    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id)
            return i;
    }
    return -1;
}
