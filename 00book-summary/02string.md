# Chapter 2. Working with Strings and String Views

* C는 NUL 문자로 배열을 닫는 문자열을 사용해서 보안 취약점 생성
  * NUL 문자라고 불리는 게 맞음
  * C++ 표준 라이브러리는 그런 단점이 없는 `std::string` 클래스를 제공함

* C 언어 스타일의 문제점
  * NUL 문자를 빼먹고 처리하는 경우가 많음

```CPP
#include <cstring>
char* appendStrings(const char* str1, const char* str2, const char* str3)
{
  char* result = new char[strlen(str1) + strlen(str2) + strlen(str3) + 1];
  strcpy(result, str1);
  strcat(result, str2);
  strcat(result, str3);
  return result;
}
```

```CPP
char text1[] = "abcdef";
size_t s1 = sizeof(text1); // is 7
size_t s2 = strlen(text1); // is 6

const char* text2 = "abcdef";
size_t s3 = sizeof(text2); // is platform-dependent (포인터 크기가 리턴됨)
size_t s4 = strlen(text2); // is 6
```

* 문자열 리터럴
  * `cout << "hello" << endl;`에서 `"hello"`는 스트링 리터럴임
  * **Literal pooling**: 스트링 리터럴은 읽기만 가능한 메모리 영역에 저장되며 재사용됨
  * C++ 표준에서는 스트링 리터컬은 "array of n `const char`"라고 하지만, 대부분의 컴파일러는 `const char*` 타입 변수에 스트링 리터럴을 할당함
    * 따라서 다음과 같은 코드는 쓰면 안 됨

```CPP
// 쓰면 안 되는 코드 (컴파일러는 허용하지만 표준은 지원하지 않음)
char* ptr = "hello"; // Assign the string literal to a variable
ptr[1] = 'a';        // Undefined behavior!

// 수정한 코드 (에러 발생)
const char* ptr = "hello"; // Assign the string literal to a variable.
ptr[1] = 'a'; // Error! Attempts to write to read-only memory

// Literal pooling을 쓰지 않는 코드
char arr[] = "hello"; // Compiler takes care of creating appropriate sized character array arr.
arr[1] = 'a'; // The contents can be modified.
```

* Raw String Literals (C++11부터 도입)
  * `R"(`과 `)"`로 감싸서 있는 그대로 인식시키는 리터럴

```CPP
const char* str = "Hello "World"!"; // Error!
const char* str = "Hello \"World\"!"; // 올바른 코드
const char* str = R"(Hello "World"!)"; // 올바른 코드

const char* str = "Line 1\nLine 2"; // 올바른 코드
const char* str = R"(Line 1
Line 2)"; // 올바른 코드

const char* str = R"(Embedded )" characters)"; // Error!
const char* str = R"-(Embedded )" characters)-"; // 중간에 )" 문자열을 넣고 싶을 때
```

* C++ `string` 틀래스의 연산자 오버로딩
  * `==`, `!=`, `<` 등의 연산자는 오버로드됨

```CPP
string myString = "hello";
myString += ", there";
string myOtherString = myString;
if (myString == myOtherString) {
  myOtherString[0] = 'H';
}
cout << myString << endl;
cout << myOtherString << endl;
```

* 위 예제 코드 결과:
```shell
hello, there
Hello, there
```

* C와의 호환성을 위해 문자열의 포인터를 돌려주는 `c_str()` 메소드가 있지만, 객체가 파괴되면 사라지므로 그 포인터를 리턴하는 짓을 하면 안 됨
  * 또한 `c_str()`는 `const char*`로 리턴하므로 수정할 수 없음
* C++14까지 `data()` 메소드는 `const char*`로 리턴했는데, C++17에서는 `const`로 선언되지 않은 문자열에 대해서는 `data()`가 `char*`를 리턴함. 즉, 이를 이용해 수정할 수 있음 (**구 버전 C 라이브러리와 연동 시 유용함**)
  * <https://medium.com/@Coder_HarryLee/c-17-8d2bc39eec62> 참고

* `std::string` 리터럴
  * 컴파일러는 보통 문자열 리터럴을 `const char*`로 처리하므로, 문자열 객체가 되도록 만들고 싶다면 s를 뒤에 붙일 것
  * 사용을 위해서는 `namespace std::string_literals;` 또는 `using namespace std;`가 필수임

```CPP
auto string1 = "Hello World"; // string1 is a const char*
auto string2 = "Hello World"s; // string2 is an std::string
```

* high-level numeric conversions
  * std에는 `string to_string(long long val);`처럼 문자열로 바꾸어주는 함수 사용할 수 있음
  * C의 `atoi`에 대응해서 `stoi(const string& str, size_t *idx=0, int base=10);`, `stol`, `stoul`, `stoll`, `stoull`, `stof`, `stod`, `stold`등이 있는데, 두 번째 인자인 `idx`는 파싱이 되지 않은 문자의 위치를 리턴함 (포인터가 주어졌다면)

```CPP
const string toParse = " 123USD";
size_t index = 0;
int value = stoi(toParse, &index);
cout << "Parsed value: " << value << endl;
cout << "First non-parsed character: '" << toParse[index] << "'" << endl;
```

```shell
Parsed value: 123
First non-parsed character: 'U'
```

* Low-Level Numeric Conversions (C++17)
  * TODO

* The `std::string_view` Class (C++17)
  * TODO
  * Use an std::string_view instead of const std::string& or const char* whenever a function or method requires a read-only string as one of  its parameters.

