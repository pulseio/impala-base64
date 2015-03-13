#ifndef _PULSE_BASE64_H_
#define _PULSE_BASE64_H_

#include <string>

extern std::string encode(const uint8_t* data, size_t size);
extern std::string decode(const uint8_t* data, size_t size);

#endif
