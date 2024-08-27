#pragma once
#include"List1.h"
#include"List2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;


// ���ļ���ȡ�γ���Ϣ��˫����
void read_courses(DLinkNode*& L, const char* filename) {
    // ���ļ���ģʽΪ��ȡ��"r"��
    FILE* file = fopen(filename, "r");
    // ����ļ���ʧ�ܣ����������Ϣ������
    if (!file) {
        perror("Error opening courses file");
        return;
    }

    int i = 1; // ���ڼ�¼�γ̵�λ������
    Course course; // ���ڴ洢ÿ���γ̵���Ϣ

    // ѭ����ȡ�ļ��еĿγ���Ϣ��ֱ���ļ�����
    while (fscanf(file, "%[^,],%[^,],%f,%[^,],%[^\n]\n", course.name, course.id, &course.credits, course.instructor, course.location) != EOF) {
        // ��ȡ�γ�������Ϣ�������������
        fscanf(file, " %[^\n]s", course.description);
        // ����ȡ���Ŀγ���Ϣ���뵽˫������
        ListInsert(L, i, course);
        i++; // ���������Ա������һ�γ�
    }

    // �ر��ļ�
    fclose(file);
}



// ���ļ���ȡѧ����Ϣ��ѭ��������
void read_students(CLinkNode*& L, const char* filename) {
    // ���ļ���ģʽΪ��ȡ��"r"��
    FILE* file = fopen(filename, "r");
    // ����ļ���ʧ�ܣ����������Ϣ������
    if (!file) {
        perror("Error opening students file");
        return;
    }

    int j = 1; // ���ڼ�¼ѧ����λ������
    Student student; // ���ڴ洢ÿ��ѧ������Ϣ

    // ѭ����ȡ�ļ��е�ѧ����Ϣ��ֱ���ļ�����
    while (fscanf(file, "%[^,],%[^,],%c,%[^\n]\n", student.name, student.id, &student.gender, student.major) != EOF) {
        // ��ȡѧ��ѡ�޿γ̵�����
        fscanf(file, "%d\n", &student.course_count);
        // ѭ����ȡѧ��ѡ�޵�ÿһ�ſγ̵�ID
        for (int i = 0; i < student.course_count; i++) {
            fscanf(file, "%s\n", student.course_ids[i]);
        }
        // ����ȡ����ѧ����Ϣ���뵽ѭ����������
        ListInsert(L, j, student);
        j++; // ���������Ա������һѧ��
    }

    // �ر��ļ�
    fclose(file);
}



// ��ʾ���пγ���Ϣ
void show_courses(DLinkNode* L) {
    // ��ȡ����ĵ�һ��ʵ�ʽڵ�
    DLinkNode* current = L->next;

    // ��ӡ����ͷָ���
    printf("========================================\n");
    printf("All Courses Information\n");
    printf("========================================\n");

    // ���������е�ÿһ���ڵ㣬��ӡ�γ���Ϣ
    while (current) {
        printf("----------------------------------------\n");
        printf("Course Name: %s\n", current->data.name); // ��ӡ�γ�����
        printf("Course ID | Credits: %s | %.2f\n", current->data.id, current->data.credits); // ��ӡ�γ�ID��ѧ��
        printf("Instructor Name: %s\n", current->data.instructor); // ��ӡ��ʦ����
        printf("Address: %s\n", current->data.location); // ��ӡ�γ̵ص�
        printf("Description: %s\n", current->data.description); // ��ӡ�γ�����
        printf("----------------------------------------\n");
        // �ƶ�����һ���ڵ�
        current = current->next;
    }

    // ��ӡ�����ķָ���
    printf("========================================\n");
}




