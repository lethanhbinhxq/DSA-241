#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#include <filesystem> //require C++17
namespace fs = std::filesystem;

#include "sformat/fmt_lib.h"
#include "tensor/xtensor_lib.h"
#include "ann/annheader.h"
#include "loader/dataset.h"
#include "loader/dataloader.h"
#include "config/Config.h"
#include "dataset/DSFactory.h"
#include "optim/Adagrad.h"
#include "optim/Adam.h"
#include "modelzoo/twoclasses.h"
#include "modelzoo/threeclasses.h"
#include "list/listheader.h"
// #include "../demo/hash/xMapDemo.h"
// #include "../demo/list/DLinkedListDemo.h"
#include "../demo/heap/HeapDemo.h"


int main(int argc, char** argv) {
    //dataloader:
    //case_data_wo_label_1();
    //case_data_wi_label_1();
    //case_batch_larger_nsamples();
    
    //Classification:
    // twoclasses_classification();
    //threeclasses_classification();

    // Doubly linked list
    // dlistDemo1();
    // dlistDemo2();
    // dlistDemo3();
    // dlistDemo4();
    // dlistDemo5();
    // dlistDemo6();

    // Hash map
    // simpleMap();
    // hashDemo1();
    // hashDemo2();
    // hashDemo3();
    // hashDemo4();
    // hashDemo5();
    // hashDemo6();
    // hashDemo7();
    // countryDemo();

    // Heap
    // anotherHeap();
    // simpleMinHeap();
    // heapDemo1();
    // heapDemo2();
    // heapDemo3();
    return 0;
}
