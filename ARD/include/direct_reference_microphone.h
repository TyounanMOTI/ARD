#pragma once

#include <deque>
#include "microphone.h"

namespace ARD {
  template <class ArrayType>
  class DirectReferenceMicrophone : public Microphone<ArrayType>
  {
  public:
    DirectReferenceMicrophone() {}
    ~DirectReferenceMicrophone() {}
    void Record(const ArrayType& input) {
      _records.push_back(&input);
    }

    ArrayType Pop() {
      if (_records.empty()) {
	return ArrayType();
      } else {
	const ArrayType* result = _records.front();
	_records.pop_front();
	return *result;
      }
    }

  private:
    std::deque<const ArrayType*> _records;
  };
}
