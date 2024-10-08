/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"

using namespace std;

template<typename DType, typename LType>
class DataLoader{
public:
    class Iterator;
private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    xt::xarray<unsigned long> index_list;
    int batch_count;
    /*TODO: add more member variables to support the iteration*/
public:
    DataLoader(Dataset<DType, LType>* ptr_dataset,
            int batch_size,
            bool shuffle=true,
            bool drop_last=false){
        /*TODO: Add your code to do the initialization */
        this->ptr_dataset = ptr_dataset;
        this->batch_size = batch_size;
        this->shuffle = shuffle;
        this->drop_last = drop_last;
        
        int length = ptr_dataset->len();
        index_list = xt::arange<unsigned long>(length);
        if (shuffle) {
            xt::random::shuffle(index_list);
        }

        // batch_count = (length > batch_size) ? (int)(length / batch_size) : 1;
        if (!drop_last && length <= batch_size) {
            batch_count = 1;
        } else {
            batch_count = (int)(length / batch_size);
        }
    }
    virtual ~DataLoader(){}
    
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
    
    /*TODO: Add your code here to support iteration on batch*/

    class Iterator {
    private:
        DataLoader *loader;
        int batch_index;

    public:
        Iterator(DataLoader *loader, int batch_index) {
            this->loader = loader;
            this->batch_index = batch_index;
        }

        Iterator &operator=(const Iterator &iterator) {
            this->loader = iterator.loader;
            this->batch_index = iterator.batch_index;
            return *this;
        }

        bool operator!=(const Iterator &iterator) {
            return this->batch_index!= iterator.batch_index;
        }

        Batch<DType, LType> operator*() const {
            int startIndex = this->batch_index * loader->batch_size;
            int endIndex;
            if ((batch_index == loader->batch_count - 1) && loader->drop_last == false) {
                endIndex = loader->ptr_dataset->len();
            }
            else {
                endIndex = startIndex + loader->batch_size;
            }
            auto dataShape = this->loader->ptr_dataset->get_data_shape();
            auto labelShape = this->loader->ptr_dataset->get_label_shape();
            dataShape[0] = labelShape[0] = endIndex - startIndex;
            
            xt::xarray<DType> batchData = xt::empty<DType>(dataShape);
            xt::xarray<LType> batchLabel = xt::empty<LType>(labelShape);

            // cout << "Data shape: (";
            // for (auto dim : dataShape) {
            //     cout << dim << ", ";
            // }
            // cout << ")" << endl;

            // cout << "Batch Index: " << startIndex << " " << endIndex << endl;

                // cout << "Index: ";
                for (int i = startIndex; i < endIndex; i++) {
                    size_t index = loader->index_list[i];
                    DataLabel<DType, LType> dataLabel = loader->ptr_dataset->getitem(index);
                    // cout << index << " ";
                    auto data = dataLabel.getData();
                    auto label = dataLabel.getLabel();

                    xt::view(batchData, i - startIndex, xt::all()) = data;
                    xt::view(batchLabel, i - startIndex, xt::all()) = label;        
                }
                // cout << endl;
            return Batch<DType, LType>(batchData, batchLabel);
        }

        // prefix
        Iterator &operator++() {
            this->batch_index++;
            return *this;
        }
        // postfix
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };

    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, batch_count);
    }
    
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};


#endif /* DATALOADER_H */

