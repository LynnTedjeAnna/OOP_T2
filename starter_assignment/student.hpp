//
// Created by Lynn Meindertsma on 13/09/2024.
//

#ifndef STARTER_ASSIGNMENT_STUDENT_HPP
#define STARTER_ASSIGNMENT_STUDENT_HPP
#include <vector>
#include <string>
using namespace std;

class Student{
public:
    Student();

    void add();                     //adds students
    uint8_t number_check();         //checks student number
    void print(uint8_t index);      //print information
    void print_all();               //print all info
    vector<uint8_t> group_check();
    void group_print(vector<uint8_t> indices);
    void print_all_groups();
    void gen_group();               //generate group name

private:
    string st_name;
    string st_number;
    string grp_name;
    int increment = 0;
    int max_random = 50;
    int random_number;
    // Declaring Vector of String type
    // Values can be added here using
    std::vector<std::string> students;
    std::vector<std::string> student_number;
    std::vector<std::string> groups;
};

#endif //STARTER_ASSIGNMENT_STUDENT_HPP
