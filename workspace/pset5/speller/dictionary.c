/**
 * CS50 - PSET5 - user: linhobru
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

#define ALPHABETSIZE 27

typedef struct node
{
    bool is_word;
    struct node *children[ALPHABETSIZE];
} 
node;

node *root = NULL;

int num_of_words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

    node* next = root;
    
    int k = ALPHABETSIZE;

    for (int i = 0, len = strlen(word); i < len ; i++) // until (char) word[i] == '\0' 
    {
        // verify letter and transform in index from 0 to 26
        if (word[i] == '\'')
        {
            k = ALPHABETSIZE - 1;
        }
        else if (isalpha(word[i]))
        {
            k = tolower(word[i]) - 97;
        }
        
        if (next->children[k] == NULL)
        {
            return false;
        }
        else
        {
        next = next->children[k];   
        }
        
    }
    return next->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    
    char word[LENGTH];
    
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        unload();
        fclose(dict);
        return false;
    }
    
    while (fscanf(dict,"%s", word) != EOF)
    {
        node* now = root;
        int k = ALPHABETSIZE;

        for (int i = 0; word[i] != '\0'; i++) 
        {
            // verify letter and transform in index from 0 to 26
            if (word[i] == 39) // '\''
            {
                k = ALPHABETSIZE - 1;
            }
            else if (word[i] >= 97 && word[i] <= 122)
            {
                k = word[i] - 97;
            }
            /* else if (word[i] >= 65 && word[i] <= 90)
            {
                k = word[i] % 65;
            }*/ 
            else
            {
                fclose(dict);
                return false;               
            }
            
            if (now->children[k] == NULL)
            {
                node* new_node = malloc(sizeof(node));
                now->children[k] = new_node;
            }
            
            now = now->children[k];
            
            if (word[i + 1] == '\0')
            {
                now->is_word = true;
            } 
                

        }
        
        num_of_words++;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return num_of_words;
}
/**
 * Receives root at first and then each children to free.
 */
void unloadNode(node* next)
{
    // call unloadNode on every node in this node's children
    for(int i = 0; i < ALPHABETSIZE; i++)
    {
        if(next->children[i] != NULL)
        {
            unloadNode(next->children[i]);
        }
    }
    
    // once the children nodes are freed, free this node
    free(next);
}
/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unloadNode(root);
    return true;
}



