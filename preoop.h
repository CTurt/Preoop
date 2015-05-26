#pragma once

#include <stdlib.h>

#define objectList(a, ...) _Generic((a), ##__VA_ARGS__)
#define objectEntry(a, b) a *: b##_##a

#define object(name, ...) typedef struct name name; struct name __VA_ARGS__
#define members

#define initCall(a, ...) init_##a(malloc(sizeof(a)), ##__VA_ARGS__)
#define new(a, ...) initCall(a, ##__VA_ARGS__)

#define method(a, b, ...) b##_##a(a *self, ##__VA_ARGS__)
#define invoke(a, b, ...) objects(a, b)(a, ##__VA_ARGS__)
