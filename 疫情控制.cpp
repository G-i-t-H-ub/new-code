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
int guard[MAX];//是否驻守
int Other_num[MAX]; int used[MAX], army[MAX];

//f[i][j]表示节点j向上走2^j步后到达哪个节点
/* f[i][0]等于i的父节点
若j不等于0 则可向上走2^（j-1）步，再向上走2^（j-1）步
f【i】【j】= f[f[i][j-1]][j-1]
*/
LL Rest_min[MAX], dis[MAX][22];
int f[MAX][22];
struct Edge {
	int to;			//出边
	int next;
	int weight;		//权值
}edge[MAX];

struct node {
	int id;
	LL rest;
}rest_army[MAX], gap[MAX];

void DFS(int x, int father, LL depth) {
	f[x][0] = father;			//父亲节点存入
	dis[x][0] = depth;

	for (int i = 1; i <= 17; i++) {
		f[x][i] = f[f[x][i - 1]][i - 1];//状态转移 2^i=2^(i-1)+2^(i-1)
		dis[x][i] = dis[x][i - 1] + dis[f[x][i - 1]][i - 1]; //距离的倍增式不要忘加dis[x][i - 1]
	}
	
	for (int i = first[x]; i; i = edge[i].next) {//遍历所有的出边
		if (edge[i].to != father)//因为是出边，所以要避免回到父亲结点上去
			DFS(edge[i].to, x, edge[i].weight);//访问儿子结点，并标记自己是父亲结点
	}
}

void input(int x, int y, int z) {
	edge[++tot].to = y;//存储结点
	edge[tot].weight = z;//新建边权值
	edge[tot].next = first[x];//形成链表
	first[x] = tot;//标记结点位置
}

int checkok(int x, int fath) {
	bool no_gap = 1;//判断有没有空隙
	bool have_son = 0;//判断有没有子节点
	if (guard[x]) return 1;//若已被驻守，返回true

	for (int i = first[x]; i; i = edge[i].next) {//遍历所有出边
		if (edge[i].to == fath) continue;//
		have_son = 1;//有
		if (!checkok(edge[i].to, x)) {
			no_gap = 0;//有空隙
			if (x == 1) {
				gap[++Num_gap].id = edge[i].to;
				gap[Num_gap].rest = edge[i].weight;
			}
			else return 0;
		}
	}

	if (!have_son) return 0;
	else return no_gap;
	//如果没有孩子且没有军队在此驻守，返回false
	//有孩子，有一条空隙则返会false
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
	//初始化

	int num, x;

	for (int i = 1; i <= m; i++) {
		x = army[i];
		num = 0;
		for (int j = 17; j >= 0; j--) {//3. 上提
			if (f[x][j] > 1 && num + dis[x][j] <= LIM) {
				num += dis[x][j];
				x = f[x][j];
			}
		}
		if (f[x][0] == 1 && LIM - num - dis[x][0] >= 0) {//4. 空闲军队的处理
			rest_army[++Rest_army].id = i;
			rest_army[Rest_army].rest = LIM - num - dis[x][0];//经过根节点后还能走多远
			if (!Other_num[x] || Rest_min[x] > rest_army[Rest_army].rest) {
				Other_num[x] = i;
				Rest_min[x] = rest_army[Rest_army].rest;
			}
		}
		else guard[x] = 1;//否则就在此节点驻守
	}

	if (checkok(1, 0)) return 1;//5. 求出根节点中有哪些子节点是有空隙到叶节点的，存入gap数组，

	//6. 贪心
	sort(rest_army + 1, rest_army + Rest_army + 1, compare);
	sort(gap + 1, gap + Num_gap + 1, compare);//对两个数组从大到小排序，来保证每一步最优

	used[0] = 1;
	int now = 1;
	for (int i = 1; i <= Num_gap; i++) {
		if (!used[Other_num[gap[i].id]]) {
			used[Other_num[gap[i].id]] = 1;
			continue;
		}//如果此节点行程最小的空闲军队没有被只用，那么这个军队直接在此驻守

		while (now <= Rest_army && (used[rest_army[now].id] || rest_army[now].rest < gap[i].rest)) now++;
		//若不行则遍历一遍，寻找可以经过根节点来到此节点的空闲军队。
		if (now > Rest_army) return 0;//若遍历完还没有，则返回false
		used[rest_army[now].id] = 1;//标记已使用
	}
	return 1;
}
int main()
{
	cout << "请输入：" << endl;
	cin >> n;    //输入城市数

	for (int i = 1; i <= n - 1; i++)	//树 n个节点 n-1条边
	{
		int u, v, w;		//出边 入边 权值
		cin >> u >> v >> w;
		//建立城市u、v之间边的关系，即双向道路相互连通构成一棵树
		input(u, v, w);
		input(v, u, w);
	}
	//预处理出每个节点的深度
	DFS(1, 0, 0);
	//军队数目
	cin >> m;
	//输入军队驻扎的城市
	for (int i = 1; i <= m; i++) {
		cin >> army[i];
	}
	int l = 1, r = 500000;
	LL ans = 0;
	int mid;
	while (l <= r) {//2. 二分答案
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
