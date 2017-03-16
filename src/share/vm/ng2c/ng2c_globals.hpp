#ifndef SHARE_VM_NG2C_NG2C_GLOBALS_HPP
#define SHARE_VM_NG2C_NG2C_GLOBALS_HPP

# include "memory/allocation.inline.hpp"

typedef unsigned long ngen_t;

const static int NG2C_GEN_ARRAY_SIZE = 16;

class NGenerationArray : public CHeapObj<mtGC>
{
 private:
  // The hash value use is for helping reference the arrays in the hashtable
  // when applying deltas.
  uint     _hash;
  char     _target_gen;
  // The actual array.
  ngen_t * _array;

 public:
  NGenerationArray(uint hash) : _hash(hash), _target_gen(0) {
      _array = NEW_C_HEAP_ARRAY(ngen_t, NG2C_GEN_ARRAY_SIZE + 1, mtGC);
      bzero(_array, (NG2C_GEN_ARRAY_SIZE + 1) * sizeof(ngen_t));
  }
  NGenerationArray(ngen_t * array, uint hash, char target_gen) : _array(array), _hash(hash), _target_gen(target_gen) { }
  NGenerationArray(const NGenerationArray& copy) : _array(copy.array()), _hash(copy.hash()), _target_gen(copy.target_gen()) { }

  ngen_t * array() const { return _array; }
  uint     hash()  const { return _hash; }
  int      size()  const { return NG2C_GEN_ARRAY_SIZE; } // hard-coded for now
  ngen_t   at(int pos) const { return _array[pos]; }
  char   target_gen() const { return _target_gen; }
  char * target_gen_addr()  { return &_target_gen; }

  void   apply_delta (NGenerationArray * thread_arr);
  unsigned int new_hash (int seed) {
    assert(false, "new_hash called for NGenerationArray...");
    return (unsigned int)0;
  } // placeholder
  
  
};

#endif // SHARE_VM_NG2C_NG2C_GLOBALS_HPP
