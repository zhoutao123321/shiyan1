#define _CRT_SECURE_NO_WARNINGS

#include"List1.h"
#include"List2.h"
#include"func.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;


int main() {
    DLinkNode* courses_list;
    CLinkNode* students_list;

    InitList(courses_list);
    InitList(students_list);

    read_courses(courses_list, "courses.txt");
    read_students(students_list, "students.txt");

    char choice[10];
    while (1) {
        printf("-------------------------------------------------------------------------------------------\n");
        printf("The choice to maintain COURSEs information [add|remove|update|search|show]\n");
        printf("The choice to maintain STUDENTs information [insert|delete|modify|retrieve|display]\n");
        printf("The choice quit means to finish the program.[quit]\n\n\n");
        printf("Please enter choice: ");
        cin >> choice;

        if (strcmp(choice, "quit") == 0) {
            printf("\n\n-- Program Terminating --\n");
            break;
        }
        else if (strcmp(choice, "add") == 0) {
            add_course(courses_list);
        }
        else if (strcmp(choice, "remove") == 0) {
            remove_course(courses_list, students_list);
        }
        else if (strcmp(choice, "update") == 0) {
            update_course(courses_list);
        }
        else if (strcmp(choice, "search") == 0) {
            search_course(courses_list);
        }
        else if (strcmp(choice, "show") == 0) {
            show_courses(courses_list);
        }
        else if (strcmp(choice, "insert") == 0) {
            insert_student(students_list);
        }
        else if (strcmp(choice, "delete") == 0) {
            delete_student(students_list);
        }
        else if (strcmp(choice, "modify") == 0) {
            modify_student(students_list, courses_list);
        }
        else if (strcmp(choice, "retrieve") == 0) {
            retrieve_student(students_list, courses_list);
        }
        else if (strcmp(choice, "display") == 0) {
            display_students(students_list, courses_list);
        }
        else {
            printf("Not a valid command - please try again.\n");
        }
        printf("\n\n\n");
    }

    write_courses(courses_list, "new_courses.txt");
    write_students(students_list, "new_students.txt");

    DestroyList(courses_list);
    DestroyList(students_list);

    return 0;
}
