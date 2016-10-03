#include "input.h"
#include "list.h"
#include "tree.h"

tree * maketree (list ** head, int strct) /* создает BST из списка */
{
	if (0 >= strct)
		return NULL;
	tree * l_tree = maketree(head, strct/2);
	
	tree * root = (tree *) calloc (1, sizeof(tree));
	root->name = (*head)->name;
	root->height = (*head)->height;
	root->weight = (*head)->weight;
	root->left = l_tree;
	*head = (*head)->next;
	root->right = maketree(head, strct - strct/2 - 1);
	return root;
}
int searchtree (tree * root, char * name) /* ищем студента в дереве, 0 если не нашли, иначе выводит данные */
{
	if (NULL == root)
	{
		return 0;	
	}
	else 
	{
		if (strcmp(name, root->name) == 0)
		{
			printf ("%s : height - %.1fsm, weight - %.2fkg\n\n", root->name, root->height, root->weight);
			return 1;
		}
		else
		{
			if (0 != searchtree(root->left, name))
				return 1;
			else 
			{
				if (0 != searchtree(root->right, name))
					return 1;
				else
				{
					return 0;
				}
			}
		}
	}
}
void deletetree (tree * root) /* удаляет дерево */
{
	if (NULL != root)
	{
		deletetree(root->left);
		deletetree(root->right);
		free(root);
	}
}