#include <stdio.h>
#include <math.h>

float CalcDist_Bet_2Points(float x1, float y1, float x2, float y2);

int main()
{
    while(1)
    {
        float x1,x2,y1,y2,dist;

        printf("please enter the coordinates of the first point (x1, y1): ");
        scanf("%f %f",&x1,&y1);

        printf("please enter the coordinates of the second point (x2, y2): ");
        scanf("%f %f",&x2,&y2);

        dist = CalcDist_Bet_2Points(x1,y1,x2,y2);

        printf("The distance between the two points is: %f\n\n",dist);
    }
}

float CalcDist_Bet_2Points(float x1,float y1,float x2,float y2)
{
    float dist;

    dist = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );

    return dist;
}