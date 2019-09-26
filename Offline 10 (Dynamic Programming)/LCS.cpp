#include<iostream>
#include<algorithm>
using namespace std;


string LCS(string s1, string s2){
	int l1 = s1.length();
	int l2 = s2.length();

	int c[l1+1][l2+1];

	for(int i=0;i<=l1;i++){
		c[i][0] = 0;
	}

	for(int i=0;i<=l2;i++){
		c[0][i] = 0;
	}

	for(int i = 1; i<=l1; i++){
		for(int j=1;j<=l2;j++){
			if (s1[i-1] == s2[j-1]){
				c[i][j] = c[i-1][j-1] + 1;
			} else if (c[i-1][j] >= c[i][j-1]){
				c[i][j] = c[i-1][j];
			} else {
				c[i][j] = c[i][j-1];
			}
		}
	}

	int i = l1, j = l2 ;
	string lcs;
	while(i>0 && j>0){
		if(c[i][j] == c[i-1][j])
			i--;
		else if (c[i][j] == c[i][j-1])
			j--;
		else{
			lcs += s1[i-1];
			i--;
			j--;
		}
	}
	reverse(begin(lcs), end(lcs));
	
	return lcs;
}



int main(){
	string s1, s2;
	cin>>s1;
	cin>>s2;
	cout<<LCS(s1,s2);
}