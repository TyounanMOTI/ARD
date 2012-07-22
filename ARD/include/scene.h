#pragma once
#include <deque>
#include <algorithm>
#include "microphone.h"
#include "source.h"
#include "dct_engine.h"
#include "update_formula.h"

namespace ARD {
  template <class ArrayType>
  class Scene
  {
    typedef std::deque<std::shared_ptr<Microphone<ArrayType> > > MicrophoneList;
    typedef std::deque<std::shared_ptr<Source<ArrayType> > > SourceList;
    
  public:
    template <class ExtentList>
    Scene(const ExtentList& extents, const typename ArrayType::element dt)
      :pressure_field_(extents),
       force_field_(extents),
       dct_engine_(force_field_),
       update_formula_(pressure_field_, dt)
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
		      source->Emit(force_field_);
		    });
      const ArrayType& force_spectrum = dct_engine_.Execute();

      update_formula_.Execute(force_spectrum);
      
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
    ArrayType force_field_;
    DCTEngine<ArrayType, Forward> dct_engine_;
    UpdateFormula<ArrayType> update_formula_;
  };
}
