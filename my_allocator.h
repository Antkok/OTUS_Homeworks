#pragma once

#include <list>
#include <cstdlib>
#include <new>
#include <limits>

template <typename T, size_t ElemCount=0>
struct myAlloc
{
public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    myAlloc() = default;

    template <typename U> 
    myAlloc(const myAlloc <U, ElemCount>&) {}

    template<typename U>
    struct rebind
    {
        using other = myAlloc<U,ElemCount>;
    };

    pointer allocate(size_t n)
    {
        pointer p;
        if (!freeElems.empty() && n == 1) {
            p = freeElems.front();
            freeElems.pop_front();
        } else if (currentShift + n < ElemCount && !packs.empty()) {
            p = packs.front() + currentShift;
            currentShift += n;
        } else {
            if (!packs.empty())
                for (;currentShift < ElemCount; ++currentShift) {
                    freeElems.push_back(packs.front() + currentShift);
                }
            p = tempAlloc(n);
            currentShift = n;
        }
        return p;
    }

    pointer allocate() {
        return allocate(1);
    }

    void deallocate(pointer p, std::size_t n=0) {
        if(p && n==0) {
            --currentShift;
            freeElems.push_back(p);
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U *p) {
        p->~U();
    }
private:
    std::list<pointer> packs;
    std::list<pointer> freeElems;
    size_t currentShift = 0;
    pointer tempAlloc (size_t cnt) {
        size_t sz = std::max(cnt, (size_t)ElemCount);
        auto p = static_cast<pointer>(std::malloc(sz*sizeof(T)));
        if (!p) {
            throw std::bad_alloc();
        }
        packs.push_front(p);
        return p;
    }
};