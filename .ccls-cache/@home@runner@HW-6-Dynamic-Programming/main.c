#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// helpers
int create_random_number(int max_value);
int get_array_size();
void create_matrix(int n, int matrix[n][n]);
void set_matrix(int n, int matrix[n][n]);
void print_matrix(int n, int matrix[n][n]);
void print_array(int n, int array[]);
int minimum(int a, int b);

// minimum sum descent functions
int minimum_sum_descent(int n, int matrix[n][n], int row, int column);
int memoized_minimum_sum_descent(int n, int table[n][n], int matrix[n][n],
                                 int row, int column);
int tabulated_minimum_sum_descent(int n, int matrix[n][n], int row, int column);
void minimum_sum_descent_driver();

// N choose K functions
void choose_driver();
int choose(int n, int k);
int memoized_choose(int n, int k, int table[n][k]);
int tabulated_choose(int n, int k);

// Rod Cutting Problem
void create_rod(int n, int rod[]);
void rod_cutting_driver();
int rod_cutting(int n, int i, int list[]);
int memoized_rod_cutting(int n, int list[]);
int tabulated_rod_cutting(int n, int list[]);

//===================================================================
int main(void) {
  printf("\n-----------------------------------------\n\n");
  printf("MINIMUM SUM DESCENT \n\n");
  minimum_sum_descent_driver();
  printf("\n-----------------------------------------\n\n");
  printf("N CHOOSE K \n\n");
  choose_driver();
  printf("\n-----------------------------------------\n\n");
  printf("ROD CUTTING PROBLEM \n\n");
  rod_cutting_driver();
  printf("\n-----------------------------------------\n\n");

  return 0;
}
//===================================================================

int create_random_number(int max) { return floor(max * drand48()); }

int get_array_size() {
  int size = 0, result;
  printf("Please enter in the size of the array: ");
  result = scanf("%d", &size);
  if (result == -1)
    return 0;
  return size;
}

void create_matrix(int n, int matrix[n][n]) {
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

int minimum(int a, int b) { return ((a < b) ? a : b); }

//-------------------------------------------------------------------------
//                          Minimum Sum Descent
//-------------------------------------------------------------------------

void minimum_sum_descent_driver() {
  int n = 10;
  int matrix[n][n];
  int table[n][n];
  int min_sum = 0;
  int memo_min_sum = 0;
  int tab_min_sum = 0;

  // naiive
  set_matrix(n, matrix);
  set_matrix(n, table);
  create_matrix(n, matrix);
  print_matrix(n, matrix);
  min_sum = minimum_sum_descent(n, matrix, 0, 0);

  // memoize
  set_matrix(n, table);
  memo_min_sum = memoized_minimum_sum_descent(n, table, matrix, 0, 0);

  // tabular
  tab_min_sum = tabulated_minimum_sum_descent(n, matrix, 0, 0);

  printf("\nThe minimum sum descent: %d\n\n", min_sum);
  printf("The memoized minimum sum descent: %d\n\n", memo_min_sum);
  printf("The tabulated minimum sum descent: %d\n\n", tab_min_sum);
}

int minimum_sum_descent(int n, int matrix[n][n], int row, int col) {
  int a = 0;
  int b = 0;

  if (row == n - 1)
    return matrix[row][col];

  a = minimum_sum_descent(n, matrix, row + 1, col);
  b = minimum_sum_descent(n, matrix, row + 1, col + 1);

  return matrix[row][col] + ((a < b) ? a : b);
}

int memoized_minimum_sum_descent(int n, int table[n][n], int matrix[n][n],
                                 int row, int col) {
  int a = 0;
  int b = 0;

  if (row == n - 1)
    return matrix[row][col];

  if (table[row][col] != -1)
    return table[row][col];

  a = memoized_minimum_sum_descent(n, table, matrix, row + 1, col);
  b = memoized_minimum_sum_descent(n, table, matrix, row + 1, col + 1);

  table[row][col] = matrix[row][col] + (minimum(a, b));

  return table[row][col];
}

int tabulated_minimum_sum_descent(int n, int matrix[n][n], int row,
                                  int column) {
  int table[n + 1][n + 1];
  int min = INT_MAX, a = 0, b = 0, minimum_sum_descent = INT_MAX;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j == 0) {
        if (i == 0) {
          table[i][j] = matrix[i][j];
        } else {
          table[i][j] = matrix[i][j] + table[i - 1][0];
        }
        min = minimum(min, table[i][j]);
        continue;
      }
      if (j == i) {
        table[i][j] = matrix[i][j] + table[i - 1][j - 1];
        min = minimum(min, table[i][j]);
        break;
      }
      a = table[i - 1][j];
      if (j == 0) {
        min = minimum(a, min);
      } else {
        b = table[i - 1][j - 1];
        min = minimum(a, b);
      }
      table[i][j] = matrix[i][j] + min;
    }
    // minimum_sum_descent = minimum(minimum_sum_descent, min);
  }

  minimum_sum_descent = 999999999;

  for (int i = 0; i < n; i++) {
    if (table[n - 1][i] < minimum_sum_descent)
      minimum_sum_descent = table[n - 1][i];
  }

  return minimum_sum_descent;
}
//-------------------------------------------------------------------------
//                          Minimum Sum Descent
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//                          N choose K problem
//-------------------------------------------------------------------------
void choose_driver() {
  int n = 5;
  int k = 3;
  int table[n][k];

  // set table
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      table[i][j] = -1;
    }
  }

  printf("N choose k normal solution: %d\n\n", choose(n, k));
  printf("N choose k memoized solution: %d\n\n", memoized_choose(n, k, table));
  printf("N choose k tabulated solution: %d\n\n", tabulated_choose(n, k));
}

int choose(int n, int k) {
  if (k == 0 || n == k)
    return 1;

  return choose(n - 1, k - 1) + choose(n - 1, k);
}

int memoized_choose(int n, int k, int table[n][k]) {
  if (k == 0 || n == k)
    return 1;
  if (table[n][k] != -1)
    return table[n][k];

  table[n][k] = choose(n - 1, k - 1) + choose(n - 1, k);

  return table[n][k];
}

int tabulated_choose(int n, int k) {
  int table[n][k];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      if (k == 0 || k == n) {
        table[n][k] = 1;
        continue;
      }
      table[n][k] = table[n - 1][k - 1] + table[n - 1][k];
    }
  }

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
