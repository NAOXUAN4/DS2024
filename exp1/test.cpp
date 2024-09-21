#include <bits/stdc++.h>
#include "utilities/vector/iyan_vector.h"
#define ll long long
using namespace std;


void print(int &a)
{
    cout << a << " ";
}

int main() 
{
    iyan_vector<int> v;
    for (int i = 0; i < 5; i++)
    {
        v.push_Back(i/2);
        cout << v[i] << " ";
    }
    cout << endl;
    v.deduplicate();
    v.traverse(print);
    increase(v);

    cout << endl;
    v.traverse(print);

    cout<< endl <<v.size() << endl;
    

}
