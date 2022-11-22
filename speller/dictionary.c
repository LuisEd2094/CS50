// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
char dict_word[LENGTH + 1];
unsigned int dict_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO


    int table_index = hash(word);

    node *check = table[table_index];

    while (check != NULL)
    {
        if (strcasecmp(check->word, word) == 0)
        {
            check = NULL;
            free(check);
            return true;
        }
        else
        {
            check = check->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return (toupper(word[0]) - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }
    while (fscanf(dict, "%s\n", dict_word) != EOF)
    {
        node *new_word = malloc(sizeof(node));

        strcpy(new_word->word, dict_word);

        int hash_index = hash(dict_word);

        if (table[hash_index] == NULL)
        {
            table[hash_index] = new_word;
            new_word->next = NULL;
        }
        else
        {
            new_word->next = table[hash_index];
            table[hash_index] = new_word;
        }
        dict_count++;

    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor;

        cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;

    }
    return true;

}
