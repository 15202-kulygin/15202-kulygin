#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum operation {
    OP_ADD,
    OP_SUB,
    OP_MPL,
    OP_DIV,
    OP_EXP
};

enum bracket {
    BR_OPEN, BR_CLOSE
};

enum type {
    DIGIT, OPERATION, BRACKET
};

typedef struct stack {
    union {
        enum operation o;
        enum bracket b;
    } data;
    int is_op; // 1 если операция
    struct stack * next;
} stack;

typedef struct rpnstack {
    int val;
    struct rpnstack * next;
} rpnstack;

typedef struct token {
    union
    {
    enum operation o;
    enum bracket b;
    int digit;
    } data;
      enum type t;
} token;

void pull (stack ** last, token ** out, int * tokencount)
{
    if((*last)->is_op == 1)
    {
        out[*tokencount]->t = OPERATION;
        out[*tokencount]->data.o = (*last)->data.o;
        (*tokencount)++;
     }
     stack * tmp = (*last);
     (*last) = (*last)->next;
     free(tmp);
 }

void push (stack ** last, token * tk)
{
     stack * snew = (stack *) calloc (1, sizeof(stack));
     snew->next = (*last);
     if (tk->t == BRACKET)
     {
         snew->is_op = 0;
         snew->data.b = BR_OPEN;
     }
     else
     {
         snew->is_op = 1;
         if (tk->data.o == OP_ADD)
             snew->data.o = OP_ADD;
         if (tk->data.o == OP_SUB)
             snew->data.o = OP_SUB;
         if (tk->data.o == OP_MPL)
             snew->data.o = OP_MPL;
         if (tk->data.o == OP_DIV)
             snew->data.o = OP_DIV;
         if (tk->data.o == OP_EXP)
             snew->data.o = OP_EXP;
     }
     (*last) = snew;
     snew = NULL;
}

int pullrpn (rpnstack ** last, int * pulled)
{
	if (NULL == (*last))
		return -1;
    *pulled = (*last)->val;
    rpnstack * temp = *last;
    *last = (*last)->next;
    free(temp);  
    return 0;
}

void pushrpn (rpnstack ** last, int value)
{
    rpnstack * temp = (rpnstack *) calloc (1, sizeof(rpnstack));
    temp->next = (*last);
    temp->val = value;
    (*last) = temp;
    temp = NULL;
}

void printtoken(token * a)
{
    if (a->t == DIGIT)
        printf ("%d ", a->data.digit);
    if (a->t == OPERATION)
    {
        if (a->data.o == OP_ADD)
            printf("+ ");
        if (a->data.o == OP_SUB)
            printf("- ");
        if (a->data.o == OP_MPL)
            printf("* ");
        if (a->data.o == OP_DIV)
            printf("/ ");
        if (a->data.o == OP_EXP)
            printf("^ ");
    }
    if (a->t == BRACKET)
    {
        if (a->data.b == BR_CLOSE)
            printf(") ");
        if (a->data.b == BR_OPEN)
            printf("( ");
    }
}

token * next_token (char * in, int * pos)
{
    int len = strlen(in);
    if (0 == len)
        return NULL;
    token * tk = (token *) calloc (1, sizeof(token));
    while ((' ' == in[*pos]) && (*pos < len))
        ++(*pos);
    if ((!isdigit(in[*pos])) && (in[*pos] != '+') && (in[*pos] != '-') && (in[*pos] != '*') && (in[*pos] != '/') && (in[*pos] != '^') && (in[*pos] != '(') && (in[*pos] != ')'))
        return NULL;
    if (*pos == len)
        return NULL;
    if (isdigit(in[*pos]))
    {
        tk->t = DIGIT;
        char * num = (char *) calloc (20, sizeof(char));
        int j = 0;
        while ((isdigit(in[*pos])) && (*pos < len))
        {
            num[j] = in[*pos];
            ++(*pos);
            ++j;
        }
        tk->data.digit = atoi(num);
        free (num);
    }
    else if ((in[*pos] == '+') || (in[*pos] == '-') || (in[*pos] == '*') || (in[*pos] == '/') || (in[*pos] == '^'))
    {
        tk->t = OPERATION;
        if (in[*pos] == '+')
            tk->data.o = OP_ADD;
        if (in[*pos] == '-')
            tk->data.o = OP_SUB;
        if (in[*pos] == '*')
            tk->data.o = OP_MPL;
        if (in[*pos] == '/')
            tk->data.o = OP_DIV;
        if (in[*pos] == '^')
            tk->data.o = OP_EXP;
        ++(*pos);
    }
    else if ((in[*pos] == '(') || (in[*pos] == ')'))
    {
        tk->t = BRACKET;
        if (in[*pos] == '(')
            tk->data.b = BR_OPEN;
        else
            tk->data.b = BR_CLOSE;
        ++(*pos);
    }
    return tk;
}

