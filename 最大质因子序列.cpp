#include<bits/stdc++.h>
using namespace std;
bool isPrime(int n)
{
	for(int i = 2; i <= sqrt(n); ++i)
		if(n%i == 0)
			return false;
	return true;
}
int maxPrimeFactor(int n)
{
	for(int i = 1; i <= sqrt(n); ++i)
		if(n%i == 0 && isPrime(n/i))
			return n/i;
}
int main()
{
    int m, n;
    cin >> m >> n;
    bool isFirst = true;
    for(int i = m; i <= n; ++i)
    {
    	if(isFirst)
    		isFirst = false;
    	else
    		cout<<',';
    	cout << maxPrimeFactor(i);
	}
	return 0;
}
