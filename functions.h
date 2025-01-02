#include "datatypes.h"

//Tieu de he thong quan ly thu vien
void displaySystemName();
// Xoa man hinh terminal
void clearScreen();
//Menu chinh cua chuong trinh
void displayMenu();
//Tai thong tin sach tu file
void loadBooksFromFile(struct Book books[], int* count);
//Luu thong tin sach vao file
void saveBooksToFile(struct Book books[], int count);
//Hien thi danh sach sach
void displayBooks(struct Book books[], int count);
//Them sach moi
void addBook(struct Book books[], int* count);
//Sua sach
void editBook(struct Book books[], int count);