int makerpn (char * in, token ** out, int * tokencount)
{
    int pos = 0;
    token * tk = NULL;
    stack * last = NULL;
    int bracketbalance = 0;
     while (1)
     {
         tk = next_token(in, &pos);
         if (NULL == tk)
             break;
        else if (tk->t == DIGIT)
         {
             out[*tokencount] = tk;
             (*tokencount)++;
         }
         else if (tk->t == OPERATION)
         {
             if ((tk->data.o == OP_ADD) || (tk->data.o == OP_SUB))
                 while ((NULL != last) && (last->is_op == 1))
                     pull(&last, out, tokencount);
             else if ((tk->data.o == OP_MPL) || (tk->data.o == OP_DIV))
                 while ((NULL != last) && (last->is_op == 1) && ((last->data.o == OP_MPL) || (last->data.o == OP_DIV) ||(last->data.o == OP_EXP)))
                     pull(&last, out, tokencount);
             else if (tk->data.o == OP_EXP)
                 while ((NULL != last) && (last->is_op == 1) && (last->data.o == OP_EXP))
                     pull(&last, out, tokencount);
             push(&last, tk);
         }
         else if (tk->t == BRACKET)
         {
             if (tk->data.b == BR_OPEN)
                 {
                     push(&last, tk);
                     bracketbalance++;
                 }
             else if (tk->data.b == BR_CLOSE)
             {
                 bracketbalance--;
                 int check = 0;
                 while (NULL != last)
                 {
                     if (last->is_op == 0)
                     {
                         check = 1;
                         pull(&last, out, tokencount);
                         break;
                     }
                     else
                         pull(&last, out, tokencount);
                 }
                 if (0 == check)
                     return 0;
             }
         }
    }
    if (0 != bracketbalance)
        return 0;
    while (NULL != last)
        pull(&last, out, tokencount);

    return 1;
}

void countrpn(token ** out, int tokencount)
{
    rpnstack * last = NULL;
    int i = 0;
    while (i < tokencount)
    {
        if (out[i]->t == DIGIT)
            pushrpn(&last, out[i]->data.digit);
        else
        {
            int  y = 0;
            int  x = 0;
            if ((-1 == pullrpn(&last, &y)) || (-1 == pullrpn(&last, &x)))
            {	
            	printf("Not enough arguments in rpn to count\n");
            	return;
            }
            int result;
            if (out[i]->data.o == OP_ADD)
                result = x + y;
            else if (out[i]->data.o == OP_SUB)
                result = x - y;
            else if (out[i]->data.o == OP_MPL)
            { 
                result = x * y;
            }
            else if (out[i]->data.o == OP_DIV)
            {
                if (0 == y)
                {
                    printf("Unable to do: division by zero\n");
                    return;
                }
                else
                    result = x / y;
            }
            else if (out[i]->data.o == OP_EXP)
            {     if ((0 == x) && (0 == y))
                {
                    printf("Unable to do: 0 in 0 exponent\n");
                    return;
                }
                else
                result = pow(x, y);
            }
            pushrpn(&last, result);
        }
        ++i;
    }
    printf("Counted from RPN : %d\n", last->val);
    return;
}

int main ()
{
    char * in = (char *) calloc (50, sizeof(char));
    token ** out = (token **) calloc(50, sizeof(token *));
    int i = 0;
    for (i = 0; i < 50; ++i)
        out[i] = (token *) calloc (1, sizeof(token));
    printf("Print expression to convert from infix to rpn and count\n");
    gets(in);
    int tokencount = 0;
    if (makerpn(in, out, &tokencount))
    {
        printf("RPN: ");
        int a = 0;
        for (a = 0; a < tokencount; ++a)
        {
            printtoken(out[a]);
        }
        printf("\n");
    }
    else
    {
        printf("WRONG BRACKETS\n");
        return -1;
    }
    countrpn(out, tokencount);
    free(in);
    free(out);
    return 0;
}