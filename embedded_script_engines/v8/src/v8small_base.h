#ifndef SOME_SMALL_DB_TEST
#define SOME_SMALL_DB_TEST
// cpp
#include <string>

// other
#include "v8.h"

// app
//#include "small_base.h"
#include "in-memory-storages/linux_version/sampler.h" 
#include "in-memory-storages/linux_version/abstract_in_memory_storage.h"
using ::tmitter_web_service::InMemoryStorageImpl;
//using ::scenarios::SmallBase;

typedef ::tmitter_web_service::InMemoryStorageImpl SmallBase;
using namespace v8;
namespace scenarios {
class V8SmallBase {
 public:
	V8SmallBase() {}

	static v8::Persistent<v8::ObjectTemplate> var_array_blueprint_;

  v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate);
/*
  static void GetTemp_(v8::Local<v8::String> name,
                 const v8::PropertyCallbackInfo<v8::Value>& info);
  static void SetTemp_(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                 const v8::PropertyCallbackInfo<void>& info); 
*/	
	
	//uchar bcl_TR1[kMaxBCLs]; 
//array ------------------ array --------------------- array ------------------------ array
	static void v8_get_array_bcl_TR1(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();

  // ���������� �����!
	
  InMemoryStorageImpl* database = static_cast<InMemoryStorageImpl*>(ptr);

  // ����� �������� � �������
  // ����� ������� V8Palette ��� ������� ����� �������
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(), 
      var_array_blueprint_);

  Handle<Object> instance = templ->NewInstance();
  Handle<External> point_handle = External::New(database->bcl_TR1);
  instance->SetInternalField(0, point_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

	void v8_get_array_index_bcl_TR1(
    uint32_t index,
		const PropertyCallbackInfo<Value>& info) {  ]
	//InMemoryStorageImpl* database = static_cast<InMemoryStorageImpl*>(ptr);
	int max_size;
	max_size = db_->kMaxBCLs;
	
  if (index < max_size) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* palette = static_cast<int*>(ptr);
    info.GetReturnValue().Set(v8::Number::New(palette[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

	// \array -------------------- \array --------------------- \array ---------
	static void V8Get_idx_oned_etv_(Local<String> name,
								 const PropertyCallbackInfo<Value>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		int value = static_cast<SmallBase*>(ptr)->idx_oned_etv_;
		info.GetReturnValue().Set(Integer::New(value));
	}

	static void V8Set_idx_oned_etv_(Local<String> property, Local<Value> value,
								 const PropertyCallbackInfo<void>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<SmallBase*>(ptr)->idx_oned_etv_ = value->Int32Value();
	}
/*
		static void V8Get_var_char(Local<String> name,
								 const PropertyCallbackInfo<Value>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		unsigned char value = static_cast<SmallBase*>(ptr)->var_char;
		info.GetReturnValue().Set(Integer::New(value));
	}

	static void V8Set_var_char(Local<String> property, Local<Value> value,
								 const PropertyCallbackInfo<void>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<SmallBase*>(ptr)->var_char = value->Int32Value();
	}
*/
	static void V8Get_ibRadioMode_(Local<String> name,
								 const PropertyCallbackInfo<Value>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		unsigned char value = static_cast<SmallBase*>(ptr)->ibRadioMode_;
		info.GetReturnValue().Set(Integer::New(value));
	}

	static void V8Set_ibRadioMode_(Local<String> property, Local<Value> value,
								 const PropertyCallbackInfo<void>& info) {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<SmallBase*>(ptr)->ibRadioMode_ = value->Int32Value();
	}

	
static void v8_get_PABTotal_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->PABTotal_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_PABTotal_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->PABTotal_= value->Int32Value();
}

static void v8_get_total_bcl_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->total_bcl_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_total_bcl_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->total_bcl_= value->Int32Value();
}

static void v8_get_excitersTotal_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->excitersTotal_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_excitersTotal_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->excitersTotal_= value->Int32Value();
}

static void v8_get_DBTotal_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->DBTotal_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_DBTotal_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->DBTotal_= value->Int32Value();
}

static void v8_get_transmitterID___(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->transmitterID___;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_transmitterID___(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->transmitterID___= value->Int32Value();
}

static void v8_get_terminal_amps_per_block___(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->terminal_amps_per_block___;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_terminal_amps_per_block___(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->terminal_amps_per_block___= value->Int32Value();
}

static void v8_get_sizeBlockPreampParams_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->sizeBlockPreampParams_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_sizeBlockPreampParams_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->sizeBlockPreampParams_= value->Int32Value();
}

static void v8_get_sizeBlockTerminalAmpParams_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->sizeBlockTerminalAmpParams_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_sizeBlockTerminalAmpParams_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->sizeBlockTerminalAmpParams_= value->Int32Value();
}

static void v8_get_sizeBlockBCNParams_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->sizeBlockBCNParams_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_sizeBlockBCNParams_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->sizeBlockBCNParams_= value->Int32Value();
}

static void v8_get_sizeBlockDBParams_(Local<String> name,
   const PropertyCallbackInfo<Value>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 int value = static_cast<SmallBase*>(ptr)->sizeBlockDBParams_;
 info.GetReturnValue().Set(Integer::New(value));
}

static void v8_set_sizeBlockDBParams_(Local<String> property, Local<Value> value,
   const PropertyCallbackInfo<void>& info) {
 Local<Object> self = info.Holder();
 Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
 void* ptr = wrap->Value();
 static_cast<SmallBase*>(ptr)->sizeBlockDBParams_= value->Int32Value();
}




 
 private:
	 SmallBase* db_;

};
}


#endif // SOME_SMALL_DB_TEST

