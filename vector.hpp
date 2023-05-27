#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    private:
        T *data;
        size_t length = 0;
        size_t max_lenth = 10;
        void doubleSpace() {
            T *tmp;
            tmp = (T *) malloc(sizeof(T) * max_lenth);
            for (int i = 0; i < length; i++) {
                new(tmp + i) T(data[i]);
                data[i].~T();
            }
            free(data);
            max_lenth <<= 1;
            data = (T *) malloc(sizeof(T) * max_lenth);
            for (int i = 0; i < length; i++) {
                new(data + i) T(tmp[i]);
                tmp[i].~T();
            }
            free(tmp);
        }
        void halfspace(){
        	T *tmp;
            tmp = (T *) malloc(sizeof(T) * max_lenth);
            for (int i = 0; i < length; i++) {
                new(tmp + i) T(data[i]);
                data[i].~T();
            }
            free(data);
            max_lenth >>= 1;
            data = (T *) malloc(sizeof(T) * max_lenth);
            for (int i = 0; i < length; i++) {
                new(data + i) T(tmp[i]);
                tmp[i].~T();
            }
            free(tmp);
		}

        void quick_sort(int l, int r){
        	if(l >= r) return;
        	int i = l, j = r, mid = (l + r) >> 1;
        	T tmp = data[mid];
            while(i <= j) {
                while (data[i] < tmp) i++;
                while (data[j] > tmp) j--;
                if (i <= j) {
                    T t = data[i];
                    data[i] = data[j];
                    data[j] = t;
                    i++;
                    j--;
                }
            }
            quick_sort(l, j);
            quick_sort(i, r);
        }
    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */


        class const_iterator;

        class iterator {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            T *iter, *begin, *end;

            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            iterator() {
                iter = begin = end = nullptr;
            }

            iterator(T *iter_, T *begin_, T *end_) {
                iter = iter_;
                begin = begin_;
                end = end_;
            }

            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                return iterator(iter + n, begin, end);
                //TODO
            }

            iterator operator-(const int &n) const {
                return iterator(iter - n, begin, end);
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (begin != rhs.begin || end != rhs.end)throw invalid_iterator();
                return iter - rhs.iter;
                //TODO
            }

            iterator &operator+=(const int &n) {
                iter += n;
                return *this;
                //TODO
            }

            iterator &operator-=(const int &n) {
                iter -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iter++;
                return iterator(iter - 1, begin, end);
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                iter++;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iter--;
                return iterator(iter + 1, begin, end);
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                iter--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return *iter;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if (iter == rhs.iter)return true;
                else return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (iter == rhs.iter)return true;
                else return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (iter != rhs.iter)return true;
                else return false;
            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)return true;
                else return false;
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        private:
            T *iter, *begin, *end;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

            const_iterator(T *iter_, T *begin_, T *end_) {
                iter = iter_;
                begin = begin_;
                end = end_;
            }

            const_iterator operator+(const int &n) const {
                return const_iterator(iter + n, begin, end);
                //TODO
            }

            const_iterator operator-(const int &n) const {
                return const_iterator(iter - n, begin, end);
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if (begin != rhs.begin || end != rhs.end)throw invalid_iterator();
                return iter - rhs.iter;
                //TODO
            }

            const_iterator &operator+=(const int &n) {
                iter += n;
                return *this;
                //TODO
            }

            const_iterator &operator-=(const int &n) {
                iter -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                iter++;
                return const_iterator(iter - 1, begin, end);
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                iter++;
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                iter--;
                return const_iterator(iter + 1, begin, end);
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                iter--;
                return *this;
            }

            /**
             * TODO *it
             */
            const T operator*() const {
                return *iter;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if (iter == rhs.iter)return true;
                else return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (iter == rhs.iter)return true;
                else return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (iter != rhs.iter)return true;
                else return false;
            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)return true;
                else return false;
            }
        };

        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        vector() {
            data = (T *) malloc(sizeof(T) * 10);
        }

        vector(const vector &other) {
            length = other.length;
            max_lenth = other.max_lenth;
            data = (T *) malloc(sizeof(T) * max_lenth);
            for (int i = 0; i < length; i++) {
                new(data + i) T(other.data[i]);
            }
        }

        /**
         * TODO Destructor
         */
        ~vector() {
            for (int i = 0; i < length; i++) {
                data[i].~T();
            }
            free(data);
        }

        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (this == &other)return *this;
            for (int i = 0; i < length; i++) {
                data[i].~T();
            }
            free(data);
            length = other.length;
            max_lenth = other.max_lenth;
            data = (T *) malloc(sizeof(T) * max_lenth);
            for (int i = 0; i < length; i++) {
                new(data + i) T(other.data[i]);
            }
            return *this;
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T &at(const size_t &pos) {
            if (pos > length - 1 || pos < 0)throw index_out_of_bound();
            return data[pos];
        }

        const T &at(const size_t &pos) const {
            if (pos > length - 1 || pos < 0)throw index_out_of_bound();
            return data[pos];
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            if (pos > length - 1 || pos < 0)throw index_out_of_bound();
            return data[pos];
        }

        const T &operator[](const size_t &pos) const {
            if (pos > length - 1 || pos < 0)throw index_out_of_bound();
            return data[pos];
        }

        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T &front() const {
            if (length == 0)throw container_is_empty();
            return data[0];
        }

        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            if (length == 0)throw container_is_empty();
            return data[length - 1];
        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(data, data, data + length);
        }

        const_iterator cbegin() const {
            return const_iterator(data, data, data + length);
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(data + length, data, data + length);
        }

        const_iterator cend() const {
            return const_iterator(data + length, data, data + length);
        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            if (length == 0)return true;
            return false;
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return length;
        }

        /**
         * clears the contents
         */
        void clear() {
            for (int i = 0; i < length; i++) {
                data[i].~T();
            }
            free(data);
            data = (T *) malloc(sizeof(T) * 10);
            length = 0;
            max_lenth=10;
        }

        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            int n = pos - begin();
            if (length == max_lenth)doubleSpace();
            new(data + length) T(data[length - 1]);
            for (int i = length - 1; i > n; i--) {
                data[i] = data[i - 1];
            }
            data[n] = value;length++;
            return pos;
        }

        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if (ind > length)throw index_out_of_bound();
            iterator pos = begin()+ind;
            if (length == max_lenth)doubleSpace();
            new(data + length) T(data[length - 1]);
            for (int i = length - 1; i > ind; i--) {
                data[i] = data[i - 1];
            }
            data[ind] = value;length++;
            return pos;
        }

        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            int n = pos - begin();
            length--;
            for (int i = n; i < length; i++) {
                data[i] = data[i + 1];
            }
            data[length].~T();
            if (length<max_lenth/4) halfspace();
            return iterator(data + n, data, data + length);
        }

        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if (ind >= length)throw index_out_of_bound();
            for (int i = ind; i < length - 1; i++) {
                data[i] = data[i + 1];
            }
            length--;
            data[length].~T();
            if (length<max_lenth/4) halfspace();
            return iterator(data + ind, data, data + length);
        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (length == max_lenth)doubleSpace();
            length++;
            new(data + length - 1) T(value);
        }

        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (length == 0)throw container_is_empty();
            length--;
            data[length].~T();
            if (length<max_lenth/4) halfspace();
        }

        void sort(){
            quick_sort(0,length-1);
        }
    };


}

#endif
