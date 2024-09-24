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
        v.push_Back(rand()%10);
    }
    cout << endl;
    // v.deduplicate();
    v.traverse(print);

    cout<<endl<<v.size()<<endl;

    v.sort(0,5,1);

    v.traverse(print);

    

}
