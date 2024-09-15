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
  	int num;
  	
  	while (true){
	  	cout << "Masukkan angka: "; cin >> num;
		if (cin.fail()) {
	      cin.clear(); 
	      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	      cout << "Masukkan angka positif." << endl;
	    }
	    else if (num < 1) {
	      cout << "Masukkan angka positif." << endl;
	    }
	    else {
	      break;
	    }
  }
  cout<<"Langkah-langkah:\n" << endl;
  tower_of_hanoi(num, "I", "III", "II");
  return 0;
}