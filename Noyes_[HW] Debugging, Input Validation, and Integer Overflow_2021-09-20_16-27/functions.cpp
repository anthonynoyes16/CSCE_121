#include <stdexcept>
#include <iostream>
int Largest(int a, int b, int c) {
  int d = 0;
  if (a > b && a > c) {
    d = a;
  } 
  if (b > a && b > c) {
    d = b;
  } 
  if (c > a && c > b) {
    d = c;
  }
  if (a == b) {
    if (a > c || b > c) {
      d = a;
    }
    else {
      d = c;
    }
  }
  if (a == c) {
    if (a > b || c > b) {
      d = a;
    }
    else {
      d = b;
    }
  }
  if (b == c) {
    if (b > a || c > a) {
      d = b;
    }
    else {
      d = a;
    }
  }
  return d;

}

bool SumIsEven(int a, int b) {
  if (((a+b) % 2) != 0) {
    return false;
  }
  else {
    return true;
  }
}

int BoxesNeeded(int apples) {
  int boxes;
  if (apples <= 0) {
    boxes = 0;
  }
  if (apples > 0) {
    boxes = (apples / 20) + 1;
    if (apples % 20 == 0) {
      boxes = apples / 20;
    }
  }
  return boxes;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
    if (A_correct < 0 || A_total <= 0 || B_correct < 0 || B_total <= 0) {
      throw std::invalid_argument("Error type 1");
    }

    if (A_correct > A_total || B_correct > B_total) {
      throw std::invalid_argument("Error type 2");
    }

  
  double A_c = A_correct;
  double A_t = A_total;
  double B_c = B_correct;
  double B_t = B_total;
  if ((A_c / A_t) > (B_c / B_t)) {
    return true;
  }
  else {
    return false;
  }
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10 && pizzas <= 20 && is_weekend == false) {
    return true;
  }
  if (is_weekend == true && pizzas >= 10) {
    return true;
  }
  else {
    return false;
  }
}

int SumBetween(int low, int high) {
  int value = 0;
  if (high < low) {
    throw std::invalid_argument("Invalid arg");
  }
  if (low < 0 && high > 0) {
    if (low != INT32_MIN && abs(low) < high) {
      low = abs(low) + 1;
    }
    else if (low == INT32_MIN || abs(low) > high) {
      high = (-high) - 1;
    }
    else if (abs(low) == high) {
      return 0;
    }
  }
  for (int n = low; n < high; n++) {
    if (n > 0 && value > INT32_MAX - n) {
      throw std::overflow_error("Overflow pos");
    }
    if (n < 0 && value < INT32_MIN - n) {
      throw std::overflow_error("Overflow neg");
    }
    value += n;
  }
  if (high > 0 && value > INT32_MAX - high) {
      throw std::overflow_error("Overflow pos");
    }
  if (high < 0 && value < INT32_MIN - high) {
      throw std::overflow_error("Overflow neg");
    }
    value += high;
  return value;
}

int Product(int a, int b) {
  int value = 0;
  if ((a > INT32_MAX / b && b > 0) || (a < INT32_MAX / b && b < 0)) {
    throw std::overflow_error("input too positive");
  }
  if ((a < INT32_MIN / b && b > 0) || (a > INT32_MIN / b && b < 0)) {
    throw std::overflow_error("input too negative");
  }
  value = a * b;
  return value;
}