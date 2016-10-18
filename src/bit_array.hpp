/*
 * bit_array.hpp
 *
 *
 * Bit Array Implementation
 *
 *
 * Copyright (C) 2012-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * See LICENSE for more information regarding the terms and conditions associated
 * with the use of this software. 
 *
 */
 
#ifndef __BIT_ARRAY__
#define __BIT_ARRAY__

#include <stdint.h>
#include <vector>
#include <cmath>
#include <cassert>


template <class T = uint64_t>
class BitArray {

public:

    BitArray(const T &elements, const T &bits_per_element = 1) :
	array_(ceil(elements * bits_per_element / (sizeof(T) * 8.0)), 0),
	elem_bits_(bits_per_element),
	elem_mask_(pow(2, bits_per_element) - 1),
	bitcount_(sizeof(T) << 3),
	len_(elements)
    { 
	assert(bits_per_element > 0 && bits_per_element < 64);
	assert(sizeof(T) * 8 % bits_per_element == 0);
	index_shift_ = log2(bitcount_);
    }
    
    T at(const T &index) const {
	T idx = index_translate(index);
	T mask = elem_mask_ << (bitcount_ - idx);
	
	return (lookup(idx, mask));
    }
    
    void inc(const T &index) {
	T idx = index_translate(index);
	T mask = elem_mask_;
	
	mask <<= (bitcount_ - idx);
	
	T value = lookup(idx, mask);
	
	if (value == elem_mask_) {
	    return;
	} else {
	    array_[idx >> index_shift_] &= ~mask;
	    
	    ++value;
	    value <<= (bitcount_ - idx);
	    
	    array_[idx >> index_shift_] |= value;
	}
    }
    
    void dec(const T &index) {
	T idx = index_translate(index);
	T mask = elem_mask_;
	
	mask <<= (bitcount_ - idx);
	
	T value = lookup(idx, mask);
	
	if (value == 0) {
	    return;
	} else {
	    array_[idx >> index_shift_] &= ~mask;
	    
	    --value;
	    value <<= (bitcount_ - idx);
	    
	    array_[idx >> index_shift_] |= value;
	}
    }
    
    void set(const T &index, T value) {
	if (value > elem_mask_) {
	    return;
	}
	
	T idx = index_translate(index);
	T mask = elem_mask_;
	
	mask <<= (bitcount_ - idx);
	array_[idx >> index_shift_] &= ~mask;
	
	value <<= (bitcount_ - idx);
	array_[idx >> index_shift_] |= value;
    }
    
    T size() const {
	return (len_);
    }
    
    void dump() {
	for (T i = 0; i < array_.size(); ++i) {
	    std::cout << array_[i] << std::endl;
	}
    }
    
    
protected:
    
    inline T index_translate(const T &index) const { 
	return (index << log2(elem_bits_));
    }
    
    inline T lookup(const T &index, T &mask) const {
	return ((array_[index >> index_shift_] & mask) >> (bitcount_ - index));
    }
    
    inline uint32_t log2(const uint32_t x) const {
	uint32_t ret;
	
	asm ( "\tbsr %1, %0\n"
	      : "=r" (ret)
	      : "r"  (x)
	      );
	
	return (ret);
    }
    
    // Array that holds the underlying datatype elements
    std::vector<T> array_;
    // number of bits per element
    T elem_bits_; 
    // mask to select each element
    T elem_mask_;
    // # of bits in the underlying datatype
    T bitcount_;
    // log2 of bitcount, used in shifting the index
    uint32_t index_shift_;
    // user defined len
    T len_;
};


#endif
