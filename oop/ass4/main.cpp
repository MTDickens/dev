#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <chrono>

#define WELCOME "Welcome to Diary CLI\n"
#define FILE_PATH "diary.dat"

/**
 * Usage
 */

void usage(char *argv[])
{
    std::cerr << "Usage: " << argv[0] << " [command] [args...]" << std::endl;
    std::cerr << "Commands:" << std::endl;
    std::cerr << "  pdadd [date] : Add a new diary entry for the given date. The content is read from the standard input until a line with a single dot (.) is encountered." << std::endl;
    std::cerr << "  pdlist : List all diary entries." << std::endl;
    std::cerr << "  pdlist [start_date] : List all diary entries no sooner than start_date" << std::endl;
    std::cerr << "  pdlist [start_date] [end_date] : List all diary entries between start_date and end_date." << std::endl;
    std::cerr << "  pdshow [date] : Show the diary entry for the given date." << std::endl;
    std::cerr << "  pdremove [date] : Remove the diary entry for the given date." << std::endl;
}

/**
 * Date Class
 */

class Date
{
public:
    int year;
    int month;
    int day;
    Date() = default;
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    bool operator<(const Date &other) const
    {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }

    std::string to_compact_string() const;

    friend std::ostream &
    operator<<(std::ostream &os, const Date &date);
};

std::ostream &
operator<<(std::ostream &os, const Date &date)
{
    os << date.year << "-" << std::setw(2) << std::setfill('0') << date.month << "-" << std::setw(2) << std::setfill('0') << date.day;
    return os;
}

/**
 * Diary Entry Class
 */

class DiaryEntry
{
public:
    std::string content;
    DiaryEntry() : content("") {}
    DiaryEntry(std::string content) : content(content) {}

    void append_line(std::string line)
    {
        content += line;
        content += "\n";
    }
};

/**
 * Personal Diary Class
 */
class PersonalDiary
{
public:
    void pdadd(Date date, std::string content);
    void pdadd(Date date, DiaryEntry de);
    void pdlist(Date start, Date end);
    void pdlist(Date start);
    void pdlist();
    void pdshow(Date date);
    int pdremove(Date date);

    PersonalDiary() : truncate_len(10) {}
    PersonalDiary(size_t truncate_len) : truncate_len(truncate_len) {}

    std::map<Date, DiaryEntry> diary_list;

protected:
    size_t truncate_len;
};

void PersonalDiary::pdadd(Date date, std::string content)
{
    diary_list[date] = DiaryEntry(content);
}
void PersonalDiary::pdadd(Date date, DiaryEntry de)
{
    diary_list[date] = de;
}

void PersonalDiary::pdlist(Date start)
{
    const auto start_it = diary_list.lower_bound(start);
    const auto end_it = diary_list.cend();

    if (start_it == end_it)
    {
        std::cerr << "No diaries found.\n";
        return;
    }

    for (auto it = start_it; it != end_it; ++it)
    {
        if (it == diary_list.end())
        {
            std::cerr << "Error: BUG found, please contact the author to fix it\n";
        }
        auto const &[date, diary] = *it;
        std::cout << date << ": ";
        if (diary.content.size() <= truncate_len)
        {
            std::cout << diary.content << "\n";
        }
        else
        {
            std::cout << diary.content.substr(0, truncate_len) << "...\n";
        }
    }
}
void PersonalDiary::pdlist()
{
    const auto start_it = diary_list.cbegin();
    const auto end_it = diary_list.cend();

    if (start_it == end_it)
    {
        std::cerr << "No diaries found.\n";
        return;
    }

    for (auto it = start_it; it != end_it; ++it)
    {
        if (it == diary_list.end())
        {
            std::cerr << "Error: BUG found, please contact the author to fix it\n";
        }
        auto const &[date, diary] = *it;
        std::cout << date << ": ";
        if (diary.content.size() <= truncate_len)
        {
            std::cout << diary.content << "\n";
        }
        else
        {
            std::cout << diary.content.substr(0, truncate_len) << "...\n";
        }
    }
}
void PersonalDiary::pdlist(Date start, Date end)
{
    if (end < start)
    {
        std::cerr << "Error: start date shouldn't be later than end date!\n";
        return;
    }

    const auto start_it = diary_list.lower_bound(start);
    const auto end_it = diary_list.upper_bound(end);

    if (start_it == end_it)
    {
        std::cerr << "No diaries found.\n";
        return;
    }

    for (auto it = start_it; it != end_it; ++it)
    {
        if (it == diary_list.end())
        {
            std::cerr << "Error: BUG found, please contact the author to fix it\n";
        }
        auto const &[date, diary] = *it;
        std::cout << date << ": ";
        if (diary.content.size() <= truncate_len)
        {
            std::cout << diary.content << "\n";
        }
        else
        {
            std::cout << diary.content.substr(0, truncate_len) << "...\n";
        }
    }
}

void PersonalDiary::pdshow(Date date)
{
    auto diary = diary_list.find(date);
    if (diary == diary_list.cend())
    {
        std::cerr << "No diary found\n";
    }
    else
        std::cout << diary->second.content;
}

