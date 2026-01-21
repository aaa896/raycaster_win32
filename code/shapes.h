#ifndef SHAPES_H_
#define SHAPES_H_
#include "mytypedefs.h"
#include "mymath_types.h"

typedef struct Linef32 Linef32;
struct Linef32 {
    V2f32 p1;
    V2f32 p2;
};

typedef struct Rectf32 Rectf32;
struct Rectf32{
    f32 x;
    f32 y;
    f32 width;
    f32 height;
};

#endif // SHAPES_H_
