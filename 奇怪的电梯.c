#include<bits/stdc++.h>
using namespace std;
#define N 205
struct Node
{
	int x, s;
	Node(){}
	Node(int a, int b):x(a), s(b){}
};
int n, a, b, np, k[N];
bool vis[N];
int bfs()
{
    queue<Node> que;
	vis[a] = true;
	que.push(Node(a, 0));
	while(que.empty() == false)
	{
		Node u = que.front();
		que.pop();
		if(u.x == b)
			return u.s;
		int x[2] = {u.x + k[u.x], u.x - k[u.x]};
		for(int i = 0; i < 2; ++i)
		{
    		if(x[i] >= 1 && x[i] <= n && vis[x[i]] == false) 
    		{
    			vis[x[i]] = true;
    			que.push(Node(x[i], u.s + 1));
    		}
    	}
	}
	return -1;
}
int main()
{
	cin >> n >> a >> b;
	for(int i = 1; i <= n; ++i)
		cin >> k[i];
	cout << bfs();
	return 0;
}
