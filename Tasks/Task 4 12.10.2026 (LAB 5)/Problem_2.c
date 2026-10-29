
#include <stdio.h>
typedef struct
{
    int real;
    int imag;
}complex;

void add_complex(complex* c1, complex* c2, complex* result);

void scan_complex(complex* c);

void multiply_complex(complex* c1, complex* c2, complex* result);


int main()
{

    printf("please enter the first complex number : \n");
    complex c1;
    scan_complex(&c1);
    printf("please enter the second complex number : \n");
    complex c2;
    scan_complex(&c2);
    printf("the first complex number is : %d + %di\n",c1.real,c1.imag);
    printf("the second complex number is : %d + %di\n",c2.real,c2.imag);
    complex result;
    add_complex(&c1, &c2, &result);
    printf("the sum of the two complex numbers is : %d + %di\n",result.real,result.imag);
    multiply_complex(&c1, &c2, &result);
    printf("the multiplication of the two complex numbers is : %d + %di\n",result.real,result.imag);

}


void scan_complex(complex* c)
{
    printf("please enter the real part : ");
    scanf("%d",&(c->real));

    printf("please enter the imaginary part only two digits : ");
    scanf("%d",&(c->imag));
}



void add_complex(complex* c1, complex* c2, complex* result)
{
    result->real = c1->real + c2->real;
    result->imag = c1->imag + c2->imag;
}


/*
 * complex number multiplication:
 *
 * (a + bi) * (c + di)
 * = ac + adi + bci + bd(i^2)
 *
 * since i^2 = -1:
 * = (ac - bd) + (ad + bc)i
 *
 * real Part = (a * c) - (b * d)
 * imag Part = (a * d) + (b * c)
 *
 * example:
 * (3 + 2i) * (4 + 5i) = 2 + 23i
 */
void multiply_complex(complex* c1, complex* c2, complex* result)
{
    result->real = c1->real * c2->real - c1->imag * c2->imag;
    result->imag = c1->real * c2->imag + c1->imag * c2->real;
}