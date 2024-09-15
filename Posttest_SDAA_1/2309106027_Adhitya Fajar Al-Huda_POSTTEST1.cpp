#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void tower_of_hanoi(int num, string asal, string tujuan, string bantu) {
  	if (num == 1) {
    	cout << " Pindahkan disk 1 dari tower " << asal << " ke tower " << tujuan << endl;
    	return;
	}
	tower_of_hanoi(num - 1, asal, bantu, tujuan);
	cout << " Pindahkan disk " << num << " dari tower " << asal << " ke tower " << tujuan << endl;
	tower_of_hanoi(num - 1, bantu, tujuan, asal);
}
int main() {
	int num = 3 ;
  	cout<<"Langkah-langkah:\n" << endl;
 	tower_of_hanoi(num, "A", "C", "B");
  	return 0;
  return 0;
}
