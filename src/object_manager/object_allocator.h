#pragma once

#include "common.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>

namespace bk
{

template<typename T>
class object_allocator
{
public:

    object_allocator(uint32_t max_objects);
    ~object_allocator();

    template<typename... Args>
    T *allocate(Args&&... args);

    void deallocate(T *p_ptr);

private:

    uint8_t* mp_buf;
    uint32_t m_max_objects;
    bool *mp_free_objects;
};

template<typename T>
object_allocator<T>::object_allocator(uint32_t max_objects) :
    m_max_objects(max_objects)
{
    mp_buf = new uint8_t[sizeof(T) * max_objects];
    mp_free_objects = new bool[max_objects];
    for (int i = 0; i < max_objects; i++) { mp_free_objects[i] = true; }
}

template<typename T>
object_allocator<T>::~object_allocator()
{
    delete[] mp_buf;
    delete[] mp_free_objects;
}

template<typename T>
template<typename... Args>
T *object_allocator<T>::allocate(Args&&... args)
{
    int object_idx = -1;
    for (int i = 0; i < m_max_objects; i++) {
        if (mp_free_objects[i]) {
            object_idx = i;
            break;
        }
    }
    
    if (object_idx == -1) {
        BK_ASSERT((0), "Object allocator %s out of memory\n", typeid(T).name());
        return nullptr;
    }
    
    new (&mp_buf[object_idx * sizeof(T)]) T(std::forward<Args>(args)...);
    mp_free_objects[object_idx] = false;
    return (T*)&mp_buf[object_idx * sizeof(T)];
}

template<typename T>
void object_allocator<T>::deallocate(T *p_ptr)
{
    T* p_curr_object = (T*)&mp_buf[0];
    
    for (int i = 0; i < m_max_objects; i++) {
        if (p_ptr == p_curr_object) {
            p_ptr->~T(); // call destructor
            mp_free_objects[i] = true;
            return;
        }

        p_curr_object++;
    }
    
    BK_ASSERT((0), "Object allocator %s invalid free\n", typeid(T).name());
}

} // namespace geri
