#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
#define INP_PATH  "input.txt"
#define OUTP_PATH "output.txt"
using namespace std;

vector < int > shortest_patch(int i, int j, vector < vector < int > > next  );

int dig_count(int a){
	if (!a)
		return 1;
	int res = 0;
	do { 
		res++;
		a /= 10;
	}while ( a );
	return res;
}
int main(){
	fstream in;
	in.open(INP_PATH, fstream::in);
	
	int n, m;
	in >> n >> m ;
	
	vector < vector < int  >  > p , next;
	
	// init matrix of пропускная способность 
	p.resize(n);
	for( int i = 0; i < n; i++ )
		p[i].resize(n);



	int inf = 0;
	while ( m-- ){
		int a,b,w;
		in >> a >> b >> w;
		a--;
		b--;
		p[a][b] = w;
		inf += abs(w);
	}
	




	// Init matrix of shortest path
	next.resize(n);
	for ( int i = 0; i < n; i++ ){
		next[i].resize(n);
		for ( int j = 0; j < n; j++ )
				next[i][j] = ( p[i][j] ) ? j : -1;
	}

	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++)
			if( !p[i][j]  )
				p[i][j] = inf + 1;
	
	


	for ( int k = 0; k < n; k++)
		for ( int i = 0; i < n; i++ )
			for ( int j = 0; j < n; j++ )
				if ( p[i][k] + p[k][j] < p[i][j]){
					p[i][j] = p[i][k] + p[k][j];
					next[i][j] = next[i][k];
				}
	// Output p
	fstream out;
	out.open(OUTP_PATH, fstream::out);
	int max_dig_count = 3;
	for ( int i = 0; i < n; i++ ){
		for ( int j = 0; j < n; j++ ){
			out << p[i][j] ;
			for (int k = 0; k <= max_dig_count - dig_count(p[i][j]); k++)
				out << ' ';
			 
		}

		out << '\n';
	}
	
	out << '\n';


	// Output shortest_patches
	for( int i = 0; i < n; i++ )
		for( int j = i+1; j < n; j++ ){
			vector <int> cur = shortest_patch( i , j , next );
			out << i + 1 << "->" << j + 1 << ':';
			for ( auto it : cur )
				out << ' ' << it;
			out << '\n'; 
		}


}	

vector < int > shortest_patch(int i, int j ,vector < vector < int > > next ){
	vector < int > res;
	if ( next[i][j] == -1 )
		return res;
	
	int c = i;
	while ( c != j ){
		res.push_back( c + 1 );
		c = next[c][j];
	}
	res.push_back(j+1);

	return res;
	
}