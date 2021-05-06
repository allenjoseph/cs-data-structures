#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    int numElements;
    double sumValues = 0;

    cout << "Enter the number of elements: ";
    cin >> numElements;

    double value;

    for (int i = 0; i < numElements; i++)
    {
        cout << "Enter number" << i + 1 << ": ";
        cin >> value;
        sumValues += 1 / (value);
    }

    double hm = 1 / (sumValues / numElements);
    cout << "Harmonic Mean: " << fixed << setprecision(2) << hm << endl;

    return 0;
}
