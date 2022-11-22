#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptor(string plaintxt, string key);
int check_key(string key);
int check_dup(string key);

int main(int argc, string argv[])
{
    string plaintxt;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (check_key(argv[1]))
    {
        printf("is not alpha\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (check_dup(argv[1]))
    {
        printf("is duplicated\n");
        return 1;
    }
    else
    {
        plaintxt = get_string("plaintext: ");
        encryptor(plaintxt, argv[1]);
        printf("\n");
        return 0;
    }
}

int check_dup(string key)
{
    for (int i = 0, j = 1; key[i + 1] != '\0'; i++, j = i + 1)
    {
        while (tolower(key[i]) != tolower(key[j]) && key[j] != '\0')
        {
            j++;
        }
        if (tolower(key[i]) == tolower(key[j]))
        {
            return 1;
        }
    }
    return 0;

}

int check_key(string key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!(isalpha(key[i])))
        {
            return 1;
        }

    }
    return 0;
}

void encryptor(string plaintxt, string key)
{
    string cyphertxt = "";
    string upper_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower_alpha = "abcdefghijklmnopqrstuvwxyz";
    int j;
    int i = 0;

    printf("ciphertext: ");
    while (plaintxt[i] != '\0')
    {
        j = 0;
        if (isupper(plaintxt[i]))
        {
            while (plaintxt[i] != upper_alpha[j])
            {
                j++;
            }
            printf("%c", toupper(key[j]));
            i++;
        }
        else if (islower(plaintxt[i]))
        {
            while (plaintxt[i] != lower_alpha[j])
            {
                j++;
            }
            printf("%c", tolower(key[j]));
            i++;
        }
        else
        {
            printf("%c", plaintxt[i]);
            i++;
        }
    }

}


