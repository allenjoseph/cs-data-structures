#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    int numValues;
    int sumValues = 0;

    cout << "Enter the number of variables: ";
    cin >> numValues;

    int *values = new int[numValues];

    for (int i = 0; i < numValues; i++)
    {
        cout << "Enter variable" << i + 1 << ": ";
        cin >> *(values + i);
        sumValues += *(values + i);
    }

    double mean = sumValues / numValues;
    double numerator = 0;
    for (int i = 0; i < numValues; i++)
    {
        numerator += pow((*(values + i) - mean), 2);
    }

    double sd = sqrt(numerator / (numValues - 1));
    cout << "Standard Deviation: " << fixed << setprecision(2) << sd << endl;

    return 0;
}
