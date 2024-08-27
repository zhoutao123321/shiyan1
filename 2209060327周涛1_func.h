#pragma once
#include"List1.h"
#include"List2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;


// 从文件读取课程信息到双链表
void read_courses(DLinkNode*& L, const char* filename) {
    // 打开文件，模式为读取（"r"）
    FILE* file = fopen(filename, "r");
    // 如果文件打开失败，输出错误信息并返回
    if (!file) {
        perror("Error opening courses file");
        return;
    }

    int i = 1; // 用于记录课程的位置索引
    Course course; // 用于存储每个课程的信息

    // 循环读取文件中的课程信息，直到文件结束
    while (fscanf(file, "%[^,],%[^,],%f,%[^,],%[^\n]\n", course.name, course.id, &course.credits, course.instructor, course.location) != EOF) {
        // 读取课程描述信息，处理多行描述
        fscanf(file, " %[^\n]s", course.description);
        // 将读取到的课程信息插入到双链表中
        ListInsert(L, i, course);
        i++; // 增加索引以便插入下一课程
    }

    // 关闭文件
    fclose(file);
}



// 从文件读取学生信息到循环单链表
void read_students(CLinkNode*& L, const char* filename) {
    // 打开文件，模式为读取（"r"）
    FILE* file = fopen(filename, "r");
    // 如果文件打开失败，输出错误信息并返回
    if (!file) {
        perror("Error opening students file");
        return;
    }

    int j = 1; // 用于记录学生的位置索引
    Student student; // 用于存储每个学生的信息

    // 循环读取文件中的学生信息，直到文件结束
    while (fscanf(file, "%[^,],%[^,],%c,%[^\n]\n", student.name, student.id, &student.gender, student.major) != EOF) {
        // 读取学生选修课程的数量
        fscanf(file, "%d\n", &student.course_count);
        // 循环读取学生选修的每一门课程的ID
        for (int i = 0; i < student.course_count; i++) {
            fscanf(file, "%s\n", student.course_ids[i]);
        }
        // 将读取到的学生信息插入到循环单链表中
        ListInsert(L, j, student);
        j++; // 增加索引以便插入下一学生
    }

    // 关闭文件
    fclose(file);
}



// 显示所有课程信息
void show_courses(DLinkNode* L) {
    // 获取链表的第一个实际节点
    DLinkNode* current = L->next;

    // 打印标题和分隔线
    printf("========================================\n");
    printf("All Courses Information\n");
    printf("========================================\n");

    // 遍历链表中的每一个节点，打印课程信息
    while (current) {
        printf("----------------------------------------\n");
        printf("Course Name: %s\n", current->data.name); // 打印课程名称
        printf("Course ID | Credits: %s | %.2f\n", current->data.id, current->data.credits); // 打印课程ID和学分
        printf("Instructor Name: %s\n", current->data.instructor); // 打印教师姓名
        printf("Address: %s\n", current->data.location); // 打印课程地点
        printf("Description: %s\n", current->data.description); // 打印课程描述
        printf("----------------------------------------\n");
        // 移动到下一个节点
        current = current->next;
    }

    // 打印结束的分隔线
    printf("========================================\n");
}




// 搜索课程信息
void search_course(DLinkNode* L) {
    char course_id[20];
    // 提示用户输入课程ID
    printf("Please enter course ID: ");
    cin >> course_id;
    DLinkNode* current = L->next; // L 是头节点，current指向第一个实际节点

    // 遍历链表中的每一个节点，查找匹配的课程ID
    while (current != NULL) {
        if (strcmp(current->data.id, course_id) == 0) {
            // 找到匹配的课程，打印课程信息
            printf("Course Name: %s\n", current->data.name); // 课程名称
            printf("Course ID | Credits: %s | %.1f\n", current->data.id, current->data.credits); // 课程ID和学分
            printf("Instructor Name: %s\n", current->data.instructor); // 教师姓名
            printf("Address: %s\n", current->data.location); // 课程地点
            printf("Description: %s\n", current->data.description); // 课程描述
            return;
        }
        // 移动到下一个节点
        current = current->next;
    }

    // 如果遍历完整个链表未找到匹配的课程ID，打印提示信息
    printf("Course (ID=%s) is not found in the courses list.\n", course_id);
}



