/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
// libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// counter for words loaded
int wordsloaded = 0;

// declare struct for node
typedef struct node
{
    bool is_word;
    struct node* children[27];
} node;

// declare the first node* called root     
node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // declare a node* that acts like a cursor
  // start off by setting to be root
    node* current = root;
    
    int i = 0;

    while(word[i] != '\0')
    {
        // declare a character to take elements of the word
        char input = word[i];
        
        // account for apostrophes
        if (word[i] == '\'')
        {
            input = 'z' + 1;
        }
	    
        // declare an integer as an index for later
        int newnum = tolower(input) - 'a';
       
        // if the child associated with newnum is not null, go there
        if (current->children[newnum] != NULL)
        {
            current = current->children[newnum];
            i++;
	    }  
	    
        // if it is null, return false
        else
        {
            return false;
         }    
    }
    
    // if at the end, it's a stored word, return true.
    if (current->is_word == true)
    {
        return true;
    }
    
    // else return false
    return false;

}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionary file and check if null
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // allocate memory for the first node, and point root there
    root = malloc(sizeof(node));
    int character = 0;
    
    // declare a cursor
    node* current = NULL;

    while(fgetc(dict) != EOF)
    {
        fseek(dict, -1, SEEK_CUR);
	    
        // Set the cursor to the root
        current = root;

        for (character = fgetc(dict); character != '\n'; 
                character = fgetc(dict))
        {    
            // Check for apostrophes
            if (character == '\'')
            {
                // Set it to one past the highest letter, z
                character = 'z' + 1;
            }
	    
            // Check if the character exists in the trie
            if (current->children[character - 'a'] == NULL)
            {
                // If the character does not exist, malloc a new node
                current->children[character - 'a'] = malloc(sizeof(node));
		
                // go to the new node
                current = current->children[character - 'a'];
	        }
	        else
            {
                // go to the node that is already present
                current = current->children[character - 'a'];
	        }
	    }
	    
        // at the end, call it a word, and increment number of words loaded
        current->is_word = true;
        wordsloaded++;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded.
 * Else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordsloaded;
}

/**
 * Unloads dictionary from memory. Takes a node* as input. 
 * Returns true if successful else false.
 */
bool freeNode(node* thisNode)
{
  // free each of the children if its not NULL
    for(int j = 0; j < 27; j++)
    {
        if (thisNode->children[j] != NULL)
        {
            freeNode(thisNode->children[j]);  
        }      
	}

    // then free this node
    free(thisNode);
    return true;
}

/**
 * Unloads dictionary from memory by calling freeNode. 
 * Returns true if successful else false.
 */
bool unload(void)
{
  // call a new function freeNode to do this, starting with root
    return freeNode(root);
}
