#include <ostream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "program.cpp"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3>" << std::endl;
        return 1;
    }

    std::cout << "enter your options" << std::endl;
    std::string sort_dir = "sort -d";
    std::string split = "split -n";

    while(true)
    {
        std::string line;
        std::getline(std::cin, line);
        if(line == "go")
        {
            break;
        }
        auto it = SORTS_LUT.find(line);
        if(it != SORTS_LUT.end())
        {
            sort_dir = line;
        }

        auto it2 =  SPLITS_LUT.find(line);
        if(it2 != SPLITS_LUT.end())
        {
            split = line;
        }
    }

    std::thread thread1(Read_file, argv[1]);
    std::thread thread2(Read_file, argv[2]);
    std::thread thread3(Read_file, argv[3]);

    thread1.join();
    thread2.join();
    thread3.join();

    std::thread write_thread(Write_file, "F4.txt");
    write_thread.join();

    Sort_file("F4.txt",sort_dir,split);

    std::string most_common_word("");
    int count = Find_most_common_word(most_common_word);

    std::cout << "the most common word is: '" << most_common_word << "' and "
                "it appears " << count << " times." << std::endl;


    return 0;
}

