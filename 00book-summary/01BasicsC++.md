# Chapter 1. The Basics of C++

* 한 헤더가 여러 번 인클루드되는 것을 막기 위한 두 가지 방법
  * `#include` guard: 전자는 리눅스 커널과 같은 대규모의 C 프로젝트에서 자주 볼 수 있는 방법
    * 리눅스 커널의 경우 #endif /* MYHEADER_H */라고 주석까지 달곤 함
  * 후자는 Visual Studio 등의 코드 템플릿에서 자주 쓰임

```CPP
#ifndef MYHEADER_H
#define MYHEADER_H
// ... the contents of this header file
#endif
```

```CPP
#pragma once
// ... the contents of this header file
```

* `cout`과 같은 이름을 특정 namespace의 것만 쓴다고 지정할 수도 있음

```CPP
using std::cout;
cout << "Hello, World!" << std::endl; // endl이라고만 쓰면 에러가 발생함
```

* C++17에서는 Nested Namespace를 지원하는 방법이 바뀜
  * 전자는 C++17 이후 지원하는 Nested Namespace
  * 후자는 과거 버전부터 지원되는 Nested Namespace

```CPP
namespace MyLib::Net::FTP {
// ...
}
```

```CPP
namespace MyLib {
  namespace Net {
    namespace FTP {
      // ...
    }
  }
}
```

* Nested Namespace의 에일리어스 (alias)를 정의할 수 있음
  * 이름은 정의할 수 없음

```CPP
namespace MyFTP = MyLib::Net::FTP;
```

* Literals
  * 수의 리터럴 사이에 `\``이 들어가면 컴파일 시 무시됨 (C++14부터)
  * `0x3.ABCp-10, 0Xb.cp121`과 같은 16진수 리터럴의 사용도 가능함. 이 때 `p`는 생략할 수 없으며, 2를 의미함 (C++17부터)
  * <https://en.cppreference.com/w/cpp/language/floating_literal>

* Operators (간단한 퀴즈)

```CPP
int someInteger = 256;
short someShort;
long someLong;
float someFloat;
double someDouble;

someInteger++;                                        // 257
someInteger * 2;                                      // 514
someShort = static_cast<short>(someInteger);          // 514
someLong = someShort * 10000;                         // 5140000
someFloat = someLong + 0.785f;                        // 5.14e+06
someDouble = static_cast<double>(someFloat) / 100000; // 51.4
cout << someDouble << endl;                           // 51.4
```

* `enum` 선언 방법
  1. `enum` 타입을 이용하는 법
  2. `enum` 클래스를 이용하는 법 (strongly-typed `enum` class)
  3. `enum` 클래스를 내부적으로 다른 타입 (예: `unsigned long`)으로 바꾸어 선언하는 법

```CPP
enum PieceType {
  PieceTypeKing = 1, // =1을 쓰지 않았으면 0부터 시작함
  PieceTypeQueen,    // 자동적으로 앞에 할당된 수에 1을 더해 2가 할당
  PieceTypeRook = 10,
  PieceTypePawn      // 자동적으로 11이 할당
};

PieceType myPiece;
myPiece = PieceTypeKing; // 1이라고 쓸 수 있지만, 경고나 에러가 발생할 수 있음
```

```CPP
enum class PieceType
{
  King = 1,
  Queen,
  Rook = 10,
  Pawn
};

PieceType piece = PlaceType::King;
```

```CPP
enum class PieceType : unsigned long
{
  King = 1,
  Queen,
  Rook = 10,
  Pawn
};
```

* C++17에서는 `if` 문, `switch` 문 등이 초기화문을 가질 수 있음 (`<initializer>`에 선언된 변수는 해당 문장 내부에서만 유효)
  * `if (<initializer>; <conditional_expression>) { <body> }`
  * `switch (<initializer>; <expression>) { <body> }`

* C++17에서는 `switch`에서의 fallthrough가 의도적임을 알리는 attribute가 있음

