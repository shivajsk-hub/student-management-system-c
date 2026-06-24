#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[100];
    int age;
    float marks;
};

void add_students(struct student *s, int count)
{
    for(int i = 0; i < count; i++)
    {
        printf("Enter name: ");
        scanf("%99s", s[i].name);

        printf("Enter age: ");
        while(scanf("%d", &s[i].age) != 1)
        {
            printf("Invalid input. Please re-enter:\n");
            while(getchar() != '\n');
        }

        printf("Enter marks: ");
        while(scanf("%f", &s[i].marks) != 1)
        {
            printf("Invalid input. Please re-enter:\n");
            while(getchar() != '\n');
        }
    }
}

void display_students(struct student *s, int totalstudents)
{
    if(totalstudents == 0)
    {
        printf("No students to display.\n");
        return;
    }

    for(int i = 0; i < totalstudents; i++)
    {
        printf("Name: %s\n", s[i].name);
        printf("Age: %d\n", s[i].age);
        printf("Marks: %.2f\n", s[i].marks);
    }
}

void search_student(struct student *s, int totalstudents, char search[])
{
    for(int i = 0; i < totalstudents; i++)
    {
        if(strcmp(s[i].name, search) == 0)
        {
            printf("Name: %s\nAge: %d\nMarks: %.2f\n",
                   s[i].name, s[i].age, s[i].marks);
            return;
        }
    }
    printf("Student not found.\n");
}

void find_topper(struct student *s, int totalstudents)
{
    if(totalstudents == 0)
    {
        printf("No students to find topper.\n");
        return;
    }

    int topper_index = 0;

    for(int i = 1; i < totalstudents; i++)
    {
        if(s[i].marks > s[topper_index].marks)
            topper_index = i;
    }

    printf("Topper: %s\nMarks: %.2f\n",
           s[topper_index].name,
           s[topper_index].marks);
}

void add_more_students(struct student *s, int start, int count)
{
    add_students(s + start, count);
}

void delete_student(struct student *s, int *totalstudents)
{
    char del[100];
    int total = *totalstudents;

    printf("Enter name to delete: ");
    scanf("%99s", del);

    for(int i = 0; i < total; i++)
    {
        if(strcmp(s[i].name, del) == 0)
        {
            for(int j = i; j < total - 1; j++)
                s[j] = s[j + 1];

            (*totalstudents)--;
            printf("Deleted %s\n", del);
            return;
        }
    }

    printf("Student not found.\n");
}

void save_data(struct student *s, int totalstudents)
{
    FILE *fp = fopen("students.txt", "w");

    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }

    fprintf(fp, "Total: %d\n", totalstudents);

    for(int i = 0; i < totalstudents; i++)
    {
        fprintf(fp, "Name: %s\n", s[i].name);
        fprintf(fp, "Age: %d\n", s[i].age);
        fprintf(fp, "Marks: %.2f\n", s[i].marks);
    }

    fclose(fp);
    printf("Data saved.\n");
}

void load_data(struct student **s, int *totalstudents)
{
    FILE *fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int total;

    fscanf(fp, "Total: %d\n", &total);

    *s = realloc(*s, total * sizeof(struct student));

    for(int i = 0; i < total; i++)
    {
        fscanf(fp, "Name: %99s\n", (*s)[i].name);
        fscanf(fp, "Age: %d\n", &(*s)[i].age);
        fscanf(fp, "Marks: %f\n", &(*s)[i].marks);
    }

    *totalstudents = total;

    fclose(fp);

    printf("Loaded %d students.\n", total);
}

void sort_students(struct student *s, int totalstudents)
{
    if(totalstudents == 0)
    {
        printf("No students to sort.\n");
        return;
    }

    int choice;

    printf("1. Name\n2. Marks\nChoose: ");
    scanf("%d", &choice);

    for(int i = 0; i < totalstudents - 1; i++)
    {
        for(int j = 0; j < totalstudents - i - 1; j++)
        {
            int swap = 0;

            if(choice == 1 &&
               strcmp(s[j].name, s[j + 1].name) > 0)
                swap = 1;

            if(choice == 2 &&
               s[j].marks < s[j + 1].marks)
                swap = 1;

            if(swap)
            {
                struct student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    printf("Sorted successfully.\n");
}

int main()
{
    struct student *s = NULL;
    int totalstudents = 0;
    int choice;
    char q;

    do
    {
        printf("\n1.Add\n2.Display\n3.Search\n4.Topper\n5.Add More\n6.Delete\n7.Save\n8.Load\n9.Sort\n");
        printf("Choice: ");
        while(scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please re-enter:\n");
            while(getchar() != '\n');
        }
        

        switch(choice)
        {
            case 1:
            {
                int count;

                printf("Enter number of students: ");
                while(scanf("%d", &count) != 1)
             {
                  printf("Invalid input. Please re-enter:\n");
                  while(getchar() != '\n');
             }
                


                s = realloc(s, (totalstudents + count) * sizeof(struct student));

                add_students(s + totalstudents, count);

                totalstudents += count;
                break;
            }

            case 2:
                display_students(s, totalstudents);
                break;

            case 3:
            {
                char search[100];
                printf("Enter name: ");
                scanf("%99s", search);
                search_student(s, totalstudents, search);
                break;
            }

            case 4:
                find_topper(s, totalstudents);
                break;

            case 5:
            {
                int count;

                printf("Enter number of students to add: ");
                scanf("%d", &count);

                s = realloc(s, (totalstudents + count) * sizeof(struct student));

                add_more_students(s, totalstudents, count);

                totalstudents += count;
                break;
            }

            case 6:
                delete_student(s, &totalstudents);
                break;

            case 7:
                save_data(s, totalstudents);
                break;

            case 8:
                load_data(&s, &totalstudents);
                break;

            case 9:
                sort_students(s, totalstudents);
                break;

            default:
                printf("Invalid choice.\n");
        }

        printf("Continue? (y/n): ");

        scanf(" %c", &q);

        while(q != 'y' && q != 'Y' && q != 'n' && q != 'N')
        {
          printf("Please enter 'y' or 'n': ");
          scanf(" %c", &q);
        }
         
    

    } while(q == 'y' || q == 'Y');
    if(q == 'n' || q == 'N')
    {
        printf("Exiting program.\n");
    }

    free(s);
    return 0;
}