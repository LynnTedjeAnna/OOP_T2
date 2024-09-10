//
// Created by Lynn Meindertsma on 06/09/2024.
//

#ifndef STARTER_ASSIGNMENT_ADMINISTRATION_HPP
#define STARTER_ASSIGNMENT_ADMINISTRATION_HPP

#include <vector>
#include <string>

using namespace std;

class Administration{
public:
    //constructor
    Administration();

    void start();
    void menu();
    void gen_group();
    void add_student();
    void view_students();
    void view_groups();
    void search_student();
    void view_a_group();
    void view_statistics();

private:
    bool run = true;
    int answer_menu;
    int max_random = 100;
    int group_random;
    int increment = 0;
    string st_name;
    string st_nmbr;
    string grp_name;
    // Declaring Vector of String type
    // Values can be added here using
    std::vector<std::string> students{};
    std::vector<std::string> student_number{};
    std::vector<std::string> groups{};

};

#endif //STARTER_ASSIGNMENT_ADMINISTRATION_HPP