```CPP
switch (backgroundColor) {
  case Color::DarkBlue:
    doSomethingForDarkBlue();
    [[fallthrough]];
  case Color::Black:
    // Code is executed for both a dark blue or black background color
    doSomethingForBlackOrDarkBlue();
    break;
  case Color::Red:
  case Color::Green:
    // Code to execute for a red or green background color
    break;
}
```

* 현재 함수 이름

```CPP
int addNumbers(int number1, int number2)
{
  std::cout << "Entering function " << __func__ << std::endl;
  return number1 + number2;
}
```

* 배열 원소 개수 계산
  * 전자는 C++17에서 지원하는 표준 라이브러리 함수임
  * 후자는 `sizeof`가 인자의 크기를 바이트 단위로 알려주는 점에 착안한 코드

```CPP
unsigned int arraySize = std::size(myArray);
unsigned int arraySize = sizeof(myArray) / sizeof(myArray[0]);
```

* C++17에서는 구조화된 바인딩 (structured binding)을 지원함

```CPP
struct Point { double mX, mY, mZ; };
Point point;
point.mX = 1.0; point mY = 2.0; point mZ = 3.0;
auto [x, y, z] = point;
```

* loop에서 `continue`를 쓰면 가독성을 떨어트리므로 피하는 게 좋음

* Range-based `for` Loop
  * 아래 코드는 `arr`을 `i`에 카피해서 출력하는 코드임 (카피하지 않는 방법도 뒤에서 배움)

```CPP
std::array<int, 4> arr = {1, 2, 3, 4};
for (int i : arr) {
  std::cout << i << std::endl;
}
```

* Initializer Lists
  * `int b = makesum({10, 20, 30, 40, 50, 60});
  * `<int>`로 타입을 주었기 때문에 `int c = makeSum({1,2,3.0});`과 같이 `double`을 섞을 수 없음

```CPP
#include <initializer_list>

using namespace std;

int makeSum(initilaizer_list<int> lst)
{
  int total = 0;
  for (int value : lst) {
    total += value;
  }
  return total;
}
```

* 스택과 힙의 비유
  * Figure 1-2에서 함수가 일종의 스택이라는 것을 설명하기 위해 `main()`이라는 종이 위에 `foo()` 종이가 올라가 있고, 그 안에 변수의 이름과 값이 적힌 표가 있다는 것은 꽤나 유용한 비유임
  * `foo()`라는 종이를 다 썼으면 쓰레기통에 버리면 그만이라는 비유라는 측면에도 적합

* 동적 (Heap) 할당
  * C에서 쓰던 `malloc()`과 `free()`는 사용하지 말 것
  * 배열 동적 할당 예제

```CPP
int arraySize = 8;
int* myVariableSizedArray = new int[arraySize];
myVariableSizedArray[3] = 2;
delete[] myVariableSizedArray;   // 배열을 삭제할 때에는 delete[]
myVariabvleSizedArray = nullptr; // C++11부터 도입된 Keyword (C++11 전에는 상수 NULL == 0이 사용됨)
```

* 스마트 포인터
  * 스마트 포인터는 객체가 out of scope (예: 함수가 실행 종료됨)이면 메모리를 자동으로 deallocate함
  * `std::unique_ptr`: 인스턴스 혼자만 주소값을 가지고 있어서, `unique_ptr` 변수가 out of scope되거나 삭제되면 메모리를 비움
  * `std::shared_ptr`: 여러 객체가 공유해서 특정 주소값을 가지고 있어서, 마지막 객체가 파괴되거나 리셋되면 메모리를 비움
  * Note: 예전에는 `auto_ptr`이라는 것도 있었지만 C++17에서 삭제되었으니 잊을 것

* `unique_ptr`, `shared_ptr` 사용법:
  * 전자는 C++14부터 도입된 `std::make_unique<>()`, `std::make_shared<>()`를 이용하는 방법 (교재 추천)
  * 후자는 C++14이전부터 쓰던 방법 (일관성 면에서는 후자가 낫긴 함)

```CPP
#include <memory>

// Employee 인스턴스를 위한 공간을 하나 잡아 스마트 포인터를 리턴
auto anEmployee = make_unique<Employee>();
auto anEmployee = make_shared<Employee>();

