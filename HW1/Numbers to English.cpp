std::string numToEng(int n) {
	std::string zero = "zero";
	std::string arr0[10] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::string arr00[10] = { "", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety" };
	std::string arr10[10] = { "ten", "eleven", "twelve", "thirtenn", "fourteen", "fifteen", "sixteen", 
		"seventeen", "eighteen", "nineteen" };



	int quotient;
	int remainder;
	int count = 0;
	std::string result[3];
	std::string result_str = "";
	
	if (n == 0)
		return 0;

	if (n >= 100) {
		result[count].append(arr0[n / 100] + " " + "hundred");
		remainder = n % 100;
		count++;
	}


	if (remainder >= 10) {
		if (remainder / 10 == 1) {
			result[count].append(arr10[remainder % 10]);
			remainder = remainder % 10;
			count++;
		}
		else {
			result[count].append(arr00[remainder / 10]);
			remainder = remainder % 10;
			count++;
		}
	}
	if (remainder > 0) {
		result[count].append(arr0[remainder]);
		count++;
	}
		
	

	for (int i = 0; i < count; i++) {
		result_str += result[i] + " ";
	}

	return result_str.substr(0, result_str.length() - 1);
}