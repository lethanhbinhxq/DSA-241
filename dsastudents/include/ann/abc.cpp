#include <iostream>
using namespace std;

template <typename T>

class AList {

    private:

       const static int MAXSIZE = 20; //the maximum members of the list

       T* data; // keep the list

       int cursor = 0; // keep the position of the cursor

       int listSize; // the real size of the list

   public:

       AList() {}
       void insertBefore(const T& v, const T& k){
    if(this->listSize >= MAXSIZE){
        throw std::out_of_range("A");
    }
    for(int i=0; i<this->listSize -1; i++){
        if(data[i] == k){
            for(int j = this->listSize -1; j >= i-1; j--){
                data[j] = data[j-1];
            }
            data[i-1] = v;
            cursor = i-1;
            break;
        }
    }
    listSize++;
}

};

int main() {
    AList<int> intList;
    intList.insertBefore(10, 5);
    intList.insertBefore(20, 10);
    intList.insertBefore(30, 20);
    return 0;
}