unique_ptr<Employee> anEmployee(new Employee);
shared_ptr<Employee> anEmployee(new Employee);
```

* `unique_ptr` 배열

```CPP
auto employees = make_unique<Employee[]>(10);
unique_ptr<Employee[]> employees(new Employee[10]); // 위의 예제를 참고로 임의로 만든 것
```

* `shared_ptr` 배열
  * `make_shared<>()`는 배열을 저장하는 포인터를 만들 수 없음에 주의할 것

```CPP
auto employees = make_shared<Employee[]>(10); // C++17에서도 이를 지원하지 않음
shared_ptr<Employee[]> employees(new Employee[10]);
```

* C++에서 `const`의 미묘함은 인터뷰 질문으로 적절함
  * 단순히 대상을 변경할 수 없는 게 아니라, `const`가 붙음으로써 동작을 제한하기 때문

```CPP
void mysteryFunction(const std::string* someString) // 인터페이스에서 someString을 수정하지 않겠다고 선언한 것이나 다를 바 없음. 새로 문자열을 대입하면 새로운 주소에 할당되어야 할테니...
{
  *someString = "Test"; // Will not compile.
}

int main()
{
  std::string myString = "The string";
  mysteryFunction(&myString);
  return 0;
}
```

* 참조
  * 존재하는 변수에 다른 이름을 부여하는 방법임

```CPP
int x = 42;
int& xReference = x;
```

* 참조 념겨주기 (pass by reference)
  * 예전엔 참조 넘겨주기로 함수 사용의 성능 패널티를 줄였음
  * C++11부터는 move semantics를 통해서 함수의 구조체나 클래스를 복사 없이 직접 넘겨줄 수 있음 (Chapter 9)

```CPP
void addOne(int i)
{
  i++; // Has no real effect because this is a copy of the original
}

void addOne(int& i)
{
  i++; // Actually changes the original variable
}

...

int myInt = 7;
addOne(myInt);
```

* `const` 참조 념겨주기 (pass by `const` reference)
  * 참조 넘겨주기는 복사를 하지 않지만, 값을 수정하는 수 있는 문제가 있음
  * `const` 참조 념겨주기는 복사를 하지 않고, 값도 수정할 수 없어야 할 때 효율적임

```CPP
void printString(const std::string& myString)
{
  std::cout << myString << std::endl;
}

int main()
{
  std::string someString = "Hello World';
  printString(someString);
  printString("Hello World"); // Passing literals works
  return 0;
}
```

* 예외

```CPP
#include <stdexcept>

using namespace std;

...

double divideNumbers(double numerator, double denominator)
{
  if (denominator == 0) {
    throw invalid_argument("Denominator cannot be 0."); // std::invalid_argument in <stdexcept>
  }
  return numerator / denominator;
}

...

try {
  cout << divideNumbers(2.5, 0.5) << endl; // 정상 동작
  cout << divideNumbers(2.3, 0) << endl;   // 0으로 나누어서 `invalid_argument` 예외 throw를 발생시키고, 이게 catch에 의해 잡힘
  cout << divideNumbers(4.5, 2.5) << endl; // 절대 실행되지 않음
} catch (const invalid_argument& exception) {
  cout << "Exception caught: " << exception.what() << endl; // catch되면서 실행됨
}
```

* Type Inference
  * 컴파일러가 `auto`와 `decltype` 키워드가 붙은 수식의 타입을 자동적으로 추론함

* `auto` 키워드
  * 함수의 리턴 타입을 추론
  * 구조화된 바인딩
  * 식의 타입을 추론
  * non-type 템플릿 파라미터의 타입을 추론 (Chapter 12)
  * `decltype(auto)` (Chapter 12)
  * 대체 함수 문법 (alternative function syntax, Chapter 12)
  * Generic lambda expression (Chapter 18)

* 식의 타입을 추론
  * `auto result = getFoo();`와 같이 함수의 리턴 타입이 복잡한 경우 길이가 짧아지고, 코드 전체에서 타입 수정하느라 시간 낭비할 필요가 없게 됨
  * **주의!** `auto`는 reference와 `const` 한정자 (qualifier)를 제거하고 타입을 결정한다는 점임

```CPP
#include <string>