// 添加课程信息
void add_course(DLinkNode*& L) {
    Course course; // 定义一个Course类型的变量，用于存储用户输入的课程信息
    string temp; // 临时字符串变量，用于接收用户输入

    // 提示用户输入课程ID
    cout << "Please enter course ID: ";
    cin >> course.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区

    // 检查课程ID是否已存在
    DLinkNode* current = L->next; // 从头节点的下一个节点开始遍历
    while (current) {
        if (strcmp(current->data.id, course.id) == 0) { // 如果找到相同的课程ID
            cout << "Course (ID=" << course.id << ") already exists in the courses list." << endl;
            return; // 提示用户并退出函数
        }
        current = current->next; // 移动到下一个节点
    }

    // 提示用户输入课程名称
    cout << "Please input course name: ";
    getline(cin, temp);
    strcpy(course.name, temp.c_str()); // 将输入的字符串拷贝到course.name中

    // 提示用户输入课程学分
    cout << "Please input course credits: ";
    cin >> course.credits;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区

    // 提示用户输入教师姓名
    cout << "Please input course instructor: ";
    getline(cin, temp);
    strcpy(course.instructor, temp.c_str()); // 将输入的字符串拷贝到course.instructor中

    // 提示用户输入课程地点
    cout << "Please input course address: ";
    getline(cin, temp);
    strcpy(course.location, temp.c_str()); // 将输入的字符串拷贝到course.location中

    // 提示用户输入课程描述
    cout << "Please input course description: ";
    getline(cin, temp);
    strcpy(course.description, temp.c_str()); // 将输入的字符串拷贝到course.description中

    // 创建一个新的双向链表节点
    DLinkNode* new_node = (DLinkNode*)malloc(sizeof(DLinkNode));
    new_node->data = course; // 将课程信息赋值给新节点的数据域
    new_node->next = L->next; // 新节点的next指针指向当前头节点的next节点
    new_node->prior = L; // 新节点的prior指针指向头节点

    // 如果头节点的next节点存在，则将其prior指针指向新节点
    if (L->next) {
        L->next->prior = new_node;
    }
    L->next = new_node; // 将头节点的next指针指向新节点

    // 提示用户课程添加成功
    cout << "Successfully added the Course (ID=" << course.id << ") to the courses list." << endl;
}




// 删除课程信息及相关学生选课信息
void remove_course(DLinkNode* L, CLinkNode* students_list) {
    char course_id[20]; // 定义一个字符数组，用于存储用户输入的课程ID
    printf("Please enter course ID: ");
    cin >> course_id; // 获取用户输入的课程ID

    DLinkNode* current = L->next; // 指向第一个实际节点
    DLinkNode* prev = L; // 指向头节点，用于保持前驱节点的引用

    // 遍历双向链表，查找要删除的课程节点
    while (current != NULL) {
        if (strcmp(current->data.id, course_id) == 0) { // 找到要删除的课程节点
            prev->next = current->next; // 将前驱节点的next指向当前节点的next
            if (current->next != NULL) {
                current->next->prior = prev; // 如果当前节点有后继节点，则将后继节点的prior指向前驱节点
            }
            free(current); // 释放当前节点的内存

            // 删除课程成功后，更新所有选择该课程的学生信息
            CLinkNode* current_student = students_list->next; // 指向学生循环链表的第一个节点
            while (current_student != students_list) { // 遍历学生循环链表
                for (int i = 0; i < current_student->data.course_count; ++i) { // 遍历学生选修的课程
                    if (strcmp(current_student->data.course_ids[i], course_id) == 0) {
                        // 找到了选修该课程的学生，进行删除操作
                        for (int j = i; j < current_student->data.course_count - 1; ++j) {
                            strcpy(current_student->data.course_ids[j], current_student->data.course_ids[j + 1]); // 向前移动数组元素，覆盖要删除的课程ID
                        }
                        current_student->data.course_count--; // 减少课程计数
                        i--; // 调整索引以检查新的当前位置
                    }
                }
                current_student = current_student->next; // 继续检查下一个学生
            }

            printf("Successfully removed the Course (ID=%s) from the courses list.\n", course_id); // 提示用户课程删除成功
            return; // 退出函数
        }
        prev = current; // 更新前驱节点
        current = current->next; // 更新当前节点
    }

    // 如果未找到匹配的课程编号
    printf("Course (ID=%s) is not found in the courses list.\n", course_id); // 提示用户课程未找到
}




