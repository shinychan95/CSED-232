int nonRepeats(int radix) {
  std::cout << "radix: " << radix << std::endl;
  
  int result = radix - 1;
  int add = radix - 1;
​
  for (int i = radix - 1; i >= 1; i--) {
    add = add * i;
    result += add;
  }
​
  return result;
​
}