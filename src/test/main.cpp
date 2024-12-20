#include <iostream>

#include <bigint.h>

int main() {

  int counter = 0;
  int SIZE = 2000;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = i + 1; j < SIZE; ++j) {
      BigInt first(i);
      BigInt second(j);
      auto res = first + second;

      if (*reinterpret_cast<int *>(res.value) != (i + j)) {
        ++counter;
        std::cout << "BAD" << std::endl;
      }
    }
  }

  std::cout << "bad variants count = " << counter << std::endl;
  std::cout << "all variants count = " << SIZE * SIZE << std::endl;
  std::cout << "% bad results = " << counter * 100 / (SIZE * SIZE) << std::endl;
  return 0;
}
