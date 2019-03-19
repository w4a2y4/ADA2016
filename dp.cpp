#include <iostream>

using namespace std;

int main (void) {

	int n, max_n;
	long long int sum=0, max=0;
	bool nagative = true;

	cin >> n;

	for ( int i=0; i<n; i++ ) {

		int tmp;
		cin >> tmp;

		if ( i==0 )  max_n = tmp;

		if ( tmp >= 0 ) nagative = false;
		else if ( tmp>max_n )
			max_n = tmp;

		if ( ( tmp + sum ) < 0 ) sum = 0;
		else sum += tmp;
		if( sum > max ) max = sum;
	}

	if ( nagative ) cout << max_n << endl;
	else cout << max << endl;

	return 0;
}