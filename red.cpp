#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

typedef struct NODE{
	int cnt;
	struct NODE* p;
	struct NODE* c;
}node;
void init( node* head ) {
	head -> cnt = 0;
	head -> p = NULL;
	head -> c = NULL;
	return;
}

int main(void) {

	int n, k;
	long long int sum=0;
	cin >> n >> k;

	node* head = (node*) malloc( sizeof(node) );
	init( head );
	node* cur = head;

	for( int i=0; i<n; i++ ) {

		cur = head;
		string buff;
		cin >> buff;

		for ( int j=0; j<k; j++ ) {
			if ( buff[j] == 'P' ) {
				if( cur->p == NULL ) {
					node* tmp = (node*) malloc( sizeof(node) );
					init( tmp );
					cur->p = tmp;
					cur = cur->p;
				}
				else {
					cur = cur->p;
					(cur->cnt)++;
					sum += (cur->cnt);
				}
			}
			else if ( buff[j] == 'C' ) {
				if( cur->c == NULL ) {
					node* tmp = (node*) malloc( sizeof(node) );
					init( tmp );
					cur->c = tmp;
					cur = cur->c;
				}
				else {
					cur = cur->c;
					(cur->cnt)++;
					sum += (cur->cnt);
				}
			}
			else {
				cout << "OAOAO!!" << endl;
				return 0;
			}
		}
	}

	long long int pairs = 1ll * n * (n-1) /2;
	double ans = (double)sum / (double)pairs;
	cout << setprecision(10) << ans << endl;

	return 0;
}