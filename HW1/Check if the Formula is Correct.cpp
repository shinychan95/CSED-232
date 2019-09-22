bool formula(std::string str) {
	std::string arr_formula[99];
	int num_formula = 0;

	// a = 4
	// ' ' = 32

	// ( = 40
	// ) = 41

	// / = 47
	// * = 42
	// ^ = 94
	// % = 37

	// + = 43
	// - = 45


	// 0 = 48
	// 9 = 57

	for (int i = 0; i < str.length(); i++) {
		if (int(str[i]) == 32) {
			str.replace(i, 1, "");
			i--;
		}
	}
	for (int i = 0; i < str.length(); i++) {
		if (int(str[i]) == 97)
			str.replace(i, 1, "4");
	}

	
	int current_index = 0;
	for (int i = 0; i < str.length(); i++) {
		if (int(str[i]) == 61) {
			arr_formula[num_formula] = str.substr(current_index, i - current_index);
			current_index = i+1;
			num_formula++;
		}
	}
	arr_formula[num_formula] = str.substr(current_index, str.length() - current_index);
	num_formula++;


	for (int i = 0; i < num_formula; i++) {
		bool check_priority = false;
		bool has_priority = false;
		bool calculate_over = false;
		std::string prior_formula = "";
		int index_of_prior[2] = { -1, -1 };

		while (!calculate_over) {
			if (calculate_over)
				break;
			prior_formula = "";
			for (int j = 0; j < arr_formula[i].length(); j++) {
				if (int(arr_formula[i][j]) == 41 and index_of_prior[1] == -1) {
					check_priority = false;
					index_of_prior[1] = j;
				}

				if (check_priority)
					prior_formula += arr_formula[i][j];

				if (int(arr_formula[i][j]) == 40) {
					check_priority = true;
					index_of_prior[0] = j;
					index_of_prior[1] = -1;
					prior_formula = "";
				}

			}


			if (prior_formula == "") {
				calculate_over = true;
				prior_formula = arr_formula[i];
				index_of_prior[0] = 0;
				index_of_prior[1] = arr_formula[i].length() - 1;
			}

			int number = 0;
			int num[99];
			char cal[99];
			int index_of_num = 0;
			int index_of_cal = 0;
			for (int j = 0; j < prior_formula.length(); j++) {
				if (int(prior_formula[j]) >= 48 and int(prior_formula[j]) <= 57) {
					number = 10 * number;
					number += prior_formula[j] - '0';
				}
				else if ((int(prior_formula[j]) >= 42 and int(prior_formula[j]) <= 47) or int(prior_formula[j]) == 94 or int(prior_formula[j]) == 37) {
					num[index_of_num] = number;
					index_of_num++;
					cal[index_of_cal] = prior_formula[j];
					index_of_cal++;
					number = 0;
				}
			}
			num[index_of_num] = number;
			index_of_num++;



			int result = 0;
			number = num[0];
			for (int j = 0; j < index_of_cal; j++) {
				if (cal[j] == '+') {
					result += number;
					number = num[j + 1];
				}
				else if (cal[j] == '-') {
					result += number;
					number = num[j + 1] * (-1);
				}
				else if (cal[j] == '*') {
					number = number * num[j + 1];
				}
				else if (cal[j] == '^') {
					for (int k = 0; k < num[j + 1]; k++) {
						number = number * num[j + 1];
					}
				}
				else if (cal[j] == '%') {
					number = number % num[j + 1];
				}
				else {
					number = number / num[j + 1];
				}

			}
			result += number;

			for (int j = 0; j < index_of_num; j++)
				num[j] = 0;
			index_of_num = 0;

			for (int j = 0; j < index_of_cal; j++)
				cal[j] = 0;
			index_of_cal = 0;

			std::string result_to_string = "";

			while (result != 0) {
				result_to_string = char(result % 10 + 48) + result_to_string;
				result = result / 10;
			}

			arr_formula[i].replace(index_of_prior[0], index_of_prior[1] - index_of_prior[0] + 1, result_to_string);

		}
	}

	bool final_result = true;

	for (int i = 0; i < num_formula - 1; i++){
		final_result = final_result && (arr_formula[i] == arr_formula[i + 1]);
	}


	return final_result;

	
}