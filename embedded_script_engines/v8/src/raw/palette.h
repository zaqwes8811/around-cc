#pragma once

// Other
#include "v8.h"

// App
#include "point.h"

class Palette {
 public:
  static const int MAX_SIZE = 32;
  Palette() {}
  int array_[MAX_SIZE];
  Point point_;
  Point point_array[MAX_SIZE];
};

using namespace v8;

//@NoThreadSafe
class V8Palette {
public:
  // Args:
  //   ������ ������ ����� � Isolate and Context.
  //   ��� ���-���� �������� ������ ���� ����.
  V8Palette(Isolate* isolate);

  // About:
  //   Getters complex objects.

  // Point Palette::point_;
  // � ������ ������ �� ���� ��������. ����� ������ ����� ���������� Point
  static void GetPointValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info);

  // int Palette::array_[MAX_SIZE]
  // ������������� �����
  static void GetIntArrayValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info);

  // �������� �����
  static void ArrayIndexGetter(
      uint32_t index,
      const PropertyCallbackInfo<Value>& info);
  static void ArrayIndexSetter(
      uint32_t index,
      Local<Value> value,
      const PropertyCallbackInfo<Value>& info) { }

  // Point Palette::point_array[MAX_SIZE];
  // ������������� �����
  static void GetPointsArrayValue(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info);

  /// � ������ ������ �� ���� ��������. ����� ������ ����� ���������� Point
  static void PointArrayIndexGetter(
      uint32_t index,
      const PropertyCallbackInfo<Value>& info);
  static void PointArrayIndexSetter(
      uint32_t index,
      Local<Value> value,
      const PropertyCallbackInfo<Value>& info) {}

  // About:
  //   Make this root object.
  Handle<Object> Forge(Palette* palette);

public:
  // ������ ������ int.
  static v8::Persistent<v8::ObjectTemplate> int_array_blueprint_;

  // ������ �����.
  static v8::Persistent<v8::ObjectTemplate> point_array_blueprint_;

private:
  // ��� ������
  static Persistent<ObjectTemplate> own_blueprint_;
  Isolate* const isolate_;
  // ���� ����� ������� - ����� ��� ����������.
  v8::Handle<v8::ObjectTemplate> MakeBlueprint();
};
