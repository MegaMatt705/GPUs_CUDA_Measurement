#include <iostream>
#include <math.h>
#include <chrono>

// function to add the elements of two arrays
void add(int n, float *x, float *y)
{
  for (int i = 0; i < n; i++)
      y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1<<29; // (512M)

  float *x = new float[N];
  float *y = new float[N];

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the CPU
  // Start the timer
  auto start = std::chrono::high_resolution_clock::now();
  
  add(N, x, y);
  
  // Stop the timer
  auto end = std::chrono::high_resolution_clock::now();

  // Calculate the duration
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Print out elapsed time for this problem size
  std::cout << "Elapsed time: " << duration.count() << " microseconds" << std::endl;

  // Free memory
  delete [] x;
  delete [] y;

  return 0;
}
