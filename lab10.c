#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
//Kevin Frazier
// 4/19/24
// Trie structure
struct Trie
{	
struct Trie* children[ALPHABET_SIZE];
int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            current->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            for (int j = 0; j < ALPHABET_SIZE; j++)
                current->children[index]->children[j] = NULL;
            current->children[index]->count = 0;
        }
        current = current->children[index];
    }
    current->count++;

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            return 0;
        current = current->children[index];
    }
    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
     if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        pTrie->children[i] = NULL;
    }
    pTrie->count = 0;
    return pTrie;
    
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int numWords;
    fscanf(file, "%d", &numWords);
    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = (char *)malloc(256 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }
    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary-1.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}


