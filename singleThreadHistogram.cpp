#include <iostream>
#include <fstream>
#include <array>

// Number of letters (refer to uppercase letter as lowercase letter)
constexpr int num_letters = 26;

// Function to calculate the letter histogram from a file
std::array<int, num_letters> histogram(const std::string& file_path)
{
    // Define an array to store letter occurrences
    std::array<int, num_letters> letterOccurrences = {0};

    // Open the input file
    std::ifstream inputFile(file_path);

    // Check if the file is opened successfully
    if (!inputFile)
    {
        std::cerr << "Error opening the file." << std::endl;
        return letterOccurrences; // Return an empty histogram
    }

    // Read words from the file and update letter occurrences
    std::string word;
    while (std::getline(inputFile, word))
        for (char letter : word)
            if (std::isalpha(letter))
            {
                char lowercaseLetter = std::tolower(letter);
                letterOccurrences[lowercaseLetter - 'a']++;
            }

    // Close the input file
    inputFile.close();

    return letterOccurrences;
}

int main()
{
    std::array<int, num_letters> letterHistogram = histogram("/usr/share/dict/words");

    // Display the histogram of letter occurrences
    for (int i = 0; i < num_letters; ++i)
    {
        char letter = 'a' + i;
        if (letterHistogram[i] > 0)
            std::cout << "Letter: '" << letter << "', Occurrences: " << letterHistogram[i] << std::endl;
    }

    return 0;
}
