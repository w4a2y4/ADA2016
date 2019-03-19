#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

vector<int> adj[20000], jda[20000];

void dfs( int now, int list[], bool visited[], int &index ) {
	visited[now] = true;
	for( int i=0; i<adj[now].size(); i++ )
		if( !visited[ adj[now].at(i) ] )
			dfs( adj[now].at(i), list, visited, index );
	list[index] = now;	index--;
	return;
}

int main(void) {

	int m, n;
	scanf("%d%d", &n, &m);
	
	for( int i=0; i<m; i++ ) {
		int a, b, s;
		scanf("%d%d%d", &a, &b, &s);
		if(!s) {	//normal road
			adj[b-1].push_back(a-1);				//happy: backward
			jda[a-1].push_back(b-1);		
			adj[a+n-1].push_back(b+n-1);	//normal: foreward
			jda[b+n-1].push_back(a+n-1);
		}
		else {		//special road
			adj[a+n-1].push_back(b-1);			//normal -> happy
			jda[b-1].push_back(a+n-1);
			adj[b-1].push_back(a+n-1);			//happy -> normal
			jda[a+n-1].push_back(b-1);
		}
	}

	//DFS 1
	bool visited[20000];
	for( int i=0; i<2*n; i++ )
		visited[i] = false;
	int topo[20000], index=2*n-1;
	for( int i=0; i<2*n; i++ )
		if( !visited[i] )
			dfs(i, topo, visited, index);

	int grp[2*n];
	for( int i=0; i<2*n; i++ ) {
		visited[i] = false;
		grp[i] = -1;
	}

	stack<int> s;
	int cnt = 0;
	
	//SCC
	for( int i=0; i<2*n; i++ ) {
		if( !visited[topo[i]] ) {
			s.push(topo[i]);
			while( !s.empty() ) {
				int cur = s.top();
				s.pop();
				grp[cur] = cnt;
				visited[cur] = true;
				for(int j=0; j<jda[cur].size(); j++)
					if( !visited[ jda[cur].at(j) ] )
						s.push( jda[cur].at(j) );
			}
			cnt++;
		}
	}

	//count elements
	int gcnt[2*n];
	for( int i=0; i<2*n; i++ )
		gcnt[i] = 0;
	for( int i=0; i<n; i++ ) {
		gcnt[(grp[i])]++;
		if( grp[i] != grp[i+n] )
			gcnt[(grp[i+n])]++;
	}

	// print answer
	for( int i=0; i<n; i++ )
		printf("%d\n", gcnt[(grp[i])]);

	return 0;
}