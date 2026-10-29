
#include "stdio.h"

#define CHAR_INNAME  20

#define MAX_STUDENT_NUMBER  4

typedef struct 
{
    int totalmarks;
    int age;
    char name[CHAR_INNAME];
    

}student;

static int student_now=0;

void scan_student(student*std);

void string_scan(char *str,int maxSize);

void string_print(char*str);

void print_student(student*std);

void print_allStudents(student*std);

int find_average(student*std);

void top_three_marks(student*std);

void scan_allStudents(student*std);

int main()
{

    student std[MAX_STUDENT_NUMBER];

    printf("please enter the information of students : \n");
    scan_allStudents(std);
    printf("the information of students is : \n");
    print_allStudents(std);
    printf("the average of total marks is : %d\n",find_average(std));
    top_three_marks(std);

}

void scan_allStudents(student*std)
{
    for(int i=0;i<MAX_STUDENT_NUMBER;i++)
    {
        scan_student(&std[i]);
    }
}

int find_average(student*std)
{
    int sum=0;
    for(int i=0;i<student_now;i++)
    {
        sum+=std[i].totalmarks;
    }
    return sum/student_now;
}

void top_three_marks(student*std)
{
    int first=0,second=0,third=0;
    for(int i=0;i<student_now;i++)
    {
        if(std[i].totalmarks>std[first].totalmarks)
        {
            third=second;
            second=first;
            first=i;
        }
        else if(std[i].totalmarks>std[second].totalmarks)
        {
            third=second;
            second=i;
        }
        else if(std[i].totalmarks>std[third].totalmarks)
        {
            third=i;
        }
    }
    printf("the top three students are : \n");
    print_student(&std[first]);
    print_student(&std[second]);
    print_student(&std[third]);
}

void print_allStudents(student*std)
{
    for(int i=0;i<student_now;i++)
    {
        print_student(&std[i]);
        printf("\n");
    }
}

void print_student(student*std)
{
    printf("the name is : ");
    string_print(std->name);

    printf("the age is : %d\n",std->age);

    printf("the total marks is : %d\n",std->totalmarks);


}

void scan_student(student*std)
{
    printf("please enter the name : ");
    string_scan(std->name,CHAR_INNAME);

    printf("please enter the age : ");
    scanf("%d",&(std->age));

    printf("please enter total marks : ");
    scanf("%d",&(std->totalmarks));

    student_now++;


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

void string_print(char*str)
{
	int i;
	for(i=0;str[i];i++)
	{
		printf("%c",str[i]);
	}
    printf("\n");
}