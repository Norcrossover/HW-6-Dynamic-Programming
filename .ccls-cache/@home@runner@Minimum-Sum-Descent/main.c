#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int create_random_number();
int get_array_size();
int create_matrix(int n, int matrix[n][n]);
void set_matrix(int n, int matrix[n][n]);
void print_matrix(int n, int matrix[n][n]);
int minimum_sum_descent(int n, int matrix[n][n], int row, int column);
int memoized_minimum_sum_descent(int n, int table[n][n], int matrix[n][n],
                                 int row, int column);

int main(void) {
  int n = 10;
  int matrix[n][n];
  int table[n][n];
  int min_sum = 0;
  int memo_min_sum = 0;

  set_matrix(n, matrix);
  set_matrix(n, table);
  create_matrix(n, matrix);
  table[0][0] = matrix[0][0];
  table[1][0] = matrix[1][0];
  table[1][1] = matrix[1][1];
  // printf("Initial tree:\n");
  print_matrix(n, matrix);
  min_sum = minimum_sum_descent(n, matrix, 0, 0);
  memo_min_sum = memoized_minimum_sum_descent(n, table, matrix, 0, 0);
  printf("The minimum sum descent: %d\n\n", min_sum);
  printf("The memoized minimum sum descent: %d\n", memo_min_sum);

  return 0;
}

int create_random_number() { return floor(10 * drand48()); }

int get_array_size() {
  int size = 0, result;
  printf("Please enter in the size of the array: ");
  result = scanf("%d", &size);
  if (result == -1)
    return 0;
  return size;
}

int create_matrix(int n, int matrix[n][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      matrix[i][j] = create_random_number();
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

/*
f(n) = f(n-1) + min{left child, right child}
*/
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