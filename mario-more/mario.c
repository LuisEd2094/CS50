#include <cs50.h>
#include <stdio.h>
void    left_colums(int width, int height, int j);
void    right_colums(int width, int height, int j);




int main(void)
{
    int height;
    int width;
    int i;
    int j;

    i = 0;
    do  //Loop to get Height, will Do until a number between 1 and 8, inclusive, is enter
    {
        height = get_int("Height: ");
    }
    while (height < 1  || height > 8);
    width = height;
    while (i < height)
    {
        j = width;
        left_colums(width, height, j);
        printf("  ");
        j = 0;
        right_colums(width, height, j);
        printf("\n");
        height--;
    }
}
void    left_colums(int width, int height, int j)
{
    while (j > (width - height + 1))// Checks number of empty spaces needed
    {
        printf(" ");
        j--;
    }
    while (j <= (width - height + 1) && j != 0) //prints # needed
    {
        printf("#");
        j--;
    }
}

void    right_colums(int width, int height, int j)
{
    while (j <= (width - height))  //prints # needed, no need for empty spaces, outside function will print \n
    {
        printf("#");
        j++;
    }
}