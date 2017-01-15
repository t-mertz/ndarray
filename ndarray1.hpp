#ifndef __NDARRAY_H__

#include <array>

template<class T>
class ndarray {
    using std::array<T> = Array;
    using std::array<unsigned int> = IndexArray;

    private:
        Array _data;

        unsigned int get_linear_index();
        IndexArray& get_nd_index();

    public:
        ndarray();

        void reshape();

        T& operator[] ();

        unsigned int size();


        /*
         * Implement these using Julian's accumulator
         */
        T& sum();

        T& mean();

};


#endif