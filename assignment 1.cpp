#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>

class Person
{
private:
    std::string FirstName;
    std::string Surname;
    std::vector<float> HomeworkScores;
    float ExamScore;
    float FinalGrade;

    void CalculateFinalGrade()
    {
        float homeworkAverage = std::accumulate(HomeworkScores.begin(), HomeworkScores.end(), 0.0f) / HomeworkScores.size();
        FinalGrade = 0.4f * homeworkAverage + 0.6f * ExamScore;
    }

public:
    Person(const std::string &firstName, const std::string &surname, const std::vector<float> &homeworkScores, float examScore)
        : FirstName(firstName), Surname(surname), HomeworkScores(homeworkScores), ExamScore(examScore)
    {
        CalculateFinalGrade();
    }

    Person(const Person &other)
        : FirstName(other.FirstName), Surname(other.Surname), HomeworkScores(other.HomeworkScores),
          ExamScore(other.ExamScore), FinalGrade(other.FinalGrade) {}

    Person &operator=(const Person &other)
    {
        if (this != &other)
        {
            FirstName = other.FirstName;
            Surname = other.Surname;
            HomeworkScores = other.HomeworkScores;
            ExamScore = other.ExamScore;
            FinalGrade = other.FinalGrade;
        }
        return *this;
    }

    ~Person() {}

    static Person InputData(const std::string &inputLine)
    {
        std::istringstream stream(inputLine);
        std::string firstName;
        std::string surname;
        std::vector<float> homeworkScores;
        float score;
        float examScore;

        stream >> firstName >> surname;
        while (stream >> score && stream.peek() != '\n')
        {
            homeworkScores.push_back(score);
        }
        examScore = homeworkScores.back();
        homeworkScores.pop_back();

        return Person(firstName, surname, homeworkScores, examScore);
    }

    void OutputData() const
    {
        std::cout << std::left << std::setw(15) << FirstName
                  << std::setw(15) << Surname
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << FinalGrade << std::endl;
    }
};

int main()
{
    std::string filePath = "students10000.txt";
    std::ifstream file(filePath);
    std::string line;

    std::cout << std::left << std::setw(15) << "Name"
              << std::setw(15) << "Family"
              << std::setw(15) << "Final_Point (Aver.)" << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    getline(file, line); // skip first line for file title

    while (getline(file, line))
    {
        if (!line.empty())
        {
            Person student = Person::InputData(line);
            student.OutputData();
        }
    }

    return 0;
}
