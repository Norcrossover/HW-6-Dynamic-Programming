#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// helpers
int create_random_number(int max_value);
int get_array_size();
int create_matrix(int n, int matrix[n][n]);
void set_matrix(int n, int matrix[n][n]);
void print_matrix(int n, int matrix[n][n]);
void print_array(int n, int array[]);

// minimum sum descent functions
int minimum_sum_descent(int n, int matrix[n][n], int row, int column);
int memoized_minimum_sum_descent(int n, int table[n][n], int matrix[n][n],
                                 int row, int column);
void minimum_sum_descent_driver();

// N choose K functions
void nck_driver();
int nck(int n, int k);
int memoized_nck(int n, int k, int table[n][k]);

// Rod Cutting Problem
void create_rod(int n, int rod[]);
void rod_cutting_driver();
int rod_cutting(int n, int i, int list[]);
int memoized_rod_cutting(int n, int lsit[]);

//===================================================================
int main(void) {
  printf("\n-----------------------------------------\n\n");
  printf("MINIMUM SUM DESCENT \n\n");
  minimum_sum_descent_driver();
  printf("\n-----------------------------------------\n\n");
  printf("N CHOOSE K \n\n");
  nck_driver();
  printf("\n-----------------------------------------\n\n");
  printf("ROD CUTTING PROBLEM \n\n");
  rod_cutting_driver();
  printf("\n-----------------------------------------\n\n");

  return 0;
}
//===================================================================

//-------------------------------------------------------------------------
//                          Minimum Sum Descent
//-------------------------------------------------------------------------

void minimum_sum_descent_driver() {
  int n = 10;
  int matrix[n][n];
  int table[n][n];
  int min_sum = 0;
  int memo_min_sum = 0;

  // set matrices
  set_matrix(n, matrix);
  set_matrix(n, table);
  create_matrix(n, matrix);

  // set table
  table[0][0] = matrix[0][0];
  table[1][0] = matrix[1][0];
  table[1][1] = matrix[1][1];

  // print solutions
  print_matrix(n, matrix);
  min_sum = minimum_sum_descent(n, matrix, 0, 0);
  memo_min_sum = memoized_minimum_sum_descent(n, table, matrix, 0, 0);
  printf("\nThe minimum sum descent: %d\n\n", min_sum);
  printf("The memoized minimum sum descent: %d\n\n", memo_min_sum);
}

int create_random_number(int max) { return floor(max * drand48()); }

int get_array_size() {
  int size = 0, result;
  printf("Please enter in the size of the array: ");
  result = scanf("%d", &size);
  if (result == -1)
    return 0;
  return size;
}

int create_matrix(int n, int matrix[n][n]) {
  int max_size_value = 10;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      matrix[i][j] = create_random_number(max_size_value);
    }
  }
}

void set_matrix(int n, int matrix[n][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = -1;
    }
  }
}

void print_matrix(int n, int matrix[n][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = i; j >= 0; j--) {
      printf("%d\t", matrix[i][j]);
    }
    printf("\n");
  }
}

void print_array(int n, int array[]) {
  for (int i = 0; i < n; i++) {
    printf("%d\t", array[i]);
  }
  printf("\n");
}

int minimum_sum_descent(int n, int matrix[n][n], int row, int col) {
  int minimum = 0;
  int left = col;
  int right = col + 1;
  int one = 0;
  int two = 0;

  if (row == n - 1)
    return matrix[row][col];

  one = minimum_sum_descent(n, matrix, row + 1, left);
  two = minimum_sum_descent(n, matrix, row + 1, right);

  if (one < two) {
    minimum = one;
  } else {
    minimum = two;
  }

  return matrix[row][col] + minimum;
}

int memoized_minimum_sum_descent(int n, int table[n][n], int matrix[n][n],
                                 int row, int col) {
  int minimum = 0;
  int left = col;
  int right = col + 1;
  int one = 0;
  int two = 0;

  if (table[row][col] != -1)
    return matrix[row][col];

  one = memoized_minimum_sum_descent(n, table, matrix, row + 1, left);
  two = memoized_minimum_sum_descent(n, table, matrix, row + 1, right);

  if (one < two) {
    minimum = one;
  } else {
    minimum = two;
  }

  table[row][col] = matrix[row][col] + minimum;

  return table[row][col];
}

//-------------------------------------------------------------------------
//                          Minimum Sum Descent
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//                          N choose K problem
//-------------------------------------------------------------------------
void nck_driver() {
  int n = 5;
  int k = 3;
  int table[n][k];

  // set table
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      table[i][j] = -1;
    }
  }

  for (int i = 0; i < n; i++) {
    table[i][0] = 1;
    table[i][1] = i;
    // table[i][i] = 1;
  }

  printf("N choose k normal solution: %d\n\n", nck(n, k));
  printf("N choose k memoized solution: %d\n\n", memoized_nck(n, k, table));
}

int nck(int n, int k) {
  if (k == 0)
    return 1;
  if (k == 1)
    return n;
  if (n == k)
    return 1;

  return nck(n - 1, k - 1) + nck(n - 1, k);
}

int memoized_nck(int n, int k, int table[n][k]) {
  if (table[n][k] != -1)
    return table[n][k];

  table[n][k] = nck(n - 1, k - 1) + nck(n - 1, k);

  return table[n][k];
}

//-------------------------------------------------------------------------
//                          N choose K problem
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//                          Rod Cutting Problem
//-------------------------------------------------------------------------
void create_rod(int n, int rod[]) {
  for (int i = 0; i < n; i++) {
    rod[i] = i;
    // create_random_number(i);
  }
  rod[0] = 0;
}

void rod_cutting_driver() {
  int n = 8;
  int array[n];

  create_rod(n, array);
  print_array(n, array);
  printf("Rod cutting driver solution: %d\n", rod_cutting(n, n - 1, array));
}

int count(int n, int value) { return n / value; }
int max_rod_value(int n, int value) { return count(n, value) * value; }

int rod_cutting(int n, int i, int rod_price[]) {
  int rod_cut = -1;
  int rod_free = -1;
  int rod_length = i + 1;

  if (i == 0)
    return n * rod_price[i];

  rod_free = rod_cutting(n, i - 1, rod_price);

  if (rod_length <= n)
    rod_cut = rod_price[i] + rod_cutting(n - rod_length, i, rod_price);

  return (rod_cut >= rod_free) ? rod_cut : rod_free;
}
//-------------------------------------------------------------------------
//                          Rod Cutting Problem
//-------------------------------------------------------------------------
