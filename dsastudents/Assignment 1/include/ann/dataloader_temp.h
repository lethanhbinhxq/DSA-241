#ifndef DATALOADER_H
#define DATALOADER_H

#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include <iostream>

using namespace std;

template<typename DType, typename LType>
class DataLoader {
public:
    class Iterator;  // Forward declaration for iterator class

private:
    Dataset<DType, LType>* ptr_dataset;  // Pointer to the dataset
    int batch_size;                      // Size of each batch
    bool shuffle;                        // Whether to shuffle the dataset
    bool drop_last;                      // Whether to drop the last incomplete batch
    xt::xarray<unsigned long> indices;   // Array of indices for accessing data
    size_t num_batches;                  // Number of batches (excluding leftover handling)

public:
    DataLoader(Dataset<DType, LType>* dataset,
               int batch_size,
               bool shuffle = true,
               bool drop_last = false)
        : ptr_dataset(dataset),
          batch_size(batch_size),
          shuffle(shuffle),
          drop_last(drop_last) {
        
        size_t total_samples = dataset->len();
        indices = xt::arange<unsigned long>(total_samples);

        // Shuffle the indices if shuffle is true
        if (shuffle) {
            xt::random::shuffle(indices);
        }

        // Calculate the number of full batches
        num_batches = total_samples / batch_size;

        // If drop_last is false, check if there are leftovers and increment num_batches if needed
        if (!drop_last && (total_samples % batch_size != 0)) {
            num_batches++;
        }
    }

    virtual ~DataLoader() {}

    // Iterator to support for-each loop in DataLoader
    class Iterator {
    private:
        DataLoader* loader;  // Pointer to the DataLoader
        size_t batch_idx;    // Index of the current batch

    public:
        Iterator(DataLoader* loader, size_t batch_idx)
            : loader(loader), batch_idx(batch_idx) {}

        // Inequality operator to check if two iterators are different
        bool operator!=(const Iterator& other) const {
            return batch_idx != other.batch_idx;
        }

        // Dereference operator to return the current batch
        Batch<DType, LType> operator*() const {
            size_t total_samples = loader->ptr_dataset->len();
            size_t start_idx = batch_idx * loader->batch_size;
            size_t end_idx;

            // Handle last batch inclusion of leftovers
            if (loader->drop_last && batch_idx == loader->num_batches) {
                throw std::out_of_range("No more batches available");
            }
            if (batch_idx == loader->num_batches - 1 && !loader->drop_last) {
                // Include remaining samples in the last batch
                end_idx = total_samples;
            } else {
                // Regular batch size
                end_idx = std::min(start_idx + loader->batch_size, total_samples);
            }

            // Prepare batch data and labels
            xt::xarray<DType> batch_data = xt::empty<DType>({end_idx - start_idx}); 
            xt::xarray<LType> batch_label;

            // Fetch each item for the current batch
            for (size_t i = start_idx; i < end_idx; ++i) {
                DataLabel<DType, LType> data_label = loader->ptr_dataset->getitem(loader->indices[i]);
                batch_data[i - start_idx] = data_label.data; // Assuming DataLabel has a data member
                batch_label.push_back(data_label.label);      // Assuming DataLabel has a label member
            }

            return Batch<DType, LType>(batch_data, batch_label);
        }

        // Increment operator to move to the next batch
        Iterator& operator++() {
            ++batch_idx;
            return *this;
        }
    };

    // Return an iterator pointing to the first batch
    Iterator begin() {
        return Iterator(this, 0);
    }

    // Return an iterator pointing one past the last valid batch
    Iterator end() {
        return Iterator(this, num_batches);
    }
};

#endif /* DATALOADER_H */
