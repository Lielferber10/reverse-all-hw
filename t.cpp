#include <stdio.h>

int main()
{
    int resources[] = {0,0,0,0,0}; // wood,brick,wool, grain, stone
    char input[16];
    while(scanf("%s", input) != EOF)//change in assembly
    {
        if(input[0] == 'r')
        {
            resources[0]+=1;
            resources[1]+=1;
        }else if(input[0] == 's')
        {
            resources[0]+=1;
            resources[1]+=1;
            resources[2]+=1;
            resources[3]+=1;
        }else if(input[0] == 'c')
        {
            resources[3]+=2;
            resources[4]+=3;
        }else if(input[0] == 'd')
        {
            resources[2]+=1;
            resources[3]+=1;
            resources[4]+=1;
        }
    }

    printf("%02d\n", resources[0]);
    printf("Wood\n");
    printf("%02d\n", resources[1]);
    printf("Brick\n");
    printf("%02d\n", resources[2]);
    printf("Wool\n");
    printf("%02d\n", resources[3]);
    printf("Grain\n");
    printf("%02d\n", resources[4]);
    printf("Stone\n");

    return 0;
}