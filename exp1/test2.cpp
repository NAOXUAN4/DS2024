#include <bits/stdc++.h>
#define ll long long
using namespace std;


int countOnes(int n)
{ 
    int ones= 0;
    while(0< n){ones+=(1& n); n>>= 1;} return ones;
};


int counterOnes_1(int n)
{
    int ones = 0;
    while(n!=0)
    {
        ones++;
        n= n&(n-1);
    }
    return ones;

}


int main() 
{

    int n;
    cin>>n;
    cout<<"1: "<< countOnes(n) <<"  2: "<<counterOnes_1(n);


    return 0;
}
