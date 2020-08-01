#include<bits/stdc++.h>
using namespace std;
#define int long long int

string convertToBinary(int n){
	vector<int> arr(32, 0);
	int bitIndex = 31;
	while(n>0){
		arr[bitIndex] = n&1;
		n >>= 1;
		bitIndex --;
	}
	string ans = "";
	for(auto i:arr){
		ans += to_string(i);
	}
	return ans;
}

int32_t main(){
    ofstream file;
    file.open("mainMemory.txt", ios::trunc | ios::in | ios::out);
    srand(time(0));
    int maxVal = 1000;
    for(int i = 0L; i < maxVal; i ++){
    	int data = (rand())%((int)(1e10));
    	file << convertToBinary(data) << endl;
    }
    file.close();
    return 0;
}
