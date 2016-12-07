/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// define the node structure
typedef struct node
{
    bool is_word;
    struct node* children[27];
} node;

// define root;
node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    
    
    return false;   // mispelled
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool load(const char* dictionary)
{
    // TODO
    // open the dictionary
    FILE* book = fopen(dictionary, "r");
    
    if (book == NULL)
    {
        printf("Could not open the dictionary file.\n");
        return false;
    }
    
    char word[LENGTH + 1];
    
    root = malloc(sizeof(node));
    node* trav = root;
    
    if(trav == NULL)
    {
        return false;
    }
    
    for (int c = fgetc(book), i = 0; c != EOF; c = fgetc(book))
    {
            if(c != '\n')
            {
                word[i] = tolower(c);
                i++;
            }
            else
            {
                word[i] = '\0';
                // add words to dictionary
                
                int wlen = strlen(word);
                
                
                for(int k = 0; k < 27; k++)
                {
                    trav -> children[k] = NULL;
                }
                
                // int flag = 0;
                
                for(int j = 0; j < wlen; j++)
                {
                    int index = (word[j] == '\'')?26:word[j] - 'a';
                    node* newNode = NULL;
                    if(trav -> children[index] == NULL)
                    {
                        newNode = malloc(sizeof(node));
                        for(int k = 0; k < 27; k++)
                        {
                            newNode -> children[k] = NULL;
                        }
                    }
                    else
                    {
                        newNode = trav-> children[index];
                    }
                    
                    trav -> children[index] = newNode;
                    trav = newNode;
                    // printf("%d ", index);
                }
                // assign is_word as true;
                trav -> is_word = true;
                trav = root;
                printf("%s\n", word);
                i = 0;
            }
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
