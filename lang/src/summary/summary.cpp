// summary.cpp : Defines the entry point for the console application.
//
// ��� �������� ��:
//   ��������� � ���������� ������������ ���� ������ �� ����, � ������ ��
//     ������� ������ �������, � �� ����������� ������ ����������.
//
// �������� ��� ����������������� ����� - Json, Yaml, XML, ...

// ������������ � Java ��� Yaml. ������� ����� ����� ��� �����.
/*
class ...
  // ��� �������� �� ������ �������. � �++ �� ���.
  // �������� ��� � ��������, ������� � �������������� ���� ����������
  //   � �����, � �� � ����.
  Object getValueByPath(String path) { some actions; }
}

// �������������� ��� �� �����������...
Map<String> getListEmployers() {
  Map<String> employers = (Map<String>)configurator.getValueByPath("any/thing");
  return employers;
}*/

// ���������� �����������
// http://commons.apache.org/proper/commons-configuration/
// ����� ��������� � �����, ���:
//   - ���� ����� �����
//   - getLong, getString... - ��� � ��������

/*
http://crypto.pp.ua/2010/06/peregruzka-metodov-klassov-java/
"��� ���������� ������ ������� �������������� ��������� ������:

� �� ������������ ������� ��������� ����������;
� �� ������������ ���������� � ���������� ������ ����������; - � � �����������
� �������� ��� ����������� ������������� ������ �� ��������� ������ �������."
*/

// C++
#include <stdexcept>
#include <string>

// ��������� ����������� � ���������, ����� ��� ����� ��� ��� �����
//   �� �� ����, ������������ ������ ������ ���-�� ������.
//
// �� ������ ������ � JsonCpp


// http://ru.wikipedia.org/wiki/%D0%9F%D0%B5%D1%80%D0%B5%D0%B3%D1%80%D1%83%D0%B7%D0%BA%D0%B0_%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BE%D0%B2
//
//@GetOnly or @GetAndSet?
template <typename T>
class Configurator {
  // T - std::string, Json::Value, int, double, map, list, vector...
  //   ���������� ������ ����� ����� ����������.
public:
  //@Trouble: ��������� �������! �� ������������� �������� ������
  // 
  //@Idea: �������������� ��������
  //  � ��� ��������� ��� ������?
  //
  //virtual T GetByPath(std::string path, T* value=NULL) const = 0;  // �� �����
  // 
  //
  //@Idea: �������� ������ ��� �����������
  // �� ������ ��� getter, �� �����������, ���� 
  //   ���� ����� ������ �������������, ��� ������������ �����.
  // �������� �� ������, ��������, � ���� ����������� ������? ��� ����� ��
  //   ������������� - �� ������ ������, ������������� ������� �����. �������� ����...
  // 
  // ��� ������ ��������� ������� �������
  //virtual void GetByPath(const std::string& path, /*mutable*/ T& value) const = 0;  

  // �������� ����� ������� ���������! �.�. �����������, � �������� �� ����� ��������
  //   �� ������?
  //
  virtual void SetByPath(const T/*&*/ value, const std::string& path) = 0;

  // ���������� ���� ������������� ������������
};


//@GetAndSet
//template <typename T>
//class Setting {

//};

/*
class BaseAppConfigurer : 
  public Configurator<std::string>, 
  public Configurator<int> {
public:
  virtual ~BaseAppConfigurer() {}
};*/


// http://www.quizful.net/post/return-type-function-overloading
// ������� ����� ����������� ������ � ����� ����������
// http://habrahabr.ru/post/149287/
// http://otvety.google.ru/otvety/thread?tid=41691fc1e0d27729
//
// ��� ���� � �������������?
class ServiceConfigurer : 
  // �����, ����� ��� ����� ���� - � �������� ����, �������� ����� �������.
  // �� ���� �����������
  //
  // ������ ��������� �������������� ������. ��� ������ �� ������������,
  //   � ������������ � �������� ��������.
  public Configurator<int>, 
  public Configurator<std::string>
{
public:
  // ��� ��� ����� ��������� ���������� ����� ����������
  virtual void SetByPath(const int/*&*/, const std::string& path) { return; }
  virtual void SetByPath(const std::string/*&*/, const std::string& path ) { return; }

  static ServiceConfigurer Build() { return ServiceConfigurer(); }

  // �������� �����!

private:
  // ������ ���� ������������!
  ServiceConfigurer() {}
  //virtual void GetByPath(const int/*&*/) { return; }
  //virtual void GetByPath(const std::string/*&*/ ) { return; }
};

//class WrapperServiceConfigurator : ...
//  int GetSNMPPort() const;
//  int SetSNMPPort


int main(int argc, char* argv[]) {
  ServiceConfigurer configurer = ServiceConfigurer::Build();
  return 0;
}

