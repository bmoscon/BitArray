'''
 Bit Array Implementation


 Copyright (C) 2013-2014  Bryant Moscon - bmoscon@gmail.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to 
 deal in the Software without restriction, including without limitation the 
 rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 1. Redistributions of source code must retain the above copyright notice, 
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, 
    this list of conditions and the following disclaimer in the documentation 
    and/or other materials provided with the distribution, and in the same 
    place and form as other copyright, license and disclaimer information.

 3. The end-user documentation included with the redistribution, if any, must 
    include the following acknowledgment: "This product includes software 
    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
    place and form as other third-party acknowledgments. Alternately, this 
    acknowledgment may appear in the software itself, in the same form and 
    location as other such third-party acknowledgments.

 4. Except as contained in this notice, the name of the author, Bryant Moscon,
    shall not be used in advertising or otherwise to promote the sale, use or 
    other dealings in this Software without prior written authorization from 
    the author.
 

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 THE SOFTWARE.

'''

import array
from math import log

class BitArray(object):
    def __init__(self, bits):
        # L = 4 bytes minimum, but could be 8 bytes. No need to waste all that space
        # so lets look up the size of L on this machine
        self.elem_size = int(log(array.array('L').itemsize * 8, 2))
        self.elem_mask =  int(pow(2, self.elem_size) - 1)
        size = bits >> self.elem_size;
        if bits & self.elem_mask:
            size += 1
        
        self.bits = array.array('L', (0,) * size)


    def set(self, bit):
        # first look up the entry in the array
        array_index = bit >> self.elem_size
        # find position of bit in the individual element
        bit_position = bit & self.elem_mask
        # generate a mask to apply to the array element
        mask = 1 << bit_position
        
        # apply the mask
        self.bits[array_index] |= mask
        
    def clear(self, bit):
        # first look up the entry in the array
        array_index = bit >> self.elem_size
        # find position of bit in the individual element
        bit_position = bit & self.elem_mask
        # generate a mask to apply to the array element,
        # but invert it since we are clearing
        mask = 1 << bit_position
        mask = ~mask
        
        self.bits[array_index] &= mask


    def bit(self, bit):
         # first look up the entry in the array
        array_index = bit >> self.elem_size
        # find position of bit in the individual element
        bit_position = bit & self.elem_mask
        # generate a mask to apply to the array element
        mask = 1 << bit_position
        
        return 1 if self.bits[array_index] & mask > 0 else 0


