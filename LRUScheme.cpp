#include<bits/stdc++.h>
using namespace std;

#define int long long

vector<string> mainMemory;
vector<vector<pair<string, string>>> cache(256, vector<pair<string, string>>(16, {"-1", "-1"}));
map<char,string> hex_to_bin = {
                                {'0',"0000"},{'1',"0001"},{'2',"0010"},{'3',"0011"},
                                {'4',"0100"},{'5',"0101"},{'6',"0110"},{'7',"0111"},
                                {'8',"1000"},{'9',"1001"},{'a',"1010"},{'b',"1011"},
                                {'c',"1100"},{'d',"1101"},{'e',"1110"},{'f',"1111"},
                              };

int hits=0, miss=0;

const int mod = 1e6;

vector<vector<int>> LRUBit(256, vector<int>(16, -1));

string convertToBinary(int n){
	/* Converts a number from Decimal To Binary */
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

int convertToDecimal(string arr){
	/* Converts From Binary String to Decimal Number */
	int decimalNumber = 0;
	int power = 1;
	int l = arr.size();
	for(int i=l-1;i>=0;i--){
		int x = arr[i]-'0';
		decimalNumber += (x*power);
		power <<= 1;
	}
	return decimalNumber;
}

void LRUScheme(string address) {
	/* 
	Function To check whether the address in Binary is present in cache.
	If Cache Hit : Updates the LRU Bit and then return using falg variable. Increment Hit
	If Cache Miss : Finds the Place if cache is still empty depending upon the Index Bits 
					else removes address with LRU bit = 0 and updates the LRU Bit in the line.
					Increment Miss
	*/
	string index = address.substr(24, 8);
	string tag = address.substr(0, 24);
	int q = (convertToDecimal(address) % mod);
	string data = mainMemory[q];
	int idx = convertToDecimal(index);
	int isPut = -1;
	int maxi = -1;
	for(int i = 0; i < 16; i ++){
		if(LRUBit[idx][i] == -1){
			/* Cache Miss */
			for(int j = 0; j < 16; j ++){
				maxi = max(maxi, LRUBit[idx][j]);
			}
			LRUBit[idx][i] = maxi + 1;
			cache[idx][i] = {tag, data};
			miss ++;
			isPut = 1;
			break;
		}
		if(cache[idx][i].first == tag) {
			/*Cache Hit*/
			hits ++;
			for(int j = 0; j < 16; j ++) {
				maxi = max(maxi, LRUBit[idx][j]);
			}
			LRUBit[idx][i] = maxi + 1;
			cache[idx][i] = {tag, data}; 
			isPut = 1;
			break;
		}
		maxi = max(maxi, LRUBit[idx][i]);
	}
	if(isPut == 1) return;
	miss ++;
	int mini = 1e9;
	int toReplace = -1;
	for(int i = 0; i < 16; i ++) {
		if(mini > LRUBit[idx][i]) {
			mini = LRUBit[idx][i];
			toReplace = i;
		}
	}
	LRUBit[idx][toReplace] = maxi + 1;
	cache[idx][toReplace] = {tag, data};
}

void readMemoryFile(){
	ifstream fi;
	fi.open("MainMemory.txt",ios::in);
	while(!fi.eof()){
		string value;
		fi>>value;
		mainMemory.push_back(value);
	}
}
void writeToMainMemory(){
	ofstream fo;
	fo.open("MainMemory.txt", ios::out | ios::trunc);
	for(int i=0;i<mainMemory.size();i++){
		if(i==mainMemory.size()-1){
			fo<<mainMemory[i];
			continue;
		}
		fo<<mainMemory[i]<<endl;
	}
}
string hexToBinary(string address){
	string binary = "";
	for(int i = 2; i < address.size(); i ++){
		binary =binary+ hex_to_bin[address[i]];
	}
	return binary;
}
int32_t main(){
	readMemoryFile();
	ifstream cacheInput;
	cacheInput.open("mcf.trace", ios::in);
	int fileSize = 0;
	while(!cacheInput.eof()){
		string operation, address, no;
		cacheInput >> operation >> address >> no;
		fileSize ++; 
 		string binary = hexToBinary(address);
 		LRUScheme(binary);
	}
	cout<<"mcf\n";
	cout << "Total File Size : " << fileSize << endl;
	cout << "Total Number Of Hits : " << hits << endl;
	cout << "Total Number Of Miss : " << miss << endl;
	cacheInput.close();
	hits=0;miss=0;

	cacheInput.open("gcc.trace", ios::in);
	fileSize = 0;
	while(!cacheInput.eof()){
		string operation, address, no;
		cacheInput >> operation >> address >> no;
		fileSize ++; 
 		string binary = hexToBinary(address);
 		LRUScheme(binary);
	}
	cout<<"\ngcc\n";
	cout << "Total File Size : " << fileSize << endl;
	cout << "Total Number Of Hits : " << hits << endl;
	cout << "Total Number Of Miss : " << miss << endl;
	cacheInput.close();
	hits=0;miss=0;


	cacheInput.open("swim.trace", ios::in);
	fileSize = 0;
	while(!cacheInput.eof()){
		string operation, address, no;
		cacheInput >> operation >> address >> no;
		fileSize ++; 
 		string binary = hexToBinary(address);
 		LRUScheme(binary);
	}
	cout<<"\nswim\n";
	cout << "Total File Size : " << fileSize << endl;
	cout << "Total Number Of Hits : " << hits << endl;
	cout << "Total Number Of Miss : " << miss << endl;
	cacheInput.close();
	hits=0;miss=0;

	cacheInput.open("gzip.trace", ios::in);
	fileSize = 0;
	while(!cacheInput.eof()){
		string operation, address, no;
		cacheInput >> operation >> address >> no;
		fileSize ++; 
 		string binary = hexToBinary(address);
 		LRUScheme(binary);
	}
	cout<<"\ngzip\n";
	cout << "Total File Size : " << fileSize << endl;
	cout << "Total Number Of Hits : " << hits << endl;
	cout << "Total Number Of Miss : " << miss << endl;
	cacheInput.close();
	hits=0;miss=0;

	cacheInput.open("twolf.trace", ios::in);
	fileSize = 0;
	while(!cacheInput.eof()){
		string operation, address, no;
		cacheInput >> operation >> address >> no;
		fileSize ++; 
 		string binary = hexToBinary(address);
 		LRUScheme(binary);
	}
	cout<<"\ntwolf\n";
	cout << "Total File Size : " << fileSize << endl;
	cout << "Total Number Of Hits : " << hits << endl;
	cout << "Total Number Of Miss : " << miss << endl;
	cacheInput.close();
	hits=0;miss=0;
	
	return 0;
}