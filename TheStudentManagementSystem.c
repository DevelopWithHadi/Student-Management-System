#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    char Name[20];
    int RollNumber;
    int Class;
    float Marks;
} Student;

Student students[100];
int StudentCount = 0;

// Functions

void LoadfromFILE()
{

    FILE *file = fopen("Students_Database.txt", "r");

    if (file == NULL)
    {
        printf("DataBase file not found\n");
    }
    else
    {
        StudentCount = 0;
        while (StudentCount < 100 &&
               fscanf(file, "%s %d %d %f",
                      students[StudentCount].Name,
                      &students[StudentCount].RollNumber,
                      &students[StudentCount].Class,
                      &students[StudentCount].Marks) == 4)
        {
            StudentCount++;
        }

        fclose(file);
    }

    printf("Students Database loaded\n");
}


int ExistingNameChecker(char Name2check[20])
{
    LoadfromFILE();
    for (int i = 0; i < StudentCount; i++)
    {
        if (strcmp(students[i].Name, Name2check) == 0)
        {
            return 0; // Found → name already exists
        }
    }
    return 1; // Not found → name is unique
}


int ExistingRollNumberChecker(int RNum2check)
{
    LoadfromFILE();
    for (int i = 0; i < StudentCount; i++)
    {
        if (students[i].RollNumber == RNum2check)
        {
            return 0; // Found → roll number already exists
        }
    }
    return 1; // Not found → roll number is unique
}



void write2File(){
    FILE *pFile = fopen("Students_Database.txt", "w");
    if (pFile == NULL)
    {
        printf("⚠️ Error: Unable to open database file for writing.\n");
        return;
    }

    for (int i = 0; i < StudentCount; i++)
    {
        fprintf(pFile, "%s %d %d %.2f\n",
                students[i].Name,
                students[i].RollNumber,
                students[i].Class,
                students[i].Marks);
    }

    fclose(pFile);
    printf("\n✅ Student record updated successfully and saved to database!\n");
}




void addStudent()
{
    char Name2check[20];
    int RNum2check;

    LoadfromFILE();

    // -------- Name Input Loop --------
    while (1)
    {
        printf("Enter Name: ");
        getchar(); // consume leftover newline
        fgets(Name2check, 20, stdin);
        Name2check[strcspn(Name2check, "\n")] = '\0'; // remove newline

        if (ExistingNameChecker(Name2check) == 0)
        {
            printf("⚠️ Student name already exists! Please enter a different name.\n");
        }
        else
        {
            strcpy(students[StudentCount].Name, Name2check);
            break; // exit loop only if name is unique
        }
    }

    // -------- Roll Number Input Loop --------
    while (1)
    {
        printf("Enter Roll Number: ");
        scanf("%d", &RNum2check);

        if (ExistingRollNumberChecker(RNum2check) == 0)
        {
            printf("⚠️ Roll Number already exists! Please enter a different number.\n");
        }
        else
        {
            students[StudentCount].RollNumber = RNum2check;
            break; // exit loop only if roll number is unique
        }
    }

    // -------- Class and Marks --------
    printf("Enter Class: ");
    scanf("%d", &students[StudentCount].Class);

    printf("Enter Marks: ");
    scanf("%f", &students[StudentCount].Marks);

    // -------- Save Data --------
    StudentCount++;
    write2File();

    printf("🎉 Student added successfully and saved to database!\n");
}





void displayStudents()
{
    LoadfromFILE();
    printf("\n┌──────────────────────────────────────────────────────────────┐\n");
    printf("│ %-3s │ %-20s │ %-10s │ %-7s │ %-7s │\n", "No", "Name", "Roll No", "Class", "Marks");
    printf("├─────┼──────────────────────┼────────────┼─────────┼─────────┤\n");

    for (int i = 0; i < StudentCount; i++)
    {
        printf("│ %-3d │ %-20s │ %-10d │ %-7d │ %-7.2f │\n",
               i + 1,
               students[i].Name,
               students[i].RollNumber,
               students[i].Class,
               students[i].Marks);
    }

    printf("└──────────────────────────────────────────────────────────────┘\n");
    printf("Total Students: %d\n", StudentCount);
}