const std::string message = "Test";
const std::string& foo()
{
  return message;
}

...
auto f1 = foo(); // const, &를 떼고 std::string f1 = foo()로 추론하게 되며, 복사가 일어남...
const auto& f2 = foo() // const, &를 붙였으므로 복사 없이 수정 불가능하게 참조함
```

* `decltype` 키워드
  * 식을 인자처럼 다루어서 타입을 결정함
  * reference, const를 떼지 않음
  * 별로 쓸모 없어 보여도, 템플릿에서 유용함 (Chapter 12, 22)

```CPP
int x = 123;
decltype(x) y = 456; // x의 타입을 보고 y를 int라고 판단함
decltype(foo()) f2 = foo(); // foo()의 타입을 보고 const string&이라고 추론함
```

* 클래스
  * **클래스**는 객체의 특징을 정의한다.
  * 데이터 멤버 (data member, 속성)와 메소드 (method, behavior)가 선언됨
  * 이 책에서는 데이터 멤버의 이름 앞에 `m`을 붙임
  * 객체의 데이터 멤버를 수정하지 않는 함수는 `const`를 붙여서 선언하는 걸 추천
    * 이런 함수를 **inspector**라고 부름
    * 데이터 멤버를 수정하는 함수는 **mutator**라고 부름

```CPP
// AirlineTicket.h
#include <string>

class AirlineTicket
{
  public:
    AirlineTicket(); // 생성자 (constructor)
    ~AirlineTicket(); // 소멸자 (destructor)

    double calculatePriceInDollars() const;

    const std::string& getPassengerName() const;
    void setPassengerName(const std::string& name);

    int getNumberOfMiles() const;
    void setNumberOfMiles(int miles);

    bool hasEliteSuperRewardsStatus() const;
    void setHasEliteSuperRewardsStatus(bool status);
  private:
    std::string mPassengerName;
    int mNumberOfMiles;
    bool mHasEliteSuperRewardsStatus;
};

// AirlineTicket.cpp

using namespace std;

AirlineTicket::AirlineTicket()
  : mPassengerName("Unknown Passenger")
  , mNumberOfMiles(0)
  , mHasEliteSuperRewardsStatus(false)
{
}

또는

// AirlineTicket.cpp
AirlineTicket::AirlineTicket()
{
  // Initialize data members
  mPassengerName = "Unknown Passenger";
  mNumberOfMiles = 0;
  mHasEliteSuperRewardsStatus = false;
}

// -----------------------------------

AirlineTicket::~AirlineTicket()
{
  // Nothing much to do in terms of cleanup
}

double AirlineTicket::calculatePriceInDollars() const
{
  if (hasEliteSuperRewardsStatus()) {
    // Elite Super Rewards customers fly for free!
    return 0;
  }
  // The cost of the ticket is the number of miles times 0.1.
  // Real airlines probably have a more complicated formula!
  return getNumberOfMiles() * 0.1;
}

const string& AirlineTicket::getPassengerName() const
{
  return mPassengerName;
}

void AirlineTicket::setPassengerName(const string& name)
{
  mPassengerName = name;
}

// Other get and set methods omitted for brevity.
```

* 클래스 정의 내에 바로 데이터 멤버를 초기화할 수도 있음

```CPP
// AirlineTicket.h
#include <string>

class AirlineTicket
{
  public:
    AirlineTicket(); // 생성자 (constructor)
    ~AirlineTicket(); // 소멸자 (destructor)

    double calculatePriceInDollars() const;

    const std::string& getPassengerName() const;
    void setPassengerName(const std::string& name);

    int getNumberOfMiles() const;
    void setNumberOfMiles(int miles);

    bool hasEliteSuperRewardsStatus() const;
    void setHasEliteSuperRewardsStatus(bool status);
  private:
    std::string mPassengerName = "Unknown Passenger";
    int mNumberOfMiles = 0;
    bool mHasEliteSuperRewardsStatus = false;
};
```

* 클래스 사용 코드

```CPP
// main_AirlineTicket.cpp
...
AirlineTicket myTicket; // Stack-based AirlineTicket
myTicket.setPassengerName("Sherman T. Socketwrench");
myTicket.setNumberOfMiles(700);
double cost = myTicket.calculatePriceInDollars();
cout << "This ticket will cost $" << cost << endl;

