#include <iostream>
#include <algorithm> 
#include <stdio.h> 

using namespace std;

int p[100010], status[100010], dep[100010];
bool doo[100010], skip[100010];

bool cmp( int a, int b ) {
	if( dep[a] == dep[b] ) return a>b;
	else return dep[a] > dep[b];
}

int set( int now, int k ) {

	//base case
	if( status[now] == now ) return now; 
	if( k==0 && skip[now] )  return -1;
	if( k==0 || now==1 ) {	
		status[now] = now;
		return now;
	}

	//check
	int rely = set( p[now], k-1 );
	if( rely == -1 ) {
		if( skip[now] ) return -1;
		status[now] = now;
		return now;
	}
	else status[now] = rely;

	return rely;
}

int main() {

	//input
	int m, k, st[100010], n;
	scanf("%d%d%d", &n, &m, &k);

	for(int i=1; i<=n; i++)	{
		status[i] = 0;
		skip[i] = false;
		st[i] = i;
	}

	p[1] = 1;	dep[1] = 1;
	for(int i=2; i<=n; i++)	{
		cin >> p[i];
		dep[i] = 1+dep[(p[i])];
	}

	sort(st+1, st+n+1, cmp);

	for(int i=0; i<m; i++) {
		int tmp;
		scanf("%d", &tmp);
		if( i==0 && tmp == 1 ) {
			printf("-1\n");
			return 0;
		}
		skip[tmp] = true;
	}

	for( int i=1; i<=n; i++ ) 
		if( status[(st[i])] == 0 ) {
			int ans = set((st[i]), k);
			if ( ans == -1 ) {
				printf("-1\n");
				return 0;
			}
		}

	int cnt = 0;
	for( int i=1; i<=n; i++) 
		if( status[i] == i ) cnt ++;
	printf("%d\n", cnt);

	return 0;
}