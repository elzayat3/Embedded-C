
#include <stdio.h>


#define MAX_EMPLOYEES 100

typedef enum {
    FULL_TIME,
    PART_TIME,
    INTERN
} EmployeeType;

typedef enum {
    HR,
    IT,
    FINANCE,
    SALES
} Department;

typedef union {
    float monthly_salary;
    float hourly_rate;
} Compensation;

typedef struct {
    int id;
    char name[50];
    Department department;
    EmployeeType type;
    Compensation salary;
    float hours_worked;
} Employee;

int searchByID(int id);

float calculateSalary(Employee e);

void addEmployee(void) ;

void string_scan(char *str,int maxSize);

void removeEmployee(void);

void searchEmployee(void);

void filterByDepartment(void);

void filterByType(void);

void calculatePayroll(void);

void displayAllEmployees(void);

Employee employees[MAX_EMPLOYEES];
int count=0;

const char *departmentNames[] = {"HR", "IT", "Finance", "Sales"};

const char *typeNames[] = {"Full Time", "Part Time", "Intern"};


int main() {
    int choice=0;

    do {
        printf("\n===== employee management System =====\n");
        printf("1-add Employee\n");
        printf("2-remove Employee\n");
        printf("3-search Employee by ID\n");
        printf("4-filter by Department\n");
        printf("5-filter by Type\n");
        printf("6-calculate Total Payroll\n");
        printf("7-display All Employees\n");
        printf("0-exit\n");

        printf("enter your choice: ");

        if (scanf("%d",&choice)!=1) 
        {
            printf("invalid input\n");
        }
        else
        {
            switch (choice) 
            {
                case 1:
                    addEmployee();
                    break;

                case 2:
                    removeEmployee();
                    break;

                case 3:
                    searchEmployee();
                    break;

                case 4:
                    filterByDepartment();
                    break;

                case 5:
                    filterByType();
                    break;

                case 6:
                    calculatePayroll();
                    break;

                case 7:
                    displayAllEmployees();
                    break;

                case 0:
                    printf("exiting\n");
                    break;

                default:
                    printf("invalid choice\n");
            }
        }
    } while (choice != 0);

    return 0;
}


int searchByID(int id) {
    int index=-1,flag=0;

    for (int i=0;i<count&&(0==flag);i++) 
    {
        if (employees[i].id==id) {
            index = i;
            flag=1;
        }
        else{;}
    }
    return index;
}



float calculateSalary(Employee e) {
    float salary;

    if (e.type==FULL_TIME)
    {
        salary=e.salary.monthly_salary;
    } 
    else 
    {
        salary=e.salary.hourly_rate * e.hours_worked;
    }
    return salary;
}


void displayEmployee(Employee e) {
    printf("\nID: %d\n",e.id);
    printf("name: %s\n",e.name);
    printf("department: %s\n",departmentNames[e.department]);
    printf("type: %s\n",typeNames[e.type]);
    printf("salary: %.2f\n",calculateSalary(e));
    printf("============\n");
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


void addEmployee(void) 
{
    Employee e;
    int flag=1;

    if (count >= MAX_EMPLOYEES) 
    {
        printf("employee list is full\n");
        flag = 0;
    }
    else{;}

    if (flag==1) 
    {
        printf("enter employee ID: ");
        scanf("%d",&e.id);

        if (searchByID(e.id)!=-1) 
        {
            printf("employee ID already exists\n");
            flag = 0;
        }
        else{;}
    }
    else{;}

    if (flag==1) 
    {
        printf("enter name: ");
        string_scan(e.name,50);

        printf("\nDepartments:\n");
        printf("1-HR\n");
        printf("2-IT\n");
        printf("3-finance\n");
        printf("4-sales\n");

        printf("choose department: ");
        scanf("%d",&e.department);

        if (e.department<HR || e.department>SALES) 
        {
            printf("invalid department\n");
            flag=0;
        }
        else{;}
    }
    else{;}

    if (flag==1) 
    {
        printf("\nemployee Types:\n");
        printf("1-Full Time\n");
        printf("2-Part Time\n");
        printf("3-Intern\n");

        printf("Choose type: ");
        scanf("%d",&e.type);

        if (e.type<FULL_TIME || e.type>INTERN)
         {
            printf("invalid employee type\n");
            flag=0;
        }
        else{;}
    }
    else{;}

    if (flag==1) 
    {
        if (e.type==FULL_TIME) 
        {
            printf("Enter monthly salary: ");
            scanf("%f",&e.salary.monthly_salary);
            e.hours_worked=0.0F;
        } 
        else 
        {
            printf("enter hourly rate: ");
            scanf("%f",&e.salary.hourly_rate);

            printf("enter hours worked: ");
            scanf("%f",&e.hours_worked);
        }

        employees[count]=e;
        count++;

        printf("employee added successfully\n");
    }
    else{;}
}



void removeEmployee(void) 
{
    int id;
    int index;

    printf("enter employee ID to remove: ");
    scanf("%d",&id);

    index=searchByID(id);

    if (index==-1) 
    {
        printf("employee not found\n");
    } 
    else 
    {
        for (int i=index;i<count-1;i++) 
        {
            employees[i]=employees[i + 1];
        }

        count--;

        printf("employee removed successfully\n");
    }

}

void searchEmployee(void) 
{
    int id;

    printf("enter employee ID: ");
    scanf("%d",&id);

    int index=searchByID(id);

    if (index==-1) 
    {
        printf("employee not found\n");
    } 
    else 
    {
        displayEmployee(employees[index]);
    }
}


void filterByDepartment(void) 
{
    int department;
    int found=0;

    printf("\n1-HR\n");
    printf("2-IT\n");
    printf("3-Finance\n");
    printf("4-Sales\n");

    printf("choose department: ");
    scanf("%d",&department);

    if (department<HR || department>SALES) 
    {
        printf("invalid department\n");
    } 
    else
    {
        for (int i=0;i<count;i++) 
        {
            if (employees[i].department==department) 
            {
                displayEmployee(employees[i]);
                found=1;
            }
            else{;}
        }

        if (found == 0) {
            printf("No employees found!\n");
        }
        else{;}
    }

}

void filterByType(void) 
{
    int type;
    int found=0;

    printf("\n1-Full Time\n");
    printf("2-Part Time\n");
    printf("3-Intern\n");

    printf("choose type: ");
    scanf("%d",&type);

    if (type<FULL_TIME || type>INTERN) 
    {
        printf("invalid type\n");
    } 
    else 
    {
        for (int i=0;i<count;i++) 
        {
            if (employees[i].type==type) 
            {
                displayEmployee(employees[i]);
                found=1;
            }
            else{;}
        }

        if (found==0) 
        {
            printf("no employees found\n");
        }
        else{;}
    }
}


void calculatePayroll(void) 
{
    float total=0;

    for (int i=0;i<count;i++)
    {
        total+=calculateSalary(employees[i]);
    }

    printf("\ntotal Payroll: %.2f\n",total);
}


void displayAllEmployees(void)
{
    if (count==0)
    {
        printf("no employees available\n");
    }
    else
    {
        for (int i=0;i<count;i++)
        {
            displayEmployee(employees[i]);
        }
    }
}



