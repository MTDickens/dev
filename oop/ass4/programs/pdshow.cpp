#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <map>

#define PDSHOW

#include "shared.hpp"

int main(int argc, char *argv[])
{
    // Local variables
    Manager manager(FILE_PATH);
    PersonalDiary pd;
    bool change_flag = false;

    // Procedure
    manager.initialize(pd);

    if (argc < 2)
    {
        std::cerr << "Error: no date\n";
        return 1;
    }
    Date date;
    if (strcasecmp(argv[1], "today") == 0)
    {
        get_today(date);
    }
    else if (parse_date(argv[1], date) == -1)
    {
        std::cerr << "Error: wrong date format\n";
        return 1;
    }
    pd.pdshow(date);

    if (change_flag)
    {
        manager.write_to_file(pd);
    }
    return 0;
}