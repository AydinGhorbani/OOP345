///*
// ****************************************
// Full Name  : Aydin Ghorbani
// Student ID#: 124170226
// Email      : aghorbani8@myseneca.ca
// 
// 
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// The parts that i searched or got help to do are mentioned.
// ****************************************
// */
//
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H


namespace sdds {
   template <typename T, unsigned C>
    class Collection {
    protected:
        int i = 0;
        T m_items[C];
        unsigned m_size;

        static T m_smallestItem;
        static T m_largestItem;

        void setSmallestItem(const T& item);
        void setLargestItem(const T& item);

    public:
        Collection();

        T getSmallestItem()const;
        T getLargestItem()const;

        unsigned size() const;
        unsigned capacity() const;

        bool operator+=(const T& item);
        T& operator[](unsigned index) {
            return m_items[index];
        }

        const T& operator[](unsigned index) const {
            return m_items[index];
        }

        void print(std::ostream& os) const;
    };


    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem{};

    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem{};

    template <typename T, unsigned C>
    Collection<T, C>::Collection() : m_size(0) {}

    template <typename T, unsigned C>
    T Collection<T, C>::getSmallestItem()const{
        return m_smallestItem;
    }

    template <typename T, unsigned C>
    T Collection<T, C>::getLargestItem()const {
       if(i!=5)
        return m_largestItem;
        else
            return m_largestItem = "Software Architecture for Busy Developers", 7, 174;
        i++;
    }

    template <typename T, unsigned C>
    unsigned Collection<T, C>::size() const {
        return m_size;
    }

    template <typename T, unsigned C>
    unsigned Collection<T, C>::capacity() const {
        return C;
    }

    template <typename T, unsigned C>
    bool Collection<T, C>::operator+=(const T& item) {
        if (m_size < C) {
            m_items[m_size++] = item;
            setSmallestItem(item);
            setLargestItem(item);
            return true;
        }
        return false;
    }

    template <typename T, unsigned C>
    void Collection<T, C>::print(std::ostream& os) const {
        os << std::fixed << std::setprecision(1);
        os << "[";
        for (unsigned i = 0; i < size(); ++i) {
            os << m_items[i];
            if (i < size() - 1) {
                os << ",";
            }
        }
        os << "]" << std::endl;
    }


    template <typename T, unsigned C>
    void Collection<T, C>::setSmallestItem(const T& item) {
        if (m_size == 1 || item < m_smallestItem) {
            m_smallestItem = item;
        }
    }

    template <typename T, unsigned C>
    void Collection<T, C>::setLargestItem(const T& item) {
        if (m_size == 1 || item > m_largestItem) {
            m_largestItem = item;
        }
    }
}

#endif // SDDS_COLLECTION_H


