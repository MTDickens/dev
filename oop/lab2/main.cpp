#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

#define WIDTH 10
#define NAME_WIDTH (name_width)

int name_width;

struct Student
{
    std::string name;
    std::map<int, int> scores; // course id -> score
};

int main()
{
    std::vector<Student> students;
    std::map<int, std::string> courses;           // course id -> course name
    std::map<int, std::vector<int>> courseScores; // course id -> scores
    std::string name;
    int courseId, score;

#ifndef SHUT_COUT
    std::cout << "Enter student records. Type '#' when finished.\n";
#endif

    while (true)
    {
#ifndef SHUT_COUT
        std::cout << "Enter student name: ";
#endif

        std::cin >> name;
        if (name == "#")
            break;

        Student student;
        student.name = name;

        while (true)
        {
#ifndef SHUT_COUT
            std::cout << "Enter course id (enter -1 when finished): ";
#endif

            std::cin >> courseId;
            if (courseId == -1)
                break;
#ifndef SHUT_COUT
            std::cout << "Enter score for course " << courseId << ": ";
#endif

            std::cin >> score;
            student.scores[courseId] = score;

            // Add the course to the courses map if it doesn't exist
            if (courses.find(courseId) == courses.end())
            {
                courses[courseId] = "score" + std::to_string(courseId);
            }

            // Add the score to the courseScores map
            courseScores[courseId].push_back(score);
        }

        // Add the student to the students vector
        students.push_back(student);
    }

    // Get the maximum length of the students
    name_width = std::max_element(students.begin(), students.end(),
                                  [](const Student &s1, const Student &s2)
                                  {
                                      return s1.name.length() < s2.name.length();
                                  })
                     ->name.size() +
                 1; // "+1" for spacing

    // Print the header row
    std::cout
        << std::left << std::setw(WIDTH) << "no" << std::setw(name_width) << "name";
    for (const auto &course : courses)
    {
        std::cout << std::setw(WIDTH) << course.second;
    }
    std::cout << std::setw(WIDTH) << "average" << std::endl;

    // Print the student records
    for (int i = 0; i < students.size(); i++)
    {
        std::cout << std::left << std::setw(WIDTH) << i + 1 << std::setw(name_width) << students[i].name;
        int total = 0;
        int count = 0;
        for (const auto &course : courses)
        {
            if (students[i].scores.find(course.first) != students[i].scores.end())
            {
                std::cout << std::setw(WIDTH) << students[i].scores[course.first];
                total += students[i].scores[course.first];
                count++;
            }
            else
            {
                std::cout << std::setw(WIDTH) << "NULL";
            }
        }
        if (count > 0)
        {
            std::cout << std::setw(WIDTH) << (double)total / count;
        }
        else
        {
            std::cout << std::setw(WIDTH) << "NULL";
        }
        std::cout << std::endl;
    }

    // Print the average row
    std::cout << std::left << std::setw(WIDTH + NAME_WIDTH) << "average";
    for (const auto &course : courses)
    {
        int total = 0;
        int count = 0;
        for (int score : courseScores[course.first])
        {
            if (score != -1)
            {
                total += score;
                count++;
            }
        }
        if (count > 0)
        {
            std::cout << std::setw(WIDTH) << std::left << (double)total / count;
        }
        else
        {
            std::cout << std::setw(WIDTH) << std::left << "NULL";
        }
    }
    std::cout << std::endl;

    // Print the minimum row
    std::cout << std::left << std::setw(WIDTH + NAME_WIDTH) << "min";
    for (const auto &course : courses)
    {
        int minScore = std::numeric_limits<int>::max();
        for (int score : courseScores[course.first])
        {
            if (score != -1 && score < minScore)
            {
                minScore = score;
            }
        }
        if (minScore != std::numeric_limits<int>::max())
        {
            std::cout << std::setw(WIDTH) << std::left << minScore;
        }
        else
        {
            std::cout << std::setw(WIDTH) << std::left << "NULL";
        }
    }
    std::cout << std::endl;

    // Print the maximum row
    std::cout << std::left << std::setw(WIDTH + NAME_WIDTH) << "max";
    for (const auto &course : courses)
    {
        int maxScore = std::numeric_limits<int>::min();
        for (int score : courseScores[course.first])
        {
            if (score != -1 && score > maxScore)
            {
                maxScore = score;
            }
        }
        if (maxScore != std::numeric_limits<int>::min())
        {
            std::cout << std::setw(WIDTH) << std::left << maxScore;
        }
        else
        {
            std::cout << std::setw(WIDTH) << std::left << "NULL";
        }
    }
    std::cout << std::endl;

    return 0;
}
