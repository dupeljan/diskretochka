#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
#define INP_PATH  "input.txt"
#define OUTP_PATH "output.txt"
#define INF true
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
	
	inf++;
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++)
			if( !p[i][j]  )
				p[i][j] = inf ;
	

	for ( int k = 0; k < n; k++)
		for ( int i = 0; i < n; i++ )
			for ( int j = 0; j < n; j++ )
				if ( p[i][k] + p[k][j] < p[i][j]){
					p[i][j] = p[i][k] + p[k][j];
					next[i][j] = next[i][k];
				}
	// P - matrix of shortest pathes
	int center[3] = { p[0][0] , 0 , 0 }; // Value, i, j
	for(int i = 0; i < n; i++){ // Compute min
		int local_max[2] = {0,0};        // Value, j
		for(int j = 0; j < n; j++)
			if ( local_max[0] < p[i][j] ){
				local_max[0] = p[i][j];
				local_max[1] = j;
			}
		
		if ( center[0] > local_max[0]){
			center[0] = local_max[0];
			center[1] = i;
			center[2] = local_max[2];
		}
	}

	fstream out;
	out.open(OUTP_PATH, fstream::out);

	out << "Center: " << center[1] << ' ' << center[2] << endl;

}	
