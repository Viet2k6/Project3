#include <stdio.h>
#include <string.h>
#include "functions.h"

//Tieu de he thong quan ly thu vien
void displaySystemName() {
	clearScreen();
	printf("***Library Management System Using C***\n");
}

// Xoa man hinh terminal
void clearScreen() {
	printf("\033[2J\033[H");
}

//Menu chinh cua chuong trinh
void displayMenu() {
	printf("\n          MENU:\n");
	printf("============================\n");
	printf("[1] Add a new book\n");
	printf("[2] Show all books\n");
	printf("[3] Search a book\n");
	printf("[4] Edit a book\n");
	printf("[5] Delete a book\n");
	printf("[6] Arrange books by prices\n");
	printf("[0] Exit the program\n");
	printf("============================\n");
	printf("Enter your choice: ");
}

//Tai thong tin sach tu file
void loadBooksFromFile(struct Book books[], int* count) {
	FILE* file = fopen("C:/Users/Lenovo/Desktop/project real/LMS/books.dat", "rb");
	if (file == NULL) {
		*count = 0;
		return;
	}

	fread(count, sizeof(int), 1, file);
	fread(books, sizeof(struct Book), *count, file);
	fclose(file);
}

//Luu thong tin sach vao file
void saveBooksToFile(struct Book books[], int count) {
	FILE* file = fopen("C:.dat", "wb");
	if (file == NULL) {
		printf("Error: Could not save books to file.\n");
		return;
	}

	fwrite(&count, sizeof(int), 1, file);
	fwrite(books, sizeof(struct Book), count, file);
	fclose(file);
}

//Hien thi danh sach sach
void displayBooks(struct Book books[], int count) {
	clearScreen();
	printf("            ***All Books***\n");
	if (count == 0) {
		printf("\nNo books available in the library.\n");
		return;
	}
	printf("|=======|======================|===========================|=================|\n");
	printf("| %-5s | %-20s | %-25s | %-15s |\n", "ID", "Title", "Author", "Price");
	printf("|=======|======================|===========================|=================|\n");
	int i;
	for (i = 0; i < count; i++) {
		printf("| %-5d | %-20s | %-25s | %-15d |\n",
			books[i].id,
			books[i].title,
			books[i].author,
			books[i].price);
		printf("|-------|----------------------|---------------------------|-----------------|\n");
	}
	printf("\nPress [9] to return the main menu: ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9') break;
	} while (1);
}

// Tim kiem sach
void searchBook(const struct Book books[], int count) {
	clearScreen();
	printf("            ***Search A Book***\n");

	if (count == 0) {
		printf("\nNo books available to search.\n");
		printf("\nPress Enter to return to the main menu...");
		getchar();
		return;
	}

	char keyword[50];
	printf("Enter title or author to search: ");
	getchar();
	fgets(keyword, sizeof(keyword), stdin);
	keyword[strcspn(keyword, "\n")] = 0; 

	int found = 0;
	printf("\nSearch Results:\n");
	printf("|=======|======================|===========================|=================|\n");
	printf("| %-5s | %-20s | %-25s | %-15s |\n", "ID", "Title", "Author", "Price");
	printf("|=======|======================|===========================|=================|\n");
    int i;
	for (i = 0; i < count; i++) {
		if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) {
			printf("| %-5d | %-20s | %-25s | %-15d |\n",
				books[i].id,
				books[i].title,
				books[i].author,
				books[i].price);
			printf("|-------|----------------------|---------------------------|-----------------|\n");
			found = 1;
		}
	}

	if (!found) {
		printf("\nNo matching books found for keyword: '%s'.\n", keyword);
	}
	printf("\nPress [9] to return the main menu: ");
	
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9') break;
	} while (1);

}

//Them sach
void addBook(struct Book books[], int* count) {
	clearScreen();
	printf("            ***Add A New book***\n");

	if (*count >= 100) {
		printf("Book list is full! Cannot add more books.\n");
		return;
	}

	printf("Enter Book ID: ");
	scanf("%d", &books[*count].id);
	getchar(); 

	printf("Enter Book Title: ");
	fgets(books[*count].title, 100, stdin);
	books[*count].title[strcspn(books[*count].title, "\n")] = 0; 

	printf("Enter Author Name: ");
	fgets(books[*count].author, 20, stdin);
	books[*count].author[strcspn(books[*count].author, "\n")] = 0; 
	
	printf("Enter Price: ");
	scanf("%d", &books[*count].price);

	(*count)++;

	printf("\nBook added successfully!\n");
	printf("\nPress [9] to return the main menu: ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9') break;
	} while (1);

}

