#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[40];
    float gpa;
};

void insertStudent();
void showAll();
void search();
void update();
void deleteRec();

int main() {
    int ch;

    while(1) {
        printf("\n*** STUDENT MENU ***");
        printf("\n1. Add Record");
        printf("\n2. Display All");
        printf("\n3. Search Record");
        printf("\n4. Update Record");
        printf("\n5. Delete Record");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if(ch == 1)
            insertStudent();
        else if(ch == 2)
            showAll();
        else if(ch == 3)
            search();
        else if(ch == 4)
            update();
        else if(ch == 5)
            deleteRec();
        else if(ch == 6)
            break;
        else
            printf("Wrong Choice\n");
    }

    return 0;
}

void insertStudent() {
    FILE *f;
    struct Student s;

    f = fopen("student.txt", "ab");

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    fwrite(&s, sizeof(struct Student), 1, f);

    fclose(f);

    printf("Record Added\n");
}

void showAll() {
    FILE *f;
    struct Student s;

    f = fopen("student.txt", "rb");

    if(f == NULL) {
        printf("No Records Found\n");
        return;
    }

    printf("\nID\tName\tGPA\n");

    while(fread(&s, sizeof(struct Student), 1, f)) {
        printf("%d\t%s\t%.2f\n", s.id, s.name, s.gpa);
    }

    fclose(f);
}

void search() {
    FILE *f;
    struct Student s;
    int id, flag = 0;

    f = fopen("student.txt", "rb");

    if(f == NULL) {
        printf("No Records Found\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(struct Student), 1, f)) {
        if(s.id == id) {
            printf("ID : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("GPA : %.2f\n", s.gpa);
            flag = 1;
            break;
        }
    }

    if(flag == 0)
        printf("Record Not Found\n");

    fclose(f);
}

void update() {
    FILE *f, *t;
    struct Student s;
    int id, flag = 0;

    f = fopen("student.txt", "rb");

    if(f == NULL) {
        printf("No Records Found\n");
        return;
    }

    t = fopen("temp.txt", "wb");

    printf("Enter ID: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(struct Student), 1, f)) {

        if(s.id == id) {
            printf("Enter New Name: ");
            scanf("%s", s.name);

            printf("Enter New GPA: ");
            scanf("%f", &s.gpa);

            flag = 1;
        }

        fwrite(&s, sizeof(struct Student), 1, t);
    }

    fclose(f);
    fclose(t);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if(flag == 1)
        printf("Record Updated\n");
    else
        printf("Record Not Found\n");
}

void deleteRec() {
    FILE *f, *t;
    struct Student s;
    int id, flag = 0;

    f = fopen("student.txt", "rb");

    if(f == NULL) {
        printf("No Records Found\n");
        return;
    }

    t = fopen("temp.txt", "wb");

    printf("Enter ID: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(struct Student), 1, f)) {

        if(s.id == id) {
            flag = 1;
        }
        else {
            fwrite(&s, sizeof(struct Student), 1, t);
        }
    }

    fclose(f);
    fclose(t);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if(flag == 1)
        printf("Record Deleted\n");
    else
        printf("Record Not Found\n");
}