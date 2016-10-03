#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMBER_OF_CODES 256
#define LONG_LONG_INT_SIZE 64
#define CHAR_SIZE 8

typedef enum nodetype 
{
	LEAVE,
	NOTLEAVE
} nodetype;

typedef struct tree
{
	unsigned int value;
	struct tree * left;
	struct tree * right;
	struct tree * parent;
	nodetype is_leave;
	unsigned char symbol;
} tree;

typedef struct opened_list
{
	struct tree * data;
	struct opened_list * next;
	struct opened_list * previous;
} opened_list;

typedef struct table
{
	unsigned char symbol;
	char * code;
} table;

typedef struct buffer
{
	unsigned char byte;
	struct buffer * next;
} buffer;

tree ** maketree(FILE * input_file, int * symbolcount, long long int * charcount)
{
	unsigned char c = ' '; 
	int i = 0;
	int rc = 0;
	int frequencies[NUMBER_OF_CODES];
	int check = 0;
	long long int counter = 0;
	for (i = 0; i < NUMBER_OF_CODES; ++i)
		frequencies[i] = 0;
	while (1)  // collecting the frequences of all the symbols
	{
		rc = fread(&c, 1, 1, input_file);
		if (1 != rc)
			break;
		check = 1;
		++counter;
		if (0 == frequencies[(unsigned int)(c)])
		{
			(*symbolcount)++;
			printf("reading %c count %lld\n", (unsigned char)c, counter);
		}
		//printf("reading %c count %lld\n", (unsigned char)c, counter);
		frequencies[(unsigned int)(c)]++;
		(*charcount)++;
	}
	if (0 == check) //if the file is empty
		return NULL;
	tree ** leaves = (tree **) calloc (*symbolcount + 1, sizeof(tree *));
	int leaveindex = 0;
	for (i = 0; i < NUMBER_OF_CODES; ++i) //making an array of all the symbols as the leaves for our tree
	{
		if (0 != frequencies[i])
		{
			tree * newleave = (tree *) calloc (1, sizeof(tree));
			newleave->value = frequencies[i];
			newleave->symbol = (unsigned char)(i);
			newleave->is_leave = LEAVE;
			newleave->left = NULL;
			newleave->right = NULL;
			newleave->parent = NULL;
			leaves[leaveindex] = newleave;
			leaveindex++;
		}
	}
	//*charcount = leaveindex;
	if (1 == leaveindex) // if there is only one symbol in the file - create a root for it
	{
		tree * root = (tree *) calloc (1, sizeof(tree));
		root->value = leaves[0]->value;
		root->left = leaves[0];
		leaves[0]->parent = root;
		root->is_leave = NOTLEAVE;
		root->right = NULL;
		leaves[leaveindex] = root;
		return leaves;
	}
	else
	{
		opened_list * head = (opened_list *) calloc (1, sizeof(opened_list)); // creating an opened list of nodes to add them to the tree
		head->data = leaves[0];
		head->next = NULL;
		head->previous = NULL;
		opened_list * last = head;
		for (i = 1; i < leaveindex; ++i)
		{
			last->next = (opened_list *) calloc (1, sizeof(opened_list));
			last->next->next = NULL;
			last->next->previous = last;
			last->next->data = leaves[i];
			last = last->next;
		}
		int openednodes = leaveindex;
		while (1 != openednodes) //creating leaves parents
		{
			opened_list * code1 = NULL;// search for two symbols with minimal frequencies in the list
			opened_list * code2 = NULL;
			opened_list * start = head;
			for (i = 0; i < openednodes; ++i)
			{
				if (NULL == code1)
				{
					code1 = start;
				}
				else
				{
					if (NULL == code2)
					{	
						code2 = start;
					}
					else
					{
						if ((start->data->value < code1->data->value) && (start->data->value < code2->data->value))
						{
							if (code1->data->value < code2->data->value)
								code2 = start;
							else
								code1 = start;
						}
						else if (start->data->value < code1->data->value)
						{
							code1 = start;
						}
						else if (start->data->value < code2->data->value)
						{
							code2 = start;
						}
					}
				}
				start = start->next;			
			}
			if (NULL != code1->previous)
				code1->previous->next = code1->next; // deleting these symbols from the opened list
			if (NULL != code1->next)
				code1->next->previous = code1->previous;
			if (last == code1)
				last = last->previous;
			if (head == code1)
				head = head->next;
			code1->next = NULL;
			code1->previous = NULL;
			if (NULL != code2->previous)
				code2->previous->next = code2->next;
			if (NULL != code2->next)
				code2->next->previous = code2->previous;
			if (last == code2)
				last = last->previous;
			if (head == code2)
				head = head->next;
			code2->next = NULL;
			code2->previous = NULL;
			opened_list * newlast = (opened_list *) calloc (1, sizeof(opened_list));// creating a new part to the list
			newlast->previous = last;
			newlast->next = NULL;
			tree * newdata = (tree *) calloc (1, sizeof(tree)); // creating a node for the two minimal frequencies
			newdata->value = code1->data->value + code2->data->value;
			newdata->left = code1->data;
			newdata->right = code2->data;
			newdata->parent = NULL;
			newdata->is_leave = NOTLEAVE;
			newlast->data = newdata;
			code1->data->parent = newdata;
			code2->data->parent = newdata;
			if (NULL != last)
				last->next = newlast;
			if (NULL == head)
				head = newlast;
			last = newlast; // new last added
			if(code1->data->is_leave == LEAVE)
			{
				//printf("added symbol '%c'\n", code1->data->symbol);
			}
			if(code2->data->is_leave == LEAVE)
			{
				//printf("added symbol '%c'\n", code2->data->symbol);
			}
			free(code1);
			free(code2);
			openednodes--;
		}
		tree * root = head->data;
		free(head);
		leaves[leaveindex] = root;
		return leaves;
	}	
}
void getcode(tree * leave, char * code)
{
	tree * start = leave;
	if (NULL == start->parent)
	{
		code[0] = '0';
		return;
	}
	else
	{
		char * reversedcode = (char *) calloc (100, sizeof(char));
		while (NULL != start->parent)
		{
			if (start == start->parent->left)
				strcat(reversedcode, "0");
			else
				strcat(reversedcode, "1");
			start = start->parent;
		}
		int len = strlen(reversedcode);
		int i = 0;
		for (i = 0; len > 0; ++i)
		{
			code[i] = reversedcode[len - 1];
			len--;
		}
		free(reversedcode);
		return;
	}
}
void printtree(FILE * output_file, tree ** leaves, int leavescount)
{
	int i = 0;
	for (i = 0; i < leavescount; ++i)
	{
		char * code = (char *) calloc (100, sizeof(char));
		getcode(leaves[i], code);
		fprintf(output_file, "%c %d %s\n", (unsigned char)(leaves[i]->symbol), leaves[i]->value, code);
		free(code);
	}
	return;
}
void insertcounts(FILE * output_file, int symbolcount, long long int charcount) // insert symbolcount and charcount in output
{
	int  i = 0;
	int bit = 0;
	unsigned char cur_byte = 0;
	for (i = 0; i < CHAR_SIZE; ++i) // printing our file size as 8 symbols in output
	{
		cur_byte = (char)(charcount >> ((CHAR_SIZE - i - 1) * CHAR_SIZE));
		fprintf(output_file, "%c", cur_byte);
		cur_byte = 0;
	}
	cur_byte = (char)symbolcount - 1; // printing our alphabet size (amount of leaves the same) in output
	fprintf(output_file, "%c", cur_byte);
	return;
}
void inserttree(FILE * output_file, tree * root, unsigned char * cur_byte, int * cur_index, int * symbolcount) // insert tree in output
{	
	if (NULL == root)
		return;
	if ((NULL == root->left) && (NULL == root->right))
	{
		int mask = 1 << (CHAR_SIZE - 1 - *cur_index);
		*cur_byte = *cur_byte | mask;
		(*cur_index)++;
		if (CHAR_SIZE == *cur_index)
		{
			fprintf(output_file, "%c", *cur_byte);
			*cur_byte = 0;
			*cur_index = 0;
		}
		if (0 == *cur_index)
		{
			*cur_byte = root->symbol;
			fprintf(output_file, "%c", *cur_byte);
			*cur_byte = 0;
		}
		else
		{
			unsigned char temp = root->symbol >> *cur_index;
			*cur_byte = *cur_byte | temp;
			fprintf(output_file, "%c", *cur_byte);
			*cur_byte = 0;
			temp = root->symbol << (CHAR_SIZE - *cur_index);
			*cur_byte = *cur_byte | temp;
		}
		(*symbolcount)--;
		if (0 == *symbolcount)
		{
			fprintf(output_file, "%c", *cur_byte);
			*cur_byte = 0;
			*cur_index = 0;
		}
		return;
	}
	else
	{
		(*cur_index)++;
		if (CHAR_SIZE == *cur_index)
		{
			fprintf(output_file, "%c", *cur_byte);
			*cur_byte = 0;
			*cur_index = 0;
		}
		inserttree(output_file, root->left, cur_byte, cur_index, symbolcount);
		inserttree(output_file, root->right, cur_byte, cur_index, symbolcount);
		return;
	}
}
void insertcode(FILE * input_file, FILE * output_file, table ** codes, int symbolcount, int charcount)
{
	unsigned char cur_byte = 0;
	int cur_byte_index = 0;
	unsigned char symbol = ' ';
	int rc = 0;
	long long int counter = 0;
	int buffer_index = 0;
	buffer * first = NULL;
	buffer * last = NULL;
	while (1)  // starting to code 
	{
		rc = fread(&symbol, 1, 1, input_file);
		if (1 != rc)
			break;
		int i = 0;
		char * code_string = NULL; // inspecting for the code of the symbol
		for (i = 0; i < symbolcount; ++i)  
		{
			if (codes[i]->symbol == symbol)
			{
				code_string = codes[i]->code;
				break;
			}
		}
		int len = strlen(code_string); // the length of the code
		long long int code = 0;
		for (i = 0; i < len; ++i) // converting the code string into int-typed code       ---------   REMAKE!!!
		{
			if ('1' == code_string[i])
			{
				long long int mask = 1 << (len - i - 1);
				code = code | mask;
			}
		}
		while (len > 0)
		{
			if (CHAR_SIZE >= len + cur_byte_index) // if current symbol code can get place in the current byte
			{
				int mask = (int)(code << (CHAR_SIZE - len - cur_byte_index));
				cur_byte = cur_byte | mask;
				cur_byte_index += len;
				if (CHAR_SIZE == cur_byte_index) // if current byte is full - print it in the output
				{
					if (NULL == first)
					{
						first = (buffer *) calloc (1, sizeof(buffer));
						first->byte = cur_byte;
						first->next = NULL;
						last = first;
						buffer_index++;
					}
					else
					{
						buffer * new = (buffer *) calloc (1, sizeof(buffer));
						new->byte = cur_byte;
						new->next = NULL;
						last->next = new;
						last = new;
						buffer_index++;
					}
					cur_byte = 0;
					cur_byte_index = 0;
				}
				len = 0;
			}
			else // if current symbol code can't get place in the current byte
			{
				int part_len = CHAR_SIZE - cur_byte_index;
				long long int part1 = code >> (len - part_len);
				cur_byte = cur_byte | (int)part1;
				if (NULL == first)
				{
					first = (buffer *) calloc (1, sizeof(buffer));
					first->byte = cur_byte;
					first->next = NULL;
					last = first;
					buffer_index++;
				}
				else
				{
					buffer * new = (buffer *) calloc (1, sizeof(buffer));
					new->byte = cur_byte;
					new->next = NULL;
					last->next = new;
					last = new;
					buffer_index++;
				}
				cur_byte = 0;
				cur_byte_index = 0;
				len -= part_len;
				long long int mask = 0;
				mask = pow(2, len) - 1;
				code = code & mask; //cutting the code
			}
		}
		++counter;
		if (counter == charcount) // if it's the last symbol of the file
		{
			if (NULL == first)
			{
				first = (buffer *) calloc (1, sizeof(buffer));
				first->byte = cur_byte;
				first->next = NULL;
				last = first;
				buffer_index++;
			}
			else
			{
				buffer * new = (buffer *) calloc (1, sizeof(buffer));
				new->byte = cur_byte;
				new->next = NULL;
				last->next = new;
				last = new;
				buffer_index++;
			}
			cur_byte = 0;
			cur_byte_index = 0;	
		}
		
		//printf("wrote %c, count %lld\n", (unsigned char)symbol, counter);
	}
	int  i = 0;
	for (i = 0; i < buffer_index; ++i)
	{
		fprintf(output_file, "%c", first->byte);
		buffer * temp = first;
		first = first->next;
		free(temp);
	}
}
table ** createtable (tree ** leaves, int leavescount)
{
	table ** main = (table **) calloc (leavescount, sizeof(table*));
	int i = 0;
	for (i = 0; i < leavescount; ++i)
	{
		main[i] = (table *) calloc (1, sizeof(table));
		main[i]->symbol = leaves[i]->symbol;
		char * code = (char *) calloc (100, sizeof(char));
		getcode(leaves[i], code);
		main[i]->code = code;
	}
	return main;
}
void deletetree(tree * root)
{
	if (NULL == root)
		return;
	deletetree(root->left);
	deletetree(root->right);
	free(root);
	return;
}
void deletetable(table ** codes, int symbolcount)
{
	int i = 0;
	for (i = 0; i < symbolcount; ++i)
	{
		free(codes[i]->code);
		free(codes[i]);
	}
	free(codes);
}
int main(int argc, char ** argv)
{
	if ((argc != 4) || (NULL == argv[1]) || (NULL == argv[2]) || (NULL == argv[3]))
	{
		printf ("Put in the input file as the first arg, output file as the second, tree file as the third\n");
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
    tree ** root_and_leaves = maketree(input_file, &symbolcount, &charcount);
    tree * hufftree = root_and_leaves[symbolcount];
    if (NULL == hufftree)
    {
     	printf("Input file is empty\n");
     	deletetree(hufftree);
     	fclose(input_file);
     	return -1;
    }
    fclose(input_file);
    FILE * tree_file = fopen(argv[3], "wb");
    if (NULL == tree_file)
    {
    	deletetree(hufftree);
    	printf("Can't open tree file\n");
    	return -1;
    }
    printtree(tree_file, root_and_leaves, symbolcount);
    fclose(tree_file);
    FILE * output_file = fopen(argv[2], "wb");
    if (NULL == output_file)
    {
    	deletetree(hufftree);
    	printf("Can't open tree file\n");
    	return -1;
    }
    insertcounts(output_file, symbolcount, charcount);
    printf("File size and tree size inserted\n");
    unsigned char cur_byte = 0;
	int cur_index = 0;
	int tempcount = symbolcount;
	inserttree(output_file, hufftree, &cur_byte, &cur_index, &tempcount);
	printf("Tree inserted\n");
	table ** codes = createtable(root_and_leaves, symbolcount);
	deletetree(hufftree);
	free(root_and_leaves);
	input_file = fopen (argv[1], "rb");
	insertcode(input_file, output_file, codes, symbolcount, charcount);
	printf("Code inserted\nAlphabet symbols amount %d\n", symbolcount);
    printf("Chars amount %lld\n", charcount);
    printf("File compressed.\n");
	fclose(output_file);
	fclose(input_file);
	deletetable(codes, symbolcount);
	return 0;
}