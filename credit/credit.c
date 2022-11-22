#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    float regular = get_float("Regular Price:");
    float sale = regular * .85;

    printf("Sale Price : %.3f    \nRegular Price : %.2f", sale, regular);

    return 0;
}




/*
int cc_check(long cc_num);
void print_cc_type(long cc_num);

int sum_cc(long cc_num)
{
    int sum;
    int i;
    int j;

    i = 1;
    sum = 0;
    while (cc_num > 0)
    {
        if (i % 2 == 1)
        {
            sum += cc_num % 10;
        }
        else
        {
            j = cc_num % 10;
            j *= 2;
            if (j > 9)
            {
                sum += j % 10;
                sum += j / 10;
            }
            else
            {
                sum += j;
            }
        }
        cc_num = cc_num / 10;
        i++;
    }
    return sum;
}

int cc_check(long cc_num)
{
    int i;
    long cc_count = cc_num;
    int j;

    j = 0;

    while (cc_count > 100)
    {
        cc_count = cc_count / 10;
        j++;
    }
    if (cc_count == 37 && j == 13)
    {
        i = 1; //AMEX
    }
    else if ((cc_count == 22 || cc_count == 55 || cc_count == 51) && j == 14)
    {
        i = 1; //MASTER
    }
    else if ((cc_count == 40 || cc_count == 41 || cc_count == 42) && (j == 11 || j == 14))
    {
        i = 1; //VISA
    }
    else
    {
        i = 0;
        printf("INVALID\n"); //INVALID
        exit(0);
    }
    return i;
}

int cc_type(long cc_num)
{
    int i;
    long cc_count = cc_num;

    while (cc_count > 100)
    {
        cc_count = cc_count / 10;
    }
    if (cc_count == 37)
    {
        i = 1; //AMEX
    }
    else if (cc_count == 22 || cc_count == 55 || cc_count == 51)
    {
        i = 2; //MASTER
    }
    else if (cc_count == 40 || cc_count == 41 || cc_count == 42)
    {
        i = 3; //VISA
    }
    else
    {
        i = 4; //INVALID
    }
    return i;
}

void    print_result(int sum, int type_cc)
{
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (type_cc == 1)
        {
            printf("AMEX\n");
        }
        else if (type_cc == 2)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("VISA\n");
        }
    }
}


int main(void)
{
    long   cc_num;
    int    sum;
    int    type_cc;

    do
    {
        cc_num = get_long("Number: "); //Asks for number and checks if it's a valid CC number
    }
    while (!(cc_check(cc_num)));
    sum = sum_cc(cc_num); //Makes sum to later check if it ends on 0
    type_cc = cc_type(cc_num); // Same as cc_check, but now returns a number associated with Type of CC
    print_result(sum, type_cc); //Checks to see if the SUM ends in 0, in which case it checks the type to Print name
    return 0;
}*/