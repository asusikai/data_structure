#include <stdio.h>
#include <stdlib.h>

typedef struct list_q* q_ptr;

typedef struct list_q{
	int data;
	q_ptr next;
}list_q;

q_ptr front = NULL;
q_ptr rear = NULL;

void en_q(int data);
int de_q();

void print_q(q_ptr p);

int main()
{
	en_q(99);
	en_q(2);
	en_q(3);
	en_q(4);
	
	print_q(front);
	
	printf("%d\n", de_q());
	printf("%d\n", de_q());
	printf("%d\n", de_q());
	printf("%d\n", de_q());
	printf("%d\n", de_q());
	printf("%d\n", de_q());
		
	en_q(6);
	en_q(7);
	en_q(8);
	en_q(9);
	
	
	print_q(front);
	print_q(front);
	
}

void en_q(int data)
{
	if(front == NULL)
	{
		q_ptr new_q = (q_ptr)malloc(sizeof(list_q));
		new_q->data = data;
		new_q->next = NULL;
		
		rear = new_q;
		front = rear;
	}
	
	else
	{
		q_ptr new_q = (q_ptr)malloc(sizeof(list_q));
		new_q->data = data;
		new_q->next = NULL;
		
		rear->next = new_q;
		rear = new_q;		
	}
}

int de_q()
{
	if(front == NULL)
	{
		printf("queue is empty");
	}
	
	else
	{
		q_ptr temp_ptr = front;
		int temp = temp_ptr->data;
		
		if(front == rear)
		{
			front = NULL;
			rear = NULL;
			free(temp_ptr);
			return temp;
		}
		
		else
		{
			front = front->next;
			free(temp_ptr);
			return temp;
			
		}
	}
}

void print_q(q_ptr p)
{
	if(p != NULL)
	{
		printf("%d\n", p->data);
		print_q(p->next);
	}
	
	else
	{
		printf("done.\n");
	}
}
