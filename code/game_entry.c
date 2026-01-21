#include "windows.h"
#include "game_state.h"
#include "platform.h"
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define SCREEN_COLS 24
#define SCREEN_ROWS 24


#define WALL_COLOR  0x3e3f43
#define EMPTY_COLOR 0x202020


typedef enum Enum_Map_Type Enum_Map_Type;
enum Enum_Map_Type {
    Enum_Map_Type_Empty,
    Enum_Map_Type_Wall,
};


int map_grid[SCREEN_ROWS][SCREEN_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


static V2f32 get_center_rectangle(Rectf32 *rect) {
    return (V2f32){.x = rect->x + rect->width/2.0, .y = rect->y + rect->height/2.0};
}


static void init_game_state(Game_State *state) {
    state->pixel_buffer.width  = SCREEN_WIDTH;
    state->pixel_buffer.height = SCREEN_HEIGHT;
    state->pixel_buffer.data = platform_alloc(state->pixel_buffer.width * state->pixel_buffer.height * sizeof(u32));
    state->init = true;
    state->player.rect.x = 100;
    state->player.rect.y = 100;
    state->player.rect.width = 10;
    state->player.rect.height = 10;
    state->player.rotation = 0;
    state->player.rotate_speed = 250;
    state->player.camera.dir_length_template = 30;
    state->player.camera.ray_count = state->player.camera.dir_length_template *2;
    state->player.camera.ray_length = state->player.camera.dir_length_template;
    state->player.camera.ray_lengths = platform_alloc(sizeof(float) * state->player.camera.ray_count);
    state->player.camera.dir_template = (Linef32) {
        .p1 = (V2f32){0,                            0},
            .p2 = (V2f32){state->player.camera.dir_length_template, 0}
    };
    state->player.camera.plane_template = (Linef32) {
        .p1 = (V2f32){state->player.camera.dir_template.p2.x, state->player.camera.dir_template.p2.y - state->player.camera.dir_length_template},
            .p2 = (V2f32){state->player.camera.dir_template.p2.x, state->player.camera.dir_template.p2.y + state->player.camera.dir_length_template},
    };
    state->player.camera.ray_template = platform_alloc(sizeof(Linef32) * state->player.camera.ray_count);
    state->player.camera.ray_current  = platform_alloc(sizeof(Linef32) * state->player.camera.ray_count);


    for (int i = 0; i <state->player.camera.ray_count; ++i) {
        float dx = state->player.camera.plane_template.p1.x - state->player.camera.dir_template.p1.x; 
        float dy = state->player.camera.plane_template.p1.y + i - state->player.camera.dir_template.p1.y; 
        float slope = dy/dx;
        float x1 = state->player.camera.dir_template.p1.x;
        float y1 = state->player.camera.dir_template.p1.y;

        float x = state->player.camera.ray_length + x1;
        float y = slope * (x - x1) + y1;
        state->player.camera.ray_template[i] = (Linef32) {
            .p1 = (V2f32){ x1, y1},
                .p2 = (V2f32){ x, y},
        };

    state->player.camera.ray_lengths[i] = 0;
    }


    state->player.starting_center = get_center_rectangle(&state->player.rect);
    state->draw_map = false;

    state->current_time = platform_get_time_milliseconds();
    state->prev_time = state->current_time;
    state->player.move_speed = 80;
}


static void clear_background(Pixel_Buffer *buffer, u32 color) {
    for (int row = 0; row < buffer->height; ++row) {
        for (int col = 0; col < buffer->width; ++col) {
            ((u32*)buffer->data)[ (row * buffer->width) + col] = color;
        }
    }
}


static void draw_rectangle(Pixel_Buffer *buffer, u32 color, int x, int y, int width, int height) {
    for (int row = y; row < height +y; ++row) {
        if (row >= buffer->height || row < 0) continue;
        for (int col = x; col < width + x; ++col) {
            if (col >= buffer->width || col < 0) continue;
            ((u32*)buffer->data)[ (row * buffer->width) + col] = color;
        }
    }
}


static void set_pixel(Pixel_Buffer *buffer, u32 color, int x, int y) {
    if (x >= buffer->width || x < 0) return;
    if (y >= buffer->height || y < 0) return;
    ((u32*)buffer->data)[( y * buffer->width) + x] = color;
}


static void draw_line(Pixel_Buffer *buffer, u32 color, int x1, int y1, int x2, int y2) {
    float change_x = x2 - x1;
    float abs_change_x = (change_x < 0 ? change_x * -1 : change_x);
    float change_y = y2 - y1;
    float abs_change_y = (change_y < 0 ? change_y * -1 : change_y);
    if (abs_change_x > abs_change_y) {
        int   x_increment = (change_x < 0 ? -1 : 1);
        float y_increment = change_y/abs_change_x;
        float y = y1;
        for (int x = x1 ; x != x2; x += x_increment) {
            set_pixel(buffer, color, x, y);
            y += y_increment;
        }
    } else {
        int   y_increment = (change_y < 0 ? -1 : 1);
        float x_increment = change_x/abs_change_y;
        float x = x1;
        for (int y = y1 ; y != y2; y += y_increment) {
            set_pixel(buffer, color, x, y);
            x += x_increment;
        }
    }
}


static void draw_line_linef32(Pixel_Buffer *buffer, u32 color, Linef32 *line) {
    draw_line(buffer, color, line->p1.x, line->p1.y, line->p2.x, line->p2.y) ;
}


static void draw_map_lines(Pixel_Buffer *buffer, u32 color) {
    int x_increment = SCREEN_WIDTH/SCREEN_COLS;
    int y_increment = SCREEN_HEIGHT/SCREEN_ROWS;
    for (int x = 0; x <SCREEN_WIDTH; x += x_increment) {
        draw_line(buffer, color, x, 0, x, SCREEN_HEIGHT -1);
        for (int y = 0; y < SCREEN_HEIGHT; y += y_increment) {
            draw_line(buffer, color, 0, y, SCREEN_WIDTH -1, y );
        }
    }
}


void draw_map_color(Pixel_Buffer *buffer) {
    int col_width = SCREEN_WIDTH/SCREEN_COLS;
    int row_width = SCREEN_HEIGHT/SCREEN_ROWS;
    for (int row = 0; row < SCREEN_ROWS; ++row) {
        for (int col = 0; col < SCREEN_COLS; ++col) {
            if (map_grid[row][col] == Enum_Map_Type_Empty) {
                draw_rectangle(buffer, EMPTY_COLOR, col * col_width, row * row_width, col_width, row_width);
            }else if (map_grid[row][col] == Enum_Map_Type_Wall) {
                draw_rectangle(buffer, WALL_COLOR, col * col_width, row * row_width, col_width, row_width);
            } 
        }
    }
}


#define PI 3.1415926535897932384626433832795028841971
static void rotate_line_point_linef32(Linef32 *line, float rotation, float cx,float cy) {

    rotation *= PI/180;
    float sin_rot = sin(rotation);
    float cos_rot = cos(rotation);

    float p1_x = line->p1.x - cx;
    float p1_y = line->p1.y - cy;
    line->p1.x = cos_rot * p1_x - (sin_rot * p1_y) + cx;
    line->p1.y = sin_rot * p1_x + (cos_rot * p1_y) + cy;

    float p2_x = line->p2.x - cx;
    float p2_y = line->p2.y - cy;
    line->p2.x = cos_rot * p2_x - (sin_rot * p2_y) + cx;
    line->p2.y = sin_rot * p2_x + (cos_rot * p2_y) + cy;
}

static V2f32 rotate_point_point(V2f32 point  , V2f32 origin, float rotation) {

    rotation *= PI/180;
    float sin_rot = sin(rotation);
    float cos_rot = cos(rotation);

    float cx = origin.x;
    float cy = origin.y;
    float p1_x = point.x - cx;
    float p1_y = point.y - cy;
    V2f32 rv ={ .x = (cos_rot * p1_x - (sin_rot * p1_y) + cx),
        .y =  (sin_rot * p1_x + (cos_rot * p1_y) + cy)};
    return rv;

}
static void rotate_line_origin_linef32(Linef32 *line, float rotation) {

    rotation *= PI/180;
    float sin_rot = sin(rotation);
    float cos_rot = cos(rotation);

    float p1_x = line->p1.x;
    float p1_y = line->p1.y;
    line->p1.x = cos_rot * p1_x - (sin_rot * p1_y);
    line->p1.y = sin_rot * p1_x + (cos_rot * p1_y);

    float p2_x = line->p2.x ;
    float p2_y = line->p2.y ;
    line->p2.x = cos_rot * p2_x - (sin_rot * p2_y);
    line->p2.y = sin_rot * p2_x + (cos_rot * p2_y);
}


static void draw_circle_lines(Pixel_Buffer *buffer, u32 color, float x, float y, float radius) {
    int px = radius;
    int py = 0;
    float radius_squared = radius * radius;
    while (px > py) {
        set_pixel(buffer, color, py + x,  px +y);
        set_pixel(buffer, color,-py + x,  px +y);
        set_pixel(buffer, color, py + x, -px +y);
        set_pixel(buffer, color,-py + x, -px +y);

        set_pixel(buffer, color, px + x,  py +y);
        set_pixel(buffer, color, px + x, -py +y);
        set_pixel(buffer, color,-px + x,  py +y);
        set_pixel(buffer, color,-px + x, -py +y);


        float y_mid = py;
        float x_mid = px - 0.5;
        float new_r_sq = x_mid * x_mid + y_mid * y_mid;
        if (new_r_sq > radius_squared) {
            px -=1;
        }
        py += 1;
    }
}


static void update_camera_rays(Camera *camera, V2f32 translation, float rotation) {
    camera->dir_current          = camera->dir_template;
    camera->dir_length_current   = camera->dir_length_template;
    camera->plane_current = camera->plane_template;

    for (int i = 0; i <camera->ray_count; ++i) {
        camera->ray_current[i] = camera->ray_template[i];
        rotate_line_origin_linef32(&camera->ray_current[i], rotation);
        camera->ray_current[i].p1.x += translation.x;
        camera->ray_current[i].p1.y += translation.y;
        camera->ray_current[i].p2.x += translation.x;
        camera->ray_current[i].p2.y += translation.y;
    }

    rotate_line_origin_linef32(&camera->dir_current, rotation);
    rotate_line_origin_linef32(&camera->plane_current, rotation);
    camera->dir_current.p1.x += translation.x;
    camera->dir_current.p1.y += translation.y;
    camera->dir_current.p2.x += translation.x;
    camera->dir_current.p2.y += translation.y;

    camera->plane_current.p1.x += translation.x;
    camera->plane_current.p1.y += translation.y;
    camera->plane_current.p2.x += translation.x;
    camera->plane_current.p2.y += translation.y;



}



void main_loop(Game_State *state) {
    if (!state->init) {
        init_game_state(state);
    }
    state->dt = state->current_time - state->prev_time;

    if ( state->keyboard_input.escape_down ) {state->running = false;}

    float player_move = state->player.move_speed * state->dt;

    float player_rotate_speed = state->player.rotate_speed * state->dt;
    if (state->keyboard_input.w_down) {
    }
    if (state->keyboard_input.s_down) {
    }
    if (state->keyboard_input.a_down) {
        state->player.rotation += player_rotate_speed;
    }
    if (state->keyboard_input.d_down) {
        state->player.rotation -= player_rotate_speed;
    }

    Linef32 forward = { {0,0}, {1,0}};
    Linef32 left = { {0,0}, {0,1}};
    Linef32 right = { {0,0}, {0,-1}};
    rotate_line_origin_linef32(&forward, state->player.rotation);
    rotate_line_origin_linef32(&left, state->player.rotation );
    rotate_line_origin_linef32(&right,   state->player.rotation );

    if (state->keyboard_input.up_down) {
        state->player.rect.y += player_move * forward.p2.y;
        state->player.rect.x +=    player_move * forward.p2.x;
    }
    if (state->keyboard_input.down_down) {
        state->player.rect.y -= player_move * forward.p2.y;
        state->player.rect.x -=    player_move * forward.p2.x;
    }

    if (state->keyboard_input.left_down) {
        state->player.rect.y +=    player_move * left.p2.y;
        state->player.rect.x +=    player_move * left.p2.x;
    }

    if (state->keyboard_input.right_down) {
        state->player.rect.y +=  player_move * right.p2.y;
        state->player.rect.x +=  player_move * right.p2.x;
    }

    if (state->keyboard_input.space_pressed) {
        OutputDebugString("Toggle!\n");
        if (state->draw_map) {
            state->draw_map = false;
        } else {
            state->draw_map = true;
        }
    }

    while (state->player.rotation < 0) {
        state->player.rotation += 360;
    }
    while (state->player.rotation > 360) {
        state->player.rotation -= 360;
    }






    update_camera_rays(&state->player.camera, get_center_rectangle(&state->player.rect), state->player.rotation);
    clear_background(&state->pixel_buffer, 0x114488);


    if (state->draw_map) {
        draw_map_color(&state->pixel_buffer);
        draw_map_lines(&state->pixel_buffer, 0x4e4a4a);
        draw_rectangle(&state->pixel_buffer, 0xff0000, state->player.rect.x, state->player.rect.y, state->player.rect.width, state->player.rect.height);

        draw_line_linef32(&state->pixel_buffer, 0x777777, &state->player.camera.dir_current);
        draw_line_linef32(&state->pixel_buffer, 0xaa7777, &state->player.camera.plane_current);
    }


    for (int i = 0; i <state->player.camera.ray_count; i+=1) {
        V2f32 origin_view = {state->player.camera.ray_current[i].p2.x -  state->player.camera.ray_current[i].p1.x, state->player.camera.ray_current[i].p2.y -  state->player.camera.ray_current[i].p1.y};
        Linef32 origin_line = {(V2f32){0,0}, origin_view};
        float tile_width  = (float)SCREEN_WIDTH/SCREEN_COLS;
        float tile_height = (float)SCREEN_HEIGHT/SCREEN_ROWS;
        float slope =  ( origin_view.y / origin_view.x );
        float dx = origin_view.x;
        float dy = origin_view.x;

        int start_col = state->player.camera.ray_current[i].p1.x/tile_width;
        int start_row = state->player.camera.ray_current[i].p1.y/tile_height;

        bool right_dir = origin_view.x > 0;
        float start_x = state->player.camera.ray_current[i].p1.x;
        float x_step = tile_width;
        bool x_match = false;
        float x_radius = 0;
        if (right_dir) {
            float  x = start_col * tile_width;
            while (x < state->player.camera.ray_current[i].p2.x) {
                x += tile_width;
            }
            start_x = x;
        } else {

            float  x = start_col * tile_width;
            while (x > state->player.camera.ray_current[i].p2.x) {
                x -= tile_width;
            }
            x_step *= -1;
            start_x = x;
        }
        for (int x  = start_x; x != (start_x + x_step * SCREEN_COLS); x+= x_step) {
            float y = slope * ( x  - state->player.camera.ray_current[i].p1.x ) + state->player.camera.ray_current[i].p1.y;

            int col = x /tile_width;
            int row = y /tile_height ;
            if (!right_dir) {col -=1;}
            if (state->draw_map) {
                draw_rectangle(&state->pixel_buffer, 0x998833, col * tile_width, row  * tile_height, tile_width/2, tile_height/2);
                draw_circle_lines(&state->pixel_buffer, 0x00ff00, x, y, 4);
            }
            if (row >= 0 && row < SCREEN_ROWS && col >= 0 && col < SCREEN_COLS) {
                if (map_grid[row][col] == 1) {

                    if (state->draw_map) {
                    draw_rectangle(&state->pixel_buffer, 0x993388, col * tile_width, row  * tile_height, tile_width/2, tile_height/2);
                    }

                    float new_dx =x - state->player.camera.ray_current[i].p1.x ;
                    float new_dy = y - state->player.camera.ray_current[i].p1.y;
                    x_radius = new_dx * new_dx + new_dy * new_dy;
                    x_match = true;
                    state->player.camera.ray_lengths[i] = sqrt(x_radius);
                    break;
                }
            }

        }

        bool up_dir    = origin_view.y > 0;
        float start_y = state->player.camera.ray_current[i].p1.y;
        float y_step = tile_height;
        if (up_dir) {
            float  y = start_row * tile_height;
            while (y < state->player.camera.ray_current[i].p2.y) {
                y += tile_height;
            }
            start_y = y;
        } else {

            float  y = start_row * tile_height;
            while (y > state->player.camera.ray_current[i].p2.y) {
                y -= tile_height;
            }
            y_step *= -1;
            start_y = y;
        }
        for (int y  = start_y; y != (start_y + y_step * SCREEN_ROWS); y+= y_step) {
            if (state->draw_map){
                draw_circle_lines(&state->pixel_buffer, 0xff0000, state->player.camera.ray_current[i].p1.x, state->player.camera.ray_current[i].p1.y, 8);
                draw_circle_lines(&state->pixel_buffer, 0xff00ff, state->player.camera.ray_current[i].p2.x, state->player.camera.ray_current[i].p2.y, 8);
            }
            if (!slope) break;
         
            float x = (y - state->player.camera.ray_current[i].p1.y )/slope  + state->player.camera.ray_current[i].p1.x;
            int col = x /tile_width;
            int row = y /tile_height ;
            if (!up_dir) {row -=1;}

                float new_dx =x -  state->player.camera.ray_current[i].p1.x ;
                float new_dy = y - state->player.camera.ray_current[i].p1.y;
                float new_radius = new_dx * new_dx + new_dy * new_dy;
                if (x_match) {
                    if (state->draw_map) {
                        draw_circle_lines(&state->pixel_buffer, 0xff0000, state->player.camera.ray_current[i].p1.x, state->player.camera.ray_current[i].p1.y, 4);
                        draw_circle_lines(&state->pixel_buffer, 0xff0000, x, y, 4);
                    }
                    if (new_radius > x_radius) break;
                }

            if (state->draw_map) {
            draw_rectangle(&state->pixel_buffer, 0x998800, col * tile_width, row  * tile_height, tile_width/2, tile_height/2);
            draw_circle_lines(&state->pixel_buffer, 0x0000ff, x, y, 4);
            }

            if (row >= 0 && row < SCREEN_ROWS && col >= 0 && col < SCREEN_COLS) {
                if (map_grid[row][col] == 1) {

                    if (state->draw_map) {
                        draw_rectangle(&state->pixel_buffer, 0xcc3388, col * tile_width, row  * tile_height, tile_width/2, tile_height/2);
                    }

                    state->player.camera.ray_lengths[i] = sqrt(new_radius);
                    break;
                }
            }
        }

        if (state->draw_map) {
            draw_line_linef32(&state->pixel_buffer, 0xaa7777, &state->player.camera.ray_current[i]);
            draw_line_linef32(&state->pixel_buffer, 0xaa77ff, &origin_line);
            set_pixel(&state->pixel_buffer, 0x0000ff, state->player.camera.ray_current[i].p1.x, state->player.camera.ray_current[i].p1.y);
        }
    }

    if (!state->draw_map) {
        draw_rectangle(&state->pixel_buffer, 0x123212, 0, 0, state->pixel_buffer.width, state->pixel_buffer.height/2.0);
        for (int x = 0; x < state->pixel_buffer.width; ++x) {
            int ray_idx = state->player.camera.ray_count * x/(float)state->pixel_buffer.width ;
            float height = state->player.camera.ray_lengths[state->player.camera.ray_count -1 - ray_idx];
            height =  7000/height;
            float by = state->pixel_buffer.height/2. - height/2.;
            float ty = state->pixel_buffer.height/2. + height/2.;
            Linef32 line= { (V2f32){x, by}, {x, ty}};
            u8 r = 0x14;
            u8 g = 0x22;
            u8 b = 0x33;
            float brightness =  height/30;
            if ((r * brightness) > 255) r = 255;
            else r *= brightness;
            //g *= brightness;
            //b *= brightness;
            u32 color = (r << 16) | (g <<8) | b   ;
            draw_line_linef32(&state->pixel_buffer,color,  &line);
        }
    }
    




    state->prev_time = state->current_time;
    state->current_time = platform_get_time_milliseconds();

}
