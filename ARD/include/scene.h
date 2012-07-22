#pragma once
#include <deque>
#include <algorithm>
#include "microphone.h"
#include "source.h"

namespace ARD {
  template <class ArrayType>
  class Scene
  {
    typedef std::deque<std::shared_ptr<Microphone<ArrayType> > > MicrophoneList;
    typedef std::deque<std::shared_ptr<Source<ArrayType> > > SourceList;
    
  public:
    template <class ExtentList>
    explicit
    Scene(const ExtentList& extents)
      :pressure_field_(extents)
    {}

    void AddMicrophone(std::shared_ptr<Microphone<ArrayType> > microphone) {
      microphones_.push_back(microphone);
    }

    void AddSource(std::shared_ptr<Source<ArrayType> > source) {
      sources_.push_back(source);
    }
    
    MicrophoneList Update() {
      std::for_each(sources_.begin(), sources_.end(),
		    [&](typename SourceList::value_type source) {
		      source->Emit(pressure_field_);
		    });
      std::for_each(microphones_.begin(), microphones_.end(),
		    [&](typename MicrophoneList::value_type microphone) {
		      microphone->Record(pressure_field_);
		    });
      return microphones_;
    }

  private:
    MicrophoneList microphones_;
    SourceList sources_;

    ArrayType pressure_field_;
  };
}