void searchStudent()
{

    LoadfromFILE();
    int choice;
    int found = 0;

    printf("Welcome to Student Finder!\n");
    printf("Which method do you prefer to search?\n");
    printf("1. Search by Name\n");
    printf("2. Search by Roll Number\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        char searchName[18];
        printf("Enter the Student Full Name: \n");
        getchar();
        fgets(searchName, 18, stdin);
        searchName[strcspn(searchName, "\n")] = 0; // remove newline

        printf("\n┌──────────────────────────────────────────────────────────────┐\n");
        printf("│ %-3s │ %-20s │ %-10s │ %-7s │ %-7s │\n", "No", "Name", "Roll No", "Class", "Marks");
        printf("├─────┼──────────────────────┼────────────┼─────────┼─────────┤\n");

        for (int i = 0; i < StudentCount; i++)
        {
            if (strcmp(students[i].Name, searchName) == 0)
            {
                printf("│ %-3d │ %-20s │ %-10d │ %-7d │ %-7.2f │\n",
                       i + 1,
                       students[i].Name,
                       students[i].RollNumber,
                       students[i].Class,
                       students[i].Marks);
                found++;
            }
        }

printf("└──────────────────────────────────────────────────────────────┘\n");
        printf("Students Found: %d\n", found);

        break;

    case 2:

        int searchTerm;
        printf("Enter the Roll Number: \n");
        scanf("%d", &searchTerm);

        printf("\n┌──────────────────────────────────────────────────────────────┐\n");
        printf("│ %-3s │ %-20s │ %-10s │ %-7s │ %-7s │\n", "No", "Name", "Roll No", "Class", "Marks");
        printf("├─────┼──────────────────────┼────────────┼─────────┼─────────┤\n");

        for (int i = 0; i < StudentCount; i++)
        {
            if (students[i].RollNumber == searchTerm)
            {
                printf("│ %-3d │ %-20s │ %-10d │ %-7d │ %-7.2f │\n",
                       i + 1,
                       students[i].Name,
                       students[i].RollNumber,
                       students[i].Class,
                       students[i].Marks);
                found++;
            }
        }
        printf("└──────────────────────────────────────────────────────────────┘\n");
        printf("Students Found: %d\n", found);

        break;

    default:
        printf("Enter a valid value!\n");
        break;
    }
}

void modifyStudent()
{
    LoadfromFILE(); // Always load latest data first

    char student2Modify[20];
    int found = 0;

    printf("Welcome to Student Editor!\n");
    printf("Enter the name of the student to modify: ");
    getchar(); // clear leftover newline
    fgets(student2Modify, sizeof(student2Modify), stdin);
    student2Modify[strcspn(student2Modify, "\n")] = '\0'; // remove newline

    for (int i = 0; i < StudentCount; i++)
    {
        if (strcmp(students[i].Name, student2Modify) == 0)
        {
            found = 1;

            printf("\nEditing details for '%s'\n", students[i].Name);
            printf("Enter New Name: ");
            fgets(students[i].Name, sizeof(students[i].Name), stdin);
            students[i].Name[strcspn(students[i].Name, "\n")] = '\0';

            printf("Enter New Roll Number: ");
            scanf("%d", &students[i].RollNumber);

            printf("Enter New Class: ");
            scanf("%d", &students[i].Class);

            printf("Enter New Marks: ");
            scanf("%f", &students[i].Marks);

            break; // Stop searching once found
        }
    }

    if (!found)
    {
        printf("\n❌ No student found with that name.\n");
        return;
    }

    // Rewrite the entire database with updated data
    write2File();
}

void deleteStudent()
{
    LoadfromFILE(); // Always load latest data first

    char student2Delete[20];
    int found = 0;

    printf("\nWelcome to Student Remover!\n");
    printf("Enter the name of the student to delete: ");
    getchar(); // clear leftover newline
    fgets(student2Delete, sizeof(student2Delete), stdin);
    student2Delete[strcspn(student2Delete, "\n")] = '\0'; // remove newline

    for (int i = 0; i < StudentCount; i++)
    {
        if (strcmp(students[i].Name, student2Delete) == 0)
        {
            for (int j = i; j < StudentCount - 1; j++)
                students[j] = students[j + 1];
            StudentCount--;
            printf("Record deleted!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n❌ No student found with that name.\n");
        return;
    }

    // Rewrite the entire database with updated data
    write2File();
}

int main()
{
    int choice;

    printf("Welcome to Students Management System\n");

    while (1)
    {
        printf("\nChoose an Option from the following to proceed:\n");
        printf("1. View All Students\n");
        printf("2. Add a new Student\n");
        printf("3. Search a Student from Database\n");
        printf("4. Modify existing Student\n");
        printf("5. Delete existing Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            addStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            modifyStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 0:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
