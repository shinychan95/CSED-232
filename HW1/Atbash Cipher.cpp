std::string atbash(std::string str) {
	std::string result = "";

	// a -> 97, z -> 122
	// A -> 65, Z -> 90
	
	int n;
	for (int i = 0; i < str.length(); i++) {
		n = int(str[i]);
		if (n >= 65 and n <= 90) 
			result += char(155 - n);
		
		else if (n >= 97 and n <= 122)
			result += char(219 - n);
		else
			result += str[i];
	}
	return result;
}