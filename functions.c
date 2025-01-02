#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
    struct Book books[100];
    int count = 0;

    loadBooksFromFile(books, &count);
    displaySystemName();

    int choice;
    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addBook(books, &count);
            saveBooksToFile(books, count);
            break;
        case 2:
            displayBooks(books, count);
            break;
        case 3: 
            searchBook(books, count);
            break;
        case 4:
            editBook(books, count);
            saveBooksToFile(books, count);
            break;
        case 5: 
            deleteBook(books, &count);
            saveBooksToFile(books, count);
            break;
        case 6: 
            sortBooksByPrice(books, count);
            break;
        case 0:
            printf("Exit!\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

