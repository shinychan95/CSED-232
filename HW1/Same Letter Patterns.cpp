bool sameLetterPattern(std::string str1, std::string str2) {
  // A = 65
  // Z = 90
​
  if (str1.length() != str2.length())
    return false;
​
  int length = str1.length();
​
​
  for (int i = 0; i < str1.length(); i++) {
    std::cout << int(str1[i]) << " ";
  }
  std::cout << std::endl;
​
  std::cout << "str2: ";
  for (int i = 0; i < str2.length(); i++) {
    std::cout << int(str2[i]) << " ";
  }
  std::cout << std::endl;
​
​
  bool result_A = true;
  bool result_B = true;
  bool result_C = true;
  
  for (int i = 0; i < length - 1; i++) {
    if ((int(str1[i]) - int(str1[i + 1])) == (int(str2[i]) - int(str2[i + 1])))
      result_A = result_A && true;
    else
      result_A = result_A && false;
  }
​
  for (int i = 0; i < length / 2; i++) {
    if ((str1[i] == str1[length - i - 1]) == (str2[i] == str2[length - i - 1]))
      result_B = result_B && true;
    else
      result_B = result_B && false;
  }
  
  for (int i = 0; i < length - 1; i++) {
    if ((str1[i] == str1[i+1]) == (str2[i] == str2[i+1]))
      result_C = result_C && true;
    else
      result_C = result_C && false;
  }
  
  
  std::cout << result_A << " // " << result_B << " // " << result_C << std::endl;
  return result_A || (result_B && result_C);
​
}