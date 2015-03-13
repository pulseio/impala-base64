#include <cstring>
#include <stdexcept>

static const char encode_vector[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

static const uint8_t decode_vector[] = { 
  65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
  65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
  65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 62, 65, 65, 65, 63,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 65, 65, 65, 64, 65, 65,
  65,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 65, 65, 65, 65, 65,
  65, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
  41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 65, 65, 65, 65, 65
};

struct triad {
  uint8_t b0:2, a:6;
  uint8_t c0:4, b1:4;
  uint8_t d:6, c1:2;
};

#include <iostream>

std::string encode(const uint8_t* data, size_t size) {
  std::string result;

  result.reserve((size + 2) / 3 * 4);
  
  auto p = reinterpret_cast<const triad*>(data);
  auto e = reinterpret_cast<const triad*>(data + (size / 3) * 3);

  while (p < e) {
    result += encode_vector[p->a];
    result += encode_vector[p->b0 << 4 | p->b1];
    result += encode_vector[p->c0 << 2 | p->c1];
    result += encode_vector[p->d];

    ++p;
  }

  triad t { 0, 0, 0, 0, 0, 0 };

  auto len = (data + size) - reinterpret_cast<const uint8_t*>(p);

  std::copy(reinterpret_cast<const uint8_t*>(p), data + size, reinterpret_cast<uint8_t*>(&t));

  if (len > 0) {
    result += encode_vector[p->a];
    result += encode_vector[p->b0 << 4 | p->b1];
  }
  if (len == 1) {
    result += '=';
    result += '=';
  }
  else if (len == 2) {
    result += encode_vector[p->c0 << 2 | p->c1];
    result += '=';
  }

  return result;
}

inline uint8_t decode_char(const uint8_t** p, const uint8_t* e) {
  while (*p < e) {
    auto c = decode_vector[*(*p)++ & 0x7f];
    if (c != 65) return c;
  }
    
  return 64;
}

std::string decode(const uint8_t* data, size_t size) {
  auto p = data;
  auto e = data + size;

  std::string result;

  result.reserve((size + 3) / 4 * 3);

  while (p != e) {
    auto a = decode_char(&p, e);
    auto b = decode_char(&p, e);
    auto c = decode_char(&p, e);
    auto d = decode_char(&p, e);

    triad t { 0, 0, 0, 0, 0, 0 };

    if (a == 64) break;

    t.a = a;

    if (b == 64) break;

    t.b0 = b >> 4;
    result += *reinterpret_cast<char*>(&t);
    t.b1 = b & 15;

    if (c == 64) break;

    t.c0 = c >> 2;
    result += *(reinterpret_cast<char*>(&t) + 1);
    t.c1 = c & 3;

    if (d == 64) break;

    t.d = d;
    result += *(reinterpret_cast<char*>(&t) + 2);
  }

  result.shrink_to_fit();

  return result;
}
