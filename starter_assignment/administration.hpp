//
// Created by Lynn Meindertsma on 06/09/2024.
//

#ifndef STARTER_ASSIGNMENT_ADMINISTRATION_HPP
#define STARTER_ASSIGNMENT_ADMINISTRATION_HPP

#include <vector>
#include <string>
#include "student.hpp"

using namespace std;

class Administration{
public:
    //constructor
    Administration();

    void start();
    void menu();

    void add_student();
    void search_student();

    void view_a_group();
    void view_statistics();

private:
    bool run = true;
    int answer_menu;
    Student student;
};

#endif //STARTER_ASSIGNMENT_ADMINISTRATION_HPP