// 更新课程信息
void update_course(DLinkNode* L) {
    string course_id; // 用于存储用户输入的课程ID
    printf("Please enter course ID: ");
    cin >> course_id; // 获取用户输入的课程ID

    DLinkNode* current = L->next; // 假设 L 是头节点，指向第一个实际节点
    while (current != NULL) { // 遍历双向链表
        if (strcmp(current->data.id, course_id.c_str()) == 0) { // 找到要更新的课程节点
            // 打印当前课程信息
            printf("Before updating, the course information:\n");
            printf("----------------------------------------\n");
            printf("Course Name: %s\n", current->data.name);
            printf("Course ID | Credits: %s | %.1f\n", current->data.id, current->data.credits);
            printf("Instructor Name: %s\n", current->data.instructor);
            printf("Address: %s\n", current->data.location);
            printf("Description: %s\n", current->data.description);
            printf("----------------------------------------\n");

            // 输入新的课程信息
            printf("Please enter course name: ");
            cin.ignore(); // 忽略之前输入留下的换行符
            string name;
            getline(cin, name); // 获取用户输入的课程名称
            strncpy(current->data.name, name.c_str(), sizeof(current->data.name) - 1); // 更新课程名称

            printf("Please enter course credits: ");
            cin >> current->data.credits; // 获取用户输入的课程学分

            printf("Please enter course instructor: ");
            cin.ignore(); // 忽略之前输入留下的换行符
            string instructor;
            getline(cin, instructor); // 获取用户输入的课程讲师
            strncpy(current->data.instructor, instructor.c_str(), sizeof(current->data.instructor) - 1); // 更新课程讲师

            printf("Please enter course address: ");
            string location;
            getline(cin, location); // 获取用户输入的课程地址
            strncpy(current->data.location, location.c_str(), sizeof(current->data.location) - 1); // 更新课程地址

            printf("Please enter course description: ");
            string description;
            getline(cin, description); // 获取用户输入的课程描述
            strncpy(current->data.description, description.c_str(), sizeof(current->data.description) - 1); // 更新课程描述

            printf("Successfully updated the Course (ID=%s) in the courses list.\n", current->data.id); // 提示用户课程更新成功
            return; // 退出函数
        }
        current = current->next; // 更新当前节点
    }

    // 如果未找到匹配的课程编号
    printf("Course (ID=%s) is not found in the courses list.\n", course_id.c_str()); // 提示用户课程未找到
}


// 查找课程名的辅助函数
const char* find_course_name(DLinkNode* course_list, const char* course_id) {
    DLinkNode* current = course_list->next; // 假设 course_list 是头节点
    while (current != NULL) {
        if (strcmp(current->data.id, course_id) == 0) {
            return current->data.name; // 返回匹配到的课程名
        }
        current = current->next; // 移动到下一个课程节点
    }
    return "Unknown Course"; // 如果未找到匹配的课程ID，返回"Unknown Course"
}


