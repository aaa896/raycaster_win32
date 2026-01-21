#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "mytypedefs.h"
#include "mymath_types.h"
#include "shapes.h"

typedef struct Pixel_Buffer Pixel_Buffer;
struct Pixel_Buffer {
    u32 width;
    u32 height;
    void *data;
};


typedef struct Keyboard_Input Keyboard_Input ;
struct Keyboard_Input {
    bool w_down;
    bool w_pressed;

    bool a_down;
    bool a_pressed;

    bool s_down;
    bool s_pressed;

    bool d_down;
    bool d_pressed;

    bool up_down;
    bool up_pressed;

    bool left_down;
    bool left_pressed;

    bool down_down;
    bool down_pressed;

    bool right_down;
    bool right_pressed;

    bool space_down;
    bool space_pressed;

    bool escape_down;
    bool escape_pressed;
};



typedef enum Enum_Draw_Mode Enum_Draw_Mode;
enum Enum_Draw_Mode {
    Enum_Draw_Mode_Map,
    Enum_Draw_Mode_Cast,
};


typedef struct Camera Camera;
struct Camera {

    Linef32 dir_template;
    float   dir_length_template;
    Linef32 plane_template;
    float   max_ray_length;

    int     ray_count;
    Linef32 *ray_template;
    Linef32 *ray_current;
    float    ray_length ;
    float *   ray_lengths;

    Linef32 dir_current;
    float   dir_length_current;
    Linef32 plane_current;
    
};


typedef struct Player Player;
struct Player {
    Rectf32 rect;
    Camera  camera;
    float rotation;
    float move_speed;
    float rotate_speed;
    V2f32 starting_center;

};

typedef struct Game_State Game_State;
struct Game_State {
    bool running;
    bool init;

    Pixel_Buffer pixel_buffer;
    Keyboard_Input keyboard_input;

    bool draw_map;

    Player player;

    f64 current_time;
    f64 prev_time;
    f64 dt;

};



#endif // GAME_STATE_H_
