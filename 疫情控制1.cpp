#include<iostream>
#include<algorithm>
#include<cstring>
#define MAX 100010
#define LL long long
using namespace std;

int n, m;
LL Rest_army, Num_gap;

int tot;
int first[MAX];
int guard[MAX];
int Other_num[MAX]; int used[MAX], army[MAX];
LL Rest_min[MAX], dis[MAX][22];
int f[MAX][22];
struct Edge {
	int to;		
	int next;
	int weight;	
}edge[MAX];

struct node {
	int id;
	LL rest;
}rest_army[MAX], gap[MAX];

void DFS(int x, int father, LL depth) {
	f[x][0] = father;			
	dis[x][0] = depth;

	for (int i = 1; i <= 17; i++) {
		f[x][i] = f[f[x][i - 1]][i - 1];
		dis[x][i] = dis[x][i - 1] + dis[f[x][i - 1]][i - 1]; 
	}
	
	for (int i = first[x]; i; i = edge[i].next) {
		if (edge[i].to != father)
			DFS(edge[i].to, x, edge[i].weight);
	}
}

void input(int x, int y, int z) {
	edge[++tot].to = y;
	edge[tot].weight = z;
	edge[tot].next = first[x];
	first[x] = tot;
}

int checkok(int x, int fath) {
	bool no_gap = 1;
	bool have_son = 0;
	if (guard[x]) return 1;

	for (int i = first[x]; i; i = edge[i].next) {
		if (edge[i].to == fath) continue;//
		have_son = 1;
		if (!checkok(edge[i].to, x)) {
			no_gap = 0;
			if (x == 1) {
				gap[++Num_gap].id = edge[i].to;
				gap[Num_gap].rest = edge[i].weight;
			}
			else return 0;
		}
	}

	if (!have_son) return 0;
	else return no_gap;
}

bool compare(node x, node y) {
	return x.rest > y.rest;
}

bool check(LL LIM) {
	Rest_army = 0;
	Num_gap = 0;
	for (int i = 1; i <= n; i++) {
		guard[i] = 0;
		Other_num[i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		used[i] = 0;
	}
	

	int num, x;

	for (int i = 1; i <= m; i++) {
		x = army[i];
		num = 0;
		for (int j = 17; j >= 0; j--) {
			if (f[x][j] > 1 && num + dis[x][j] <= LIM) {
				num += dis[x][j];
				x = f[x][j];
			}
		}
		if (f[x][0] == 1 && LIM - num - dis[x][0] >= 0) {
			rest_army[++Rest_army].id = i;
			rest_army[Rest_army].rest = LIM - num - dis[x][0];
			if (!Other_num[x] || Rest_min[x] > rest_army[Rest_army].rest) {
				Other_num[x] = i;
				Rest_min[x] = rest_army[Rest_army].rest;
			}
		}
		else guard[x] = 1;
	}

	if (checkok(1, 0)) return 1;

	
	sort(rest_army + 1, rest_army + Rest_army + 1, compare);
	sort(gap + 1, gap + Num_gap + 1, compare);

	used[0] = 1;
	int now = 1;
	for (int i = 1; i <= Num_gap; i++) {
		if (!used[Other_num[gap[i].id]]) {
			used[Other_num[gap[i].id]] = 1;
			continue;
		}

		while (now <= Rest_army && (used[rest_army[now].id] || rest_army[now].rest < gap[i].rest)) now++;
		
		if (now > Rest_army) return 0;
		used[rest_army[now].id] = 1;
	}
	return 1;
}
int main()
{
	cout << "请输入：" << endl;
	cin >> n;    

	for (int i = 1; i <= n - 1; i++)	
	{
		int u, v, w;		
		cin >> u >> v >> w;
		
		input(u, v, w);
		input(v, u, w);
	}

	DFS(1, 0, 0);

	cin >> m;

	for (int i = 1; i <= m; i++) {
		cin >> army[i];
	}
	int l = 1, r = 500000;
	LL ans = 0;
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		}
		else
			l = mid + 1;
	}

	cout << "控制疫情所需要的最少时间为：" << ans << endl;
	return 0;

} 