// 添加学生信息
void insert_student(CLinkNode*& L) {
    Student student; // 定义一个学生对象用于存储输入信息
    cout << "Please enter student ID: ";
    cin >> student.id; // 获取用户输入的学生ID

    // 检查学生学号是否已存在
    CLinkNode* current = L->next; // L 是头节点，指向第一个实际节点
    while (current != L) { // 遍历循环单链表
        if (strcmp(current->data.id, student.id) == 0) { // 检查学生ID是否已存在
            printf("Student (ID=%s) already exists in the students list.\n", student.id); // 如果存在，提示用户
            return; // 退出函数
        }
        current = current->next; // 更新当前节点
    }

    // 输入学生信息
    cout << "Please enter student name: ";
    cin.ignore(); // 忽略之前输入留下的换行符
    string name;
    getline(cin, name); // 获取用户输入的学生姓名
    strncpy(student.name, name.c_str(), sizeof(student.name) - 1); // 拷贝姓名到学生对象
    student.name[sizeof(student.name) - 1] = '\0'; // 确保字符串以空字符结尾

    cout << "Please enter student gender (M/F): ";
    cin >> student.gender; // 获取用户输入的学生性别

    cout << "Please enter student major: ";
    cin.ignore(); // 忽略之前输入留下的换行符
    string major;
    getline(cin, major); // 获取用户输入的学生专业
    strncpy(student.major, major.c_str(), sizeof(student.major) - 1); // 拷贝专业到学生对象
    student.major[sizeof(student.major) - 1] = '\0'; // 确保字符串以空字符结尾

    // 创建新的节点并添加到链表
    CLinkNode* new_node = (CLinkNode*)malloc(sizeof(CLinkNode)); // 分配新节点内存
    new_node->data = student; // 将学生信息赋值给新节点
    new_node->next = L->next; // 新节点指向当前头节点的下一个节点
    L->next = new_node; // 头节点指向新节点
    new_node->data.course_count = 0;  //新添加的学生选课数目为零

    printf("Successfully inserted the Student (ID=%s) into the students list.\n", student.id); // 提示用户学生信息插入成功
}


// 删除某一位学生信息
void delete_student(CLinkNode*& L) {
    char student_id[20]; // 定义一个字符数组用于存储输入的学生ID
    printf("Please enter student ID to delete: ");
    scanf("%s", student_id); // 获取用户输入的学生ID

    CLinkNode* current = L->next; // 指向第一个实际节点
    CLinkNode* prev = L; // 前驱节点，初始为头节点

    while (current != L) { // 遍历循环单链表
        if (strcmp(current->data.id, student_id) == 0) { // 检查当前节点的学生ID是否匹配
            // 找到要删除的节点
            prev->next = current->next; // 前驱节点的next指针指向当前节点的next指针，跳过当前节点
            free(current); // 释放当前节点内存
            printf("Successfully deleted Student (ID=%s) from the students list.\n", student_id); // 提示用户删除成功
            return; // 退出函数
        }
        prev = current; // 更新前驱节点
        current = current->next; // 更新当前节点
    }

    // 如果未找到匹配的学生学号
    printf("Student (ID=%s) is not found in the students list.\n", student_id); // 提示用户未找到学生信息
}



// 检查课程ID是否存在
bool course_exists(DLinkNode* L, const char* course_id) {
    DLinkNode* current = L->next; // 从头节点的下一个节点开始遍历
    while (current) {
        if (strcmp(current->data.id, course_id) == 0) {
            return true; // 找到匹配的课程ID，返回true
        }
        current = current->next; // 移动到下一个节点
    }
    return false; // 未找到匹配的课程ID，返回false
}

