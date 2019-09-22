long long int bonacci(int N, int k) {
  std::cout << "N: " << N << " // " << "k: " << k << std::endl;
  
  if (k < N)
    return 0;
  if (k == N)
    return 1;
  long long* arr = (long long*)malloc(sizeof(long long) * k);
​
  for (long long i = 0; i < N - 1; i++) {
    arr[i] = 0;
  }
  arr[N - 1] = 1;
  arr[N] = 1;
​
  
​
  for (long long i = N + 1; i < k; i++)
    arr[i] = 2 * arr[i - 1] - arr[i - N - 1];
​
​
  return arr[k-1];
}