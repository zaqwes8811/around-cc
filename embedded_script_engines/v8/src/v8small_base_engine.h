#ifndef SOME_DB_SMALL_ENGINE
#define SOME_DB_SMALL_ENGINE
// cpp
#include <string>
#include <iostream>

// other
#include "v8.h"
#include "process.h"

// app
#include "v8small_base.h"
#include "in-memory-storages/linux_version/sampler.h" 
#include "in-memory-storages/linux_version/abstract_in_memory_storage.h"

using namespace v8;
using ::tmitter_web_service::InMemoryStorageImpl;
using ::in_memory_storages::InMemoryStorage;
using ::scenarios::V8SmallBase;
using ::std::cout;
using std::endl;
//typedef ::tmitter_web_service::InMemoryStorageImpl SmallBase;
namespace scenarios {



class V8SmallBaseEngine {

 public:
  static V8SmallBaseEngine* CreateForOwn(
      Isolate* isolate, 
      Handle<String> source,
		//	SmallBase* database,
			::tmitter_web_service::InMemoryStorageImpl*,
      V8SmallBase* v8database);  
	bool Process();
 protected:
  V8SmallBaseEngine(
    Isolate* isolate, 
    Handle<String> source,
		::tmitter_web_service::InMemoryStorageImpl* const database,
    V8SmallBase* temp) 
				: isolate_(isolate), source_(source), database_(database), temp_(temp) { }

	bool Initialize();

	void Log(const char* event);
	bool ExecuteScript(Handle<String> script);
	Handle<Object> WrapVar(::tmitter_web_service::InMemoryStorageImpl* obj);
	bool InstallVars(::tmitter_web_service::InMemoryStorageImpl* opts, ::tmitter_web_service::InMemoryStorageImpl* output);	
	Handle<Object> WrapRequest(); 
	Handle<ObjectTemplate> MakeRequestTemplate (Isolate* isolate);

 private:
  Isolate* GetIsolate() { return isolate_; }
  Isolate* isolate_;  // �������� �������� ��������
  Handle<String> source_;
	SmallBase* smdb_;
  
  // "A context is an execution environment that allows separate, 
  // unrelated, JavaScript code to run in a single instance of 
  // V8. You must explicitly specify the context in which you 
  // want any JavaScript code to be run."
  //
  // ��� �������������� ������ �� �����.
  Persistent<Context> context_;
	Persistent<Function> process_;

  // ����� � �� ����� �����
  V8SmallBase* temp_;
	::tmitter_web_service::InMemoryStorageImpl* const database_;

  // Blueprints
  static Persistent<ObjectTemplate> point_template_;
	static Persistent<ObjectTemplate> request_template_;
};

//Persistent<ObjectTemplate> V8SmallBaseEngine::point_template_;

}

#endif // SOME_DB_SMALL_ENGINE