// 修改学生信息
void modify_student(CLinkNode* L, DLinkNode* course_list) {
    char student_id[20]; // 用于存储用户输入的学生ID
    printf("Please enter student ID: ");
    cin >> student_id; // 获取用户输入的学生ID

    CLinkNode* current = L->next; // 指向第一个实际节点，L是头节点
    while (current != L) { // 遍历循环单链表
        if (strcmp(current->data.id, student_id) == 0) { // 检查当前节点的学生ID是否匹配
            printf("Modify student (ID=%s) [major|enroll|drop]: ", student_id);
            char command[10]; // 用于存储用户输入的命令
            cin >> command; // 获取用户输入的命令

            if (strcmp(command, "major") == 0) { // 修改学生专业
                printf("Please enter the new student major: ");
                cin.ignore(); // 忽略之前输入留下的换行符
                cin.getline(current->data.major, sizeof(current->data.major)); // 获取新的专业信息
                printf("Successfully modified the major of Student (ID=%s).\n", student_id);
                printf("----------------------------------------\n");
                printf("Student Name: %s\n", current->data.name);
                printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender);
                printf("Major: %s\n", current->data.major);
                printf("Selected Courses (%d):\n", current->data.course_count);
                for (int i = 0; i < current->data.course_count; i++) { // 遍历并输出学生选修课程ID和课程名
                    const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
                    printf("%s:%s\n", current->data.course_ids[i], course_name); // 输出课程ID和课程名
                }
                printf("----------------------------------------\n");
                return; // 退出函数
            }
            else if (strcmp(command, "enroll") == 0) { // 添加选修课程
                char course_id[20]; // 用于存储课程ID
                printf("Please enter the course ID to be enrolled in: ");
                cin >> course_id; // 获取用户输入的课程ID

                // 检查课程编号是否存在
                if (!course_exists(course_list, course_id)) {
                    printf("Course (ID=%s) is not found in the courses list.\n", course_id);
                    printf("----------------------------------------\n");
                    return; // 退出函数
                }

                // 检查选修课程编号是否已经存在
                for (int i = 0; i < current->data.course_count; ++i) {
                    if (strcmp(current->data.course_ids[i], course_id) == 0) {
                        printf("Course (ID=%s) is already in the enrolled courses list.\n", course_id);
                        printf("----------------------------------------\n");
                        return; // 退出函数
                    }
                }

                // 添加选修课程编号到列表中
                strcpy(current->data.course_ids[current->data.course_count], course_id);
                current->data.course_count++; // 更新选修课程数量

                printf("Successfully modified the courses of Student (ID=%s).\n", student_id);
                printf("----------------------------------------\n");
                printf("Student Name: %s\n", current->data.name);
                printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender);
                printf("Major: %s\n", current->data.major);
                printf("Selected Courses (%d):\n", current->data.course_count);
                for (int i = 0; i < current->data.course_count; i++) { // 遍历并输出学生选修课程ID和课程名
                    const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
                    printf("%s:%s\n", current->data.course_ids[i], course_name); // 输出课程ID和课程名
                }
                printf("----------------------------------------\n");
                return; // 退出函数
            }
            else if (strcmp(command, "drop") == 0) { // 删除选修课程
                char course_id[20]; // 用于存储课程ID
                printf("Please enter the course ID to be dropped: ");
                cin >> course_id; // 获取用户输入的课程ID

                // 检查选修课程编号是否存在于学生的课程列表中
                int found = 0;
                for (int i = 0; i < current->data.course_count; ++i) {
                    if (strcmp(current->data.course_ids[i], course_id) == 0) {
                        found = 1;
                        // 从选修课程列表中移除选修课程编号
                        for (int j = i; j < current->data.course_count - 1; ++j) {
                            strcpy(current->data.course_ids[j], current->data.course_ids[j + 1]);
                        }
                        current->data.course_count--; // 更新选修课程数量

                        printf("Successfully modified the courses of Student (ID=%s).\n", student_id);
                        printf("----------------------------------------\n");
                        printf("Student Name: %s\n", current->data.name);
                        printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender);
                        printf("Major: %s\n", current->data.major);
                        printf("Selected Courses (%d):\n", current->data.course_count);
                        for (int k = 0; k < current->data.course_count; k++) { // 遍历并输出学生选修课程ID和课程名
                            const char* course_name = find_course_name(course_list, current->data.course_ids[k]);
                            printf("%s:%s\n", current->data.course_ids[k], course_name); // 输出课程ID和课程名
                        }
                        printf("----------------------------------------\n");
                        return; // 退出函数
                    }
                }

                // 如果选修课程编号不存在于选修课程列表中
                if (!found) {
                    printf("Course (ID=%s) is not found in the enrolled courses list.\n", course_id);
                    printf("----------------------------------------\n");
                }
                return; // 退出函数
            }
            else {
                printf("Invalid command - returning to main menu.\n");
                printf("----------------------------------------\n");
                return; // 退出函数
            }
        }
        current = current->next; // 更新当前节点
    }

    // 如果学生学号未找到
    printf("Student (ID=%s) is not found in the students list.\n", student_id);
    printf("----------------------------------------\n");
}


