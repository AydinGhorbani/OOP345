#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>

namespace sdds {
template <typename T>
class Collection {
    
public:
    // Constructor: Sets the name of the collection and initializes other attributes
    Collection(const std::string& name)
    : name_(name),size_(0), items_(nullptr),  observer_(nullptr) {
    }
    
    // Destructor
    ~Collection() {
        delete[] items_;
    }
    
    // Query: Return the name of the collection
    const std::string& name() const {
        return name_;
    }
    
    // Query: Return the number of items in the collection
    size_t size() const {
        return size_;
    }
    
    // Set the observer function
    void setObserver(void (*observer)(const Collection<T>&, const T&)) {
        observer_ = observer;
    }
    
    // Overload += operator to add an item to the collection
    Collection<T>& operator+=(const T& item) {
        if (!containsItem(item)) {
            T* newItems = new T[size_ + 1];
            // Copy existing items
            for (size_t i = 0; i < size_; ++i) {
                newItems[i] = items_[i];
            }
            newItems[size_] = item;
            delete[] items_;
            items_ = newItems;
            size_++;
            
            // Notify the observer if available
            if (observer_) {
                observer_(*this, item);
            }
        }
        return *this;
    }
    
    // Overload [] operator to access items by index
    const T& operator[](size_t idx) const {
        if (idx >= size_) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(size_) + "] items.");
        }
        return items_[idx];
    }
    
    // Overload [] operator to access items by title
    T* operator[](const std::string& title) const {
        for (size_t i = 0; i < size_; ++i) {
            if (items_[i].title() == title) {
                return &items_[i];
            }
        }
        return nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const Collection& col) {
        for (size_t i = 0; i < col.size_; ++i) {
            os << col.getItem(i);
        }
        return os;
    }

    const T& getItem(size_t index) const {
        if (index < size_) {
            return items_[index];
        } else {
            throw std::out_of_range("Bad index [" + std::to_string(index) + "]. Collection has [" + std::to_string(size_) + "] items.");
        }
    }
    

private:
    std::string name_;
    size_t size_;
    T* items_;
    void (*observer_)(const Collection<T>&, const T&);
    
    bool containsItem(const T& item) {
        for (size_t i = 0; i < size_; ++i) {
            if (items_[i].title() == item.title()) {
                return true;
            }
        }
        return false;
    }
};
}
#endif //SDDS_COLLECTION_H
