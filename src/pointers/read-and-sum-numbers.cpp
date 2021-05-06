/**
 * Your program must read N that is the number of double
 * notes that a teacher must enter. Then, you should read
 * the N Notes. You must report the sum of the notes onthe
 * screen. You must round two decimals the resulting sum. 
 **/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int exams;
    double grade;
    double totalGrade = 0;

    cout << "Enter the number of exams: ";
    cin >> exams;
    for (int i = 0; i < exams; i++)
    {
        cout << "Enter the gade of exam " << i + 1 << ": ";
        cin >> grade;
        totalGrade += grade;
    }
    cout << "Sum of grades is: " << fixed << setprecision(2) << totalGrade << endl;

    double average = totalGrade / exams;
    cout << "Average: " << fixed << setprecision(2) << average << endl;

    return 0;
}
