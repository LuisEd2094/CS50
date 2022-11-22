#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string str);
int count_words(string str);
int count_sentences(string str);
int get_reading_grade(int l, int w, int s);
void print_grade(int index);

int main(void)
{
    int letters;
    int words = 0;
    int sentences = 0;
    int index = 0;

    string text = get_string("Insert Text: ");

    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    index = get_reading_grade(letters, words, sentences);
    print_grade(index);
    return 0;

}
void print_grade(int index)
{
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}


int get_reading_grade(int l, int w, int s)
{
    float avr_l;
    float avr_w;
    float index;

    avr_l = (((float)l / w) * 100);
    avr_w = (((float)s / w) * 100);
    index = (0.0588 * avr_l) - (0.296 * avr_w) - 15.8;
    return ((int)roundf(index));
}

int count_sentences(string str)
{
    int i;
    int n;

    i = 0;
    n = 0;

    while (str[i] != '\0')
    {
        if (str[i] != '.' && str[i] != '?' && str[i] != '!'  && str[i])
        {
            while (str[i] != '.' && str[i] != '?' && str[i] != '!' && str[i] != '\0')
            {
                i++;
            }
            if (str[i] == '?' && str[i + 1] == '"')
            {
                i++;
            }
            else
            {
                n++;
            }
        }
        else
        {
            i++;
        }

    }
    return n;
}


int count_words(string str)
{
    int i;
    int n;

    i = 0;
    n = 0;

    while (str[i] != '\0')
    {
        if (str[i] != ' ')
        {
            while (str[i] != ' ' && str[i] != '\0')
            {
                i++;
            }
            n++;
        }
        else
        {
            i++;
        }

    }
    return n;
}

int count_letters(string str)
{
    int i;
    int n;

    i = 0;
    n = 0;

    while (str[i] != '\0')
    {
        if (isalpha(str[i]))
        {
            n++;
            i++;
        }
        else
        {
            i++;
        }

    }
    return n;
}