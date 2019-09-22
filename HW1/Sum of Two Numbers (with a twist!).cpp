std::string sum2(std::string a, std::string b) {
	
	std::string tmp;

	if (a.length() < b.length()) {
		tmp = a;
		a = b;
		b = tmp;
	}
	
	int length_diff = a.length() - b.length();

	for (int i = 0; i < length_diff; i++)
		b = "0" + b;
	


	std::string result = "";
	int digit_a;
	int digit_b;
	int sum = 0;
	for (int i = b.length() - 1; i >= 0; i--) {
		digit_a = a[i] - '0';
		digit_b = b[i] - '0';
		sum = sum + digit_a + digit_b;
		if (sum / 10 == 1) {
			result =  char(sum % 10 + 48) + result;
			sum = 1;
		}
		else {
			result = char(sum + 48) + result;
			sum = 0;
		}
	}

	if (sum == 1)
		result = char(sum + 48) + result;
	
	return result;
}