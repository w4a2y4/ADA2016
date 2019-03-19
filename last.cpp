#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cstring>
#include <vector>

using namespace std;

int hasEOF = 0, V, E, ans[100000], M = 0;
clock_t start;
vector<int> adj[100000];
bool reach[100000];

int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;   
        }
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
void print_ans() {
	int *ptr = ans;
	for( int i=0; i<M; i++ ) {
		printf("%d ", *ptr);
		ptr++;
	}
	printf("\n");
	return;
}
void dfs( int index, int ans_buf[100000], int curr, int sum ) {

	clock_t now = clock();
	if( (now-start) >= 3.98 * CLOCKS_PER_SEC ) {
		printf("%d\n", M);
		print_ans();
		exit(0);
	}

	for( int i=0; i<adj[curr].size(); i++ ) {
		int node = adj[curr].at(i);
		if( !reach[node] ) {
			reach[node] = true;
			ans_buf[index] = node;
			dfs( index+1, ans_buf, node, sum+1 );
			reach[node] = false;
		}
	}

	if( sum > M ) {
		memcpy( ans, ans_buf, sizeof(int)*100000 );
		M = sum;
	}

	return;
}

int main(void) {

	start = clock();

	//input
	int u, v;
	scanf("%d%d", &V, &E);
	for( int i=0; i<V; i++ )
		reach[i] = false;

	for( int i=0; i<E; i++ ) {
		scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int ans_buf[100000];
	// for( int i=0; i<V; i++ ) {
	for( int i=V-1; i>=0; i-- ) {
		ans_buf[0] = i;
		dfs(0, ans_buf, i, 0);
	}

	printf("%d\n", M);
	print_ans();

	return 0;
}