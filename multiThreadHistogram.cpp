#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <thread>
#include <mutex>

// Number of threads to process histogram simulatnic
const int NUM_WORKERS = 10;

// Mutex to synchronize access to shared resources
std::mutex mtx;

// Number of letters (refer to uppercase letter as lowercase letter)
constexpr int num_letters = 26;

// Wrap the critical section of getline
bool readLine(std::ifstream& inputFile, std::string& word)
{
    mtx.lock();
    std::istream& flag = std::getline(inputFile, word);
    mtx.unlock();
    return flag.good();
}
 
// Execute by each worker (thread)
void processHistogram(std::ifstream& inputFile, std::array<int, num_letters>& letterOccurrences)
{
    // Read words from the file and update letter occurrences
    std::string word;

    while (readLine(inputFile, word))
        for (char letter : word)
            if (std::isalpha(letter))
            {
                char lowercaseLetter = std::tolower(letter);
                mtx.lock();
                letterOccurrences[lowercaseLetter - 'a']++; // Critical section
                mtx.unlock();
            }
} 

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

    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_WORKERS; ++i)
        threads.emplace_back(processHistogram, std::ref(inputFile), std::ref(letterOccurrences));

    for (auto& thread : threads)
        thread.join(); // Wait for all threads to finish

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
