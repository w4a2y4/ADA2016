#include <iostream>
#include <stdio.h>
using namespace std;

int main() {

	int N, M, n[355], p[355], s[355]; 
	scanf("%d%d", &N, &M);
	//cin >> N >> M;
	for ( int i=1; i<=N; i++ )
		scanf("%d%d%d", &n[i], &p[i], &s[i]);
		//cin >> n[i] >> p[i] >> s[i];

	long long int dp[N+1][M+1];

	//set base case
	for( int j=0; j<=M; j++ ) dp[0][j] = 0;

	for( int i=1; i<=N; i++ ) {
		for( int j=0; j<=M; j++ ) {

			long long int max = dp[i-1][j];
			int pp=p[i], ss=s[i];

			for( int k=1; k<=n[i]; k++, pp+=p[i], ss+=s[i] ) {
				if ( j >= pp ) {
					long long int tmp = 1L * ( ss + dp[i-1][j-pp] );
					if( tmp > max ) max = tmp;
				}
			}

			dp[i][j] = max;
		}
	}

	cout << dp[N][M] << endl;

	return 0;
}