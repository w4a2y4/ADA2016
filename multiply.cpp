#include <stdio.h>
typedef long int ull;

ull p[140000];

int complete( int n ) {
	int two[18] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 
		2048, 4096, 8192, 16384, 32768, 65536, 131072 };
	for( int i=0; i<18; i++ )
		if ( n <= two[i] ) return two[i];
	return -1;
}

int max( int &a, int &b ) {
	if ( a>b ) return a;
	else return b;
}

void init( ull* ptr, int n ) {
	for( int i=0; i<n; i++, ptr++ )
		*ptr = 0;
}

ull* mult( ull* x, ull* y, int nn ) {

	//every element of the array = 0
	if( *x == 0 || *y == 0 ) {	
		ull *tmp = new ull[nn*3];
		init( tmp, nn*3 );
		return tmp;
	}

	//perform traditional multiflication (base case)
	if( nn <= 64 ) {	
		ull *tmp = new ull[nn*2];
		init( tmp, nn*2 );
		for( int i=0; i<nn; i++ )
			for( int j=0; j<nn; j++ ) {
				*(tmp+i+j) += ( *(x+i) % 1000000007 ) * ( *(y+j) % 1000000007) ;
				*(tmp+i+j) %= 1000000007;
			}
		return tmp;
	}

	//divide
	int n = nn/2;
	ull *x1, *y1, *x2, *y2;
	x1 = x+n;	x2 = new ull[n];
	y1 = y+n;	y2 = new ull[n];
	for( int i=0; i<n; i++ ) {
		*(x2+i) = ( *(x+i) + *(x1+i) ) % 1000000007 ;
		*(y2+i) = ( *(y+i) + *(y1+i) ) % 1000000007 ;
	}

	//conquer
	ull *z0, *z1, *z2, *ans = new ull[n*6];
	init( ans, n*6 );
	z0 = mult( x, y, n);	
	z1 = mult( x1, y1, n);
	z2 = mult( x2, y2, n);
	delete [] x2;	delete [] y2;

	//combine
	for( int i=0; i<2*n-1; i++) {
		*(ans+i)     += *(z0+i);
		*(ans+i+n)   += ( *(z2+i) - *(z0+i) - *(z1+i) );
		*(ans+i+n*2) += *(z1+i);
	}
	delete [] z0;	delete [] z1;	delete [] z2;	

	ull* ptr = ans;
	for( int i=0; i<n*3; i++, ptr++ ) {
		*(ptr) %= 1000000007;
		while ( *(ptr) < 0 ) *(ptr) += 1000000007;
	}

	return ans;
}

ull* cut (int nn, int index) { //nn:length	index:where to start in p[]

	if( nn==1 ) {	//base case
		ull *tmp = new ull[4];
		*tmp = 1;
		*(tmp+1) = p[index];
		*(tmp+2) = *(tmp+3) = 0;
		return tmp;
	}

	//divide
	int n = (nn+1)/2, ns = complete(n+1);	
	ull *x, *y, *ans;
	x = cut( n, index );	y = cut( nn-n, index+n);
	init( x+n+1, ns-n-1 );	init( y+nn-n+1, ns-nn+n-1 );
		
	//conquer & combine
	ans = mult( x, y, ns );
	delete [] x;	delete [] y;
	return ans;
}

int main() {

	int nn;

	scanf("%d", &nn);
	for( int i=0; i<nn; i++ ) 
		scanf("%ld", &p[i]);

	ull* ans = cut(nn, 0);

	printf("0 ");
	for(int i=0; i<nn+1; i++)
		printf("%ld ", *(ans+i) % 1000000007 );
	printf("\n");

	return 0;
}