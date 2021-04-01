#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Data* dp;
typedef struct Data{
    int item; //item
    dp next; // 다음 구조체 포인터
}Data;


dp head;


void addData(int item); // 오름차순으로 삽입
void deleteData(int n); // item에 n이 들어있는 노드 삭제
void printData(); // 전체 데이터 프린트

int main()
{
    int i, item;
    srand(time(NULL));

    head = malloc(sizeof(Data*));
    head = NULL;
    printData();

    for (i = 0; i < 10; i++)
    {
        item = rand() % 100;
        printf("%d. %d\n",i+1, item);
        addData(item);
    }
    printData();

    deleteData(10); // item 이 10인 Data 삭제
    printData();

   
    return 0;
}

void addData(int item)
{
    if(head == NULL) // 노드가 하나도 없을 때
    {
        Data* data = malloc(sizeof(Data));
        data->item = item;
        data->next = NULL;
        head = data;
        printf("first add success - item :%d\n", head->item);
    }

    else // 노드가 존재할 때
    {
        dp temp = head;
        if(head->item > item) // 첫 노드보다 삽입 값이 작을 때
        {
            Data* data = malloc(sizeof(Data));
            data->item =item;
            if(head->next->next != NULL)
            {
                data->next = head->next->next;
            }

            else
            {
                data->next = NULL;
            }
            
            head = data;
            free(temp);
            printf("head change - item :%d\n", data->item);
        }

        else
        {
            while(temp->item < item && temp->next != NULL) // 데이터 값이 삽입할 값보다 더 작다면
            {
                temp = temp->next; // temp의 위치를 계속 다음 노드로 보낸다.
            }

            Data* new_data = malloc(sizeof(Data)); // 새 노드 생성
            

            
            
            if(temp->next->next != NULL) // 다음 노드가 있다면
            {
                new_data->next = temp->next->next; // 새노드의 next가 다음 노드 가리킴
            }

            else // 다음 노드가 없다면
            {
                new_data->next = NULL; // 새 노드의 next 값 NULL
            }
            new_data = temp->next; //temp의 다음 위치에 새노드 삽입
            new_data->item = item; // 새 노드의 item 값 삽입
            free(temp);

            printf("add success - item :%d\n", new_data->item);
        }
    }
}

void deleteData(int n)
{
    dp  temp = head;

    while(temp->next != NULL) // 다음 노드 없을 때까지
    {
        if(temp->item == n)  //item이 일치하면
        {
            if(temp == head) // 1번째 노드면
            {
                head = temp->next;
                free(temp);
                temp = head;

                printf("first node deleted.\n");
            }

            else //1번째가 아니라면
            {
                dp temp2 = temp;
                temp2 = temp2->next->next;
                free(temp2);
                printf("node deleted.\n");
            }
        }

        temp = temp->next;
    }
}

void printData()
{
    if(head == NULL)
    {
        printf("it's empty!\n");
    }

    else
    {
        dp temp = head;
        printf("Datas\n");
        while(temp->next != NULL)
        {
            printf("item : %d\n", temp->item);
            temp = temp->next;
        }
    }
}