#pragma once

#include<cstdlib>
#include<map>

template<typename T, T default_value, size_t dimensions = 2>
class matrix {
public:
    using nested_stor = std::map<size_t, matrix<T, default_value, dimensions-1>>;
    using innerIter = typename matrix<T, default_value, dimensions-1>::myIterator;
    using iter = typename nested_stor::iterator;
    using citer = typename nested_stor::const_iterator;

    [[nodiscard]] size_t size() const {
        size_t res = 0;
        for (const auto& a : elements)
            res += a.second.size();
        return res;
    }
    auto& operator[](size_t idx1) {
        return elements[idx1];
    }
    class myIterator: public std::iterator<std::forward_iterator_tag, iter>
    {
    public:
        myIterator(const iter& _ptr, nested_stor& stor): ptr(_ptr), innerPtr(_ptr->second.begin()), mapPtr(stor)
        {
            changeInner();
        }

        myIterator(const myIterator& other, nested_stor& stor): ptr(other.ptr), innerPtr(other->second.begin()), mapPtr(stor)
        {
            changeInner();
        }

        auto operator *() const
        {
            return std::make_tuple(ptr->first, innerPtr->first, innerPtr->second);
        }

        bool operator!=(myIterator const& other) const
        {
            return this->ptr != other.ptr;
        }

        bool operator==(myIterator const& other) const
        {
            return this->ptr == other.ptr;
        }

        myIterator& operator++()
        {
            if (innerPtr != (*ptr).second.end()) innerPtr++;
            changeInner();
            return *this;
        }

    private:
        iter ptr;
        innerIter innerPtr;
        nested_stor& mapPtr;
        void changeInner() {
            while ((innerPtr == (*ptr).second.end() || (*ptr).second.size() == 0) && ptr != mapPtr.end()) {
                ptr++;
                if (ptr != mapPtr.end() && (*ptr).second.size() != 0) {
                    innerPtr = (*ptr).second.begin();
                }
            }
        }
    };
    auto begin() {
        return myIterator(elements.begin(), elements);
    }
    auto end() {
        return myIterator(elements.end(), elements);
    }
private:
    nested_stor elements;
};

template<typename T, T default_value>
class matrix<T, default_value, 1> {
public:
    using stor = typename std::map<size_t, T>;
    using myIterator = typename stor::iterator;

    class ElemsProxy{
        stor& data;
        size_t idx;
    public:
        ElemsProxy(stor& data, size_t _idx) : data(data), idx(_idx){};
        operator T(){
            return data.find(idx) != data.end() ? data[idx] : default_value;
        }
        operator const T() const {
            return data.find(idx) != data.end() ? data[idx] : default_value;
        }
        ElemsProxy& operator=(T value){
            if(value != default_value)
                data[idx] = value;
            else
                data.erase(idx);
            return *this;
        };
    };
    [[nodiscard]] size_t size() const {
        return elements.size();
    }
    auto operator[](size_t idx) {
        return ElemsProxy(elements, idx);
    }
    [[nodiscard]] bool empty() const {
        return size() == 0;
    }
    auto begin() {
        return elements.begin();
    }
    auto end() {
        return elements.end();
    }
private:
    stor elements;
};