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

// size of dictionary
int book_size;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int wlen = strlen(word);
    node* trav = root;
    
    for (int i = 1; i < wlen; i++)
    {
        int index = (word[i - 1] == '\'') ? 26 : tolower(word[i - 1]) - 'a';
        
        if (trav->children[index] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->children[index];
        }
    }
    
    int index = (word[wlen - 1] == '\'') ? 26 : tolower(word[wlen - 1]) - 'a';
    
    if (trav->children[index] == NULL)
    {
        return false;
    }
    
    trav = trav->children[index];
    if (trav->is_word != true)
    {
        
        return false;
    }
    return true;  
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool load(const char* dictionary)
{
    
    // open the dictionary
    FILE* book = fopen(dictionary, "r");
    book_size = 0;
    if (book == NULL)
    {
        printf("Could not open the dictionary file.\n");
        return false;
    }
    
    char word[LENGTH + 1];
    
    root = malloc(sizeof(node));
    node* trav = root;
    
    for(int k = 0; k < 27; k++)
    {
        trav->children[k] = NULL;
    }
    
    if (trav == NULL)
    {
        return false;
    }
    
    for (int chr = fgetc(book), i = 0; chr != EOF; chr = fgetc(book))
    {
        if (chr != '\n')
        {
            word[i] = tolower(chr);
            i++;
        }
        else
        {
            word[i] = '\0';
            // add words to dictionary
            
            int wlen = strlen(word);
            
            
            
            // int flag = 0;
            
            for(int j = 0; j < wlen; j++)
            {
                int index = (word[j] == '\'') ? 26 : word[j] - 'a';
                node* newNode = NULL;
                if (trav->children[index] == NULL)
                {
                    newNode = malloc(sizeof(node));
                    
                    for(int k = 0; k < 27; k++)
                    {
                        newNode->children[k] = NULL;
                    }
                }
                else
                {
                    newNode = trav->children[index];
                }
                
                trav->children[index] = newNode;
                trav = newNode;
                // printf("%d ", index);
            }
            // assign is_word as true;
            trav->is_word = true;
            trav = root;
            // printf("%s\n", word);
            i = 0;
            book_size++;
        }
    }
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return book_size;
}

void freeit(node* ptr)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptr->children[i] != NULL)
        {
            freeit(ptr->children[i]);
        }
    }
    free(ptr);
    return;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

    freeit(root);
    return true;
}