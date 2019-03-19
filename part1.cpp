#include <iostream>
#include <queue> 
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;
bool g[310][310], pass[310];
int sorted[310];

void dfs( int now, int v, int &time ) {
	pass[now] = true;
	for( int i=0; i<v; i++ )
		if( g[now][i] && !pass[i] )
			dfs( i, v, time );
	sorted[time] = now;	time--;
	return;
}

int main(void) {

	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int v;
	cin >> v;
	for( int i=0; i<v; i++ ) {
		pass[i] = false;
		for ( int j=0; j<v; j++ )
			cin >> g[i][j];
	}

	//do topological sort
	int time = v-1;
	for( int i=0; i<v; i++ )
		if( pass[i] == false )
			dfs( i, v, time);

	//dp
	int ans[310][310];
	for( int ii=v-1; ii>=0; ii-- ) {
		int i = sorted[ii];
		for( int jj=ii; jj<v; jj++ ) {
			int j = sorted[jj];
			if( g[i][j] ) ans[i][j] = 1;
			else ans[i][j] = 0;
			for( int kk=ii+1; kk<jj; kk++ ) {
				int k = sorted[kk];
				if ( g[i][k] ) {
					ans[i][j] += ans[k][j];
					ans[i][j] %= 10;
				}
			}
		}
	}

	// print answer
	for( int i=0; i<v; i++ ) {
		cout << ans[i][0];
		for( int j=1; j<v; j++ )
			cout << " " << ans[i][j];
		cout << endl;
	}

	return 0;
}
