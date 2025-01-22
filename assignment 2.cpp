#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>

class Person {
private:
    std::string FirstName;
    std::string Surname;
    std::vector<float> HomeworkScores;
    float ExamScore;
    float FinalAverageGrade;
    float FinalMedianGrade;

    void CalculateFinalGrades() {
        float average = 0.0f;
        if (!HomeworkScores.empty()) {
            average = std::accumulate(HomeworkScores.begin(), HomeworkScores.end(), 0.0f) / HomeworkScores.size();
        }
        float median = GetMedian(HomeworkScores);
        FinalAverageGrade = 0.4f * average + 0.6f * ExamScore;
        FinalMedianGrade = 0.4f * median + 0.6f * ExamScore;
    }

    float GetMedian(std::vector<float>& scores) {
        size_t size = scores.size();
        if (size == 0) return 0;

        std::sort(scores.begin(), scores.end());
        size_t mid = size / 2;

        if (size % 2 == 0) {
            return (scores[mid - 1] + scores[mid]) / 2.0f;
        } else {
            return scores[mid];
        }
    }

public:
    Person(const std::string& firstName, const std::string& surname, const std::vector<float>& homeworkScores, float examScore)
    : FirstName(firstName), Surname(surname), HomeworkScores(homeworkScores), ExamScore(examScore) {
        CalculateFinalGrades();
    }

    Person(const Person& other)
    : FirstName(other.FirstName), Surname(other.Surname), HomeworkScores(other.HomeworkScores),
      ExamScore(other.ExamScore), FinalAverageGrade(other.FinalAverageGrade), FinalMedianGrade(other.FinalMedianGrade) {}

    Person& operator=(const Person& other) {
        if (this != &other) {
            FirstName = other.FirstName;
            Surname = other.Surname;
            HomeworkScores = other.HomeworkScores;
            ExamScore = other.ExamScore;
            FinalAverageGrade = other.FinalAverageGrade;
            FinalMedianGrade = other.FinalMedianGrade;
        }
        return *this;
    }

    static Person InputData(const std::string& inputLine) {
        std::istringstream stream(inputLine);
        std::string firstName, surname;
        std::vector<float> homeworkScores;
        float score;

        stream >> firstName >> surname;
        while (stream >> score) {
            homeworkScores.push_back(score);
        }
        float examScore = homeworkScores.back();
        homeworkScores.pop_back();

        return Person(firstName, surname, homeworkScores, examScore);
    }

    void OutputData() {
        std::cout << std::left << std::setw(15) << FirstName
                  << std::setw(15) << Surname
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << FinalAverageGrade
                  << " | " << std::setw(15) << std::fixed << std::setprecision(2) << FinalMedianGrade << std::endl;
    }
};

int main() {
    std::string filePath = "homeworks.txt";
    std::ifstream file(filePath);
    std::string line;

    std::cout << std::left << std::setw(15) << "Name"
              << std::setw(14) << "Surname"
              << std::setw(15) << "Final (Avg.)| " << std::setw(15) << "Final (Med.)" << std::endl;

    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    getline(file, line); // skip first line for file title

    while (std::getline(file, line)) {
        if (!line.empty()) {
            Person student = Person::InputData(line);
            student.OutputData();
        }
    }

    return 0;
}
