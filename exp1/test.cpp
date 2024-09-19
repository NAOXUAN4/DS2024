#include <bits/stdc++.h>
#include "utilities/vector/iyan_vector.h"
#define ll long long
using namespace std;

int main() 
{
    iyan_vector<int> v;
    
    v[0] = 1;
    v[1] = 1;

    int x = v.size();
    cout << x<<endl;

    cout<<eq(v[0], v[1])<<endl;
    return 0;
}
