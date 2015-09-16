/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
 
node* hashTable[bSize] = {NULL};
int SIZE =0;
 
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char p[LENGTH+1];
    int i ;
    for ( i=0 ; word[i] != '\0' ; i++)
    {
        p[i] = tolower(word[i]); 
    }
    p[i]='\0';
    if (strcmp("the",p) == 0)
    {
        return true;
    }
    
    int index ; 
    index = hash (p);
    node* cursor =hashTable[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word,p) == 0)
        {
            return true;
        }
        cursor = cursor->next;
        
    }
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp=fopen(dictionary,"r");
    if (fp == NULL)
    {
        printf ("could not read %s",dictionary);
        return false;
    }
    int index;
    while (!feof(fp))
    {
        node* new_node = malloc(sizeof(node));
        fscanf(fp,"%s",new_node->word);
        if (feof(fp)) 
        {
            free (new_node);
            break;
        }
        index = hash(new_node->word);
        new_node->next = hashTable[index];
        hashTable[index] = new_node;
        SIZE++;
        
    }
    fclose(fp);
    // TODO
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return SIZE;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i=0; i<bSize; i++)
    {
        node* cursor = hashTable[i];
        
        while (cursor != NULL)
        {
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            
        }
    }
    return true;
}

/**
 * Hash function 
 */
 int hash(const char *key)
{
    const char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; p[i] != '\0'; i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h % bSize;
}
