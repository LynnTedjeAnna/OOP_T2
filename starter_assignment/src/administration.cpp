//
// Created by Lynn Meindertsma on 06/09/2024.
//
#include <iostream>

#include "administration.hpp"

Administration::Administration() = default;

void Administration::start() {
    while (run) {
        printf("your options: (enter number for option)\n"
               "1) add student \n"
               "2) view students \n"
               "3) view all groups \n"
               "4) search for a student \n"
               "5) view a group \n"
               "6) view statistics \n"
               "7) quit program\n");

        do {
            cin >> answer_menu;
        } while (answer_menu > 7 || answer_menu == 0);
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after reading the menu option
        menu();
    }
}

void Administration::menu(){
    switch (answer_menu) {
        case 1:
            add_student();
            break;
        case 2:
            student.print_all();
            break;
        case 3:
            student.print_all_groups();
            break;
        case 4:
            search_student();
            break;
        case 5:
            view_a_group();
            break;
        case 6:
            view_statistics();
            break;
        case 7:
            run = false;        //break out of loop
            break;
        default:
            break;
    }
}

void Administration::add_student() {
    cout << "Give number of student pls: \n" ;
    if (student.number_check()){
        printf("ERROR give unique student number\n\n");
        //start();
        return;
    }

    cout << "Give name of student pls: \n" ;
    student.add();
    student.gen_group();
}

void Administration::search_student() {
    cout << "Give number of student pls: \n" ;
    uint8_t index = student.number_check();
    if (index) {
        student.print((index-1));
    }
    else{
        printf("No student with that number present\n\n");
    }
}

void Administration::view_a_group() {
    cout << "Give group name of student pls: \n";
    vector<uint8_t> indices = student.group_check();  // Get all indices of students in the group

    if (!indices.empty()) {
        student.group_print(indices);  // Print all students in the group
    } else {
        printf("No group with that name present\n\n");
    }
}


void Administration::view_statistics() {
    cout << "Course: " << "Object Oriented Programming" << "\n\n";
    student.print_all();
}
