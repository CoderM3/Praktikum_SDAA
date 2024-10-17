#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
using namespace std;

struct cartbarang{
    string namaItem;
    int quantity;
    int price;
};

struct Node {
    string namaItem;
    int quantity;
    int price;
    Node* next;
};

struct StackNode {
    string namaItem;
    int quantity;
    int price;
    StackNode* next;
};

StackNode* stackTop = nullptr;

struct QueueNode {
    string namaItem;
    int quantity;
    int price;
    QueueNode* next;
};

QueueNode* queueFront = nullptr;
QueueNode* queueRear = nullptr;

Node* head = nullptr;
Node* lastNode(Node* node);

//function prototype
void beliBarang();
void beliTurbo();
void beliSuspension();
void beliRem();
void lihatKeranjang();

//sorting merge asc
Node* sortedMergeAsc(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->price <= b->price) {
        a->next = sortedMergeAsc(a->next, b);
        return a;
    } else {
        b->next = sortedMergeAsc(a, b->next);
        return b;
    }
}

void split(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

void mergeSortAsc(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    split(head, &a, &b);

    mergeSortAsc(&a);
    mergeSortAsc(&b);

    *headRef = sortedMergeAsc(a, b);
}

void sortAscending() {
    mergeSortAsc(&head);
    cout << "Keranjang diurutkan secara ascending berdasarkan harga.\n";
}


//sorting quick desc
Node* partitionDesc(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->price >= pivot->price) {
            if ((*newHead) == nullptr) 
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;

            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr) 
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

Node* quickSortRecurDesc(Node* head, Node* end) {
    if (!head || head == end)
        return head;

    Node* newHead = nullptr, *newEnd = nullptr;

    Node* pivot = partitionDesc(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecurDesc(newHead, temp);

        temp = lastNode(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurDesc(pivot->next, newEnd);

    return newHead;
}

void quickSortDesc(Node** headRef) {
    (*headRef) = quickSortRecurDesc(*headRef, lastNode(*headRef));
}

void sortDescending() {
    quickSortDesc(&head);
    cout << "Keranjang diurutkan secara descending berdasarkan harga.\n";
}

Node* lastNode(Node* node) {
    while (node && node->next)
        node = node->next;
    return node;
}


void beliBarang(){
    int pilihan;
    while (true) {
	    cout << "1. Turbo Kit" << endl;
	    cout << "2. Suspension" << endl;
        cout << "3. Brake Pads" <<endl;
        cout << "4. Lihat Keranjang" <<endl;
	    cout << "5. Kembali" << endl;
		do {
			cout << "Pilih menu (1-5): ";
			cin >> pilihan;
				
			if(cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Masukan tidak valid. Silakan masukkan angka.\n";
			}
			} while (cin.fail());     
	
	        switch (pilihan) {
                case 1:{
                    beliTurbo();
                    break;
                }
                    
                case 2:{
                    beliSuspension();
                    break;
                }
                    
                case 3:{
                    beliRem();
					break;
				}

                case 4:{
                    lihatKeranjang();
                    break;
                }  

                case 5:{
                    return;
                }  

                default:
                    cout << "Pilihan tidak valid." << endl;
	        }
        break;
    }
}

void pushToStack(const string& namaItem, int quantity, int price) {
    StackNode* newNode = new StackNode{namaItem, quantity, price, stackTop};
    stackTop = newNode;
}

void popFromStack() {
    if (stackTop == nullptr) {
        cout << "Tidak ada item untuk di-undo.\n";
        return;
    }
    cout << "Item '" << stackTop->namaItem << "' berhasil di-undo.\n";
    StackNode* temp = stackTop;
    stackTop = stackTop->next;
    delete temp;
}

void enqueueToQueue(const string& namaItem, int quantity, int price) {
    QueueNode* newNode = new QueueNode{namaItem, quantity, price, nullptr};
    if (queueRear == nullptr) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }
}

void dequeueFromQueue() {
    if (queueFront == nullptr) {
        cout << "Antrian checkout kosong.\n";
        return;
    }
    QueueNode* temp = queueFront;
    queueFront = queueFront->next;
    if (queueFront == nullptr) {
        queueRear = nullptr;
    }
    delete temp;
}

void keranjang(string namaItem, int quantity, int price){
    Node* newItem = new Node{namaItem, quantity, price, nullptr};

    if (!head) {
        head = newItem;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newItem;
    }

    pushToStack(namaItem, quantity, price);

    cout << "Item '" << namaItem << "' ditambahkan ke keranjang belanja.\n";
}

void lihatKeranjang() {
    if (!head) {
        cout << "Keranjang kosong.\n";
        return;
    }

    cout << "\n--- Isi Keranjang ---\n";
    Node* temp = head;
    int index = 1;
    while (temp != nullptr) {
        cout << index++ << ". " << temp->namaItem << " - Qty: " << temp->quantity
             << " - Price: $" << temp->price << "\n";
        temp = temp->next;
    }

    int pilihan;
    cout << "1. Hapus item" << endl;
    cout << "2. Update jumlah item" << endl;
    cout << "3. Tambah Produk" << endl;
    cout << "4. Urutkan secara Ascending (harga)" << endl;
    cout << "5. Urutkan secara Descending (harga)" << endl;
    cout << "6. Kembali ke menu utama" << endl;
    cout << "Pilih opsi: " << endl;
    cin >> pilihan;

    switch (pilihan) {
        case 1: {
            int deleteIndex;
            cout << "Masukkan nomor item yang ingin dihapus: ";
            cin >> deleteIndex;

            if (deleteIndex <= 0 || deleteIndex >= index) {
                cout << "Nomor item tidak valid.\n";
                return;
            }

            Node* temp = head;
            Node* prev = nullptr;

            for (int i = 1; i < deleteIndex; ++i) {
                prev = temp;
                temp = temp->next;
            }

            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            delete temp;
            cout << "Item dihapus dari keranjang.\n";
            break;
        }
        case 2: {
            int updateIndex, newQty;
            cout << "Masukkan nomor item yang ingin diupdate: ";
            cin >> updateIndex;

            if (updateIndex <= 0 || updateIndex >= index) {
                cout << "Nomor item tidak valid.\n";
                return;
            }

            Node* temp = head;

            for (int i = 1; i < updateIndex; ++i) {
                temp = temp->next;
            }

            cout << "Masukkan jumlah baru: ";
            cin >> newQty;

            if (newQty > 0) {
                temp->quantity = newQty;
                cout << "Jumlah item diperbarui.\n";
            } else {
                cout << "Jumlah tidak valid.\n";
            }
            break;
        }
        case 3:
            beliBarang();
            break;
        case 4:
            sortAscending();
            break;
        case 5:
            sortDescending();
            break;
        case 6:
            cout << "Kembali ke menu utama.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
    }
}

void undoBarang() {
    if (stackTop == nullptr) {
        cout << "Tidak ada item untuk di-undo.\n";
        return;
    }
    
    string namaUndo = stackTop->namaItem;
    
    StackNode* temp = stackTop;
    stackTop = stackTop->next;
    delete temp;

    if (head == nullptr) {
        cout << "Keranjang kosong.\n";
        return;
    }

    if (head->namaItem == namaUndo) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Item '" << namaUndo << "' berhasil di-undo dan dihapus dari keranjang.\n";
        return;
    }

    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr && current->namaItem != namaUndo) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        prev->next = current->next;
        delete current;
        cout << "Item '" << namaUndo << "' berhasil di-undo dan dihapus dari keranjang.\n";
    } else {
        cout << "Item '" << namaUndo << "' tidak ditemukan di keranjang.\n";
    }
}

