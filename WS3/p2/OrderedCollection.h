#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H
#include "Collection.h"

namespace sdds {
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    private:
        bool m_isEmpty;

    public:
        OrderedCollection() : m_isEmpty(true) {}

        bool operator+=(const T& item) {
            if (this->size() < this->capacity()) {
                // Find the index where the item should be inserted to maintain ascending order
                unsigned insertIndex = 0;
                while (insertIndex < this->size() && item > this->operator[](insertIndex)) {
                    insertIndex++;
                }

                // Shift elements to make space for the new item
                for (unsigned i = this->size(); i > insertIndex; i--) {
                    this->m_items[i] = this->m_items[i - 1];
                }

                // Insert the item at the appropriate index
                this->m_items[insertIndex] = item;
                this->m_size++; // Increase the size

                // Update the smallest and largest items if necessary
                if (m_isEmpty || item < this->getSmallestItem()) {
                    this->setSmallestItem(item);
                }
                if (m_isEmpty || item > this->getLargestItem()) {
                    this->setLargestItem(item);
                }

                m_isEmpty = false; // The collection is no longer empty

                return true;
            }
            return false;
        }

        std::ostream& print(std::ostream& os) const {
            for (unsigned i = 0; i < this->size(); i++) {
                os << this->m_items[i];
                if (i < this->size() - 1) {
                    os << " | ";
                }
            }
            return os;
        }
    };
}

#endif // SDDS_ORDEREDCOLLECTION_H
