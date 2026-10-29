
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

typedef enum
{
    AVAILABLE,
    BORROWED
} BookStatus;

typedef enum
{
    SCIENCE,
    HISTORY,
    NOVEL,
    TECHNOLOGY
} BookCategory;

typedef struct
{
    char title[100];
    char author[100];
    float price;
    BookCategory category;
    BookStatus availability;
} Book;


void addBook(Book*library, int*count);

void string_scan(char *str,int maxSize);
void displayBook(Book*book);
void searchBook(Book*library, int count);
void changeStatus(Book *library, int count);
void countCategories(Book *library, int count);


int main()
{
    Book library[MAX_BOOKS];

    int count=0;
    int choice;

    do
    {
        printf("\n========== LIBRARY SYSTEM ==========\n");
        printf("1-add new book\n");
        printf("2-search book\n");
        printf("3-change book status\n");
        printf("4-count books by category\n");
        printf("5-display all books\n");
        printf("0-exit\n");

        printf("enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                addBook(library, &count);
                break;

            case 2:
                searchBook(library, count);
                break;

            case 3:
                changeStatus(library, count);
                break;

            case 4:
                countCategories(library, count);
                break;

            case 5:
                for(int i=0; i<count;i++)
                {
                    displayBook(&library[i]);
                }
                break;

            case 0:
                printf("goodbye");
                break;

            default:
                printf("invalid choice");
        }
        printf("\n");

    } while(choice!=0);
}


void addBook(Book *library, int *count)
{
    if(*(count)>=MAX_BOOKS)
    {
        printf("Library is full\n");
    }
    else
    {
        Book *book = &library[*(count)];

        printf("enter book title: ");
        string_scan(book->title,100);

        printf("enter author name: ");
        string_scan(book->author,100);

        printf("enter price: ");
        scanf("%f",&book->price);

        int category;

        printf("\nchoose Category:\n");
        printf("0-science\n");
        printf("1-history\n");
        printf("2-novel\n");
        printf("3-technology\n");

        printf("enter category: ");
        scanf("%d", &category);

        if(category<SCIENCE || category>TECHNOLOGY)
        {
            printf("invalid category\n");
        }
        else
        {

            book->category=category;

            book->availability=AVAILABLE;

            (*count)++;

            printf("book added successfully\n");
        }
    }
    
}

void string_scan(char *str,int maxSize)
{
    int i=0;
    fflush(stdin);
    scanf("%c",&str[i]);
    while((str[i]!='\n')&&(i<maxSize-1))
    {
        i++;
        scanf("%c",&str[i]);
    }
    str[i]=0;
}

void displayBook(Book *book)
{
    char *categories[]=
    {
        "science",
        "history",
        "novel",
        "technology"
    };

    printf("\n------------------------\n");

    printf("Title: %s\n",book->title);
    printf("Author: %s\n",book->author);
    printf("Price: %.2f\n",book->price);

    printf("Category: %s\n",categories[book->category]);

    printf("Status: %s\n", book->availability == AVAILABLE ? "Available" : "Borrowed");

    printf("------------------------\n");
}

void searchBook(Book *library, int count)
{
    char keyword[100];
    int found=0;

    printf("enter title or author: ");
    string_scan(keyword,100);

    for(int i=0;i<count;i++)
    {
        if(strstr(library[i].title, keyword) != NULL ||
           strstr(library[i].author, keyword) != NULL)
        {
            displayBook(&library[i]);
            found=1;
        }
        else{;}
    }

    if(found==0)
    {
        printf("book not found\n");
    }
    else{;}
}


void changeStatus(Book *library, int count)
{
    char title[100],flag=0;

    printf("enter book title: ");
    string_scan(title,100);

    for(int i=0;(i<count)&&(0==flag); i++)
    {
        if(strcmp(library[i].title, title) == 0)
        {
            if(library[i].availability == AVAILABLE)
            {
                library[i].availability = BORROWED;

                printf("book borrowed successfully\n");
            }
            else
            {
                library[i].availability = AVAILABLE;

                printf("book returned successfully\n");
            }
            flag=1;
        }
        else{;}
    }

    if(flag==0)
    {
        printf("book not found\n");
    }
    else{;}
}

void countCategories(Book *library, int count)
{
    int categoriesCount[4]={0};

    char *categories[]=
    {
        "science",
        "history",
        "novel",
        "technology"
    };

    for(int i=0;i<count;i++)
    {
        categoriesCount[library[i].category]++;
    }

    printf("\n===== BOOKS BY CATEGORY =====\n");

    for(int i=0;i<4;i++)
    {
        printf("%s: %d books\n", categories[i],categoriesCount[i]);
    }
}
