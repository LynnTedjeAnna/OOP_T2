//
// Created by Lynn Meindertsma on 13/09/2024.
//

#include <iostream>
#include "student.hpp"

Student::Student() {}

void Student::add() {
    getline (cin, st_name);
    students.push_back(st_name);
    student_number.push_back(st_number);
}

uint8_t Student::number_check(){
    getline (cin, st_number);
    for (int i = 0; i < students.size(); i++) {
        if(st_number == student_number[i]) {
            return (i+1);       //if index 0 still return true
        }
    }
    return 0;
}

void Student::print(uint8_t index) {
    // Print Strings stored in Vector
        cout << "Student number: " << student_number[index] << "\n";
        cout << "Student name: " << students[index] << "\n";
        cout << "Student group: " << groups[index] << "\n\n";
}

void Student::print_all() {
    for (int i = 0; i < students.size(); ++i) {
        print(i);
    }
}

// Check if group exists and return vector of indexes of students in the group
vector<uint8_t> Student::group_check() {
    vector<uint8_t> indices;  // Store the indices of students in the group
    getline(cin, grp_name);

    for (int i = 0; i < students.size(); i++) {
        if (grp_name == groups[i]) {
            indices.push_back(i);  // Save the index of the student in the group
        }
    }

    return indices;  // Return all the found indices
}

void Student::group_print(vector<uint8_t> indices) {
    if (indices.empty()) {
        cout << "No students found in this group.\n\n";
        return;
    }

    // Print each student in the group
    for (uint8_t index : indices) {
        cout << "Student number: " << student_number[index] << "\n";
        cout << "Student name: " << students[index] << "\n";
        cout << "Student group: " << groups[index] << "\n\n";
    }
}


void Student::print_all_groups() {
    for (int i = 0; i < students.size(); i++) {
        print(i);
        increment++;
        if (!(increment %3)){
        }
    }
    printf("\n");
}

void::Student::gen_group(){
    random_number = rand() % max_random;
    string string_grp_rnd = to_string(random_number);
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