//Sua sach
void editBook(struct Book books[], int count) {
	clearScreen();
	printf("            ***Edit A book***\n");

	if (count == 0) {
		printf("\nNo books available to edit.\n");
		printf("\nPress [9] to return the main menu:");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9') break;
		} while (1);
		return;
	}

	int id;
	printf("Enter the ID of the book you want to edit: ");
	scanf("%d", &id);
	getchar(); 
    int i;
	int existsId = 0; 
	for (i = 0; i < count; i++) {
		if (books[i].id == id) {
			existsId = 1;

			printf("\nCurrent Information:\n");
			printf("ID: %d\n", books[i].id); 
			printf("Title: %s\n", books[i].title); 
			printf("Author: %s\n", books[i].author); 
			printf("Price: %d\n", books[i].price);  

			printf("\nEnter New Title:");
			fgets(books[i].title, sizeof(books[i].title), stdin);
			books[i].title[strcspn(books[i].title, "\n")] = 0;

			printf("Enter New Author:");
			fgets(books[i].author, sizeof(books[i].author), stdin);
			books[i].author[strcspn(books[i].author, "\n")] = 0; 

			printf("Enter New Price:");
			scanf("%d", &books[i].price);
			getchar();  

			printf("\nBook information updated successfully!\n");
			printf("\nPress [9] to return the main menu:");
			char choice;
			do {
				scanf(" %c", &choice);
				if (choice == '9') break;
			} while (1);

			return;
		}
	}

	if (existsId == 0) {
		printf("\nBook with ID %d not found.\n", id);
	}

	printf("\nPress [9] to return the main menu: ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9') 
			break;
	} while (1);

}

//Xoa sach
void deleteBook(struct Book books[], int* count) {
	clearScreen();
	printf("            ***Delete a book***\n");
	int id;
	printf("\nEnter the ID of the book to delete: ");
	scanf("%d", &id);
	getchar(); 
    int i;
	int index = -1;
	for (i = 0; i < *count; i++) {
		if (books[i].id == id) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("\nBook with ID %d not found.\n", id);
		printf("\nPress [9] to return to the main menu:");
		char choice;
		do {
			scanf(" %c", &choice);
			if (choice == '9') break;
		} while (1);
		return;
	}

	printf("\nBook Found:\n");
	printf("ID: %d\n", books[index].id);
	printf("Title: %s\n", books[index].title);
	printf("Author: %s\n", books[index].author);
	char confirmation;
	printf("\nAre you sure you want to delete this book? (y/n): ");
	scanf(" %c", &confirmation);
	getchar(); 

	if (confirmation == 'y' || confirmation == 'Y') {
		int i;
		for (i = index; i < *count - 1; i++) {
			books[i] = books[i + 1]; 
		}

		(*count)--;
		printf("\nBook deleted successfully!\n");
	}
	else {
		printf("\nOperation canceled.\n");
	}
	printf("\nPress [9] to return to the main menu: ");
	char choice;
	do {
		scanf(" %c", &choice);
		if (choice == '9') 
		break;
	} while (1);
}

//Sap xep sach theo gia
void sortBooksByPrice(struct Book books[], int count) {
    int order;
    printf("\nChoose sorting order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter your choice: ");
    scanf("%d", &order);

    if (order != 1 && order != 2) {
        printf("Invalid choice. Returning to main menu.\n");
        return;
    }
    int i,j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if ((order == 1 && books[j].price > books[j + 1].price) || 
                (order == 2 && books[j].price < books[j + 1].price)) {
                struct Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    printf("\nBooks sorted successfully.\n");
    printf("\nSorted Book List:\n");
    printf("|=======|======================|===========================|=================|\n");
    printf("| %-5s | %-20s | %-25s | %-15s |\n", "ID", "Title", "Author", "Price");
    printf("|=======|======================|===========================|=================|\n");
    
    for (i = 0; i < count; i++) {
        printf("| %-5d | %-20s | %-25s | %-15d |\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].price);
        printf("|-------|----------------------|---------------------------|-----------------|\n");
    }

    printf("\nPress [9] to return to the main menu: ");
    char choice;
    do {
        scanf(" %c", &choice);
        if (choice == '9') 
		break;
    } while (1);
}



