#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <array>
#include <numeric>
#include <cmath>

#define NAME_COUNT 10
#define SCORE_COUNT 3
#define FUNCTION_COUNT 3
#define LINE_AVG_PRECISION 6
#define COLUMN_AVG_PRECISION 2

using score_matrix = std::array<std::array<int, SCORE_COUNT>, NAME_COUNT>;
using score_matrix_transpose = std::array<std::array<int, NAME_COUNT>, SCORE_COUNT>;

void print_title(int count_padding_length = 0, int name_padding_length = 0, int score_padding_length = 0, char padding = ' ')
{
    std::cout << std::left << std::setw(count_padding_length) << "no";
    std::cout << std::left << std::setw(name_padding_length) << "name";
    for (int i = 0; i != SCORE_COUNT; ++i)
    {
        std::cout << std::left << std::setw(score_padding_length) << "score" + std::to_string(i + 1);
    }
    std::cout << "average" << '\n';
}

static int count = 0;
static void print_line(std::string name, std::array<int, SCORE_COUNT> scores,
                       int count_padding_length = 0, int name_padding_length = 0, int score_padding_length = 0, int avg_precision = 1,
                       char padding = ' ')
{
    ++count;
    std::cout << std::left << std::setw(count_padding_length) << count;
    std::cout << std::left << std::setw(name_padding_length) << name;
    for (auto score : scores)
    {
        std::cout << std::left << std::setw(score_padding_length) << score;
    }
    std::cout << std::setprecision(avg_precision)
              << static_cast<float>(std::accumulate(scores.cbegin(), scores.cend(), 0)) / scores.size()
              << '\n';
}

void print_avg(score_matrix_transpose scores_s_transpose,
               int count_padding_length = 0, int name_padding_length = 0, int score_padding_length = 0)
{
    std::cout << std::setw(count_padding_length) << "";
    std::cout << std::setw(name_padding_length) << "average";

    for (int i = 0; i != SCORE_COUNT; ++i)
    {
        // no padding at the last score
        if (i != SCORE_COUNT - 1)
            std::cout << std::setw(score_padding_length);
        std::cout << std::setprecision(COLUMN_AVG_PRECISION)
                  << static_cast<float>(std::accumulate(scores_s_transpose[i].cbegin(), scores_s_transpose[i].cend(), 0)) / scores_s_transpose[i].size();
    }

    std::cout << '\n';
}

void print_min(score_matrix_transpose scores_s_transpose,
               int count_padding_length = 0, int name_padding_length = 0, int score_padding_length = 0)
{
    std::cout << std::setw(count_padding_length) << "";
    std::cout << std::setw(name_padding_length) << "min";

    for (int i = 0; i != SCORE_COUNT; ++i)
    {
        // no padding at the last score
        if (i != SCORE_COUNT - 1)
            std::cout << std::setw(score_padding_length);
        std::cout << *std::min_element(scores_s_transpose[i].begin(), scores_s_transpose[i].end());
    }

    std::cout << '\n';
}

void print_max(score_matrix_transpose scores_s_transpose,
               int count_padding_length = 0, int name_padding_length = 0, int score_padding_length = 0)
{
    std::cout << std::setw(count_padding_length) << "";
    std::cout << std::setw(name_padding_length) << "max";

    for (int i = 0; i != SCORE_COUNT; ++i)
    {
        // no padding at the last score
        if (i != SCORE_COUNT - 1)
            std::cout << std::setw(score_padding_length);
        std::cout << *std::max_element(scores_s_transpose[i].begin(), scores_s_transpose[i].end());
    }

    // std::cout << '\n';
}

int main()
{
    std::array<std::string, FUNCTION_COUNT> function_names({"average", "min", "max"});
    std::array<std::string, NAME_COUNT> names;
    // Each element in scores_s is the array of scores of the corresponding name.
    score_matrix scores_s;
    score_matrix_transpose scores_s_transpose;

    /**
     * Input
     */
    for (int i = 0; i != NAME_COUNT; ++i)
    {
        std::cin >> names[i];
        for (int j = 0; j != SCORE_COUNT; ++j)
        {
            std::cin >> scores_s[i][j];
            scores_s_transpose[j][i] = scores_s[i][j];
        }
    }

    /**
     * Padding length
     */
    int count_padding_length = 8;
    // name_padding_length should be exactly one more than the maximum of name length
    int name_padding_length = std::max(std::max_element(names.begin(), names.end(),
                                                        [](const std::string &a, const std::string &b)
                                                        {
                                                            return a.size() < b.size();
                                                        })
                                           ->size(),
                                       std::max_element(function_names.begin(), function_names.end(),
                                                        [](const std::string &a, const std::string &b)
                                                        {
                                                            return a.size() < b.size();
                                                        })
                                           ->size()) +
                              1;
    // = max(length("score"), COLUMN_AVG_PRECISION + 1) + 2 + length("3") = max(5, COLUMN_AVG_PRECISION + 1) + 3 + log10(3)
    int score_padding_length = std::max(5, COLUMN_AVG_PRECISION + 1) + 3 + static_cast<int>(std::log10(SCORE_COUNT));

    /**
     * Output
     */
    print_title(count_padding_length, name_padding_length, score_padding_length);
    for (int i = 0; i != NAME_COUNT; ++i)
    {
        print_line(names[i], scores_s[i],
                   count_padding_length, name_padding_length, score_padding_length, LINE_AVG_PRECISION);
    }
    print_avg(scores_s_transpose,
              count_padding_length, name_padding_length, score_padding_length);
    print_min(scores_s_transpose,
              count_padding_length, name_padding_length, score_padding_length);
    print_max(scores_s_transpose,
              count_padding_length, name_padding_length, score_padding_length);

    return 0;
}