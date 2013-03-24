/*
 * array_test.cpp
 *
 *
 * Bit Array Test Program
 *
 *
 * Copyright (C) 2012-2013  Bryant Moscon - bmoscon@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright,
 *    license and disclaimer information.
 *
 * 3. The end-user documentation included with the redistribution, if any, must 
 *    include the following acknowledgment: "This product includes software 
 *    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
 *    place and form as other third-party acknowledgments. Alternately, this 
 *    acknowledgment may appear in the software itself, in the same form and 
 *    location as other such third-party acknowledgments.
 *
 * 4. Except as contained in this notice, the name of the author, Bryant Moscon,
 *    shall not be used in advertising or otherwise to promote the sale, use or 
 *    other dealings in this Software without prior written authorization from 
 *    the author.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 */
 

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../src/bit_array.hpp"

#define RANDOM_RUN 10

int main () 
{
  srand(time(NULL));
  
  for (uint32_t bits = 1; bits < 64; bits *= 2) {
    for (uint32_t size = 1; size < 10000; size += (rand() % 500)) {
      std::cout << "Running for Array size " << size << " and element bit-width " 
                << bits << std::endl;
      
      uint64_t max_size = pow(2, bits);
      BitArray<uint64_t> array = BitArray<uint64_t>(size, bits);
    
      std::cout << "Verifying array is initalized correctly..." << std::endl;
      // verify each element is zeroed
      for (uint64_t i = 0; i < array.size(); ++i) {
	assert(array.at(i) == 0);
    }
      
      std::cout << "Verifying bounds are enforced..." << std::endl;
      for (uint64_t i = 0; i < array.size(); ++i) {
	//check first that we are still 0
	assert(array.at(i) == 0);
	array.set(i, max_size);
	assert(array.at(i) == 0);
	array.set(i, max_size-1);
	assert(array.at(i) == max_size-1);
	array.inc(i);
      }
      
      // make sure each element in array is at max
      for (uint64_t i = 0; i < array.size(); ++i) {
	assert(array.at(i) == max_size-1);
      }
      
      // re-zero array
      for (uint64_t i = 0; i < array.size(); ++i) {
	array.set(i, 0);
      }
      
      // verify each element is zeroed
      for (uint64_t i = 0; i < array.size(); ++i) {
	assert(array.at(i) == 0);
      }
      
      std::cout << "Pattern test..." << std::endl;
      // set every other element to 1, check that pattern is correct
      for (uint64_t i = 0; i < array.size(); i += 2) {
	array.inc(i);
      }
      
      for (uint64_t i = 0; i < array.size(); i += 2) {
	assert(array.at(i) == 1);
      }
      
      for (uint64_t i = 1; i < array.size(); i += 2) {
	assert(array.at(i) == 0);
      }
      
      
      // re-zero array
      for (uint64_t i = 0; i < array.size(); ++i) {
	array.set(i, 0);
      }
      
      // verify each element is zeroed
      for (uint64_t i = 0; i < array.size(); ++i) {
	assert(array.at(i) == 0);
      }
      
      std::vector<uint64_t> random_numbers(array.size());
      std::cout << "Filling array with random numbers and verifying..." << std::endl;      

      for (uint64_t j = 0; j < RANDOM_RUN; ++j) {	
	for (uint64_t i = 0; i < random_numbers.size(); ++i) {
	  random_numbers[i] = rand() % (max_size - 1);
	  array.set(i, random_numbers[i]);
	}
	
	for (uint64_t i = 0; i < array.size(); ++i) {
	  assert(array.at(i) == random_numbers[i]);
	} 
      }
    }
  }

  std::cout << std::endl << "-------- PASS --------" << std::endl;  

  return 0;
}
