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
#include "tensor/xtensor_lib.h"
#include "loader/dataset.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader
{
public:
    class Iterator;

private:
    Dataset<DType, LType> *ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int seed;
    /*TODO: add more member variables to support the iteration*/
    xt::xarray<unsigned long> index_list;
    int batch_count;

public:
    DataLoader(Dataset<DType, LType> *ptr_dataset,
               int batch_size,
               bool shuffle = true,
               bool drop_last = false,
               int seed = -1)
    {
        /*TODO: Add your code to do the initialization */
        this->ptr_dataset = ptr_dataset;
        this->batch_size = batch_size;
        this->shuffle = shuffle;
        this->drop_last = drop_last;
        this->seed = seed;

        int length = ptr_dataset->len();
        index_list = xt::arange<unsigned long>(length);
        batch_count = (int)(length / batch_size);
    }
    virtual ~DataLoader() {}

    // New method: from V2: begin
    int get_batch_size() { return batch_size; }
    int get_sample_count() { return ptr_dataset->len(); }
    int get_total_batch() { return int(ptr_dataset->len() / batch_size); }

    // New method: from V2: end
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////

    /*TODO: Add your code here to support iteration on batch*/

    class Iterator
    {
    private:
        DataLoader *loader;
        int batch_index;

    public:
        Iterator(DataLoader *loader, int batch_index)
        {
            this->loader = loader;
            this->batch_index = batch_index;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->loader = iterator.loader;
            this->batch_index = iterator.batch_index;
            return *this;
        }

        bool operator!=(const Iterator &iterator)
        {
            return this->batch_index != iterator.batch_index;
        }

        Batch<DType, LType> operator*() const
        {
            int startIndex = this->batch_index * loader->batch_size;
            int endIndex;
            if ((batch_index == loader->batch_count - 1) && loader->drop_last == false)
            {
                endIndex = loader->ptr_dataset->len();
            }
            else
            {
                endIndex = startIndex + loader->batch_size;
            }
            auto dataShape = this->loader->ptr_dataset->get_data_shape();
            auto labelShape = this->loader->ptr_dataset->get_label_shape();
            dataShape[0] = endIndex - startIndex;

            xt::xarray<DType> batchData = xt::empty<DType>(dataShape);
            xt::xarray<LType> batchLabel;
            bool labelFlag = (labelShape != xt::svector<unsigned long>());
            if (labelFlag)
            {
                labelShape[0] = dataShape[0];
                batchLabel = xt::empty<LType>(labelShape);
            }

            for (int i = startIndex; i < endIndex; i++)
            {
                size_t index = loader->index_list[i];
                DataLabel<DType, LType> dataLabel = loader->ptr_dataset->getitem(index);
                auto data = dataLabel.getData();
                auto label = dataLabel.getLabel();

                xt::view(batchData, i - startIndex, xt::all()) = data;
                if (labelFlag)
                {
                    xt::view(batchLabel, i - startIndex, xt::all()) = label;
                }
            }
            return Batch<DType, LType>(batchData, batchLabel);
        }

        // prefix
        Iterator &operator++()
        {
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

    Iterator begin()
    {
        if (shuffle)
        {
            int m_seed = this->seed;
            if (this->seed >= 0)
            {
                xt::random::seed(m_seed);
            }
            xt::random::shuffle(index_list);
        }
        return Iterator(this, 0);
    }

    Iterator end()
    {
        return Iterator(this, batch_count);
    }

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};

#endif /* DATALOADER_H */
