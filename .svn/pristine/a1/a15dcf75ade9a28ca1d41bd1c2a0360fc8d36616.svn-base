#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMBER_OF_CODES 256
#define LONG_LONG_INT_SIZE 64
#define CHAR_SIZE 8
#define INT_SIZE 32

typedef enum nodetype 
{
	LEAVE,
	NOTLEAVE
} nodetype;

typedef struct tree
{
	struct tree * left;
	struct tree * right;
	nodetype is_leave;
	unsigned char symbol;
} tree;

typedef struct bitstream
{
	FILE * file;
	unsigned char cur_letter;
	int cur_bit_index;
} bitstream;

int getcounts(FILE * input_file, int * symbolcount, long long int * charcount) // get the amount of symbols in the code, and capacity of the alphabet
{
	int i = 0;
	int counted = 0;
	unsigned char c = 0;
	int rc = 0;
	while (1) // getting the charcount
	{
		if (LONG_LONG_INT_SIZE/CHAR_SIZE == counted)
			break;
		rc = fread(&c, 1, 1, input_file);
		if (1 != rc) 
			return 0;
		long long int mask = (long long int)(c) << ((LONG_LONG_INT_SIZE/CHAR_SIZE - counted - 1) * CHAR_SIZE);
		*charcount = *charcount | mask;
		counted++;
	}
	rc = fread(&c, 1, 1, input_file); // getting the symbolcount
	if (1 != rc) 
		return 0;
	if (*charcount < (long long int)c)
		return 0;
	*symbolcount = (int) c + 1;
	return 1;
}
unsigned char getbit(bitstream * bs)
{
	if (0 == bs->cur_bit_index % CHAR_SIZE)
	{
		int rc = 0;
		unsigned char c = 0;
		rc = fread(&c, 1, 1, bs->file);
		if (1 != rc) 
			return -1;
		bs->cur_bit_index = 0;
		bs->cur_letter = c;
		unsigned char mask = pow(2, CHAR_SIZE - bs->cur_bit_index - 1);
		unsigned char bit = bs->cur_letter & mask;
		bit = bit >> (CHAR_SIZE - bs->cur_bit_index - 1);
		bs->cur_bit_index++;
		return bit;
	}
	else
	{
		unsigned char mask = pow(2, CHAR_SIZE - bs->cur_bit_index - 1);
		unsigned char bit = bs->cur_letter & mask;
		bit = bit >> (CHAR_SIZE - bs->cur_bit_index - 1);
		bs->cur_bit_index++;
		return bit;
	}
}
tree * gettree(bitstream * bs)
{
	unsigned char bit = getbit(bs);
	if (-1 == bit)
		return NULL;
	//printf("%d bit\n", bit);
	if (0 == bit)
	{
		tree * root = (tree *) calloc (1, sizeof(tree));
		root->is_leave = NOTLEAVE;
		root->left = gettree(bs);
		root->right = gettree(bs);
		if ((NULL == root->left) || (NULL == root->right))
		{
			free(root);
			return NULL;
		}
		return root;
	}
	else
	{
		tree * root = (tree *) calloc (1, sizeof(tree));
		root->is_leave = LEAVE;
		root->left = NULL;
		root->right = NULL;
		root->symbol = 0;
		int i = 0;
		for (i = 0; i < CHAR_SIZE; ++i)
		{
			unsigned char b = getbit(bs);
			if (-1 == b)
			{
				free(root);
				return NULL;
			}
			unsigned char mask = pow(2, CHAR_SIZE - i - 1) * b;
			root->symbol = root->symbol | mask;
		}
		printf("Added leave %c\n", root->symbol);
		return root;
	}
}
int getfile(bitstream * bs, FILE * output_file, tree * root, long long int charcount)
{
	tree * start = root;
	long long int decoded = 0;
	if (1 == charcount)
	{
		fprintf(output_file, "%c", root->left->symbol);
		return 1;
	}
	while (decoded < charcount)
	{
		unsigned char bit = getbit(bs);
		if (-1 == bit)
			return 0;
		if (0 == bit)
			start = start->left;
		else
			start = start->right;
		if (start->is_leave == LEAVE)
		{
			fprintf(output_file, "%c", start->symbol);
			start = root;
			decoded++;
			continue;
		}
		else
			continue;
	}
	return decoded;
}
int main(int argc, char ** argv)
{
	if ((argc != 3) || (NULL == argv[1]) || (NULL == argv[2]))
	{
		printf ("Put in the input file as the first arg, output file as the second\n");
       	return -1;
	}
    FILE* input_file = fopen (argv[1], "rb");
    if (NULL == input_file)
    {
    	printf("Can't open input file\n");
    	return -1;
    }
    int symbolcount = 0;
    long long int charcount = 0;
   	if (0 == getcounts(input_file, &symbolcount, &charcount))
   	{
   		printf("Wrong file format : no counts were found or the alphabet capacity is larger than amount of the chars in code\n");
   		fclose(input_file);
   		return -1;
   	}
   	printf("Predicted counts:\nAlphabet capacity %d\nLength of the code %lld\n", symbolcount, charcount);
   	bitstream * bs = (bitstream *) calloc (1, sizeof(bitstream));
   	bs->file = input_file;
   	bs->cur_letter = 0;
   	bs->cur_bit_index = 0;
   	tree * hufftree = gettree(bs);
   	while (bs->cur_bit_index < CHAR_SIZE)
   	{	
   		unsigned int b = getbit(bs);
   		bs->cur_bit_index++;
   	}
   	bs->cur_bit_index = 0;
   	if (NULL == hufftree)
   	{
   		printf("Problem with decoding of the tree\n");
   		free(bs);
   		fclose(input_file);
   	}
   	printf("Tree decoded.\n");
   	FILE * output_file = fopen(argv[2], "wb");
   	long long int result = getfile(bs, output_file, hufftree, charcount);
   	printf("File decoded. Total char amount : %lld symbols\n", result);
   
	return 0;
}