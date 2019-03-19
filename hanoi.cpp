#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

typedef struct {
	int num, from, to;
}record;

int t = 0;
std::vector<record> v;

void hanoi ( int now, int dest, int buf, int n) {

	if ( n==0 )	return;

	t++;
	hanoi ( now, buf, dest, n-1 );
	record tmp;
	tmp.num = n;
	tmp.from = now;
	tmp.to = dest;
	v.push_back(tmp);
	hanoi ( buf, dest, now, n-1 );

	return;
}

int main(void) {

	int n;
	string a, b, c;
	cin >> n >> a >> b >> c;
	hanoi( 1, 3, 2, n);

	cout << t << endl;
	for( int i=0; i<t; i++ ) {
		cout << i+1 << ": move #" << v[i].num << " disk from rod ";
		switch( v[i].from ){
			case 1:	cout << a;	break;
			case 2:	cout << b;	break;
			case 3:	cout << c;	break;
		}
		cout << " to rod ";
		switch( v[i].to ){
			case 1:	cout << a;	break;
			case 2:	cout << b;	break;
			case 3:	cout << c;	break;
		}
		cout << endl;
	}

	return 0;
}