#include <bits/stdc++.h>
#include <vector>
#define ll long long
using namespace std;

vector<int> n = {2,3,4,5};
vector<int> m = {2,3,4,5};



double binSearch_sp()
{
    //规则：左比右边多一（如果偶数）
    //      切在选定的后面的空隙1 2 3 |4  <-p
    //因此指针指向的是min_Right
    int mid_n = 0, mid_m = 0;
    int n_l=0,n_r=n.size(),m_l=0, m_r=m.size();
    

    //mid_n>0)
    while(n_l<=n_r)
    {
        mid_n = n.size()>>1;   
          //n，左边元素多于右边元素的个数  
        mid_m = (m.size() + n.size() + 1) / 2 - mid_n;

        int maxLeftX = (mid_n == 0) ? numeric_limits<int>::min() : n[mid_n - 1];
        int minRightX = (mid_n == n.size()) ? numeric_limits<int>::max() : n[mid_n];
            
        int maxLeftY = (mid_m == 0) ? numeric_limits<int>::min() : m[mid_m - 1];
        int minRightY = (mid_m == m.size()) ? numeric_limits<int>::max() : m[mid_m];
           

        if(maxLeftX<minRightY && maxLeftY<minRightX)
        {
            if ((m.size() + n.size()) % 2 == 0) {
                    return (min(minRightX,minRightY) + max(maxLeftX,maxLeftY)) / 2.0;
                } else {
                    return max(maxLeftX,maxLeftY);
                }
        }

        if(maxLeftX>minRightY){
            n_r = mid_n -1;
            
            
        } 
        else if (maxLeftY>minRightX)
        {
            n_l = mid_n + 1;
        }

       

         
        
    }


      
    

}





int main() 
{
    cout<<binSearch_sp();
    
   




    


    return 0;
}
