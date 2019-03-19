#include <iostream>

using namespace std;

int max( int &a, int &b ) {
	if( a>b ) return a;
	else return b;
}

int main() {

	int dp[4][101], k, n;
	cin >> n >> k;
	for( int i=1; i<=k; i++ ) dp[1][i] = i;
	for( int j=1; j<=n; j++ ) dp[j][1] = 1;
	
	for( int j=2; j<=n; j++ )
		for( int i=2; i<=k; i++ ) {
			//find x
			int x, L, R;
			for( x=1; x<=i-2; x++ ) {
				L = dp[j-1][x];
				R = dp[j][i-x-1];
				if( L >= R ) break;
			}
			//fill
			dp[j][i] = 1 + max(L,R);
			//cout << "[" << j << "][" << i << "]" << dp[j][i] << " max{" << L << "," << R << "} x=" << x << endl; 
		}

	cout << "answer: " << dp[n][k] << endl; 


	return 0;
}