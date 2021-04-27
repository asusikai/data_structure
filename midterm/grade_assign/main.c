#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct student{
    char name[10];
    float att;
    float ass;
    float mid;
    float fin;
    float total;
    char grade;
}student;

void grade_input(student s, char name[], char att[], char ass[], char mid[], char fin[]);

void total_score(student s, float att, float ass, float mid, float fin); //

void b_sort(student s[]);

void grading(student s[]);

void print_info(student s[]);

int main()
{
    student std[10];
    float percent[4] = {0.1, 0.2 ,0.3, 0.4};

    FILE *f;
    f = fopen("student.txt", "rt");

    char name[10] ,att[5], ass[5], mid[5], fin[5];

    int i;
    for(i = 0; i<SIZE; i++)
    {
        fscanf(f, "%s %s %s %s %s", name, att, ass, mid, fin);
        grade_input(std[i], name, att, ass, mid, fin);
        //total_score(std[i], percent[0], percent[1], percent[2], percent[3]);
        std[i].total = std[i].att+std[i].ass+std[i].mid+std[i].fin;
        printf("%f\n", std[i].total);
    }
    fclose(f);

    b_sort(std);
    grading(std);

    print_info(std);


}

void grade_input(student s, char name[], char att[], char ass[], char mid[], char fin[])
{
    strcpy(s.name, name);
    s.att = atof(att);
    s.ass = atof(ass);
    s.mid = atof(mid);
    s.fin = atof(fin);

    printf("%.f %.f %.f %.f\n", s.att, s.ass, s.mid, s.fin);
}

void total_score(student s, float att, float ass, float mid, float fin)
{
    s.total = att + ass + mid + fin;
    printf("total : %f\n", s.total);
}

void b_sort(student s[])
{
    int i,j;
    float temp;

    for(i = 0; i<SIZE; i++)
    {
        for(j = 0; j< SIZE-i; j++)
        {
            if(s[j].total < s[j+1].total)
            {
                temp = s[j].total;
                s[j].total = s[j+1].total;
                s[j+1].total = temp;
            }
        }
    }
}

void grading(student s[])
{
     int i;

     for(i=0; i<SIZE; i++)
     {
         if(i < SIZE*0.3)
         {
             s[i].grade = 'A';
         }

         else if(i < SIZE*0.7)
         {
             s[i].grade = 'B';
         }

         else if(i < SIZE*0.9)
         {
             s[i].grade = 'C';
         }

         else
         {
             s[i].grade = 'F';

         }
     }
}

void print_info(student s[])
{
    int i;

    for(i=0; i<SIZE; i++)
    {
        printf("Name: %s  total: %f grade: %c\n", s[i].name, s[i].total, s[i].grade);
    }
}