int PersonalDiary::pdremove(Date date)
{
    auto diary = diary_list.find(date);
    if (diary == diary_list.cend())
        return -1;
    diary_list.erase(diary);
    return 0;
}

/**
 * Manager Class
 */

class Manager
{
public:
    void initialize(PersonalDiary &pd);
    void read_from_file(PersonalDiary &pd);
    void write_to_file(const PersonalDiary &pd);

    Manager() = delete;
    Manager(std::string filename) : file_name(filename) {}

private:
    std::string file_name;
};

void Manager::read_from_file(PersonalDiary &pd)
{
    std::ifstream read_file(file_name);
    if (!read_file.is_open())
    {
        std::cerr << "Error: can't open file " << file_name << "\n";
        exit(EXIT_FAILURE);
    }
    size_t cnt;
    std::string line;

    std::getline(read_file, line);
    std::stringstream ss(line);
    ss >> cnt;
    if (ss.fail())
    {
        std::cerr << "Error: file format is corrupted\n";
        exit(EXIT_FAILURE);
    }
    std::clog << "Reading from file, please wait ...";
    for (size_t i = 0; i != cnt && std::getline(read_file, line); ++i)
    {
        std::stringstream ss_date(line);
        int y, m, d;
        ss_date >> y >> m >> d;
        if (ss_date.fail())
        {
            std::cerr << "Error: file format is corrupted\n";
            exit(EXIT_FAILURE);
        }
        Date date(y, m, d);
        DiaryEntry de;
        while (std::getline(read_file, line) && line != ".")
        {
            de.append_line(line);
        }
        pd.pdadd(date, de);
    }
    std::clog << "Read finished\n";
}

void Manager::write_to_file(const PersonalDiary &pd)
{
    std::ofstream ofs(file_name);
    if (!ofs.is_open())
    {
        std::cerr << "Error: can't open file " << file_name << "\n";
        exit(EXIT_FAILURE);
    }
    ofs << pd.diary_list.size() << "\n";
    for (auto it = pd.diary_list.begin(); it != pd.diary_list.end(); ++it)
    {
        const auto &[date, diary] = *it;
        ofs << date.year << " " << date.month << " " << date.day << "\n"
            << diary.content << ".\n";
    }
}

void Manager::initialize(PersonalDiary &pd)
{
    // Read from file
    read_from_file(pd);
}

int parse_date(std::string str, Date &date)
{
    if (str.size() != 8)
    {
        return -1;
    }

    try
    {
        date.year = std::stoi(str.substr(0, 4));
        date.month = std::stoi(str.substr(4, 2));
        date.day = std::stoi(str.substr(6, 2));
    }
    catch (std::invalid_argument &e)
    {
        return -1;
    }
    catch (std::out_of_range &e)
    {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage(argv);
        return 1;
    }
    // argc >= 2
    // Local variables
    std::string command = argv[1];
    Manager manager(FILE_PATH);
    PersonalDiary pd;
    bool change_flag = false;

    // Procedure
    manager.initialize(pd);
    if (command == "pdadd")
    {
        if (argc < 3)
        {
            std::cerr << "Error: no date\n";
            return 1;
        }
        Date date;

        if (strcasecmp(argv[2], "today") == 0)
        {

            // Set date to today
            auto now = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(now);
            std::tm *today = std::localtime(&time);
            date = Date(today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
        }
        else if (parse_date(argv[2], date) == -1)
        {
            std::cerr << "Error: wrong date format\n";
            return 1;
        }

        DiaryEntry de;
        std::string line;
        while (!std::cin.eof() && std::getline(std::cin, line))
        {
            if (line == ".")
                break;
            else
                de.append_line(line);
        }
        pd.pdadd(date, de);
        change_flag = true;
    }
    else if (command == "pdlist")
    {
        if (argc == 2)
        {
            pd.pdlist();
            return 0;
        }
        // argc >= 3
        Date start_date;
        if (parse_date(argv[2], start_date) == -1)
        {
            std::cerr << "Error: wrong start date format\n";
            return 1;
        }
        if (argc == 3)
        {
            pd.pdlist(start_date);
            return 0;
        }
        // argc >= 4
        Date end_date;
        if (parse_date(argv[3], end_date) == -1)
        {
            std::cerr << "Error: wrong start date format\n";
            return 1;
        }
        pd.pdlist(start_date, end_date);
    }
    else if (command == "pdshow")
    {
        if (argc < 3)
        {
            std::cerr << "Error: no date\n";
            return 1;
        }
        Date date;
        if (parse_date(argv[2], date) == -1)
        {
            std::cerr << "Error: wrong date format\n";
            return 1;
        }
        pd.pdshow(date);
    }
    else if (command == "pdremove")
    {
        if (argc < 3)
        {
            std::cerr << "Error: no date\n";
            return 1;
        }
        Date date;
        if (parse_date(argv[2], date) == -1)
        {
            std::cerr << "Error: wrong date format\n";
            return 1;
        }
        int ret_pdremove = pd.pdremove(date);
        change_flag = (ret_pdremove == 0);
        std::cout << ret_pdremove << "\n";
    }
    else
    {
        usage(argv);
        return 1;
    }
    if (change_flag)
    {
        manager.write_to_file(pd);
    }
    return 0;
}