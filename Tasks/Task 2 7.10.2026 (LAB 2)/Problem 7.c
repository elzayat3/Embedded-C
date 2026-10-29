
#include<stdio.h>
#include <ctype.h>

int main()
{

    char c;
    printf("please enter the character : ");
    scanf("%c",&c);

    if(isalpha(c))
    {
        if(c>='a'&& c<='z')
        {
            c=c-'a'+'A';
        }
        else{;}

        if(('A'==c) || ('E'==c) || ('O'==c) || ('I'==c) || ('U'==c))
        {
            printf("it is a vowel character ");
        
        }
        else
        {
           printf("it is a consonant character "); 
        }

    }
    else
    {
        printf("invalid input");
    }

}