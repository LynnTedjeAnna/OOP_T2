//
// Created by Lynn Meindertsma on 06/09/2024.
//
#include <iostream>

#include "administration.hpp"

//todo fix getline

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
            scanf("%d", &answer_menu);
        } while (answer_menu > 7 || answer_menu == 0);
        menu();
    }
}


void Administration::menu(){
    switch (answer_menu) {
        case 1:
            add_student();
            break;
        case 2:
            view_students();
            break;
        case 3:
            view_groups();
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To discard any leftover characters
    getline (cin, st_nmbr);

    for (int i = 0; i < students.size(); i++) {
        if(st_nmbr == student_number[i]) {
            printf("ERROR give unique student number\n\n");
            start();
        }
    }

    cout << "Give name of student pls: \n" ;
    getline (cin, st_name);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To discard any leftover characters

    students.push_back(st_name);
    student_number.push_back(st_nmbr);
    gen_group();
}
void Administration::gen_group() {
    group_random = rand() % max_random;
    string string_grp_rnd = to_string(group_random);
    string grp_base = "G1_PCS.";        //clear string everytime

    if (students.size() == 1){
        groups.push_back( grp_base.append(string_grp_rnd));
        return;
    }

    //group max size is 3, so when divided by 3 and outcome is 0 new group has to be made
    if (!(groups.size() % 3)){
        // Appending the string.
        groups.push_back( grp_base.append(string_grp_rnd));
        return;
    }

    // Check if the vector is non-empty before accessing the last element
    if (!groups.empty()) {
        groups.push_back(groups[groups.size() - 1]);  // Push the last element into the vector
    }


}

void Administration::view_students() {
    // Print Strings stored in Vector
    for (int i = 0; i < students.size(); i++){
        cout << "Student number: " << student_number[i] << "\n";
        cout << "Student name: " << students[i] << "\n";
        cout << "Student group: " << groups[i] << "\n\n";
    }
}

//todo: error dived by 3
void Administration::view_groups() {
    for (int i = 0; i < students.size(); i++) {
        cout << "Student group: " << groups[i] << "\n";
        cout << "Student name: " << students[i] << "\n";
        //todo: diveded by 0 is 0 fix
        if (!((i++) %3)){
            printf("\n");
        }
    }
}

//todo: done? test
void Administration::search_student() {
    cout << "Give number of student pls: \n" ;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To discard any leftover characters
    getline (cin, st_nmbr);
    for (int i = 0; i < students.size(); i++) {
        if(st_nmbr == student_number[i]) {
            cout << "Student name: " << students[i] << "\n";
            cout << "Student number: " <<student_number[i] << "\n";
            cout << "Student group: " << groups[i] << "\n";
            return;
        }
    }
    printf("No student with that number present\n\n");
}

void Administration::view_a_group() {
    cout << "Give group name of student pls: \n" ;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To discard any leftover characters
    getline (cin, grp_name);
    for (int i = 0; i < students.size(); i++) {
        if(grp_name == groups[i]) {
            cout << "Student name: " << students[i] << "\n";
            cout << "Student number: " <<student_number[i] << "\n";
            cout << "Student group: " << groups[i] << "\n";
            return;
        }
    }
    printf("No group with that name present\n\n");
}

//done? test
void Administration::view_statistics() {
    cout << "Course: " << "Object Oriented Programming" << "\n";
    cout << "Students: " << students.size() << "\n";
    cout << "Student number: " <<student_number.size() << "\n";
    cout << "Groups: " << groups.size() << "\n\n";
}
