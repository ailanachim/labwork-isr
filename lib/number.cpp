#include "number.h"
#include <cstring>
#include <iomanip>

uint2022_t from_uint(uint32_t i) {
  uint2022_t res{};
  for (int j = size - 1; j >= 0; j--) {
    res.array[j] = i % base;
    i = i / base;
  }

  return res;
}

uint2022_t from_string(const char *buff) {
  uint2022_t res{};
  memset(res.array, 0, size);

  size_t n = strlen(buff);
  for (int i = 0; i < n; i++) {
    size_t num = size - 1 - (n - i - 1) / len;
    res.array[num] = res.array[num] * 10 + buff[i] - '0';
  }

  return res;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t res{};

  size_t d = 0;
  for (int i = size - 1; i >= 0; i--) {
    res.array[i] = lhs.array[i] + rhs.array[i] + d;
    d = res.array[i] / base;
    res.array[i] = res.array[i] % base;
  }

  return res;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t res{};

  size_t d = 0;
  for (int i = size - 1; i >= 0; i--) {
      res.array[i] = base + lhs.array[i] - d - rhs.array[i];
      d = 1 - res.array[i] / base;
      res.array[i] = res.array[i] % base;
  }

  return res;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t res{};
  memset(res.array, 0, size);

  for (int j = size - 1; j >= 0; j--) {
    for (int i = size - 1; i >= 0; i--) {
      uint64_t c = static_cast<uint64_t>(lhs.array[i]) * static_cast<uint64_t>(rhs.array[j]);
      int num = j + i - size + 1;
      res.array[num] += c % base;
      res.array[num - 1] += c / base + res.array[num] / base;
      res.array[num] = res.array[num] % base;
    }
  }

  return res;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
  if (rhs == from_uint(0)) {
    std::cerr << "division by zero";
    abort();
  }

  uint2022_t res = from_uint(0);
  uint2022_t dividend = lhs;
  uint2022_t divider = rhs;
  int quotient = 0;
  int add_digit = 0;

  while (dividend >= divider * from_uint(10)) {
    divider = divider * from_uint(10);
    add_digit++;
  }

  while (dividend >= rhs) {
    while (dividend >= divider) { // quotient = dividend / divider; dividend %= divider
      dividend = dividend - divider;
      quotient++;
    }

    res = res * from_uint(10) + from_uint(quotient);
    quotient = 0;
    add_digit--;

    for (int i = size - 1; i > 0; i--) { // divider /= 10
      divider.array[i] = divider.array[i] / 10 + divider.array[i - 1] % 10 * (base / 10);
    }
    divider.array[0] = divider.array[0] / 10;
  }

  for (int i = 0; i <= add_digit; i++) {
    res = res * from_uint(10);
  }

  return res;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
  for (int i = 0; i < size; i++) {
    if (lhs.array[i] != rhs.array[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
  if (!(lhs == rhs)) {
    return true;
  }
  return false;
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs) {
  for (int i = 0; i < size; i++) {
    if (lhs.array[i] > rhs.array[i]) {
      return true;
    }
    if (lhs.array[i] < rhs.array[i]) {
      return false;
    }
  }
  return false;
}

bool operator>=(const uint2022_t& lhs, const uint2022_t& rhs) {
  if (lhs > rhs || lhs == rhs) {
    return true;
  } else {
    return false;
  }
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
  if (!(lhs >= rhs)) {
    return true;
  } else {
    return false;
  }
}

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs) {
  if (!(lhs > rhs)) {
    return true;
  } else {
    return false;
  }
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
  int i = 0;
  while (value.array[i] == 0 && i < size - 1) {
    i++;
  }
  stream << value.array[i++];

  while (i < size) {
    stream << std::setw(len) << std::setfill('0') << value.array[i];
    i++;
  }

  return stream;
}
