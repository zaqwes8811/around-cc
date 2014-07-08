// http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
//
// Как понял проблема в том, чтобы можно было залить в контейнер разные типы
// но не пользоватья указателями.
//
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

#include <typeinfo>  // не хотелось бы включать, но похоже нужно

#include <gtest/gtest.h>

using std::ostream;
using std::string;
using std::endl;
using std::cout;
using std::vector;

//using object_t = int;  // step 2

/*
void draw(const int& x, ostream& out, size_t position)  // object_t -> int and move here
{ out << string(position, ' ') << x << endl; }

void draw(const string& x, ostream& out, size_t position)  // object_t -> int and move here
{ out << string(position, ' ') << x << endl; }
*/

/*
// step 3: remove
class object_t {
public:
  object_t(const int& x) : self_(x)
  {}

  friend void draw(const object_t &x, ostream &out, size_t position)
  { draw(x.self_, out, position); }

private:
  int self_;
};*/

/*
class object_t {
public:
  object_t(const int& x) : self_(new int_model_t(x))
  { }

  object_t(const object_t& x) : self_(new int_model_t(*x.self_))
  { }  // если оставить только копирующий констр. компилятор (gcc 4.7) заругается

  object_t& operator=(const object_t& x)
  { object_t tmp(x);
    self_ = std::move(tmp.self_);
    //std::swap(self_, tmp.self_);  // also compiled, but may be not exc. safe
    return *this; }

  friend void draw(const object_t &x, ostream &out, size_t position)
  { x.self_->draw_(out, position); }  // разрешаем доступ к закрытым частям

private:
  struct int_model_t {
    int_model_t(const int& x) : data_(x) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    int data_;
  };
  std::unique_ptr<int_model_t> self_;
};*/

using std::move;
/*
class object_t {
public:
  object_t(const int& x) : self_(new int_model_t(x))
  { cout << "ctor\n";}

  object_t(const object_t& x) : self_(new int_model_t(*x.self_))
  { cout << "copy\n";}  // если оставить только копирующий констр. компилятор (gcc 4.7) заругается

  // Speed up
  object_t(object_t&&) noexcept = default;

  object_t& operator=(const object_t& x)
  { object_t tmp(x);
    *this = std::move(tmp);  // if no move assign progr. is failed
    //std::swap(self_, tmp.self_);  // also compiled, but may be not exc. safe
    return *this; }
  object_t& operator=(object_t&&) noexcept = default;  // Need it!


  friend void draw(const object_t &x, ostream &out, size_t position)
  { x.self_->draw_(out, position); }  // разрешаем доступ к закрытым частям

private:
  struct int_model_t {
    int_model_t(const int& x) : data_(x) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    int data_;
  };
  std::unique_ptr<int_model_t> self_;
};
*/

// "Don't allow polymorphism to complicate client code"
// и все равно много обращений к куче. Но суть думаю в том, что пользователю не нужно
// будет думать об этом.
/*class object_t {
public:
  object_t(const string& x) : self_(new string_model_t(move(x)))
  {}

  object_t(const int& x) : self_(new int_model_t(move(x)))
  { cout << "ctor\n";}

  // Not compiled
  //object_t(const object_t& x) : self_(new int_model_t(*x.self_))
  object_t(const object_t& x) : self_(x.self_->copy_())
  { cout << "copy\n";}  // если оставить только копирующий констр. компилятор (gcc 4.7) заругается

  // Speed up
  object_t(object_t&&) noexcept = default;

  object_t& operator=(const object_t& x)
  { object_t tmp(x);
    *this = std::move(tmp);  // if no move assign progr. is failed
    //std::swap(self_, tmp.self_);  // also compiled, but may be not exc. safe
    return *this; }
  object_t& operator=(object_t&&) noexcept = default;  // Need it!


  friend void draw(const object_t &x, ostream &out, size_t position)
  { x.self_->draw_(out, position); }  // разрешаем доступ к закрытым частям

private:
  struct concept_t {
    virtual ~concept_t() = default;
    virtual concept_t* copy_() const = 0;
    virtual void draw_(ostream& out, size_t position) const = 0;
  };

  struct string_model_t : concept_t {
    string_model_t(const string& x) : data_(move(x)) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    concept_t* copy_() const { return new string_model_t(*this); }

    string data_;
  };

  struct int_model_t : concept_t {
    int_model_t(const int& x) : data_(move(x)) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    concept_t* copy_() const { return new int_model_t(*this); }

    int data_;
  };

  // std::unique_ptr<int_model_t> self_;
  std::unique_ptr<concept_t> self_;
};
*/

template<typename T>
void draw(const T& x, ostream& out, size_t position)  // object_t -> int and move here
{ out << string(position, ' ') << x << endl; }

class object_t {
public:
  object_t(string x) : self_(new string_model_t(move(x)))  // by value
  {}

  object_t(int x) : self_(new int_model_t(move(x)))
  { cout << "ctor\n";}

  // Not compiled
  //object_t(const object_t& x) : self_(new int_model_t(*x.self_))
  object_t(const object_t& x) : self_(x.self_->copy_())
  { cout << "copy\n";}  // если оставить только копирующий констр. компилятор (gcc 4.7) заругается

  // Speed up
  object_t(object_t&&) noexcept = default;

  object_t& operator=(const object_t& x)
  { object_t tmp(x);
    *this = std::move(tmp);  // if no move assign progr. is failed
    //std::swap(self_, tmp.self_);  // also compiled, but may be not exc. safe
    return *this; }
  object_t& operator=(object_t&&) noexcept = default;  // Need it!


  friend void draw(const object_t &x, ostream &out, size_t position)
  { x.self_->draw_(out, position); }  // разрешаем доступ к закрытым частям

private:
  struct concept_t {
    virtual ~concept_t() = default;
    virtual concept_t* copy_() const = 0;
    virtual void draw_(ostream& out, size_t position) const = 0;
  };

  struct string_model_t : concept_t {
    string_model_t(const string& x) : data_(move(x)) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    concept_t* copy_() const { return new string_model_t(*this); }

    string data_;
  };

  struct int_model_t : concept_t {
    int_model_t(const int& x) : data_(move(x)) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    concept_t* copy_() const { return new int_model_t(*this); }

    int data_;
  };

  // std::unique_ptr<int_model_t> self_;
  std::unique_ptr<concept_t> self_;
};

using document_t = vector<object_t>;  // полиморфизм только через shared_ptrs

void draw(const document_t&x, ostream &out, size_t position)
{
  out << string(position, ' ') << "<document>" << endl;
  for (const auto& e : x) draw(e, out, position + 2);
  out << string(position, ' ') << "</document>" << endl;
}

TEST(EvelC11, App) {
  // TODO:
  document_t document;
  document.reserve(5);

  document.emplace_back(0);
  document.emplace_back(string("hello"));
  document.emplace_back(2);
  document.emplace_back(3);

  //std::reverse(document.begin(), document.end());

  draw(document, cout, 0);

  // http://en.cppreference.com/w/cpp/language/typeid
  // RTII cost:
  // http://stackoverflow.com/questions/579887/how-expensive-is-rtti
  assert(typeid(document[0]) == typeid(document[1]));
}

// Other example
// http://www.codeguru.com/cpp/misc/misc/templatizedclasses/article.php/c14955/Polymorphism-and-TemplateBased-Designs.htm


//TODO: boost::any
// http://www.boost.org/doc/libs/1_55_0/doc/html/any.html
// http://stackoverflow.com/questions/9105381/boost-any-get-original-type
// http://sandfly.net.nz/blog/2009/12/the-c-boost-libraries-part-6-boostany/