// �����γ���Ϣ
void search_course(DLinkNode* L) {
    char course_id[20];
    // ��ʾ�û�����γ�ID
    printf("Please enter course ID: ");
    cin >> course_id;
    DLinkNode* current = L->next; // L ��ͷ�ڵ㣬currentָ���һ��ʵ�ʽڵ�

    // ���������е�ÿһ���ڵ㣬����ƥ��Ŀγ�ID
    while (current != NULL) {
        if (strcmp(current->data.id, course_id) == 0) {
            // �ҵ�ƥ��Ŀγ̣���ӡ�γ���Ϣ
            printf("Course Name: %s\n", current->data.name); // �γ�����
            printf("Course ID | Credits: %s | %.1f\n", current->data.id, current->data.credits); // �γ�ID��ѧ��
            printf("Instructor Name: %s\n", current->data.instructor); // ��ʦ����
            printf("Address: %s\n", current->data.location); // �γ̵ص�
            printf("Description: %s\n", current->data.description); // �γ�����
            return;
        }
        // �ƶ�����һ���ڵ�
        current = current->next;
    }

    // �����������������δ�ҵ�ƥ��Ŀγ�ID����ӡ��ʾ��Ϣ
    printf("Course (ID=%s) is not found in the courses list.\n", course_id);
}



