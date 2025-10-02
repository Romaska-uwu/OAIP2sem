#include <iostream>
#include <vector>
using namespace std;

struct ExamResult {   
    string fullName;
    int numExams;
    vector<int> grades;
};

bool allExamsPassedWithGrades4And5(const ExamResult& result) {
    for (int grade : result.grades) {
        if (grade < 4) {
            return false;
        }
    }
    return true;
}

float calculateSuccessRate(const vector<ExamResult>& results) {
    int passedCount = 0;
    for (const ExamResult& result : results) {
        if (allExamsPassedWithGrades4And5(result)) {
            passedCount++;
        }
    }
    return static_cast<float>(passedCount) / results.size() * 100;
}

int main() {
    setlocale(LC_CTYPE, "Rus");
    vector<ExamResult> examResults = {
        {"Иванов Иван Иванович", 3, {5, 4, 5}},
        {"Петров Петр Петрович", 2, {3, 4}},
        {"Сидоров Сидор Сидорович", 4, {4, 5, 4, 5}},
        {"Алексеев Алексей Алексеевич", 1, {3}}
    };

    float successRate = calculateSuccessRate(examResults);

    cout << "Успеваемость студентов: " << successRate << "%\n";

    return 0;
}