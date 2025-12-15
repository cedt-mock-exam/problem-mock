#include <iostream>
using namespace std;

int main(){
    //input size of paper and no. of balls
	int n, m, k;
	cin >> n >> m >> k;
	char map[n][m];
	
	//write all tiles as '-'
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			map[i][j] = '-';
	}
	
    //loop for each ball
	while(k--){
        //input each ball's color, radius, and position
		char c;
		int r, x, y;
		cin >> c >> r >> x >> y;
	
//		//Method 1 (easy) loop everything and check condition
//		for(int i=0;i<n;i++){
//			for(int j=0;j<m;j++){
//				if(abs(x-i)+abs(y-j) <= r)
//					map[i][j] = c;
//			}
//		}


        //Method 2 
		for(int i=x-r; i<=x+r; i++){
            //in each row have a loop to draw colors in columns satisfying the condition
			for(int j=y-(r-abs(x-i)); j<=y+(r-abs(x-i)); j++){
				if(!(i<0||j<0||i>=n||j>=m))
					map[i][j] = c;
			}
		}
	}
	
    //print answer
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			cout << map[i][j] << ' ';
		cout << '\n';
	}		
}