// ��ӿγ���Ϣ
void add_course(DLinkNode*& L) {
    Course course; // ����һ��Course���͵ı��������ڴ洢�û�����Ŀγ���Ϣ
    string temp; // ��ʱ�ַ������������ڽ����û�����

    // ��ʾ�û�����γ�ID
    cout << "Please enter course ID: ";
    cin >> course.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������

    // ���γ�ID�Ƿ��Ѵ���
    DLinkNode* current = L->next; // ��ͷ�ڵ����һ���ڵ㿪ʼ����
    while (current) {
        if (strcmp(current->data.id, course.id) == 0) { // ����ҵ���ͬ�Ŀγ�ID
            cout << "Course (ID=" << course.id << ") already exists in the courses list." << endl;
            return; // ��ʾ�û����˳�����
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }

    // ��ʾ�û�����γ�����
    cout << "Please input course name: ";
    getline(cin, temp);
    strcpy(course.name, temp.c_str()); // ��������ַ���������course.name��

    // ��ʾ�û�����γ�ѧ��
    cout << "Please input course credits: ";
    cin >> course.credits;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������

    // ��ʾ�û������ʦ����
    cout << "Please input course instructor: ";
    getline(cin, temp);
    strcpy(course.instructor, temp.c_str()); // ��������ַ���������course.instructor��

    // ��ʾ�û�����γ̵ص�
    cout << "Please input course address: ";
    getline(cin, temp);
    strcpy(course.location, temp.c_str()); // ��������ַ���������course.location��

    // ��ʾ�û�����γ�����
    cout << "Please input course description: ";
    getline(cin, temp);
    strcpy(course.description, temp.c_str()); // ��������ַ���������course.description��

    // ����һ���µ�˫������ڵ�
    DLinkNode* new_node = (DLinkNode*)malloc(sizeof(DLinkNode));
    new_node->data = course; // ���γ���Ϣ��ֵ���½ڵ��������
    new_node->next = L->next; // �½ڵ��nextָ��ָ��ǰͷ�ڵ��next�ڵ�
    new_node->prior = L; // �½ڵ��priorָ��ָ��ͷ�ڵ�

    // ���ͷ�ڵ��next�ڵ���ڣ�����priorָ��ָ���½ڵ�
    if (L->next) {
        L->next->prior = new_node;
    }
    L->next = new_node; // ��ͷ�ڵ��nextָ��ָ���½ڵ�

    // ��ʾ�û��γ���ӳɹ�
    cout << "Successfully added the Course (ID=" << course.id << ") to the courses list." << endl;
}




// ɾ���γ���Ϣ�����ѧ��ѡ����Ϣ
void remove_course(DLinkNode* L, CLinkNode* students_list) {
    char course_id[20]; // ����һ���ַ����飬���ڴ洢�û�����Ŀγ�ID
    printf("Please enter course ID: ");
    cin >> course_id; // ��ȡ�û�����Ŀγ�ID

    DLinkNode* current = L->next; // ָ���һ��ʵ�ʽڵ�
    DLinkNode* prev = L; // ָ��ͷ�ڵ㣬���ڱ���ǰ���ڵ������

    // ����˫����������Ҫɾ���Ŀγ̽ڵ�
    while (current != NULL) {
        if (strcmp(current->data.id, course_id) == 0) { // �ҵ�Ҫɾ���Ŀγ̽ڵ�
            prev->next = current->next; // ��ǰ���ڵ��nextָ��ǰ�ڵ��next
            if (current->next != NULL) {
                current->next->prior = prev; // �����ǰ�ڵ��к�̽ڵ㣬�򽫺�̽ڵ��priorָ��ǰ���ڵ�
            }
            free(current); // �ͷŵ�ǰ�ڵ���ڴ�

            // ɾ���γ̳ɹ��󣬸�������ѡ��ÿγ̵�ѧ����Ϣ
            CLinkNode* current_student = students_list->next; // ָ��ѧ��ѭ������ĵ�һ���ڵ�
            while (current_student != students_list) { // ����ѧ��ѭ������
                for (int i = 0; i < current_student->data.course_count; ++i) { // ����ѧ��ѡ�޵Ŀγ�
                    if (strcmp(current_student->data.course_ids[i], course_id) == 0) {
                        // �ҵ���ѡ�޸ÿγ̵�ѧ��������ɾ������
                        for (int j = i; j < current_student->data.course_count - 1; ++j) {
                            strcpy(current_student->data.course_ids[j], current_student->data.course_ids[j + 1]); // ��ǰ�ƶ�����Ԫ�أ�����Ҫɾ���Ŀγ�ID
                        }
                        current_student->data.course_count--; // ���ٿγ̼���
                        i--; // ���������Լ���µĵ�ǰλ��
                    }
                }
                current_student = current_student->next; // ���������һ��ѧ��
            }

            printf("Successfully removed the Course (ID=%s) from the courses list.\n", course_id); // ��ʾ�û��γ�ɾ���ɹ�
            return; // �˳�����
        }
        prev = current; // ����ǰ���ڵ�
        current = current->next; // ���µ�ǰ�ڵ�
    }

    // ���δ�ҵ�ƥ��Ŀγ̱��
    printf("Course (ID=%s) is not found in the courses list.\n", course_id); // ��ʾ�û��γ�δ�ҵ�
}




// ���¿γ���Ϣ
void update_course(DLinkNode* L) {
    string course_id; // ���ڴ洢�û�����Ŀγ�ID
    printf("Please enter course ID: ");
    cin >> course_id; // ��ȡ�û�����Ŀγ�ID

    DLinkNode* current = L->next; // ���� L ��ͷ�ڵ㣬ָ���һ��ʵ�ʽڵ�
    while (current != NULL) { // ����˫������
        if (strcmp(current->data.id, course_id.c_str()) == 0) { // �ҵ�Ҫ���µĿγ̽ڵ�
            // ��ӡ��ǰ�γ���Ϣ
            printf("Before updating, the course information:\n");
            printf("----------------------------------------\n");
            printf("Course Name: %s\n", current->data.name);
            printf("Course ID | Credits: %s | %.1f\n", current->data.id, current->data.credits);
            printf("Instructor Name: %s\n", current->data.instructor);
            printf("Address: %s\n", current->data.location);
            printf("Description: %s\n", current->data.description);
            printf("----------------------------------------\n");

            // �����µĿγ���Ϣ
            printf("Please enter course name: ");
            cin.ignore(); // ����֮ǰ�������µĻ��з�
            string name;
            getline(cin, name); // ��ȡ�û�����Ŀγ�����
            strncpy(current->data.name, name.c_str(), sizeof(current->data.name) - 1); // ���¿γ�����

            printf("Please enter course credits: ");
            cin >> current->data.credits; // ��ȡ�û�����Ŀγ�ѧ��

            printf("Please enter course instructor: ");
            cin.ignore(); // ����֮ǰ�������µĻ��з�
            string instructor;
            getline(cin, instructor); // ��ȡ�û�����Ŀγ̽�ʦ
            strncpy(current->data.instructor, instructor.c_str(), sizeof(current->data.instructor) - 1); // ���¿γ̽�ʦ

            printf("Please enter course address: ");
            string location;
            getline(cin, location); // ��ȡ�û�����Ŀγ̵�ַ
            strncpy(current->data.location, location.c_str(), sizeof(current->data.location) - 1); // ���¿γ̵�ַ

            printf("Please enter course description: ");
            string description;
            getline(cin, description); // ��ȡ�û�����Ŀγ�����
            strncpy(current->data.description, description.c_str(), sizeof(current->data.description) - 1); // ���¿γ�����

            printf("Successfully updated the Course (ID=%s) in the courses list.\n", current->data.id); // ��ʾ�û��γ̸��³ɹ�
            return; // �˳�����
        }
        current = current->next; // ���µ�ǰ�ڵ�
    }

    // ���δ�ҵ�ƥ��Ŀγ̱��
    printf("Course (ID=%s) is not found in the courses list.\n", course_id.c_str()); // ��ʾ�û��γ�δ�ҵ�
}


// ���ҿγ����ĸ�������
const char* find_course_name(DLinkNode* course_list, const char* course_id) {
    DLinkNode* current = course_list->next; // ���� course_list ��ͷ�ڵ�
    while (current != NULL) {
        if (strcmp(current->data.id, course_id) == 0) {
            return current->data.name; // ����ƥ�䵽�Ŀγ���
        }
        current = current->next; // �ƶ�����һ���γ̽ڵ�
    }
    return "Unknown Course"; // ���δ�ҵ�ƥ��Ŀγ�ID������"Unknown Course"
}


// ���ѧ����Ϣ
void insert_student(CLinkNode*& L) {
    Student student; // ����һ��ѧ���������ڴ洢������Ϣ
    cout << "Please enter student ID: ";
    cin >> student.id; // ��ȡ�û������ѧ��ID

    // ���ѧ��ѧ���Ƿ��Ѵ���
    CLinkNode* current = L->next; // L ��ͷ�ڵ㣬ָ���һ��ʵ�ʽڵ�
    while (current != L) { // ����ѭ��������
        if (strcmp(current->data.id, student.id) == 0) { // ���ѧ��ID�Ƿ��Ѵ���
            printf("Student (ID=%s) already exists in the students list.\n", student.id); // ������ڣ���ʾ�û�
            return; // �˳�����
        }
        current = current->next; // ���µ�ǰ�ڵ�
    }

    // ����ѧ����Ϣ
    cout << "Please enter student name: ";
    cin.ignore(); // ����֮ǰ�������µĻ��з�
    string name;
    getline(cin, name); // ��ȡ�û������ѧ������
    strncpy(student.name, name.c_str(), sizeof(student.name) - 1); // ����������ѧ������
    student.name[sizeof(student.name) - 1] = '\0'; // ȷ���ַ����Կ��ַ���β

    cout << "Please enter student gender (M/F): ";
    cin >> student.gender; // ��ȡ�û������ѧ���Ա�

    cout << "Please enter student major: ";
    cin.ignore(); // ����֮ǰ�������µĻ��з�
    string major;
    getline(cin, major); // ��ȡ�û������ѧ��רҵ
    strncpy(student.major, major.c_str(), sizeof(student.major) - 1); // ����רҵ��ѧ������
    student.major[sizeof(student.major) - 1] = '\0'; // ȷ���ַ����Կ��ַ���β

    // �����µĽڵ㲢��ӵ�����
    CLinkNode* new_node = (CLinkNode*)malloc(sizeof(CLinkNode)); // �����½ڵ��ڴ�
    new_node->data = student; // ��ѧ����Ϣ��ֵ���½ڵ�
    new_node->next = L->next; // �½ڵ�ָ��ǰͷ�ڵ����һ���ڵ�
    L->next = new_node; // ͷ�ڵ�ָ���½ڵ�
    new_node->data.course_count = 0;  //����ӵ�ѧ��ѡ����ĿΪ��

    printf("Successfully inserted the Student (ID=%s) into the students list.\n", student.id); // ��ʾ�û�ѧ����Ϣ����ɹ�
}


// ɾ��ĳһλѧ����Ϣ
void delete_student(CLinkNode*& L) {
    char student_id[20]; // ����һ���ַ��������ڴ洢�����ѧ��ID
    printf("Please enter student ID to delete: ");
    scanf("%s", student_id); // ��ȡ�û������ѧ��ID

    CLinkNode* current = L->next; // ָ���һ��ʵ�ʽڵ�
    CLinkNode* prev = L; // ǰ���ڵ㣬��ʼΪͷ�ڵ�

    while (current != L) { // ����ѭ��������
        if (strcmp(current->data.id, student_id) == 0) { // ��鵱ǰ�ڵ��ѧ��ID�Ƿ�ƥ��
            // �ҵ�Ҫɾ���Ľڵ�
            prev->next = current->next; // ǰ���ڵ��nextָ��ָ��ǰ�ڵ��nextָ�룬������ǰ�ڵ�
            free(current); // �ͷŵ�ǰ�ڵ��ڴ�
            printf("Successfully deleted Student (ID=%s) from the students list.\n", student_id); // ��ʾ�û�ɾ���ɹ�
            return; // �˳�����
        }
        prev = current; // ����ǰ���ڵ�
        current = current->next; // ���µ�ǰ�ڵ�
    }

    // ���δ�ҵ�ƥ���ѧ��ѧ��
    printf("Student (ID=%s) is not found in the students list.\n", student_id); // ��ʾ�û�δ�ҵ�ѧ����Ϣ
}



// ���γ�ID�Ƿ����
bool course_exists(DLinkNode* L, const char* course_id) {
    DLinkNode* current = L->next; // ��ͷ�ڵ����һ���ڵ㿪ʼ����
    while (current) {
        if (strcmp(current->data.id, course_id) == 0) {
            return true; // �ҵ�ƥ��Ŀγ�ID������true
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }
    return false; // δ�ҵ�ƥ��Ŀγ�ID������false
}

// �޸�ѧ����Ϣ
void modify_student(CLinkNode* L, DLinkNode* course_list) {
    char student_id[20]; // ���ڴ洢�û������ѧ��ID
    printf("Please enter student ID: ");
    cin >> student_id; // ��ȡ�û������ѧ��ID

    CLinkNode* current = L->next; // ָ���һ��ʵ�ʽڵ㣬L��ͷ�ڵ�
    while (current != L) { // ����ѭ��������
        if (strcmp(current->data.id, student_id) == 0) { // ��鵱ǰ�ڵ��ѧ��ID�Ƿ�ƥ��
            printf("Modify student (ID=%s) [major|enroll|drop]: ", student_id);
            char command[10]; // ���ڴ洢�û����������
            cin >> command; // ��ȡ�û����������

            if (strcmp(command, "major") == 0) { // �޸�ѧ��רҵ
                printf("Please enter the new student major: ");
                cin.ignore(); // ����֮ǰ�������µĻ��з�
                cin.getline(current->data.major, sizeof(current->data.major)); // ��ȡ�µ�רҵ��Ϣ
                printf("Successfully modified the major of Student (ID=%s).\n", student_id);
                printf("----------------------------------------\n");
                printf("Student Name: %s\n", current->data.name);
                printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender);
                printf("Major: %s\n", current->data.major);
                printf("Selected Courses (%d):\n", current->data.course_count);
                for (int i = 0; i < current->data.course_count; i++) { // ���������ѧ��ѡ�޿γ�ID�Ϳγ���
                    const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
                    printf("%s:%s\n", current->data.course_ids[i], course_name); // ����γ�ID�Ϳγ���
                }
                printf("----------------------------------------\n");
                return; // �˳�����
            }
            else if (strcmp(command, "enroll") == 0) { // ���ѡ�޿γ�
                char course_id[20]; // ���ڴ洢�γ�ID
                printf("Please enter the course ID to be enrolled in: ");
                cin >> course_id; // ��ȡ�û�����Ŀγ�ID

                // ���γ̱���Ƿ����
                if (!course_exists(course_list, course_id)) {
                    printf("Course (ID=%s) is not found in the courses list.\n", course_id);
                    printf("----------------------------------------\n");
                    return; // �˳�����
                }

                // ���ѡ�޿γ̱���Ƿ��Ѿ�����
                for (int i = 0; i < current->data.course_count; ++i) {
                    if (strcmp(current->data.course_ids[i], course_id) == 0) {
                        printf("Course (ID=%s) is already in the enrolled courses list.\n", course_id);
                        printf("----------------------------------------\n");
                        return; // �˳�����
                    }
                }

                // ���ѡ�޿γ̱�ŵ��б���
                strcpy(current->data.course_ids[current->data.course_count], course_id);
                current->data.course_count++; // ����ѡ�޿γ�����

                printf("Successfully modified the courses of Student (ID=%s).\n", student_id);
                printf("----------------------------------------\n");
                printf("Student Name: %s\n", current->data.name);
                printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender);
                printf("Major: %s\n", current->data.major);
                printf("Selected Courses (%d):\n", current->data.course_count);
                for (int i = 0; i < current->data.course_count; i++) { // ���������ѧ��ѡ�޿γ�ID�Ϳγ���
                    const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
                    printf("%s:%s\n", current->data.course_ids[i], course_name); // ����γ�ID�Ϳγ���
                }
                printf("----------------------------------------\n");
                return; // �˳�����
            }
            else if (strcmp(command, "drop") == 0) { // ɾ��ѡ�޿γ�
                char course_id[20]; // ���ڴ洢�γ�ID
                printf("Please enter the course ID to be dropped: ");
                cin >> course_id; // ��ȡ�û�����Ŀγ�ID

                // ���ѡ�޿γ̱���Ƿ������ѧ���Ŀγ��б���
                int found = 0;
                for (int i = 0; i < current->data.course_count; ++i) {
                    if (strcmp(current->data.course_ids[i], course_id) == 0) {
                        found = 1;
                        // ��ѡ�޿γ��б����Ƴ�ѡ�޿γ̱��
                        for (int j = i; j < current->data.course_count - 1; ++j) {
                            strcpy(current->data.course_ids[j], current->data.course_ids[j + 1]);
                        }
                        current->data.course_count--; // ����ѡ�޿γ�����

                        printf("Successfully modified the courses of Student (ID=%s).\n", student_id);
                        printf("----------------------------------------\n");
                        printf("Student Name: %s\n", current->data.name);
                        printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender);
                        printf("Major: %s\n", current->data.major);
                        printf("Selected Courses (%d):\n", current->data.course_count);
                        for (int k = 0; k < current->data.course_count; k++) { // ���������ѧ��ѡ�޿γ�ID�Ϳγ���
                            const char* course_name = find_course_name(course_list, current->data.course_ids[k]);
                            printf("%s:%s\n", current->data.course_ids[k], course_name); // ����γ�ID�Ϳγ���
                        }
                        printf("----------------------------------------\n");
                        return; // �˳�����
                    }
                }

                // ���ѡ�޿γ̱�Ų�������ѡ�޿γ��б���
                if (!found) {
                    printf("Course (ID=%s) is not found in the enrolled courses list.\n", course_id);
                    printf("----------------------------------------\n");
                }
                return; // �˳�����
            }
            else {
                printf("Invalid command - returning to main menu.\n");
                printf("----------------------------------------\n");
                return; // �˳�����
            }
        }
        current = current->next; // ���µ�ǰ�ڵ�
    }

    // ���ѧ��ѧ��δ�ҵ�
    printf("Student (ID=%s) is not found in the students list.\n", student_id);
    printf("----------------------------------------\n");
}


