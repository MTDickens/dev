#include "shared.hpp"

/**
 * Normal functions
 */

void get_today(Date &date)
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm *today = std::localtime(&time);
    date = Date(today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
}

void usage(char *argv[])
{
    std::cerr << "Usage: " << argv[0] << " [command] [args...]" << std::endl;
    std::cerr << "Commands:" << std::endl;
#ifdef PDADD
    std::cerr << "  [date] : Add a new diary entry for the given date. The content is read from the standard input until a line with a single dot (.) is encountered." << std::endl;
#endif

#ifdef PDLIST
    std::cerr << "  pdlist : List all diary entries." << std::endl;
    std::cerr << "  pdlist [start_date] : List all diary entries no sooner than start_date" << std::endl;
    std::cerr << "  pdlist [start_date] [end_date] : List all diary entries between start_date and end_date." << std::endl;
#endif

#ifdef PDSHOW
    std::cerr << "  pdshow [date] : Show the diary entry for the given date." << std::endl;
#endif

#ifdef PDREMOVE
    std::cerr << "  pdremove [date] : Remove the diary entry for the given date." << std::endl;
#endif
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

/**
 * Member functions
 */

std::ostream &
operator<<(std::ostream &os, const Date &date)
{
    os << date.year << "-" << std::setw(2) << std::setfill('0') << date.month << "-" << std::setw(2) << std::setfill('0') << date.day;
    return os;
}

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

    std::cout << "----------------------------\n";
    for (auto it = start_it; it != end_it; ++it)
    {
        if (it == diary_list.end())
        {
            std::cerr << "Error: BUG found, please contact the author to fix it\n";
        }
        auto const &[date, diary] = *it;
        std::cout << "[" << date << "]\n";
        if (diary.content.size() <= truncate_len)
        {
            std::cout << diary.content << "\n";
        }
        else
        {
            std::cout << diary.content.substr(0, truncate_len) << "...\n";
        }
    }
    std::cout << "----------------------------\n";
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

    std::cout << "----------------------------\n";
    for (auto it = start_it; it != end_it; ++it)
    {
        if (it == diary_list.end())
        {
            std::cerr << "Error: BUG found, please contact the author to fix it\n";
        }
        auto const &[date, diary] = *it;
        std::cout << "[" << date << "]\n";
        if (diary.content.size() <= truncate_len)
        {
            std::cout << diary.content << "\n";
        }
        else
        {
            std::cout << diary.content.substr(0, truncate_len) << "...\n";
        }
    }
    std::cout << "----------------------------\n";
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

    std::cout << "----------------------------\n";
    for (auto it = start_it; it != end_it; ++it)
    {
        if (it == diary_list.end())
        {
            std::cerr << "Error: BUG found, please contact the author to fix it\n";
        }
        auto const &[date, diary] = *it;
        std::cout << "[" << date << "]\n";
        if (diary.content.size() <= truncate_len)
        {
            std::cout << diary.content << "\n";
        }
        else
        {
            std::cout << diary.content.substr(0, truncate_len) << "...\n";
        }
    }
    std::cout << "----------------------------\n";
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
#ifndef BLOCK_CLOG
    std::clog << "Reading from file, please wait ...\n";
#endif
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
#ifndef BLOCK_CLOG
    std::clog << "Reading finished\n";
#endif
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