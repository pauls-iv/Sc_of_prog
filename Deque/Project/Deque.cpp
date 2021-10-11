#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Deque.h"
#include "MyMemStrategy.h"

using std::cout;
using std::endl;

void Test(std::string const& correct, Deque<int, MyMemStrategy>& dq) {
  std::string result = dq.str();
  cout << "Expectation: " << correct << endl;
  cout << "Reality    : " << result << endl;
  
  if (result == correct)
    cout << "[OK]\n" << endl;
  else
    cout << "[FAIL]\n" << endl;
}

int main(void) {

  cout << "Test 1: default c-tor" << endl;
  Deque<int, MyMemStrategy> dq;
  Test("< >", dq);


  cout << "Test 2: initializer list c-tor" << endl;
  Deque<int, MyMemStrategy> dq1 = {1, 2, 3};
  Test("< 1 2 3 >", dq1);


  cout << "Test 3: copy c-tor" << endl;
  Deque<int, MyMemStrategy> dq2 = dq1;
  Test("< 1 2 3 >", dq2);


  cout << "Test 4: move c-tor" << endl;
  Deque<int, MyMemStrategy> dq3 = std::move(dq1);
  Test("< 1 2 3 >", dq3);


  cout << "Test 5: clear" << endl;
  dq3.clear();
  Test("< >", dq3);


  cout << "Test 6: pushHead (copy semantics)" << endl;
  int data = 42;
  dq.pushHead(data);
  Test("< 42 >", dq);


  cout << "Test 7: pushHead (move semantics)" << endl;
  dq.pushHead(666);
  Test("< 666 42 >", dq);


  cout << "Test 8: pushTail (copy semantics)" << endl;
  data = 1;
  dq.pushTail(data);
  Test("< 666 42 1 >", dq);


  cout << "Test 9: pushTail (move semantics)" << endl;
  dq.pushTail(9);
  Test("< 666 42 1 9 >", dq);


  cout << "Test 10: popHead" << endl;
  dq.popHead();
  Test("< 42 1 9 >", dq);


  cout << "Test 11: popTail" << endl;
  dq.popTail();
  Test("< 42 1 >", dq);


  cout << "Test 12: isEmpty" << endl; 
  cout << "Expectation: 0" << endl;
  cout << "Reality    : " << dq.isEmpty() << endl;
  if (dq.isEmpty() == 0)
    cout << "[OK]\n" << endl;
  else
    cout << "[FAIL]\n" << endl;


  cout << "Test 13: size" << endl;
  cout << "Expectation: 2" << endl;
  cout << "Reality    : " << dq.size() << endl;
  if (dq.size() == 2)
    cout << "[OK]\n" << endl;
  else
    cout << "[FAIL]\n" << endl;


  cout << "Test 14: op= (copy semantics)" << endl;
  dq1 = dq;
  Test("< 42 1 >", dq1);


  cout << "Test 15: op= (move semantics)" << endl;
  dq = std::move(dq2);
  Test("< 1 2 3 >", dq);

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  return 0;
}