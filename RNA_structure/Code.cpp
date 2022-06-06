#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

#define MAX_N 1001

#define DPRINTC(C) printf(#C " = %c\n", (C))
#define DPRINTS(S) printf(#S " = %s\n", (S))
#define DPRINTD(D) printf(#D " = %d\n", (D))
#define DPRINTLLD(LLD) printf(#LLD " = %lld\n", (LLD))
#define DPRINTLF(LF) printf(#LF " = %.5lf\n", (LF))

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

long long int n;
string A;
long long int dp[MAX_N][MAX_N];


/**
 * A boolean function to check whether the pairs possible are base pairs
 *@param X , reportedly the first base of the pair
 *@param Y , reportedly the second base of the pair
 *@return  this function returns that the conditional pairs are valid or not.
*/

bool complement(char X, char Y)
{
    return ((X == 'A' && Y == 'U') || (X == 'U' && Y == 'A') 
    || (X == 'C' && Y == 'G') || (X == 'G' && Y == 'C'));
   
}





/**
 * This function is to obtain all possible pairs with inline to rules
 *@param i , reportedly the first end of the pair
 *@param j , reportedly the second end of the pair
 *@return  this function returns maximum no. of base pairs possible in secondary structure.
*/

long long int possiblepairs(long long int i, long long int j)
{
    if (dp[i][j] != -1) 
        return dp[i][j];
    
    // No sharp turns
    if (i >= j - 4)
    {
        dp[i][j] = 0;
        return 0;
    }
    
    long long int ret = 0;
    ret = max(ret, possiblepairs(i + 1, j));    
    ret = max(ret, possiblepairs(i, j - 1));
    // No knots
    if (complement(A[i], A[j])) ret = max(ret, possiblepairs(i + 1, j - 1) + 1);
    for (long long int k=i+1;k<j;k++)
    {
        ret = max(ret, possiblepairs(i, k) + possiblepairs(k + 1, j));
    }
    
    dp[i][j] = ret;
    return ret;
}
inline long long int possiblepairs()
{
    for (long long int i=0;i<n;i++)
    {
        for (long long int j=0;j<n;j++)
        {
            dp[i][j] = -1;
        }
    }
    
    return possiblepairs(0, n - 1);
}




/**
 * This function is to obtain the desired braceted string.
 *@param i , reportedly the first end of the pair
 *@param j , reportedly the second end of the pair
 *@return  this function returns the the rna string with correct division of pairs using brackets.
*/

string bracketing(long long int i, long long int j)
{
    if (i == j) return A.substr(i, 1);
    if (i > j) return "";
    
    if (possiblepairs(i, j) == possiblepairs(i + 1, j))
    {
        string left = A.substr(i, 1);
        return left + bracketing(i + 1, j);
    }
    
    if (possiblepairs(i, j) == possiblepairs(i, j - 1))
    {
        string right = A.substr(j, 1);
        return bracketing(i, j - 1) + right;
    }
    
    if (complement(A[i], A[j]) && possiblepairs(i, j) == possiblepairs(i+1, j-1) + 1)
    {
        string left = A.substr(i, 1);
        string right = A.substr(j, 1);
        cout << left << " " << right << endl;
        return "(" + left + bracketing(i+1, j-1) + right + ")";
    }
    
    for (long long int k=i+1;k<j;k++)
    {
        if (possiblepairs(i, j) == possiblepairs(i, k) + possiblepairs(k + 1, j))
        {
            return bracketing(i, k) + bracketing(k + 1, j);
        }
    }
    
    return "FAIL"; // should never happen!
}



int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    long long int no_of_rna;
    cin >> no_of_rna;
    
    while(no_of_rna--){
        A.clear();
        cin>>A;
        cout << "-----------------------------------------" << endl;
        cout << A << endl;
        n = A.length();
        
        cout << possiblepairs() << endl;
        cout << bracketing(0, n - 1) << endl;
        cout << "-----------------------------------------" << endl;

    }  

    return 0;
}