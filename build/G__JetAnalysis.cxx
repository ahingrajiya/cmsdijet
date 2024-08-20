// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__JetAnalysis
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "JetESRAnalysis.h"
#include "Event.h"
#include "Track.h"
#include "GenTrack.h"
#include "RecoJet.h"
#include "GenJet.h"
#include "BaseAnalysis.h"
#include "BaseReader.h"
#include "BaseHistoManager.h"
#include "BaseJet.h"
#include "BaseTrack.h"
#include "HistoManagerJetESR.h"
#include "Collections.h"
#include "ForestAODReader.h"
#include "ForestminiAODReader.h"
#include "JetCorrector.h"
#include "JetUncertainty.h"
#include "EventCut.h"
#include "JetCut.h"
#include "Manager.h"
#include "TriggerAndSkim.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void delete_BaseAnalysis(void *p);
   static void deleteArray_BaseAnalysis(void *p);
   static void destruct_BaseAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BaseAnalysis*)
   {
      ::BaseAnalysis *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BaseAnalysis >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("BaseAnalysis", ::BaseAnalysis::Class_Version(), "BaseAnalysis.h", 23,
                  typeid(::BaseAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BaseAnalysis::Dictionary, isa_proxy, 4,
                  sizeof(::BaseAnalysis) );
      instance.SetDelete(&delete_BaseAnalysis);
      instance.SetDeleteArray(&deleteArray_BaseAnalysis);
      instance.SetDestructor(&destruct_BaseAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BaseAnalysis*)
   {
      return GenerateInitInstanceLocal(static_cast<::BaseAnalysis*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BaseAnalysis*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BaseHistoManager(void *p = nullptr);
   static void *newArray_BaseHistoManager(Long_t size, void *p);
   static void delete_BaseHistoManager(void *p);
   static void deleteArray_BaseHistoManager(void *p);
   static void destruct_BaseHistoManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BaseHistoManager*)
   {
      ::BaseHistoManager *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BaseHistoManager >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("BaseHistoManager", ::BaseHistoManager::Class_Version(), "BaseHistoManager.h", 19,
                  typeid(::BaseHistoManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BaseHistoManager::Dictionary, isa_proxy, 4,
                  sizeof(::BaseHistoManager) );
      instance.SetNew(&new_BaseHistoManager);
      instance.SetNewArray(&newArray_BaseHistoManager);
      instance.SetDelete(&delete_BaseHistoManager);
      instance.SetDeleteArray(&deleteArray_BaseHistoManager);
      instance.SetDestructor(&destruct_BaseHistoManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BaseHistoManager*)
   {
      return GenerateInitInstanceLocal(static_cast<::BaseHistoManager*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BaseHistoManager*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HistoManagerJetESR(void *p = nullptr);
   static void *newArray_HistoManagerJetESR(Long_t size, void *p);
   static void delete_HistoManagerJetESR(void *p);
   static void deleteArray_HistoManagerJetESR(void *p);
   static void destruct_HistoManagerJetESR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistoManagerJetESR*)
   {
      ::HistoManagerJetESR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HistoManagerJetESR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("HistoManagerJetESR", ::HistoManagerJetESR::Class_Version(), "HistoManagerJetESR.h", 29,
                  typeid(::HistoManagerJetESR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HistoManagerJetESR::Dictionary, isa_proxy, 4,
                  sizeof(::HistoManagerJetESR) );
      instance.SetNew(&new_HistoManagerJetESR);
      instance.SetNewArray(&newArray_HistoManagerJetESR);
      instance.SetDelete(&delete_HistoManagerJetESR);
      instance.SetDeleteArray(&deleteArray_HistoManagerJetESR);
      instance.SetDestructor(&destruct_HistoManagerJetESR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HistoManagerJetESR*)
   {
      return GenerateInitInstanceLocal(static_cast<::HistoManagerJetESR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::HistoManagerJetESR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BaseJet(void *p = nullptr);
   static void *newArray_BaseJet(Long_t size, void *p);
   static void delete_BaseJet(void *p);
   static void deleteArray_BaseJet(void *p);
   static void destruct_BaseJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BaseJet*)
   {
      ::BaseJet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BaseJet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("BaseJet", ::BaseJet::Class_Version(), "BaseJet.h", 20,
                  typeid(::BaseJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BaseJet::Dictionary, isa_proxy, 4,
                  sizeof(::BaseJet) );
      instance.SetNew(&new_BaseJet);
      instance.SetNewArray(&newArray_BaseJet);
      instance.SetDelete(&delete_BaseJet);
      instance.SetDeleteArray(&deleteArray_BaseJet);
      instance.SetDestructor(&destruct_BaseJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BaseJet*)
   {
      return GenerateInitInstanceLocal(static_cast<::BaseJet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BaseJet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RecoJet(void *p = nullptr);
   static void *newArray_RecoJet(Long_t size, void *p);
   static void delete_RecoJet(void *p);
   static void deleteArray_RecoJet(void *p);
   static void destruct_RecoJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RecoJet*)
   {
      ::RecoJet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RecoJet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RecoJet", ::RecoJet::Class_Version(), "RecoJet.h", 23,
                  typeid(::RecoJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RecoJet::Dictionary, isa_proxy, 4,
                  sizeof(::RecoJet) );
      instance.SetNew(&new_RecoJet);
      instance.SetNewArray(&newArray_RecoJet);
      instance.SetDelete(&delete_RecoJet);
      instance.SetDeleteArray(&deleteArray_RecoJet);
      instance.SetDestructor(&destruct_RecoJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RecoJet*)
   {
      return GenerateInitInstanceLocal(static_cast<::RecoJet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RecoJet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GenJet(void *p = nullptr);
   static void *newArray_GenJet(Long_t size, void *p);
   static void delete_GenJet(void *p);
   static void deleteArray_GenJet(void *p);
   static void destruct_GenJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenJet*)
   {
      ::GenJet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GenJet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GenJet", ::GenJet::Class_Version(), "GenJet.h", 23,
                  typeid(::GenJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GenJet::Dictionary, isa_proxy, 4,
                  sizeof(::GenJet) );
      instance.SetNew(&new_GenJet);
      instance.SetNewArray(&newArray_GenJet);
      instance.SetDelete(&delete_GenJet);
      instance.SetDeleteArray(&deleteArray_GenJet);
      instance.SetDestructor(&destruct_GenJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenJet*)
   {
      return GenerateInitInstanceLocal(static_cast<::GenJet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::GenJet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BaseTrack(void *p = nullptr);
   static void *newArray_BaseTrack(Long_t size, void *p);
   static void delete_BaseTrack(void *p);
   static void deleteArray_BaseTrack(void *p);
   static void destruct_BaseTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BaseTrack*)
   {
      ::BaseTrack *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BaseTrack >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("BaseTrack", ::BaseTrack::Class_Version(), "BaseTrack.h", 20,
                  typeid(::BaseTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BaseTrack::Dictionary, isa_proxy, 4,
                  sizeof(::BaseTrack) );
      instance.SetNew(&new_BaseTrack);
      instance.SetNewArray(&newArray_BaseTrack);
      instance.SetDelete(&delete_BaseTrack);
      instance.SetDeleteArray(&deleteArray_BaseTrack);
      instance.SetDestructor(&destruct_BaseTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BaseTrack*)
   {
      return GenerateInitInstanceLocal(static_cast<::BaseTrack*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BaseTrack*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Track(void *p = nullptr);
   static void *newArray_Track(Long_t size, void *p);
   static void delete_Track(void *p);
   static void deleteArray_Track(void *p);
   static void destruct_Track(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Track*)
   {
      ::Track *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Track >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Track", ::Track::Class_Version(), "Track.h", 20,
                  typeid(::Track), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Track::Dictionary, isa_proxy, 4,
                  sizeof(::Track) );
      instance.SetNew(&new_Track);
      instance.SetNewArray(&newArray_Track);
      instance.SetDelete(&delete_Track);
      instance.SetDeleteArray(&deleteArray_Track);
      instance.SetDestructor(&destruct_Track);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Track*)
   {
      return GenerateInitInstanceLocal(static_cast<::Track*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Track*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GenTrack(void *p = nullptr);
   static void *newArray_GenTrack(Long_t size, void *p);
   static void delete_GenTrack(void *p);
   static void deleteArray_GenTrack(void *p);
   static void destruct_GenTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GenTrack*)
   {
      ::GenTrack *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GenTrack >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GenTrack", ::GenTrack::Class_Version(), "GenTrack.h", 20,
                  typeid(::GenTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GenTrack::Dictionary, isa_proxy, 4,
                  sizeof(::GenTrack) );
      instance.SetNew(&new_GenTrack);
      instance.SetNewArray(&newArray_GenTrack);
      instance.SetDelete(&delete_GenTrack);
      instance.SetDeleteArray(&deleteArray_GenTrack);
      instance.SetDestructor(&destruct_GenTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GenTrack*)
   {
      return GenerateInitInstanceLocal(static_cast<::GenTrack*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::GenTrack*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TriggerAndSkim(void *p = nullptr);
   static void *newArray_TriggerAndSkim(Long_t size, void *p);
   static void delete_TriggerAndSkim(void *p);
   static void deleteArray_TriggerAndSkim(void *p);
   static void destruct_TriggerAndSkim(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TriggerAndSkim*)
   {
      ::TriggerAndSkim *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TriggerAndSkim >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TriggerAndSkim", ::TriggerAndSkim::Class_Version(), "TriggerAndSkim.h", 20,
                  typeid(::TriggerAndSkim), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TriggerAndSkim::Dictionary, isa_proxy, 4,
                  sizeof(::TriggerAndSkim) );
      instance.SetNew(&new_TriggerAndSkim);
      instance.SetNewArray(&newArray_TriggerAndSkim);
      instance.SetDelete(&delete_TriggerAndSkim);
      instance.SetDeleteArray(&deleteArray_TriggerAndSkim);
      instance.SetDestructor(&destruct_TriggerAndSkim);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TriggerAndSkim*)
   {
      return GenerateInitInstanceLocal(static_cast<::TriggerAndSkim*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TriggerAndSkim*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Event(void *p = nullptr);
   static void *newArray_Event(Long_t size, void *p);
   static void delete_Event(void *p);
   static void deleteArray_Event(void *p);
   static void destruct_Event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Event*)
   {
      ::Event *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Event >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Event", ::Event::Class_Version(), "Event.h", 21,
                  typeid(::Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Event::Dictionary, isa_proxy, 4,
                  sizeof(::Event) );
      instance.SetNew(&new_Event);
      instance.SetNewArray(&newArray_Event);
      instance.SetDelete(&delete_Event);
      instance.SetDeleteArray(&deleteArray_Event);
      instance.SetDestructor(&destruct_Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Event*)
   {
      return GenerateInitInstanceLocal(static_cast<::Event*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Event*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_JetESRAnalysis(void *p = nullptr);
   static void *newArray_JetESRAnalysis(Long_t size, void *p);
   static void delete_JetESRAnalysis(void *p);
   static void deleteArray_JetESRAnalysis(void *p);
   static void destruct_JetESRAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JetESRAnalysis*)
   {
      ::JetESRAnalysis *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JetESRAnalysis >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("JetESRAnalysis", ::JetESRAnalysis::Class_Version(), "JetESRAnalysis.h", 27,
                  typeid(::JetESRAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JetESRAnalysis::Dictionary, isa_proxy, 4,
                  sizeof(::JetESRAnalysis) );
      instance.SetNew(&new_JetESRAnalysis);
      instance.SetNewArray(&newArray_JetESRAnalysis);
      instance.SetDelete(&delete_JetESRAnalysis);
      instance.SetDeleteArray(&deleteArray_JetESRAnalysis);
      instance.SetDestructor(&destruct_JetESRAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JetESRAnalysis*)
   {
      return GenerateInitInstanceLocal(static_cast<::JetESRAnalysis*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::JetESRAnalysis*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_BaseReader(void *p);
   static void deleteArray_BaseReader(void *p);
   static void destruct_BaseReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BaseReader*)
   {
      ::BaseReader *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BaseReader >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("BaseReader", ::BaseReader::Class_Version(), "BaseReader.h", 26,
                  typeid(::BaseReader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BaseReader::Dictionary, isa_proxy, 4,
                  sizeof(::BaseReader) );
      instance.SetDelete(&delete_BaseReader);
      instance.SetDeleteArray(&deleteArray_BaseReader);
      instance.SetDestructor(&destruct_BaseReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BaseReader*)
   {
      return GenerateInitInstanceLocal(static_cast<::BaseReader*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BaseReader*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventCut(void *p = nullptr);
   static void *newArray_EventCut(Long_t size, void *p);
   static void delete_EventCut(void *p);
   static void deleteArray_EventCut(void *p);
   static void destruct_EventCut(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventCut*)
   {
      ::EventCut *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventCut >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("EventCut", ::EventCut::Class_Version(), "EventCut.h", 25,
                  typeid(::EventCut), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventCut::Dictionary, isa_proxy, 4,
                  sizeof(::EventCut) );
      instance.SetNew(&new_EventCut);
      instance.SetNewArray(&newArray_EventCut);
      instance.SetDelete(&delete_EventCut);
      instance.SetDeleteArray(&deleteArray_EventCut);
      instance.SetDestructor(&destruct_EventCut);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventCut*)
   {
      return GenerateInitInstanceLocal(static_cast<::EventCut*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::EventCut*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_JetCut(void *p = nullptr);
   static void *newArray_JetCut(Long_t size, void *p);
   static void delete_JetCut(void *p);
   static void deleteArray_JetCut(void *p);
   static void destruct_JetCut(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JetCut*)
   {
      ::JetCut *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JetCut >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("JetCut", ::JetCut::Class_Version(), "JetCut.h", 26,
                  typeid(::JetCut), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JetCut::Dictionary, isa_proxy, 4,
                  sizeof(::JetCut) );
      instance.SetNew(&new_JetCut);
      instance.SetNewArray(&newArray_JetCut);
      instance.SetDelete(&delete_JetCut);
      instance.SetDeleteArray(&deleteArray_JetCut);
      instance.SetDestructor(&destruct_JetCut);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JetCut*)
   {
      return GenerateInitInstanceLocal(static_cast<::JetCut*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::JetCut*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SingleJetCorrector(void *p = nullptr);
   static void *newArray_SingleJetCorrector(Long_t size, void *p);
   static void delete_SingleJetCorrector(void *p);
   static void deleteArray_SingleJetCorrector(void *p);
   static void destruct_SingleJetCorrector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SingleJetCorrector*)
   {
      ::SingleJetCorrector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SingleJetCorrector >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SingleJetCorrector", ::SingleJetCorrector::Class_Version(), "JetCorrector.h", 38,
                  typeid(::SingleJetCorrector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SingleJetCorrector::Dictionary, isa_proxy, 4,
                  sizeof(::SingleJetCorrector) );
      instance.SetNew(&new_SingleJetCorrector);
      instance.SetNewArray(&newArray_SingleJetCorrector);
      instance.SetDelete(&delete_SingleJetCorrector);
      instance.SetDeleteArray(&deleteArray_SingleJetCorrector);
      instance.SetDestructor(&destruct_SingleJetCorrector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SingleJetCorrector*)
   {
      return GenerateInitInstanceLocal(static_cast<::SingleJetCorrector*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SingleJetCorrector*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_JetCorrector(void *p = nullptr);
   static void *newArray_JetCorrector(Long_t size, void *p);
   static void delete_JetCorrector(void *p);
   static void deleteArray_JetCorrector(void *p);
   static void destruct_JetCorrector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JetCorrector*)
   {
      ::JetCorrector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JetCorrector >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("JetCorrector", ::JetCorrector::Class_Version(), "JetCorrector.h", 80,
                  typeid(::JetCorrector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JetCorrector::Dictionary, isa_proxy, 4,
                  sizeof(::JetCorrector) );
      instance.SetNew(&new_JetCorrector);
      instance.SetNewArray(&newArray_JetCorrector);
      instance.SetDelete(&delete_JetCorrector);
      instance.SetDeleteArray(&deleteArray_JetCorrector);
      instance.SetDestructor(&destruct_JetCorrector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JetCorrector*)
   {
      return GenerateInitInstanceLocal(static_cast<::JetCorrector*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::JetCorrector*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_JetUncertainty(void *p = nullptr);
   static void *newArray_JetUncertainty(Long_t size, void *p);
   static void delete_JetUncertainty(void *p);
   static void deleteArray_JetUncertainty(void *p);
   static void destruct_JetUncertainty(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JetUncertainty*)
   {
      ::JetUncertainty *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JetUncertainty >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("JetUncertainty", ::JetUncertainty::Class_Version(), "JetUncertainty.h", 36,
                  typeid(::JetUncertainty), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JetUncertainty::Dictionary, isa_proxy, 4,
                  sizeof(::JetUncertainty) );
      instance.SetNew(&new_JetUncertainty);
      instance.SetNewArray(&newArray_JetUncertainty);
      instance.SetDelete(&delete_JetUncertainty);
      instance.SetDeleteArray(&deleteArray_JetUncertainty);
      instance.SetDestructor(&destruct_JetUncertainty);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JetUncertainty*)
   {
      return GenerateInitInstanceLocal(static_cast<::JetUncertainty*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::JetUncertainty*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ForestAODReader(void *p = nullptr);
   static void *newArray_ForestAODReader(Long_t size, void *p);
   static void delete_ForestAODReader(void *p);
   static void deleteArray_ForestAODReader(void *p);
   static void destruct_ForestAODReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ForestAODReader*)
   {
      ::ForestAODReader *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ForestAODReader >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("ForestAODReader", ::ForestAODReader::Class_Version(), "ForestAODReader.h", 32,
                  typeid(::ForestAODReader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ForestAODReader::Dictionary, isa_proxy, 4,
                  sizeof(::ForestAODReader) );
      instance.SetNew(&new_ForestAODReader);
      instance.SetNewArray(&newArray_ForestAODReader);
      instance.SetDelete(&delete_ForestAODReader);
      instance.SetDeleteArray(&deleteArray_ForestAODReader);
      instance.SetDestructor(&destruct_ForestAODReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ForestAODReader*)
   {
      return GenerateInitInstanceLocal(static_cast<::ForestAODReader*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::ForestAODReader*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ForestminiAODReader(void *p = nullptr);
   static void *newArray_ForestminiAODReader(Long_t size, void *p);
   static void delete_ForestminiAODReader(void *p);
   static void deleteArray_ForestminiAODReader(void *p);
   static void destruct_ForestminiAODReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ForestminiAODReader*)
   {
      ::ForestminiAODReader *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ForestminiAODReader >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("ForestminiAODReader", ::ForestminiAODReader::Class_Version(), "ForestminiAODReader.h", 32,
                  typeid(::ForestminiAODReader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ForestminiAODReader::Dictionary, isa_proxy, 4,
                  sizeof(::ForestminiAODReader) );
      instance.SetNew(&new_ForestminiAODReader);
      instance.SetNewArray(&newArray_ForestminiAODReader);
      instance.SetDelete(&delete_ForestminiAODReader);
      instance.SetDeleteArray(&deleteArray_ForestminiAODReader);
      instance.SetDestructor(&destruct_ForestminiAODReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ForestminiAODReader*)
   {
      return GenerateInitInstanceLocal(static_cast<::ForestminiAODReader*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::ForestminiAODReader*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Manager(void *p = nullptr);
   static void *newArray_Manager(Long_t size, void *p);
   static void delete_Manager(void *p);
   static void deleteArray_Manager(void *p);
   static void destruct_Manager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Manager*)
   {
      ::Manager *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Manager >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Manager", ::Manager::Class_Version(), "Manager.h", 25,
                  typeid(::Manager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Manager::Dictionary, isa_proxy, 4,
                  sizeof(::Manager) );
      instance.SetNew(&new_Manager);
      instance.SetNewArray(&newArray_Manager);
      instance.SetDelete(&delete_Manager);
      instance.SetDeleteArray(&deleteArray_Manager);
      instance.SetDestructor(&destruct_Manager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Manager*)
   {
      return GenerateInitInstanceLocal(static_cast<::Manager*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Manager*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr BaseAnalysis::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BaseAnalysis::Class_Name()
{
   return "BaseAnalysis";
}

//______________________________________________________________________________
const char *BaseAnalysis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseAnalysis*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BaseAnalysis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseAnalysis*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BaseAnalysis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseAnalysis*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BaseAnalysis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseAnalysis*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BaseHistoManager::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BaseHistoManager::Class_Name()
{
   return "BaseHistoManager";
}

//______________________________________________________________________________
const char *BaseHistoManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseHistoManager*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BaseHistoManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseHistoManager*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BaseHistoManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseHistoManager*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BaseHistoManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseHistoManager*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HistoManagerJetESR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *HistoManagerJetESR::Class_Name()
{
   return "HistoManagerJetESR";
}

//______________________________________________________________________________
const char *HistoManagerJetESR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistoManagerJetESR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int HistoManagerJetESR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistoManagerJetESR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HistoManagerJetESR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistoManagerJetESR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HistoManagerJetESR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistoManagerJetESR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BaseJet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BaseJet::Class_Name()
{
   return "BaseJet";
}

//______________________________________________________________________________
const char *BaseJet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseJet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BaseJet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseJet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BaseJet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseJet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BaseJet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseJet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RecoJet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RecoJet::Class_Name()
{
   return "RecoJet";
}

//______________________________________________________________________________
const char *RecoJet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RecoJet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RecoJet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RecoJet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RecoJet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RecoJet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RecoJet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RecoJet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr GenJet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *GenJet::Class_Name()
{
   return "GenJet";
}

//______________________________________________________________________________
const char *GenJet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GenJet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int GenJet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GenJet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GenJet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GenJet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GenJet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GenJet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BaseTrack::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BaseTrack::Class_Name()
{
   return "BaseTrack";
}

//______________________________________________________________________________
const char *BaseTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseTrack*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BaseTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseTrack*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BaseTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseTrack*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BaseTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseTrack*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Track::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Track::Class_Name()
{
   return "Track";
}

//______________________________________________________________________________
const char *Track::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Track*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Track::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Track*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Track::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Track*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Track::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Track*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr GenTrack::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *GenTrack::Class_Name()
{
   return "GenTrack";
}

//______________________________________________________________________________
const char *GenTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GenTrack*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int GenTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GenTrack*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GenTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GenTrack*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GenTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GenTrack*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TriggerAndSkim::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TriggerAndSkim::Class_Name()
{
   return "TriggerAndSkim";
}

//______________________________________________________________________________
const char *TriggerAndSkim::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TriggerAndSkim*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TriggerAndSkim::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TriggerAndSkim*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TriggerAndSkim::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TriggerAndSkim*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TriggerAndSkim::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TriggerAndSkim*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Event::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Event::Class_Name()
{
   return "Event";
}

//______________________________________________________________________________
const char *Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Event*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Event*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Event*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Event*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr JetESRAnalysis::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *JetESRAnalysis::Class_Name()
{
   return "JetESRAnalysis";
}

//______________________________________________________________________________
const char *JetESRAnalysis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetESRAnalysis*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int JetESRAnalysis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetESRAnalysis*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *JetESRAnalysis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetESRAnalysis*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *JetESRAnalysis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetESRAnalysis*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BaseReader::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BaseReader::Class_Name()
{
   return "BaseReader";
}

//______________________________________________________________________________
const char *BaseReader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseReader*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BaseReader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseReader*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BaseReader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseReader*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BaseReader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseReader*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventCut::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *EventCut::Class_Name()
{
   return "EventCut";
}

//______________________________________________________________________________
const char *EventCut::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventCut*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int EventCut::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventCut*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventCut::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventCut*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventCut::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventCut*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr JetCut::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *JetCut::Class_Name()
{
   return "JetCut";
}

//______________________________________________________________________________
const char *JetCut::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetCut*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int JetCut::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetCut*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *JetCut::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetCut*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *JetCut::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetCut*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SingleJetCorrector::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SingleJetCorrector::Class_Name()
{
   return "SingleJetCorrector";
}

//______________________________________________________________________________
const char *SingleJetCorrector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SingleJetCorrector*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SingleJetCorrector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SingleJetCorrector*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SingleJetCorrector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SingleJetCorrector*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SingleJetCorrector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SingleJetCorrector*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr JetCorrector::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *JetCorrector::Class_Name()
{
   return "JetCorrector";
}

//______________________________________________________________________________
const char *JetCorrector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetCorrector*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int JetCorrector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetCorrector*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *JetCorrector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetCorrector*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *JetCorrector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetCorrector*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr JetUncertainty::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *JetUncertainty::Class_Name()
{
   return "JetUncertainty";
}

//______________________________________________________________________________
const char *JetUncertainty::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetUncertainty*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int JetUncertainty::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JetUncertainty*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *JetUncertainty::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetUncertainty*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *JetUncertainty::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JetUncertainty*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ForestAODReader::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *ForestAODReader::Class_Name()
{
   return "ForestAODReader";
}

//______________________________________________________________________________
const char *ForestAODReader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ForestAODReader*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int ForestAODReader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ForestAODReader*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ForestAODReader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ForestAODReader*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ForestAODReader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ForestAODReader*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ForestminiAODReader::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *ForestminiAODReader::Class_Name()
{
   return "ForestminiAODReader";
}

//______________________________________________________________________________
const char *ForestminiAODReader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ForestminiAODReader*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int ForestminiAODReader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ForestminiAODReader*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ForestminiAODReader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ForestminiAODReader*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ForestminiAODReader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ForestminiAODReader*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Manager::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Manager::Class_Name()
{
   return "Manager";
}

//______________________________________________________________________________
const char *Manager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Manager*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Manager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Manager*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Manager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Manager*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Manager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Manager*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void BaseAnalysis::Streamer(TBuffer &R__b)
{
   // Stream an object of class BaseAnalysis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BaseAnalysis::Class(),this);
   } else {
      R__b.WriteClassBuffer(BaseAnalysis::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_BaseAnalysis(void *p) {
      delete (static_cast<::BaseAnalysis*>(p));
   }
   static void deleteArray_BaseAnalysis(void *p) {
      delete [] (static_cast<::BaseAnalysis*>(p));
   }
   static void destruct_BaseAnalysis(void *p) {
      typedef ::BaseAnalysis current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BaseAnalysis

//______________________________________________________________________________
void BaseHistoManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class BaseHistoManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BaseHistoManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(BaseHistoManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BaseHistoManager(void *p) {
      return  p ? new(p) ::BaseHistoManager : new ::BaseHistoManager;
   }
   static void *newArray_BaseHistoManager(Long_t nElements, void *p) {
      return p ? new(p) ::BaseHistoManager[nElements] : new ::BaseHistoManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_BaseHistoManager(void *p) {
      delete (static_cast<::BaseHistoManager*>(p));
   }
   static void deleteArray_BaseHistoManager(void *p) {
      delete [] (static_cast<::BaseHistoManager*>(p));
   }
   static void destruct_BaseHistoManager(void *p) {
      typedef ::BaseHistoManager current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BaseHistoManager

//______________________________________________________________________________
void HistoManagerJetESR::Streamer(TBuffer &R__b)
{
   // Stream an object of class HistoManagerJetESR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HistoManagerJetESR::Class(),this);
   } else {
      R__b.WriteClassBuffer(HistoManagerJetESR::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HistoManagerJetESR(void *p) {
      return  p ? new(p) ::HistoManagerJetESR : new ::HistoManagerJetESR;
   }
   static void *newArray_HistoManagerJetESR(Long_t nElements, void *p) {
      return p ? new(p) ::HistoManagerJetESR[nElements] : new ::HistoManagerJetESR[nElements];
   }
   // Wrapper around operator delete
   static void delete_HistoManagerJetESR(void *p) {
      delete (static_cast<::HistoManagerJetESR*>(p));
   }
   static void deleteArray_HistoManagerJetESR(void *p) {
      delete [] (static_cast<::HistoManagerJetESR*>(p));
   }
   static void destruct_HistoManagerJetESR(void *p) {
      typedef ::HistoManagerJetESR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::HistoManagerJetESR

//______________________________________________________________________________
void BaseJet::Streamer(TBuffer &R__b)
{
   // Stream an object of class BaseJet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BaseJet::Class(),this);
   } else {
      R__b.WriteClassBuffer(BaseJet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BaseJet(void *p) {
      return  p ? new(p) ::BaseJet : new ::BaseJet;
   }
   static void *newArray_BaseJet(Long_t nElements, void *p) {
      return p ? new(p) ::BaseJet[nElements] : new ::BaseJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_BaseJet(void *p) {
      delete (static_cast<::BaseJet*>(p));
   }
   static void deleteArray_BaseJet(void *p) {
      delete [] (static_cast<::BaseJet*>(p));
   }
   static void destruct_BaseJet(void *p) {
      typedef ::BaseJet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BaseJet

//______________________________________________________________________________
void RecoJet::Streamer(TBuffer &R__b)
{
   // Stream an object of class RecoJet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RecoJet::Class(),this);
   } else {
      R__b.WriteClassBuffer(RecoJet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RecoJet(void *p) {
      return  p ? new(p) ::RecoJet : new ::RecoJet;
   }
   static void *newArray_RecoJet(Long_t nElements, void *p) {
      return p ? new(p) ::RecoJet[nElements] : new ::RecoJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_RecoJet(void *p) {
      delete (static_cast<::RecoJet*>(p));
   }
   static void deleteArray_RecoJet(void *p) {
      delete [] (static_cast<::RecoJet*>(p));
   }
   static void destruct_RecoJet(void *p) {
      typedef ::RecoJet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RecoJet

//______________________________________________________________________________
void GenJet::Streamer(TBuffer &R__b)
{
   // Stream an object of class GenJet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GenJet::Class(),this);
   } else {
      R__b.WriteClassBuffer(GenJet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenJet(void *p) {
      return  p ? new(p) ::GenJet : new ::GenJet;
   }
   static void *newArray_GenJet(Long_t nElements, void *p) {
      return p ? new(p) ::GenJet[nElements] : new ::GenJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenJet(void *p) {
      delete (static_cast<::GenJet*>(p));
   }
   static void deleteArray_GenJet(void *p) {
      delete [] (static_cast<::GenJet*>(p));
   }
   static void destruct_GenJet(void *p) {
      typedef ::GenJet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::GenJet

//______________________________________________________________________________
void BaseTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class BaseTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BaseTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(BaseTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BaseTrack(void *p) {
      return  p ? new(p) ::BaseTrack : new ::BaseTrack;
   }
   static void *newArray_BaseTrack(Long_t nElements, void *p) {
      return p ? new(p) ::BaseTrack[nElements] : new ::BaseTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_BaseTrack(void *p) {
      delete (static_cast<::BaseTrack*>(p));
   }
   static void deleteArray_BaseTrack(void *p) {
      delete [] (static_cast<::BaseTrack*>(p));
   }
   static void destruct_BaseTrack(void *p) {
      typedef ::BaseTrack current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BaseTrack

//______________________________________________________________________________
void Track::Streamer(TBuffer &R__b)
{
   // Stream an object of class Track.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Track::Class(),this);
   } else {
      R__b.WriteClassBuffer(Track::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Track(void *p) {
      return  p ? new(p) ::Track : new ::Track;
   }
   static void *newArray_Track(Long_t nElements, void *p) {
      return p ? new(p) ::Track[nElements] : new ::Track[nElements];
   }
   // Wrapper around operator delete
   static void delete_Track(void *p) {
      delete (static_cast<::Track*>(p));
   }
   static void deleteArray_Track(void *p) {
      delete [] (static_cast<::Track*>(p));
   }
   static void destruct_Track(void *p) {
      typedef ::Track current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Track

//______________________________________________________________________________
void GenTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class GenTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GenTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(GenTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GenTrack(void *p) {
      return  p ? new(p) ::GenTrack : new ::GenTrack;
   }
   static void *newArray_GenTrack(Long_t nElements, void *p) {
      return p ? new(p) ::GenTrack[nElements] : new ::GenTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_GenTrack(void *p) {
      delete (static_cast<::GenTrack*>(p));
   }
   static void deleteArray_GenTrack(void *p) {
      delete [] (static_cast<::GenTrack*>(p));
   }
   static void destruct_GenTrack(void *p) {
      typedef ::GenTrack current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::GenTrack

//______________________________________________________________________________
void TriggerAndSkim::Streamer(TBuffer &R__b)
{
   // Stream an object of class TriggerAndSkim.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TriggerAndSkim::Class(),this);
   } else {
      R__b.WriteClassBuffer(TriggerAndSkim::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TriggerAndSkim(void *p) {
      return  p ? new(p) ::TriggerAndSkim : new ::TriggerAndSkim;
   }
   static void *newArray_TriggerAndSkim(Long_t nElements, void *p) {
      return p ? new(p) ::TriggerAndSkim[nElements] : new ::TriggerAndSkim[nElements];
   }
   // Wrapper around operator delete
   static void delete_TriggerAndSkim(void *p) {
      delete (static_cast<::TriggerAndSkim*>(p));
   }
   static void deleteArray_TriggerAndSkim(void *p) {
      delete [] (static_cast<::TriggerAndSkim*>(p));
   }
   static void destruct_TriggerAndSkim(void *p) {
      typedef ::TriggerAndSkim current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TriggerAndSkim

//______________________________________________________________________________
void Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class Event.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Event::Class(),this);
   } else {
      R__b.WriteClassBuffer(Event::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Event(void *p) {
      return  p ? new(p) ::Event : new ::Event;
   }
   static void *newArray_Event(Long_t nElements, void *p) {
      return p ? new(p) ::Event[nElements] : new ::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_Event(void *p) {
      delete (static_cast<::Event*>(p));
   }
   static void deleteArray_Event(void *p) {
      delete [] (static_cast<::Event*>(p));
   }
   static void destruct_Event(void *p) {
      typedef ::Event current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Event

//______________________________________________________________________________
void JetESRAnalysis::Streamer(TBuffer &R__b)
{
   // Stream an object of class JetESRAnalysis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JetESRAnalysis::Class(),this);
   } else {
      R__b.WriteClassBuffer(JetESRAnalysis::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_JetESRAnalysis(void *p) {
      return  p ? new(p) ::JetESRAnalysis : new ::JetESRAnalysis;
   }
   static void *newArray_JetESRAnalysis(Long_t nElements, void *p) {
      return p ? new(p) ::JetESRAnalysis[nElements] : new ::JetESRAnalysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_JetESRAnalysis(void *p) {
      delete (static_cast<::JetESRAnalysis*>(p));
   }
   static void deleteArray_JetESRAnalysis(void *p) {
      delete [] (static_cast<::JetESRAnalysis*>(p));
   }
   static void destruct_JetESRAnalysis(void *p) {
      typedef ::JetESRAnalysis current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::JetESRAnalysis

//______________________________________________________________________________
void BaseReader::Streamer(TBuffer &R__b)
{
   // Stream an object of class BaseReader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BaseReader::Class(),this);
   } else {
      R__b.WriteClassBuffer(BaseReader::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_BaseReader(void *p) {
      delete (static_cast<::BaseReader*>(p));
   }
   static void deleteArray_BaseReader(void *p) {
      delete [] (static_cast<::BaseReader*>(p));
   }
   static void destruct_BaseReader(void *p) {
      typedef ::BaseReader current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BaseReader

//______________________________________________________________________________
void EventCut::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventCut.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventCut::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventCut::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventCut(void *p) {
      return  p ? new(p) ::EventCut : new ::EventCut;
   }
   static void *newArray_EventCut(Long_t nElements, void *p) {
      return p ? new(p) ::EventCut[nElements] : new ::EventCut[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventCut(void *p) {
      delete (static_cast<::EventCut*>(p));
   }
   static void deleteArray_EventCut(void *p) {
      delete [] (static_cast<::EventCut*>(p));
   }
   static void destruct_EventCut(void *p) {
      typedef ::EventCut current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::EventCut

//______________________________________________________________________________
void JetCut::Streamer(TBuffer &R__b)
{
   // Stream an object of class JetCut.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JetCut::Class(),this);
   } else {
      R__b.WriteClassBuffer(JetCut::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_JetCut(void *p) {
      return  p ? new(p) ::JetCut : new ::JetCut;
   }
   static void *newArray_JetCut(Long_t nElements, void *p) {
      return p ? new(p) ::JetCut[nElements] : new ::JetCut[nElements];
   }
   // Wrapper around operator delete
   static void delete_JetCut(void *p) {
      delete (static_cast<::JetCut*>(p));
   }
   static void deleteArray_JetCut(void *p) {
      delete [] (static_cast<::JetCut*>(p));
   }
   static void destruct_JetCut(void *p) {
      typedef ::JetCut current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::JetCut

//______________________________________________________________________________
void SingleJetCorrector::Streamer(TBuffer &R__b)
{
   // Stream an object of class SingleJetCorrector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SingleJetCorrector::Class(),this);
   } else {
      R__b.WriteClassBuffer(SingleJetCorrector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SingleJetCorrector(void *p) {
      return  p ? new(p) ::SingleJetCorrector : new ::SingleJetCorrector;
   }
   static void *newArray_SingleJetCorrector(Long_t nElements, void *p) {
      return p ? new(p) ::SingleJetCorrector[nElements] : new ::SingleJetCorrector[nElements];
   }
   // Wrapper around operator delete
   static void delete_SingleJetCorrector(void *p) {
      delete (static_cast<::SingleJetCorrector*>(p));
   }
   static void deleteArray_SingleJetCorrector(void *p) {
      delete [] (static_cast<::SingleJetCorrector*>(p));
   }
   static void destruct_SingleJetCorrector(void *p) {
      typedef ::SingleJetCorrector current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SingleJetCorrector

//______________________________________________________________________________
void JetCorrector::Streamer(TBuffer &R__b)
{
   // Stream an object of class JetCorrector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JetCorrector::Class(),this);
   } else {
      R__b.WriteClassBuffer(JetCorrector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_JetCorrector(void *p) {
      return  p ? new(p) ::JetCorrector : new ::JetCorrector;
   }
   static void *newArray_JetCorrector(Long_t nElements, void *p) {
      return p ? new(p) ::JetCorrector[nElements] : new ::JetCorrector[nElements];
   }
   // Wrapper around operator delete
   static void delete_JetCorrector(void *p) {
      delete (static_cast<::JetCorrector*>(p));
   }
   static void deleteArray_JetCorrector(void *p) {
      delete [] (static_cast<::JetCorrector*>(p));
   }
   static void destruct_JetCorrector(void *p) {
      typedef ::JetCorrector current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::JetCorrector

//______________________________________________________________________________
void JetUncertainty::Streamer(TBuffer &R__b)
{
   // Stream an object of class JetUncertainty.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JetUncertainty::Class(),this);
   } else {
      R__b.WriteClassBuffer(JetUncertainty::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_JetUncertainty(void *p) {
      return  p ? new(p) ::JetUncertainty : new ::JetUncertainty;
   }
   static void *newArray_JetUncertainty(Long_t nElements, void *p) {
      return p ? new(p) ::JetUncertainty[nElements] : new ::JetUncertainty[nElements];
   }
   // Wrapper around operator delete
   static void delete_JetUncertainty(void *p) {
      delete (static_cast<::JetUncertainty*>(p));
   }
   static void deleteArray_JetUncertainty(void *p) {
      delete [] (static_cast<::JetUncertainty*>(p));
   }
   static void destruct_JetUncertainty(void *p) {
      typedef ::JetUncertainty current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::JetUncertainty

//______________________________________________________________________________
void ForestAODReader::Streamer(TBuffer &R__b)
{
   // Stream an object of class ForestAODReader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ForestAODReader::Class(),this);
   } else {
      R__b.WriteClassBuffer(ForestAODReader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ForestAODReader(void *p) {
      return  p ? new(p) ::ForestAODReader : new ::ForestAODReader;
   }
   static void *newArray_ForestAODReader(Long_t nElements, void *p) {
      return p ? new(p) ::ForestAODReader[nElements] : new ::ForestAODReader[nElements];
   }
   // Wrapper around operator delete
   static void delete_ForestAODReader(void *p) {
      delete (static_cast<::ForestAODReader*>(p));
   }
   static void deleteArray_ForestAODReader(void *p) {
      delete [] (static_cast<::ForestAODReader*>(p));
   }
   static void destruct_ForestAODReader(void *p) {
      typedef ::ForestAODReader current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::ForestAODReader

//______________________________________________________________________________
void ForestminiAODReader::Streamer(TBuffer &R__b)
{
   // Stream an object of class ForestminiAODReader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ForestminiAODReader::Class(),this);
   } else {
      R__b.WriteClassBuffer(ForestminiAODReader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ForestminiAODReader(void *p) {
      return  p ? new(p) ::ForestminiAODReader : new ::ForestminiAODReader;
   }
   static void *newArray_ForestminiAODReader(Long_t nElements, void *p) {
      return p ? new(p) ::ForestminiAODReader[nElements] : new ::ForestminiAODReader[nElements];
   }
   // Wrapper around operator delete
   static void delete_ForestminiAODReader(void *p) {
      delete (static_cast<::ForestminiAODReader*>(p));
   }
   static void deleteArray_ForestminiAODReader(void *p) {
      delete [] (static_cast<::ForestminiAODReader*>(p));
   }
   static void destruct_ForestminiAODReader(void *p) {
      typedef ::ForestminiAODReader current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::ForestminiAODReader

//______________________________________________________________________________
void Manager::Streamer(TBuffer &R__b)
{
   // Stream an object of class Manager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Manager::Class(),this);
   } else {
      R__b.WriteClassBuffer(Manager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Manager(void *p) {
      return  p ? new(p) ::Manager : new ::Manager;
   }
   static void *newArray_Manager(Long_t nElements, void *p) {
      return p ? new(p) ::Manager[nElements] : new ::Manager[nElements];
   }
   // Wrapper around operator delete
   static void delete_Manager(void *p) {
      delete (static_cast<::Manager*>(p));
   }
   static void deleteArray_Manager(void *p) {
      delete [] (static_cast<::Manager*>(p));
   }
   static void destruct_Manager(void *p) {
      typedef ::Manager current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Manager

namespace ROOT {
   static TClass *vectorlEunsignedsPchargR_Dictionary();
   static void vectorlEunsignedsPchargR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPchargR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPchargR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPchargR(void *p);
   static void deleteArray_vectorlEunsignedsPchargR(void *p);
   static void destruct_vectorlEunsignedsPchargR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned char>*)
   {
      vector<unsigned char> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned char>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned char>", -2, "vector", 428,
                  typeid(vector<unsigned char>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPchargR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned char>) );
      instance.SetNew(&new_vectorlEunsignedsPchargR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPchargR);
      instance.SetDelete(&delete_vectorlEunsignedsPchargR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPchargR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPchargR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned char> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned char>","std::vector<unsigned char, std::allocator<unsigned char> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned char>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPchargR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned char>*>(nullptr))->GetClass();
      vectorlEunsignedsPchargR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPchargR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPchargR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned char> : new vector<unsigned char>;
   }
   static void *newArray_vectorlEunsignedsPchargR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned char>[nElements] : new vector<unsigned char>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPchargR(void *p) {
      delete (static_cast<vector<unsigned char>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPchargR(void *p) {
      delete [] (static_cast<vector<unsigned char>*>(p));
   }
   static void destruct_vectorlEunsignedsPchargR(void *p) {
      typedef vector<unsigned char> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned char>

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = nullptr);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 428,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<string>","std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr))->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete (static_cast<vector<string>*>(p));
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] (static_cast<vector<string>*>(p));
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 428,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr))->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete (static_cast<vector<int>*>(p));
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] (static_cast<vector<int>*>(p));
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = nullptr);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 428,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<float>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<float>*>(nullptr))->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete (static_cast<vector<float>*>(p));
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] (static_cast<vector<float>*>(p));
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEboolgR_Dictionary();
   static void vectorlEboolgR_TClassManip(TClass*);
   static void *new_vectorlEboolgR(void *p = nullptr);
   static void *newArray_vectorlEboolgR(Long_t size, void *p);
   static void delete_vectorlEboolgR(void *p);
   static void deleteArray_vectorlEboolgR(void *p);
   static void destruct_vectorlEboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bool>*)
   {
      vector<bool> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bool>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bool>", -2, "vector", 740,
                  typeid(vector<bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEboolgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<bool>) );
      instance.SetNew(&new_vectorlEboolgR);
      instance.SetNewArray(&newArray_vectorlEboolgR);
      instance.SetDelete(&delete_vectorlEboolgR);
      instance.SetDeleteArray(&deleteArray_vectorlEboolgR);
      instance.SetDestructor(&destruct_vectorlEboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bool> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bool>","std::vector<bool, std::allocator<bool> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bool>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bool>*>(nullptr))->GetClass();
      vectorlEboolgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEboolgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bool> : new vector<bool>;
   }
   static void *newArray_vectorlEboolgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bool>[nElements] : new vector<bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEboolgR(void *p) {
      delete (static_cast<vector<bool>*>(p));
   }
   static void deleteArray_vectorlEboolgR(void *p) {
      delete [] (static_cast<vector<bool>*>(p));
   }
   static void destruct_vectorlEboolgR(void *p) {
      typedef vector<bool> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<bool>

namespace ROOT {
   static TClass *vectorlETrackmUgR_Dictionary();
   static void vectorlETrackmUgR_TClassManip(TClass*);
   static void *new_vectorlETrackmUgR(void *p = nullptr);
   static void *newArray_vectorlETrackmUgR(Long_t size, void *p);
   static void delete_vectorlETrackmUgR(void *p);
   static void deleteArray_vectorlETrackmUgR(void *p);
   static void destruct_vectorlETrackmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Track*>*)
   {
      vector<Track*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Track*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Track*>", -2, "vector", 428,
                  typeid(vector<Track*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETrackmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Track*>) );
      instance.SetNew(&new_vectorlETrackmUgR);
      instance.SetNewArray(&newArray_vectorlETrackmUgR);
      instance.SetDelete(&delete_vectorlETrackmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETrackmUgR);
      instance.SetDestructor(&destruct_vectorlETrackmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Track*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<Track*>","std::vector<Track*, std::allocator<Track*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<Track*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETrackmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<Track*>*>(nullptr))->GetClass();
      vectorlETrackmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETrackmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETrackmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<Track*> : new vector<Track*>;
   }
   static void *newArray_vectorlETrackmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<Track*>[nElements] : new vector<Track*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETrackmUgR(void *p) {
      delete (static_cast<vector<Track*>*>(p));
   }
   static void deleteArray_vectorlETrackmUgR(void *p) {
      delete [] (static_cast<vector<Track*>*>(p));
   }
   static void destruct_vectorlETrackmUgR(void *p) {
      typedef vector<Track*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<Track*>

namespace ROOT {
   static TClass *vectorlERecoJetmUgR_Dictionary();
   static void vectorlERecoJetmUgR_TClassManip(TClass*);
   static void *new_vectorlERecoJetmUgR(void *p = nullptr);
   static void *newArray_vectorlERecoJetmUgR(Long_t size, void *p);
   static void delete_vectorlERecoJetmUgR(void *p);
   static void deleteArray_vectorlERecoJetmUgR(void *p);
   static void destruct_vectorlERecoJetmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<RecoJet*>*)
   {
      vector<RecoJet*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<RecoJet*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<RecoJet*>", -2, "vector", 428,
                  typeid(vector<RecoJet*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlERecoJetmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<RecoJet*>) );
      instance.SetNew(&new_vectorlERecoJetmUgR);
      instance.SetNewArray(&newArray_vectorlERecoJetmUgR);
      instance.SetDelete(&delete_vectorlERecoJetmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlERecoJetmUgR);
      instance.SetDestructor(&destruct_vectorlERecoJetmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<RecoJet*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<RecoJet*>","std::vector<RecoJet*, std::allocator<RecoJet*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<RecoJet*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERecoJetmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<RecoJet*>*>(nullptr))->GetClass();
      vectorlERecoJetmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERecoJetmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERecoJetmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RecoJet*> : new vector<RecoJet*>;
   }
   static void *newArray_vectorlERecoJetmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RecoJet*>[nElements] : new vector<RecoJet*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERecoJetmUgR(void *p) {
      delete (static_cast<vector<RecoJet*>*>(p));
   }
   static void deleteArray_vectorlERecoJetmUgR(void *p) {
      delete [] (static_cast<vector<RecoJet*>*>(p));
   }
   static void destruct_vectorlERecoJetmUgR(void *p) {
      typedef vector<RecoJet*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<RecoJet*>

namespace ROOT {
   static TClass *vectorlEGenTrackmUgR_Dictionary();
   static void vectorlEGenTrackmUgR_TClassManip(TClass*);
   static void *new_vectorlEGenTrackmUgR(void *p = nullptr);
   static void *newArray_vectorlEGenTrackmUgR(Long_t size, void *p);
   static void delete_vectorlEGenTrackmUgR(void *p);
   static void deleteArray_vectorlEGenTrackmUgR(void *p);
   static void destruct_vectorlEGenTrackmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenTrack*>*)
   {
      vector<GenTrack*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenTrack*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenTrack*>", -2, "vector", 428,
                  typeid(vector<GenTrack*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenTrackmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GenTrack*>) );
      instance.SetNew(&new_vectorlEGenTrackmUgR);
      instance.SetNewArray(&newArray_vectorlEGenTrackmUgR);
      instance.SetDelete(&delete_vectorlEGenTrackmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenTrackmUgR);
      instance.SetDestructor(&destruct_vectorlEGenTrackmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenTrack*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<GenTrack*>","std::vector<GenTrack*, std::allocator<GenTrack*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<GenTrack*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenTrackmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<GenTrack*>*>(nullptr))->GetClass();
      vectorlEGenTrackmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenTrackmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenTrackmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<GenTrack*> : new vector<GenTrack*>;
   }
   static void *newArray_vectorlEGenTrackmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<GenTrack*>[nElements] : new vector<GenTrack*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenTrackmUgR(void *p) {
      delete (static_cast<vector<GenTrack*>*>(p));
   }
   static void deleteArray_vectorlEGenTrackmUgR(void *p) {
      delete [] (static_cast<vector<GenTrack*>*>(p));
   }
   static void destruct_vectorlEGenTrackmUgR(void *p) {
      typedef vector<GenTrack*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<GenTrack*>

namespace ROOT {
   static TClass *vectorlEGenJetmUgR_Dictionary();
   static void vectorlEGenJetmUgR_TClassManip(TClass*);
   static void *new_vectorlEGenJetmUgR(void *p = nullptr);
   static void *newArray_vectorlEGenJetmUgR(Long_t size, void *p);
   static void delete_vectorlEGenJetmUgR(void *p);
   static void deleteArray_vectorlEGenJetmUgR(void *p);
   static void destruct_vectorlEGenJetmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GenJet*>*)
   {
      vector<GenJet*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GenJet*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GenJet*>", -2, "vector", 428,
                  typeid(vector<GenJet*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGenJetmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GenJet*>) );
      instance.SetNew(&new_vectorlEGenJetmUgR);
      instance.SetNewArray(&newArray_vectorlEGenJetmUgR);
      instance.SetDelete(&delete_vectorlEGenJetmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGenJetmUgR);
      instance.SetDestructor(&destruct_vectorlEGenJetmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GenJet*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<GenJet*>","std::vector<GenJet*, std::allocator<GenJet*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<GenJet*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGenJetmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<GenJet*>*>(nullptr))->GetClass();
      vectorlEGenJetmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGenJetmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGenJetmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<GenJet*> : new vector<GenJet*>;
   }
   static void *newArray_vectorlEGenJetmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<GenJet*>[nElements] : new vector<GenJet*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGenJetmUgR(void *p) {
      delete (static_cast<vector<GenJet*>*>(p));
   }
   static void deleteArray_vectorlEGenJetmUgR(void *p) {
      delete [] (static_cast<vector<GenJet*>*>(p));
   }
   static void destruct_vectorlEGenJetmUgR(void *p) {
      typedef vector<GenJet*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<GenJet*>

namespace {
  void TriggerDictionaryInitialization_libJetAnalysis_Impl() {
    static const char* headers[] = {
"JetESRAnalysis.h",
"Event.h",
"Track.h",
"GenTrack.h",
"RecoJet.h",
"GenJet.h",
"BaseAnalysis.h",
"BaseReader.h",
"BaseHistoManager.h",
"BaseJet.h",
"BaseTrack.h",
"HistoManagerJetESR.h",
"Collections.h",
"ForestAODReader.h",
"ForestminiAODReader.h",
"JetCorrector.h",
"JetUncertainty.h",
"EventCut.h",
"JetCut.h",
"Manager.h",
"TriggerAndSkim.h",
nullptr
    };
    static const char* includePaths[] = {
"/usr/include",
"/home/abhishek/Analysis/jetAnalysis",
"/usr/include",
"/home/abhishek/Analysis/jetAnalysis/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libJetAnalysis dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$BaseAnalysis.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  BaseAnalysis;
class __attribute__((annotate("$clingAutoload$BaseHistoManager.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  BaseHistoManager;
class __attribute__((annotate("$clingAutoload$HistoManagerJetESR.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  HistoManagerJetESR;
class __attribute__((annotate("$clingAutoload$BaseJet.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  BaseJet;
class __attribute__((annotate("$clingAutoload$RecoJet.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  RecoJet;
class __attribute__((annotate("$clingAutoload$GenJet.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  GenJet;
class __attribute__((annotate("$clingAutoload$BaseTrack.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  BaseTrack;
class __attribute__((annotate("$clingAutoload$Track.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  Track;
class __attribute__((annotate("$clingAutoload$GenTrack.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  GenTrack;
class __attribute__((annotate("$clingAutoload$TriggerAndSkim.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  TriggerAndSkim;
class __attribute__((annotate("$clingAutoload$Event.h")))  __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  Event;
class __attribute__((annotate("$clingAutoload$JetESRAnalysis.h")))  JetESRAnalysis;
class __attribute__((annotate("$clingAutoload$BaseReader.h")))  BaseReader;
class __attribute__((annotate("$clingAutoload$EventCut.h")))  __attribute__((annotate("$clingAutoload$ForestAODReader.h")))  EventCut;
class __attribute__((annotate("$clingAutoload$JetCut.h")))  __attribute__((annotate("$clingAutoload$ForestAODReader.h")))  JetCut;
class __attribute__((annotate("$clingAutoload$JetCorrector.h")))  __attribute__((annotate("$clingAutoload$ForestAODReader.h")))  SingleJetCorrector;
class __attribute__((annotate("$clingAutoload$JetCorrector.h")))  __attribute__((annotate("$clingAutoload$ForestAODReader.h")))  JetCorrector;
class __attribute__((annotate("$clingAutoload$JetUncertainty.h")))  __attribute__((annotate("$clingAutoload$ForestAODReader.h")))  JetUncertainty;
class __attribute__((annotate("$clingAutoload$ForestAODReader.h")))  ForestAODReader;
class __attribute__((annotate("$clingAutoload$ForestminiAODReader.h")))  ForestminiAODReader;
class __attribute__((annotate("$clingAutoload$Manager.h")))  Manager;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libJetAnalysis dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "JetESRAnalysis.h"
#include "Event.h"
#include "Track.h"
#include "GenTrack.h"
#include "RecoJet.h"
#include "GenJet.h"
#include "BaseAnalysis.h"
#include "BaseReader.h"
#include "BaseHistoManager.h"
#include "BaseJet.h"
#include "BaseTrack.h"
#include "HistoManagerJetESR.h"
#include "Collections.h"
#include "ForestAODReader.h"
#include "ForestminiAODReader.h"
#include "JetCorrector.h"
#include "JetUncertainty.h"
#include "EventCut.h"
#include "JetCut.h"
#include "Manager.h"
#include "TriggerAndSkim.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"BaseAnalysis", payloadCode, "@",
"BaseHistoManager", payloadCode, "@",
"BaseJet", payloadCode, "@",
"BaseReader", payloadCode, "@",
"BaseTrack", payloadCode, "@",
"Event", payloadCode, "@",
"EventCut", payloadCode, "@",
"ForestAODReader", payloadCode, "@",
"ForestminiAODReader", payloadCode, "@",
"GenJet", payloadCode, "@",
"GenTrack", payloadCode, "@",
"HistoManagerJetESR", payloadCode, "@",
"JetCorrector", payloadCode, "@",
"JetCut", payloadCode, "@",
"JetESRAnalysis", payloadCode, "@",
"JetUncertainty", payloadCode, "@",
"Manager", payloadCode, "@",
"RecoJet", payloadCode, "@",
"SingleJetCorrector", payloadCode, "@",
"Track", payloadCode, "@",
"TriggerAndSkim", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libJetAnalysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libJetAnalysis_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libJetAnalysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libJetAnalysis() {
  TriggerDictionaryInitialization_libJetAnalysis_Impl();
}