// ��ʾ����ѧ����Ϣ
void display_students(CLinkNode* student_list, DLinkNode* course_list) {
    CLinkNode* current = student_list->next; // ���� student_list ��ͷ�ڵ�

    printf("========================================\n");
    printf("All Students Information\n");
    printf("========================================\n");
    while (current != student_list) { // ����ѭ��������
        printf("----------------------------------------\n");
        printf("Student Name: %s\n", current->data.name); // ���ѧ������
        printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender); // ���ѧ��ѧ�ź��Ա�
        printf("Major: %s\n", current->data.major); // ���ѧ��רҵ
        printf("Selected Courses (%d) :\n", current->data.course_count); // ���ѧ��ѡ�޿γ�����
        for (int i = 0; i < current->data.course_count; i++) { // ���������ѧ��ѡ�޿γ�ID�Ϳγ���
            const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
            printf("%s:%s\n", current->data.course_ids[i], course_name); // ����γ�ID�Ϳγ���
        }
        printf("----------------------------------------\n");
        current = current->next; // �ƶ�����һ��ѧ���ڵ�
    }
    printf("========================================\n");
}




// �г�ĳһλѧ����Ϣ������
void retrieve_student(CLinkNode* L, DLinkNode* course_list) {
    char student_id[20];
    printf("Please enter student ID: ");
    cin >> student_id;

    CLinkNode* current = L->next; // L ��ͷ�ڵ�
    while (current != L) { // ����ѭ�����������ѧ��
        if (strcmp(current->data.id, student_id) == 0) {
            // �ҵ�ƥ���ѧ��ѧ�ţ���ӡѧ����Ϣ
            printf("========================================\n");
            printf("Student Information\n");
            printf("----------------------------------------\n");
            printf("Student Name: %s\n", current->data.name); // ���ѧ������
            printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender); // ���ѧ��ѧ�ź��Ա�
            printf("Major: %s\n", current->data.major); // ���ѧ��רҵ
            printf("Selected Courses (%d) :\n", current->data.course_count); // ���ѧ��ѡ�޿γ�����
            for (int i = 0; i < current->data.course_count; i++) { // ���������ѧ��ѡ�޿γ�ID�Ϳγ���
                const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
                printf("%s:%s\n", current->data.course_ids[i], course_name); // ����γ�ID�Ϳγ���
            }
            printf("----------------------------------------\n");
            printf("========================================\n");
            return;
        }
        current = current->next; // �ƶ�����һ��ѧ���ڵ�
    }

    // ���δ�ҵ�ƥ���ѧ��ѧ��
    printf("Student (ID=%s) is not found in the students list.\n", student_id);
}




