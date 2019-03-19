#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main() {

	char num[100010], ans[100010], c;
	int size=0;

	while( scanf("%c", &c) != EOF && c!='\n' ) {
		num[size] = c;
		size++;
	}

	if( size%2 == 1 ) {
		for( int i=0; i<=size/2; i++ ) putchar('4');
		for( int i=0; i<=size/2; i++ ) putchar('7');
		putchar('\n');
		return 0;
	}

	int s=(size/2), f=(size/2), flag=-1, ff=-1, ss=-1;
	for( int i=0; i<size; i++ ) {

		if( num[i] < '4' ) {
			for ( int j=0; j<f; j++ ) ans[i+j] = '4';
			for ( int k=0; k<s; k++ ) ans[i+f+k] = '7';
			break;
		}

		else if( num[i] == '4' ){
			if( f ) {
				ans[i] = '4';	f--;
				if( s ) {
					flag = i;
					ff=f;	ss=s;
				}
			}
			else {
				ans[i] = '7';
				s--;
			}
		}

		else if( num[i] < '7' ) {
			if( s==0 ) {
				if( flag < 0 ) {
					for( int j=0; j<(size/2)+1; j++ ) putchar('4');
					for( int j=0; j<(size/2)+1; j++ ) putchar('7');
					putchar('\n');
					return 0;
				}
				ans[flag] = '7';
				ff++;	ss--;
				for ( int j=0; j<ff; j++ ) ans[flag+1+j] = '4';
				for ( int k=0; k<ss; k++ ) ans[flag+1+ff+k] = '7';
				break;
			}
			ans[i] = '7'; s--;
			for ( int j=0; j<f; j++ ) ans[i+1+j] = '4';
			for ( int k=0; k<s; k++ ) ans[i+1+f+k] = '7';
			break;
		}

		else if( num[i] == '7' ){
			if( s==0 ) {
				if( flag < 0 ) {
					for( int j=0; j<(size/2)+1; j++ ) putchar('4');
					for( int j=0; j<(size/2)+1; j++ ) putchar('7');
					putchar('\n');
					return 0;
				}
				ans[flag] = '7';
				ff++;	ss--;
				for ( int j=0; j<ff; j++ ) ans[flag+1+j] = '4';
				for ( int k=0; k<ss; k++ ) ans[flag+1+ff+k] = '7';
				break;
			}
			ans[i] = '7';
			s--;
		}

		else{ //num[i] > 7
			if( flag < 0 ) {
				for( int j=0; j<(size/2)+1; j++ ) putchar('4');
				for( int j=0; j<(size/2)+1; j++ ) putchar('7');
				putchar('\n');
				return 0;
			}
			ans[flag] = '7';
			ff++;	ss--;
			for ( int j=0; j<ff; j++ ) ans[flag+1+j] = '4';
			for ( int k=0; k<ss; k++ ) ans[flag+1+ff+k] = '7';
			break;
		}

	}

	for( int i=0; i<size; i++ ) putchar(ans[i]);
	putchar('\n');

	return 0;
}