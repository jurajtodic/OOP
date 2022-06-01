#include <iostream>
#include<numeric>
#include <fstream>
#include<sstream>
#include <algorithm>

using namespace std;

struct Student {
    int scores[5];
    Student();
    void fillScores(int(& arr)[5]); // po referenci prihvacamo polje (arr) duljine 5 tipa int
    int calculateTotalScore() const;
    void print() const;
};

Student :: Student() : scores{} {}

void Student :: fillScores(int (& arr)[5]) {
    unsigned int i {0};
    for (auto el : arr)
        scores[i++] = el;
} 

int Student :: calculateTotalScore() const {
    return accumulate(scores, scores+5, 0.0);
}

void Student :: print() const {
    for (int i = 0; i<5; i++)
        cout << scores[i] << "\t";
    cout << endl;
}

int grade;

bool gradeGreaterThan (const Student& s) {
    return s.calculateTotalScore() >= grade;
}


int main () 
{
    ifstream inFile("data.txt"); // inFile je objekt koji predstavlja file
    string line{}; // u line cemo puniti redke data.txt-a

    int n;
    getline(inFile, line); // parsiramo prvi redak datoteke, line = "3"
    istringstream iss{line}; // "3" pretvaramo u int 3
    iss >> n; // 3 spremamo u n

    Student* students = new Student [n]; 

    int i = 0;
    while (getline(inFile, line)) { // uzimamo redke datoteke
        istringstream iss{line}; 
        int arr[5]; // ocjene svakog studenta
        for (auto& el : arr) // mora biti po referenci
            iss >> el; // stavljla intove iz stringa u listu
        students[i++].fillScores(arr); // students[0] = [30, 40, 45, 10, 10]
    }

    //students = [[30, 40, 45, 10, 10], [40, 40, 40, 10, 10], [50, 20, 30, 10, 10]]

    grade = students[0].calculateTotalScore();

    cout <<count_if(students+1, students + n, gradeGreaterThan) << endl;
    delete [] students;
    return 0;
}