// ���γ���Ϣ���浽���ļ�
void write_courses(DLinkNode* L, const char* filename) {
    // ��ָ���ļ�����д�����
    FILE* file = fopen(filename, "w");
    if (!file) { // ����ļ���ʧ�ܣ����������Ϣ������
        perror("Error opening new courses file");
        return;
    }

    DLinkNode* current = L->next; // ��ͷ�ڵ����һ���ڵ㿪ʼ����
    while (current) { // ����˫�������е�ÿ���ڵ�
        // ����ǰ�ڵ�Ŀγ���Ϣд���ļ�
        fprintf(file, "%s,%s,%.2f,%s,%s\n", current->data.name, current->data.id, current->data.credits, current->data.instructor, current->data.location);
        fprintf(file, "%s", current->data.description);
        current = current->next; // �ƶ�����һ���ڵ�
    }
    fclose(file); // �ر��ļ�
}



// ��ѧ����Ϣ���浽���ļ�
void write_students(CLinkNode* L, const char* filename) {
    // ��ָ���ļ�����д�����
    FILE* file = fopen(filename, "w");
    if (!file) { // ����ļ���ʧ�ܣ����������Ϣ������
        perror("Error opening new students file");
        return;
    }

    CLinkNode* current = L->next; // ��ͷ�ڵ����һ���ڵ㿪ʼ����
    while (current != L) { // ����ѭ���������е�ÿ���ڵ�
        // ����ǰ�ڵ��ѧ��������Ϣд���ļ�
        fprintf(file, "%s,%s,%c,%s\n", current->data.name, current->data.id, current->data.gender, current->data.major);
        // ��ѧ����ѡ������д���ļ�
        fprintf(file, "%d\n", current->data.course_count);
        // ��ѧ����ѡ�α�����д���ļ�
        for (int i = 0; i < current->data.course_count; i++) {
            fprintf(file, "%s\n", current->data.course_ids[i]);
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }
    fclose(file); // �ر��ļ�
}

