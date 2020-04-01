#include <iostream>
#include <sstream>
#include <random>
#include <vector>

using namespace std;

int main()
{
    while (!cin.eof())
    {
        string s{};
        cout<<"Skriv en mening: ";

        getline(cin, s);

        stringstream ss{s};
        vector<string> v{};
        string new_s{};

        while (ss >> new_s)
            v.push_back(new_s);

        random_device rnd;
        shuffle (begin(v),end(v),rnd);

        for (string st: v)
            cout << st << " ";
        cout << endl << endl;
    }
    return 0;
}
