#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <algorithm> 
#include <unordered_set>
#include <unordered_map>
#include <functional>

std::mutex mtx;
std::unordered_set<std::string> words_set;
std::unordered_map<std::string, int> words_map;

std::unordered_map<std::string, char> SPLITS_LUT
{
    {"split -s",' '},
    {"split -c",','},
    {"split -n",'\n'}
};

std::unordered_map<std::string,std::function<
                bool(const std::string&, const std::string&)>> SORTS_LUT
{
    {"sort -a",std::greater<std::string>()},
    {"sort -d",std::less<std::string>()}
};

static void Tolower(std::string& input) 
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
}

static bool Is_not_Alphabetic(char c) 
{
    return !std::isalpha(c);
}

static void Remove_non_Alphabetic(std::string& input) 
{
    input.erase(std::remove_if(input.begin(), input.end(),Is_not_Alphabetic), input.end());
}

static void FixWord(std::string& word)
{
    Tolower(word);
    Remove_non_Alphabetic(word);
}

void Read_file(const std::string& file_name) 
{
    std::ifstream file(file_name); //Stream class to read from files
    if(file.is_open()) 
    {
        std::string word;
        while(file >> word) //Read words from the file until end of file or error
        {
            std::lock_guard<std::mutex> lock(mtx);
            words_set.insert(word);
            words_map[word]++;
        }
    }
    else 
    {
        std::cerr << "Error reading " << file_name << std::endl;
    }
}

void Write_file(const std::string& file_name) 
{
    std::ofstream file(file_name); //Stream class to writh on files
    if(file.is_open()) 
    {
        std::string word;
        while(!words_set.empty()) 
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!words_set.empty()) 
                {
                    auto it = words_set.begin();
                    word = *it;
                    words_set.erase(it);
                }
            }

            if(!word.empty()) 
            {
                FixWord(word);
                file << word << std::endl;
            }

            else 
            {
                break;
            }
        }
    }
    else 
    {
        std::cerr << "Error writing " << file_name << std::endl;
    }
}

int Find_most_common_word(std::string& most_common_word)
{
    int result = 0;
    for(auto it = words_map.begin(); it != words_map.end(); ++it)
    {
        if(result < it->second)
        {
            result = it->second;
            most_common_word = it->first;
        }
    }

    return result;
}

void Sort_file(const std::string& file_name, const std::string& sort_dir,
                const std::string& split) 
{
    std::ifstream file_input(file_name); //Stream class to writh on files
    if(file_input.is_open())
    {
        std::vector<std::string> words;
        std::string word;

        while(file_input >> word) 
        {
            words.push_back(word);
        }

        file_input.close();

        std::sort(words.begin(), words.end(), SORTS_LUT[sort_dir]);

        std::ofstream file_output(file_name);
        if (!file_output.is_open()) 
        {
            std::cerr << "Error opening " << file_name << " for writing" << std::endl;
            return;
        }

        for (const std::string& sorted_word : words) 
        {
            file_output << sorted_word << SPLITS_LUT[split];
        }

        file_output.close();
    }

    else 
    {
        std::cerr << "Error writing " << file_name << std::endl;
    }

}