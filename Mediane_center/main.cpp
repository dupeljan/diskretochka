#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
#define INP_PATH  "input.txt"
#define OUTP_PATH "output.txt"
#define INF true
#define ORIENTED 0
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
		#if ! ORIENTED
		p[b][a] = w;
		#endif
		inf += abs(w);
	}
	
	
	inf++;
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++)
			if( !p[i][j] && i != j )
				p[i][j] = inf ;
	

	for ( int k = 0; k < n; k++)
		for ( int i = 0; i < n; i++ )
			for ( int j = 0; j < n; j++ )
				if ( p[i][k] + p[k][j] < p[i][j]){
					p[i][j] = p[i][k] + p[k][j];
				}
	
	// P - matrix of shortest pathes
	int center[3] = { inf , 0 }; // Value, num
	int medium[3] = { inf , 0 }; // Value, num
	for(int i = 0; i < n; i++){ // Compute min
		
		int local_max = 0;        
		int local_sum = 0;
		for(int j = 0; j < n; local_sum+=p[i][j] , j++ )
			local_max = max( local_max , p[i][j]);
		
		if ( center[0] > local_max){
			center[0] = local_max;
			center[1] = i;
		}

		if ( medium[0] > local_sum ){
			medium[0] = local_sum;
			medium[1] = i;
		}
	}

	fstream out;
	out.open(OUTP_PATH, fstream::out);
		// Output p
	int max_dig_count = 3;
	for ( int i = 0; i < n; i++ ){
		for ( int j = 0; j < n; j++ ){
			#ifdef INF
			out << ( ( p[i][j] ==  inf )? "inf" : to_string(p[i][j]).data() ) << ' ';
			#else
			out << p[i][j];	
			#endif
			for (int k = 0; k <= max_dig_count - dig_count(p[i][j]); k++)
				out << ' ';
			
			 
		}

		out << '\n';
	}
	
	out << '\n';


	out << "Center: " << center[1] << endl;
	out << "Medium: "   << medium[1] << endl;
	

}	
