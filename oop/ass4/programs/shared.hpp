#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <map>
#include <iomanip>

#define WELCOME "Welcome to Diary CLI\n"
#define FILE_PATH "diary.dat"

class Date;

void usage(char *argv[]);
int parse_date(std::string str, Date &date);
void get_today(Date &date);

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

    friend std::ostream &
    operator<<(std::ostream &os, const Date &date);
};


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

