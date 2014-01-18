#pragma once 

// Other
#include <v8.h>

// Accessing to dynamic vars.
// Point x y
class Point {
  public:
  Point() : x_(1), y_(2) { }
  Point(int x, int y) : x_(x), y_(y) { }
  int x_;
  int y_;
  //std::vector<int> rgb_;
  
  // cppclean failed here.
  //std::vector<vector<int>> rgb_add_;
};

class V8Point {
public:
  V8Point(v8::Isolate* isolate) : isolate_(isolate) { }

  v8::Handle<v8::Object> Forge(Point* point, v8::Handle<v8::Context> context);

  v8::Handle<v8::ObjectTemplate> MakeBlueprint();

  static void GetPointX(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);

  static void SetPointX(
      v8::Local<v8::String> property, v8::Local<v8::Value> value,
      const v8::PropertyCallbackInfo<void>& info);
  
  static void GetPointY(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info);
  
  static void SetPointY(
      v8::Local<v8::String> property, 
      v8::Local<v8::Value> value,
      const v8::PropertyCallbackInfo<void>& info);

private:
  v8::Isolate* const isolate_;
  static v8::Persistent<v8::ObjectTemplate> own_blueprint_;
};

