#include <iostream>
#include <queue> 
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int min( int &a, int &b ) {
	if( a < b ) return a;
	else return b;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	queue<int> q;
	int n, m, a, b;
	cin >> n >> m >> a >> b;

	set<int> adj[100010];
	int vertice[100010];
	int level[100010];
	set<int> unreach;

	// init
	for( int i=0; i<=n; i++ ) {
		vertice[i] = 0;
		unreach.insert(i);
		level[i] = 0;
	}
	for( int i=0; i<m; i++ ) {
		int u, v;
		cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
	}

	if( a == b ) {
		cout << 0;
		for( int i=1; i<n; i++ )
			cout << " " << a;
		cout << endl;
	}

	else if( a < b ) {

		q.push( 1 );
		int biggest = b/a;
		unreach.erase(0);
		unreach.erase(1);

		while( !q.empty() ) {
			int tmp = q.front();
			q.pop();
			for( set<int>::iterator ptr = adj[tmp].begin(); ptr!=adj[tmp].end(); ptr++ ) {
				int node = *ptr;
				if( unreach.find(node)!=unreach.end() ) {
					unreach.erase(node);
					vertice[node] = min( (vertice[tmp])+a, b) ;
					q.push( node );
				}
			}
		}

		//print answer
		cout << 0;
		for( int i=2; i<=n; i++ ){
			if( !vertice[i] ) cout << " " << b;
			else cout << " " << vertice[i];
		}
		cout << endl;

	} 

	else {		//a>b

		unreach.erase(0);
		unreach.erase(1);
		q.push(1);
		set<int>::iterator ptr;

		int biggest = a/b;

		while( !q.empty() ) {

			int tmp = q.front();
			if( level[tmp] >= biggest ) break;
			q.pop();
			ptr = unreach.begin();

			// for every unreached point, check if it can directly reach from [tmp]
			while(  ptr != unreach.end() ) {
				int node = *ptr;
				if( adj[tmp].find(node) == adj[tmp].end() ) {
					vertice[node] = min( vertice[tmp]+b, a) ;
					level[node] = level[tmp] +1;
					q.push( node );
					unreach.erase(node);
					if( unreach.empty() ) break;
					ptr = unreach.lower_bound(node);
				}
				else ptr++;
			}

		}

		printf("0");
		for( int i=2; i<=n; i++ ){
			if( !vertice[i] ) printf(" %d", a);
			else printf(" %d", vertice[i]);
		}
		printf("\n");

	}

	return 0;
}