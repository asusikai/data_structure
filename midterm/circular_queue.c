// 원형 큐 안에 딜리트 큐 구현 

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int que[SIZE];

void en_q(int n);
int de_q();
void print_q();

int front = 0, rear = 0;

int main()
{
	en_q(1);
	en_q(2);
	en_q(3);
	en_q(4);
	en_q(5);
	en_q(6);
	print_q();
	
	printf("de_q : %d\n",de_q());
	printf("de_q : %d\n",de_q());
	printf("de_q : %d\n",de_q());
	print_q();
	
	en_q(5);
	en_q(6);
	en_q(7);
	
	print_q();
	
	
}

void en_q(int n)
{
	if(rear+1 == front || (rear > front && rear-front == SIZE-1))
	{
		printf("queue is full.\n");
	}
	
	else
	{
		if(front <= rear)
		{
			if(rear+1 == SIZE)
			{
				rear = 0;
				que[rear] = n;
			}
			
			else
			{
				que[++rear] = n;
			}
		}
		else
		{
			que[++rear] = n;
		}
	}
}

int de_q()
{
	if(front == rear)
	{
		printf("queue is empty.\n");
	}
	
	else
	{
		if(front+1 == SIZE)
		{
			front = 0;
			return que[front];
		}
		
		else
		{
			return que[++front];
		}
	}
}

void print_q()
{
	int i;
	if(front < rear)
	{
		for(i=front+1; i<rear+1; i++)
		{
			printf("%d\n", que[i]);
		}
	}
	
	else
	{
		for(i=front+1; i<SIZE; i++)
		{
			printf("%d\n", que[i]);
		}
		
		for(i = 0; i<rear+1; i++)
		{
			printf("%d\n",que[i]);
		}
	}
}