// 显示所有学生信息
void display_students(CLinkNode* student_list, DLinkNode* course_list) {
    CLinkNode* current = student_list->next; // 假设 student_list 是头节点

    printf("========================================\n");
    printf("All Students Information\n");
    printf("========================================\n");
    while (current != student_list) { // 遍历循环单链表
        printf("----------------------------------------\n");
        printf("Student Name: %s\n", current->data.name); // 输出学生姓名
        printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender); // 输出学生学号和性别
        printf("Major: %s\n", current->data.major); // 输出学生专业
        printf("Selected Courses (%d) :\n", current->data.course_count); // 输出学生选修课程数量
        for (int i = 0; i < current->data.course_count; i++) { // 遍历并输出学生选修课程ID和课程名
            const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
            printf("%s:%s\n", current->data.course_ids[i], course_name); // 输出课程ID和课程名
        }
        printf("----------------------------------------\n");
        current = current->next; // 移动到下一个学生节点
    }
    printf("========================================\n");
}




// 列出某一位学生信息供查阅
void retrieve_student(CLinkNode* L, DLinkNode* course_list) {
    char student_id[20];
    printf("Please enter student ID: ");
    cin >> student_id;

    CLinkNode* current = L->next; // L 是头节点
    while (current != L) { // 遍历循环单链表查找学生
        if (strcmp(current->data.id, student_id) == 0) {
            // 找到匹配的学生学号，打印学生信息
            printf("========================================\n");
            printf("Student Information\n");
            printf("----------------------------------------\n");
            printf("Student Name: %s\n", current->data.name); // 输出学生姓名
            printf("Student ID (Gender): %s (%c)\n", current->data.id, current->data.gender); // 输出学生学号和性别
            printf("Major: %s\n", current->data.major); // 输出学生专业
            printf("Selected Courses (%d) :\n", current->data.course_count); // 输出学生选修课程数量
            for (int i = 0; i < current->data.course_count; i++) { // 遍历并输出学生选修课程ID和课程名
                const char* course_name = find_course_name(course_list, current->data.course_ids[i]);
                printf("%s:%s\n", current->data.course_ids[i], course_name); // 输出课程ID和课程名
            }
            printf("----------------------------------------\n");
            printf("========================================\n");
            return;
        }
        current = current->next; // 移动到下一个学生节点
    }

    // 如果未找到匹配的学生学号
    printf("Student (ID=%s) is not found in the students list.\n", student_id);
}




// 将课程信息保存到新文件
void write_courses(DLinkNode* L, const char* filename) {
    // 打开指定文件用于写入操作
    FILE* file = fopen(filename, "w");
    if (!file) { // 如果文件打开失败，输出错误信息并返回
        perror("Error opening new courses file");
        return;
    }

    DLinkNode* current = L->next; // 从头节点的下一个节点开始遍历
    while (current) { // 遍历双向链表中的每个节点
        // 将当前节点的课程信息写入文件
        fprintf(file, "%s,%s,%.2f,%s,%s\n", current->data.name, current->data.id, current->data.credits, current->data.instructor, current->data.location);
        fprintf(file, "%s", current->data.description);
        current = current->next; // 移动到下一个节点
    }
    fclose(file); // 关闭文件
}



// 将学生信息保存到新文件
void write_students(CLinkNode* L, const char* filename) {
    // 打开指定文件用于写入操作
    FILE* file = fopen(filename, "w");
    if (!file) { // 如果文件打开失败，输出错误信息并返回
        perror("Error opening new students file");
        return;
    }

    CLinkNode* current = L->next; // 从头节点的下一个节点开始遍历
    while (current != L) { // 遍历循环单链表中的每个节点
        // 将当前节点的学生基本信息写入文件
        fprintf(file, "%s,%s,%c,%s\n", current->data.name, current->data.id, current->data.gender, current->data.major);
        // 将学生的选课数量写入文件
        fprintf(file, "%d\n", current->data.course_count);
        // 将学生的选课编号逐个写入文件
        for (int i = 0; i < current->data.course_count; i++) {
            fprintf(file, "%s\n", current->data.course_ids[i]);
        }
        current = current->next; // 移动到下一个节点
    }
    fclose(file); // 关闭文件
}

