
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const argv[])
{
    float y = 2.4;
    int x = atoi(argv);
    FILE *file = fopen("file.txt","r");
    fscanf(file,"%f","%d",&y,&x);
    return 0;
}
