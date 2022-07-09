extern "C"
double approximate_point_using_newton_polynomial(double x, int size, double* x_list, double* y_list) {
	double value = 0.0;
	double bk = 0.0;
	double temp;
	double multiply_result = 0.0;
	for (int k = 0; k < size; k++) {
		bk = 0.0;
		for (int i = 0; i <= k; i++) {
			temp = y_list[i];
			multiply_result = 1.0;
			for (int j = 0; j < i; j++) {
				multiply_result *= x_list[i] - x_list[j];

			}
			for (int j = i + 1; j <= k; j++) {
				multiply_result *= x_list[i] - x_list[j];
			}
			bk += temp / multiply_result;
		}
		temp = bk;
		for (int i = 0; i < k; i++) {
			temp *= x - x_list[i];
		}
		value += temp;
	}
	return value;
}

int main() {

}