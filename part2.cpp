#include <iostream>
#include <set>

using namespace std;

int main(void) {

	ios::sync_with_stdio(0);
	cin.tie(0);	cout.tie(0);

	int v;
	cin >> v;

	bool g[v][v];
	int num[v][v], cmp[v][v];
	set<int> unsort;

	//read data
	for( int i=0; i<v; i++ ) {
		unsort.insert(i);
		for( int j=0; j<v; j++ ) {
			cin >> num[i][j];
			cmp[i][j] = num[i][j];	
			g[i][j] = false;
		}
	}

	//get topological sort
	int sorted[v];
	for( int cnt=0; cnt<v; cnt++ ) {
		for( set<int>::iterator it=unsort.begin(); it!=unsort.end(); it++ ) {
			int i = *it;
			set<int>::iterator jt;
			for( jt=unsort.begin(); jt!=unsort.end(); jt++ ) 
				if( num[*jt][i] ) break;
			if( jt == unsort.end() ) {
				unsort.erase(i);
				sorted[cnt] = i;
				break;
			}
		}
	}

	// dp
	for( int ii=0; ii<v; ii++ ) {
		int i = sorted[ii];
		for( int jj=ii-1; jj>=0; jj-- ) {
			int j = sorted[jj];
			for( int kk=jj-1; kk>=0; kk-- ) {
				int k = sorted[kk];
				if( g[k][j] ) cmp[k][i] -= num[j][i];
				while( cmp[k][i] < 0 ) cmp[k][i] += 10;
			}
			if( cmp[j][i] ) {
				g[j][i] = true;
				cmp[j][i] --;
			}
		}
	}

	// print answer
	for( int i=0; i<v; i++ ) {
		cout << g[i][0];
		for( int j=1; j<v; j++ )
			cout << " " << g[i][j];
		cout << endl;
	}

	return 0;
}
