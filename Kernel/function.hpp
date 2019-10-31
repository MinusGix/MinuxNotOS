#ifndef INCLUDE_FUNCTION_H
#define INCLUDE_FUNCTION_H

// Partial template specialization, so we can use it like Function<int(int, bool)>
// rather than Function<int, int, bool>
template<typename>
class Function;

template<typename ReturnValue, typename... Args>
class Function<ReturnValue(Args...)> {
    private:

    ReturnValue (*callable) (Args...);

    public:

    explicit Function () {
        callable = 0;
    }

    explicit Function (ReturnValue (*z) (Args...)) {
        callable = z;
    }

    bool hasFunction () const {
        return callable != 0;
    }

    template<typename T>
    Function& operator= (T* t) {
        callable = t;
        return *this;
    }

    ReturnValue operator()(Args... args) const {
        return callable(args...);
    }

};

#endif