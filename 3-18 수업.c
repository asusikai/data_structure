#include <stdio.h>

char stk[50];
int top = -1; 

int IsEmpty();
int IsFull();
char top_element();
void push(char n);
char pop();

int main()
{
	char input[100];
	
	scanf("%s", input);
	
	int i=0;
	char pop_element;
	
	while(input[i] != '\0')
	{
		if(input[i] == '*' || input[i] == '/')
		{
			if(input[i] == '+' || input[i] == '-')
			{
				pop_element = pop();
				printf("%c", pop_element);
				push(input[i]);
			}
			
			else
			{
				push(input[i]);
			}
		}
		
		else if(input[i] == '+' || input[i] == '-')
		{
			pop_element = pop();
			printf("%c", pop_element);
			push(input[i]);
		}
		
		else
		{
			printf("%c", input[i]);
			
		}
		
		
		i++;
	}
	
	while(!IsEmpty())
	{
		pop_element = pop();
		printf("%c", pop_element);
	}
	
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

char top_element()
{
	return stk[top];
}

void push(char n)
{
	if(!IsFull())
	{
		stk[++top] = n;
	}
}

char pop()
{
	if(!IsEmpty())
	{
		return stk[top--];
	}
}
