#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stk[50];
int top = -1; 

int IsEmpty();
int IsFull();
int top_element();
void push(int n);
int pop();

int c2i(char c);

int main()
{
	char input[100];
	
	//scanf("%s", input);
	strcpy(input,"823*4-+2/");
	//strcpy(input,"77*");

	printf("input : %s\n", input);

	int i=0;
	int pop_element;
	int j;
	while(input[i] != '\0')
	{
		for(j=0; j<=top; j++)
		{
			printf("stk[%d] : %d\n",j,stk[j]);
		}
		printf("============\n");
		if(input[i] == '*')
		{
			pop_element = pop();
			pop_element =pop_element * pop();
			push(pop_element);
		}
		else if(input[i] == '/')
		{
			pop_element = pop();
			pop_element =pop()/pop_element;
			push(pop_element);
		}
		else if(input[i] == '+')
		{
			pop_element = pop();
			pop_element =pop_element+pop();
			push(pop_element);
		}
		
		else if(input[i] == '-')
		{
			pop_element = pop();
			pop_element =pop()-pop_element;
			push(pop_element);
		}

		else
		{
			push(c2i(input[i]));
			//printf("%d", stk[top]);
		}

		i++;
	}

	printf("output: %d\n", stk[0]);
	
	return 0;
}

int IsEmpty()
{
	if(top == -1)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}

int IsFull()
{
	if(top == 49)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}	
}

int top_element()
{
	return stk[top];
}

void push(int n)
{
	if(!IsFull())
	{
		stk[++top] = n;
	}
}

int pop()
{
	if(!IsEmpty())
	{
		return stk[top--];
	}
}

int c2i(char c)
{
	return (c-'0');
}