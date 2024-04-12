#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <map>

#define PDLIST

#include "shared.hpp"

int main(int argc, char *argv[])
{
    // Local variables
    Manager manager(FILE_PATH);
    PersonalDiary pd;
    bool change_flag = false;

    // Procedure
    manager.initialize(pd);

    if (argc == 1)
    {
        pd.pdlist();
        return 0;
    }
    // argc >= 2
    Date start_date;
    if (strcasecmp(argv[1], "today") == 0)
    {
        get_today(start_date);
    }
    else if (parse_date(argv[1], start_date) == -1)
    {
        std::cerr << "Error: wrong start date format\n";
        return 1;
    }
    if (argc == 2)
    {
        pd.pdlist(start_date);
        return 0;
    }
    // argc >= 3
    Date end_date;
    if (strcasecmp(argv[2], "today") == 0)
    {
        get_today(end_date);
    }
    else if (parse_date(argv[2], end_date) == -1)
    {
        std::cerr << "Error: wrong start date format\n";
        return 1;
    }
    pd.pdlist(start_date, end_date);

    if (change_flag)
    {
        manager.write_to_file(pd);
    }
    return 0;
}