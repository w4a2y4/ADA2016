#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int p[100010];

typedef struct {
	int a;
	int b;
	long long int w;
}edge;

bool cmp( edge &x, edge &y ) {
	return( x.w < y.w );
}

int find(int &x) {
	if( x == p[x] ) return x;
	else return ( p[x] = find(p[x]) );
}

int main(void) {
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	long long int ans=0;
	cin >> n >> m;

	vector<edge> vec(m);
	for( int i=0; i<m; i++ )
		cin >> vec.at(i).a >> vec.at(i).b >> vec.at(i).w;

	bool loop=false;
	int target=n+1;
	for( int i=0; i<n; i++ ) {
		p[i] = i;
	}

	sort(vec.begin(), vec.end(), cmp);

	for( int i=0; i<m; i++ ) {
		int a=find(vec[i].a), b=find(vec[i].b), w=vec[i].w;
		if( a != b ) {
			ans += w;
			p[b] = a;
			target--;
		}
		else if( !loop ) {
			ans += w;
			loop = true;
			target--;
		}
		else if ( w < 0 ) {
			ans += w;
		}
		if( target == 0 ) break;
	}

	cout << ans << endl;

	return 0;
}