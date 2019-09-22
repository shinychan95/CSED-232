std::string longestSubstring(std::string digits) {
  std::cout << "digits: " << digits << std::endl;
  // '1' = 49
  // '9' = 57
  std::string count_string = "";
  count_string += digits[0];
  std::string largest_string = "";
  largest_string += digits[0];
  int count = 1;
  int largest = 1;
  
​
  for (int i = 0; i < digits.length(); i++) {
    if (int(digits[i]) % 2 != int(digits[i + 1]) % 2) {
      count++;
      count_string += digits[i+1];
    }
    else {
      if (largest < count) {
        largest = count;
        largest_string = count_string;
        count = 1;
        count_string = "";
        count_string += digits[i+1];
      }
      else {
        count = 1;
        count_string = "";
        count_string += digits[i+1];
      }
    }
  }
​
  return largest_string;
}