#include<string>
#include<vector>
#include<exception> // invalid_argument

using namespace std;

class slice {
    /*
     * slice
     * stores start, stop and step for array filtering
     */
    private:
        int _start, _stop, _step;
    
    public:
        slice(int stop) : _start(0), _stop(stop), _step(1){}
        slice(int start, int stop) : _start(start), _stop(stop), _step(1){}
        slice(int start, int stop, int step) : _start(start), _stop(stop), _step(step) {}

        int get_start() {
            return _start;
        }

        int get_stop() {
            return _stop;
        }
        
        int get_step() {
            return _step;
        }
}

template <typename st>
class ndarray {
    /*
     * n-dimensional array.
     * template typename st is scalar type, basic arithmetic operations are defined between builtin scalar types
     * and ndarrays.
     */


    /*
        members
    */
    using Array = vector<st>; // use array instead? contiguous memory!
    using IndexVector = vector<unsigned int>;

    private:
        Array _array;
        IndexVector _dims;
    
    /* 
        operators st=scalar type
    */
    operator+(ndarray, ndarray);
    
    template <typename st_arg>
    operator+(ndarray, st_arg);
    
    template <typename st_arg>
    operator+(st_arg, ndarray);
    
    operator-(ndarray, ndarray);
    
    template <typename st_arg>
    operator-(ndarray, st_arg);
    
    template <typename st_arg>
    operator-(st_arg, ndarray);
    
    operator*(ndarray, ndarray);
    
    template <typename st_arg>
    operator*(ndarray, st_arg);
    
    template <typename st_arg>
    operator*(st_arg, ndarray);
    
    operator/(ndarray, ndarray);

    template <typename st_arg>
    operator/(ndarray, st_arg);

    template <typename st_arg>
    operator/(st_arg, ndarray);

    st operator[] ();
    
    /*
        methods
    */
    public:
        ndarray(string);
        ~ndarray();
        sum(int);
        int sum();
        slice(int, int);
        unsigned int size();
        IndexVector& shape();
};

template <typename t>
ndarray::ndarray(string dims) {
    vector<unsigned int> idims = util::get_dims(dims);
    unsigned int elements = util::prod<unsigned int>(idims);
    _array = vector<t>(elements);
}

ndarray& operator[] (slice) {
    // this should return an array of references to entries in the original array.
}

ndarray::~ndarray() {
    delete _array;
}

st ndarray::sum() {
    /*
     * Sum up all array elements.sum
     *
     * ! This should really be implemented using some accumulator that resolves
     * ! the cancellation problem.
     */
    st OUT = 0;
    for (iterator it=_array.begin(); it != _array.end(); ++it) {
        OUT += *it;
    }
    return OUT;
}






namespace util {
    /*
        convenience functions
    */
    using IndexVector = vector<unsigned int>;

    IndexVector get_dims(string dims) {
        /*
        * Parse the input string, find dimensions and return them as vector<unsigned int>.
        */
        IndexVector OUT;
        for (string::iterator it=dims.begin(); it != dims.end(); ++it) {
            string temp;
            if (*it != ",") {
                temp.push_back(*it);
            }
            else {
                if (temp.size() > 0) {
                    try {
                        OUT.push_back(stoi(temp));
                    }
                    catch {
                        throw exception::invalid_argument;
                    }
                }
                throw exception::invalid_argument;
            }
        }
    }

    template <typename st>
    st prod(vector<st> IN) {
        st OUT = 1;
        for (iterator it=IN.begin; it != IN.end(); ++it) {
            OUT *= *it;
        }
        return OUT;
    }

}