int checkout() {
    if (!head) {
        cout << "Keranjang kosong, tidak ada yang bisa di-checkout.\n";
        return 0;
    }

    int total = 0;
    cout << "\n--- Checkout ---\n";
    Node* temp = head;
    while (temp != nullptr) {
        int subtotal = temp->quantity * temp->price;
        cout << temp->namaItem << " - Qty: " << temp->quantity 
             << " - Subtotal: $" << subtotal << "\n";
        total += subtotal;

        enqueueToQueue(temp->namaItem, temp->quantity, temp->price);

        temp = temp->next;
    }

    cout << "Total belanja: $" << total << "\n";

    while (head != nullptr) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }

    cout << "Terima kasih telah berbelanja!\n";
    return total;
}

void beliTurbo() {
    int pilihanTurbo, jumlah;
    
    cout << "\n--- Daftar Turbo ---\n";
    cout << "1. HKS GT75100_BB Turbo - $5400\n";
    cout << "2. Custom Calvo Motorsports Twin Billet 76mm 42R Turbo Chargers - $9000\n";
    cout << "3. Garrett GTX3071R GEN II 54mm - $2360\n";
    
    do {
        cout << "Pilih turbo (1-3): ";
        cin >> pilihanTurbo;

        if(cin.fail() || pilihanTurbo < 1 || pilihanTurbo > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (cin.fail() || pilihanTurbo < 1 || pilihanTurbo > 3);

     do {
        cout << "Masukkan jumlah yang ingin dibeli: ";
        cin >> jumlah;
        
        if(cin.fail() || jumlah <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukan tidak valid. Silakan masukkan jumlah yang benar.\n";
        }
    } while (cin.fail() || jumlah <= 0);

    string namaTurbo;
    int hargaTurbo;
    
    switch (pilihanTurbo) {
        case 1:
            namaTurbo = "HKS GT75100_BB Turbo";
            hargaTurbo = 5400;
            break;
        case 2:
            namaTurbo = "Custom Calvo Motorsports Twin Billet 76mm 42R Turbo Chargers";
            hargaTurbo = 14000;
            break;
        case 3:
            namaTurbo = "Garrett GTX3071R GEN II 54mm";
            hargaTurbo = 2360;
            break;
    }
    
    cout << "Anda membeli " << jumlah << " unit " << namaTurbo << " dengan total harga $" << hargaTurbo * jumlah << ".\n";
    keranjang(namaTurbo, jumlah, hargaTurbo);
    beliBarang();
}

void beliSuspension() {
    int pilihanSuspension, jumlah;
    
    cout << "\n--- Daftar Suspension ---\n";
    cout << "1. Skunk 2 Pro-S II Coilovers (For Acura RSX Only!)- $1049\n";
    cout << "2. Bilstein 46-207364 - B12 Series Pro-Kit Suspension Lowering Kit (For Ford Mustang Only!) - $1122\n";
    cout << "3. KW Suspensions 1021000B - Variant 1 CoilOvers (For Audi A6 Only!) - $1974\n";
    
    do {
        cout << "Pilih Suspension (1-3): ";
        cin >> pilihanSuspension;

        if(cin.fail() || pilihanSuspension < 1 || pilihanSuspension > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (cin.fail() || pilihanSuspension < 1 || pilihanSuspension > 3);

     do {
        cout << "Masukkan jumlah yang ingin dibeli: ";
        cin >> jumlah;
        
        if(cin.fail() || jumlah <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukan tidak valid. Silakan masukkan jumlah yang benar.\n";
        }
    } while (cin.fail() || jumlah <= 0);

    string namaSuspension;
    int hargaSuspension;
    
    switch (pilihanSuspension) {
        case 1:
            namaSuspension = "Skunk 2 Pro-S II Coilovers";
            hargaSuspension = 1049;
            break;
        case 2:
            namaSuspension = "Bilstein 46-207364 - B12 Series Pro-Kit Suspension Lowering Kit";
            hargaSuspension = 1122;
            break;
        case 3:
            namaSuspension = "KW Suspensions 1021000B - Variant 1 CoilOvers";
            hargaSuspension = 1974;
            break;
    }
    
    cout << "Anda membeli " << jumlah << " unit " << namaSuspension << " dengan total harga $" << hargaSuspension * jumlah << ".\n";
    keranjang(namaSuspension, jumlah, hargaSuspension);
    beliBarang();
}

void beliRem() {
    int pilihanRem, jumlah;
    
    cout << "\n--- Daftar Rem ---\n";
    cout << "1. Brembo Gt Drilled Brake Kits - $1195\n";
    cout << "2. EBC Stage 5 Superstreet Brake Kit - $155\n";
    cout << "3. Dynamic Friction - Drilled and Slotted - Stage 2 Street Rotor and Pad Kit - $269\n";
    
    do {
        cout << "Pilih Rem (1-3): ";
        cin >> pilihanRem;

        if(cin.fail() || pilihanRem < 1 || pilihanRem > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (cin.fail() || pilihanRem < 1 || pilihanRem > 3);

     do {
        cout << "Masukkan jumlah yang ingin dibeli: ";
        cin >> jumlah;
        
        if(cin.fail() || jumlah <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukan tidak valid. Silakan masukkan jumlah yang benar.\n";
        }
    } while (cin.fail() || jumlah <= 0);

    string namaRem;
    int hargaRem;
    
    switch (pilihanRem) {
        case 1:
            namaRem = "Brembo Gt Drilled Brake Kits";
            hargaRem = 1195;
            break;
        case 2:
            namaRem = "EBC Stage 5 Superstreet Brake Kit";
            hargaRem = 155;
            break;
        case 3:
            namaRem = "Dynamic Friction - Drilled and Slotted - Stage 2 Street Rotor and Pad Kit";
            hargaRem = 269;
            break;
    }
    
    cout << "Anda membeli " << jumlah << " unit " << namaRem << " dengan total harga $" << hargaRem * jumlah << ".\n";
    keranjang(namaRem, jumlah, hargaRem);
    beliBarang();
}

int main(){
    int pilihan;
    while (true) {
        cout << "===============================================" << endl;
        cout << "Toko Spare Parts Aftermarket:" << endl;
        cout << "===============================================" << endl;
        cout << "1. Beli Barang" << endl;
        cout << "2. Checkout" << endl;
        cout << "3. Lihat Keranjang" << endl;
        cout << "4. Undo Item Terakhir" << endl;
        cout << "5. Keluar" << endl;
        do {
            cout << "Pilih menu (1-5): ";
            cin >> pilihan;

            if(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukan tidak valid. Silakan masukkan angka.\n";
            }
        } while (cin.fail());     

        switch (pilihan) {
            case 1:{
                beliBarang();
                break;
            }

            case 2:{
                int totalBelanja = checkout();
                break;
            }

            case 3:{
                lihatKeranjang();
                break;
            }

            case 4:{
                undoBarang();
                break;
            }

            case 5:
                cout << "Terima kasih telah menggunakan program. Program berakhir." << endl;
                return 0;

            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }
}