// Heap-based AirlineTicket with smart pointer
auto myTicket2 = make_unique<AirlineTicket>();
myTicket2->setPassengerName("Laudimore M. Hallidue");
myTicket2->setNumberOfMiles(2000);
myTicket2->setHasEliteSuperRewardsStatus(true);
double cost2 = myTicket2->calculatePriceInDollars();
cout << "This other ticket will cost $" << cost2 << endl;
// No need to delete myTicket2, happens automatically

// Heap-based AirlineTicket without smart pointer (not recommended)
AirlineTicket* myTicket3 = new AirlineTicket();
// ... Use ticket 3
delete myTicket3; // delete the heap object!
```

* 클래스와 구조체의 동일한 초기화 (uniform initialization) 방법 지원

```CPP
struct CircleStruct
{
  int x, y;
  double radius;
};

class CircleClass
{
  public:
    CircleClass(int x, int y, double radius)
      : mX(x), mY(y), mRadius(radius) {}
  private:
    int mX, mY;
    double mRadius;
};

// C++11 전에서는 구조체와 클래스의 초기화 방법이 달라야 함
CircleStruct myCircle1 = {10, 10, 2.5};
CircleClass myCircle2(10, 10, 2.5);

// 동일한 초기화 (uniform initialization)에 따라 C++11 이후에서는 구조체와 클래스의 초기화는 같아도 됨
CircleStruct myCircle3 = {10, 10, 2.5};
CircleClass myCircle4 = {10, 10, 2.5};

// =을 생략해도 됨
CircleStruct myCircle5{10, 10, 2.5};
CircleClass myCircle6{10, 10, 2.5};

// 변수를 초기화 하는 방법
int a = 3;
int b(3);
int c = {3}; // Uniform initialization
int d{3}; // Uniform initialization

// 클래스 생성자에서 초기화하는 방법
class MyClass
{
  public:
    MyClass() : mArray{0, 1, 2, 3} {}
  private:
    int mArray[4];
};

// zero-initializtion을 하는 방법
// Zero-initialization constructs objects with the default constructor, and initializes primitive integer types (such as char, int, and so on) to zero, primitive floating-point types to 0.0, and pointer types to nullptr.
int e{}; // Uniform initialization, e will be 0
```

* 동일한 초기화는 C++가 값을 자동적으로 truncate하는 narrowing을 방지함
  * C++11 표준을 컴파일러가 준수한다면 다음 코드는 에러를 발생시킴

```CPP
// 에러 없는 코드
void func(int i) { /* ... */ }

int main()
{
  int x = 3.14;
  func(3.14);
}

// 에러 발생 코드
void func(int i) { /* ... */ }

int main()
{
  int x = {3.14}; // Error because narrowing
  func({3.14}); // Error because narrowing
}
```

* 직접 리스트 초기화 vs. 복사를 통한 리스트 초기화
  * 복사를 통한 리스트 초기화 `T obj = {arg1, arg2, ...};`
  * 직접 리스트 초기화 `T obj {arg1, arg2, ...};` (C++17에서 차이가 발생함)

```CPP
// C++17에서는 다음과 같이 동작한다.
// Copy list initialization
auto a = {11};      // initializer_list<int>
auto b = {11, 22};  // initializer_list<int>
auto b = {11, 22.33}; // Compilation error (리스트 내의 원소는 같은 타입이어야 하기 때문)

// Direct list initialization
auto c {11};        // int
auto d {11, 22};    // Error, too many elements.

// C++11, C++14에서는 다음과 같이 initializer_list<int>가 실행된다.
// Copy list initialization
auto a = {11};      // initializer_list<int>
auto b = {11, 22};  // initializer_list<int>
// Direct list initialization
auto c {11};        // initializer_list<int>
auto d {11, 22};    // initializer_list<int>
```