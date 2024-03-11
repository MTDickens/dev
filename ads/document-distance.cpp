// Input:
// 3
// A00
// A B C
// #
// A01
// B C D
// #
// A02
// A C
// D A
// #
// 2
// A00 A01
// A00 A02

// Output:
// Case 1: 0.841
// Case 2: 0.785

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

unordered_map<string, long> filename_to_long;
long filename_index = 0;

class Document
{
public:
    long index;
    unordered_map<string, long> word_cnt;
    long long l2_squared;
    Document() = delete;
    Document(long index) : index(index) {}

    void calc_l2_squared();
};

double compare_docs(Document &doc1, Document &doc2)
{
    long vec_dot = 0;
    for (auto &i : doc1.word_cnt)
    {

        auto it = doc2.word_cnt.find(i.first);
        if (it != doc2.word_cnt.end())
        {
            vec_dot += (long)i.second * (long)it->second;
        }
    }
    return acos((double)vec_dot / sqrt(((double)doc1.l2_squared * (double)doc2.l2_squared)));
}

string stem_analysis(string &str)
{
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), str.begin(), ::tolower); // Convert to lowercase for case-insensitive comparison

    const vector<string> suffixes = {"ies", "es", "ed", "ing"};
    for (const string &suffix : suffixes)
    {
        if (lower_str.length() >= suffix.length() &&
            lower_str.substr(lower_str.length() - suffix.length()) == suffix)
        {
            // cout << "Erased " << str << ": ";
            str.erase(str.length() - suffix.length());
            // cout << str << '\n';
            return str;
        }
    }

    return str;
}
int main()
{
    long N, M;

    /**
     * Read files
     */
    cin >> N;
    vector<Document> documents;
    for (long i = 0; i != N; ++i)
    {
        string filename;
        cin >> filename;
        filename_to_long.insert({filename, filename_index});
        documents.push_back(Document(filename_index)); // Corrected line
        Document &cur_doc = documents[filename_index]; // Index should start from 0
        ++filename_index;

        while (true)
        {
            string word;
            cin >> word;
            if (word == "#")
                break;
            stem_analysis(word); // make it case-insensitive and remove the stems
            auto it = cur_doc.word_cnt.find(word);
            if (it != cur_doc.word_cnt.end())
            {
                // `word` already exists
                ++it->second;
            }
            else
            {
                // `word` is new
                cur_doc.word_cnt.insert({word, 1});
            }
        }

        cur_doc.calc_l2_squared();
        // cout << filename << ": " << cur_doc.l2_squared << '\n';
        // for (auto &i : cur_doc.word_cnt)
        // {
        //     cout << "(\"" << i.first << "\": " << i.second << ", ";
        // }
        // cout << "\n\n";
    }

    /**
     * Queries
     */
    cin >> M;
    for (long i = 0; i != M; ++i)
    {
        string filename_1, filename_2;
        cin >> filename_1 >> filename_2;
        auto it1 = filename_to_long.find(filename_1);
        auto it2 = filename_to_long.find(filename_2);
        if (it1 != filename_to_long.end() && it2 != filename_to_long.end())
        {
            double angle_dis = compare_docs(documents[it1->second], documents[it2->second]);
            cout << "Case " << i + 1 << ": " << setiosflags(ios::fixed) << setprecision(3) << angle_dis << '\n';
        }
    }

    return 0;
}

void Document::calc_l2_squared()
{
    l2_squared = 0;
    for (auto &i : word_cnt)
    {
        l2_squared += (long long)i.second * (long long)i.second;
        if (l2_squared < 0)
        {
            int *null_ptr = nullptr;
            *null_ptr = 0; // Dereferencing a null pointer to trigger segmentation fault
        }
    }
}
