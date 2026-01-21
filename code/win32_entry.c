#include <windows.h>
#include "mytypedefs.h"
#include "game_state.h"
#include "game_entry.h"

#define UNICODE



LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: {
                           PostQuitMessage(0);
                           return 1;
                       }break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
    int screen_width = 1280;
    int screen_height = 720;

    HCURSOR hcursor = LoadCursor(NULL, IDC_WAIT);
    WNDCLASSEXW wndclass = {0};
    wchar_t *class_name = L"c_name";
    wndclass.cbSize = sizeof(WNDCLASSEXW);
    wndclass.style  = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = wnd_proc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = 0;
    wndclass.hCursor = hcursor;
    wndclass.hbrBackground = 0;
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = class_name;
    wndclass.hIconSm = 0;

    if (!RegisterClassExW(&wndclass)) {
        return -1;
    }
    int buffer_width =  1280;
    int buffer_height = 720;

    BITMAPINFOHEADER bitmap_info_header = {0};
    bitmap_info_header.biSize  = sizeof(BITMAPINFOHEADER);
    bitmap_info_header.biPlanes= 1;
    bitmap_info_header.biBitCount = 32;
    bitmap_info_header.biCompression = BI_RGB;
    bitmap_info_header.biWidth = buffer_width;
    bitmap_info_header.biHeight= buffer_height;
    BITMAPINFO bitmap_info =  {0};
    bitmap_info.bmiHeader = bitmap_info_header;




    wchar_t *window_name = L"window!!";
    HWND hwnd = CreateWindowExW(
            WS_EX_WINDOWEDGE,
            class_name,
            window_name,
            WS_SYSMENU| WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
            0,
            0,
            screen_width,
            screen_height,
            0,
            0,
            hInstance,
            0
            );
    if (!hwnd) {
        OutputDebugString("Hwnd Creation Failure!\n");
        return -1;
    }







    Game_State game_state = {0};
    game_state.running = true;

    MSG msg = { };

    while (game_state.running) {


        game_state.keyboard_input.space_pressed = false;
        game_state.keyboard_input.w_pressed = false;
        game_state.keyboard_input.a_pressed = false;
        game_state.keyboard_input.s_pressed = false;
        game_state.keyboard_input.d_pressed = false;
        game_state.keyboard_input.up_pressed = false;
        game_state.keyboard_input.left_pressed = false;
        game_state.keyboard_input.right_pressed = false;
        game_state.keyboard_input.down_pressed = false;
        while (PeekMessageW( &msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            switch (msg.message) {
                case WM_KEYUP:
                case WM_KEYDOWN: {
                                     u32 previously_down = msg.lParam & (1 << 30);
                                     u32 key_up = msg.lParam & (1 << 31);
                                     u8 vk_w = 0x57;
                                     u8 vk_a = 0x41;
                                     u8 vk_s = 0x53;
                                     u8 vk_d = 0x44;

                                     u8 vk_escape = 0x1B;

                                     u8 vk_left  = 0x25;
                                     u8 vk_up    = 0x26;
                                     u8 vk_right = 0x27;
                                     u8 vk_down  = 0x28;

                                     u8 vk_space = 0x20;

                                     if (msg.wParam == vk_w) {
                                         game_state.keyboard_input.w_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.w_pressed = false;
                                         } else {
                                             game_state.keyboard_input.w_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.w_pressed = false;
                                             game_state.keyboard_input.w_down = false;
                                         }
                                     } 

                                     if (msg.wParam == vk_a) {
                                         game_state.keyboard_input.a_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.a_pressed = false;
                                         } else {
                                             game_state.keyboard_input.a_pressed = true;
                                         }

                                         if (key_up) {
                                             game_state.keyboard_input.a_pressed = false;
                                             game_state.keyboard_input.a_down = false;
                                         }
                                     }

                                     if (msg.wParam == vk_s) {
                                         game_state.keyboard_input.s_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.s_pressed = false;
                                         } else {
                                             game_state.keyboard_input.s_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.s_pressed = false;
                                             game_state.keyboard_input.s_down = false;
                                         }

                                     } 

                                     if (msg.wParam == vk_d) {
                                         game_state.keyboard_input.d_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.d_pressed = false;
                                         } else {
                                             game_state.keyboard_input.d_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.d_pressed = false;
                                             game_state.keyboard_input.d_down = false;
                                         }

                                     } 

                                     if (msg.wParam == vk_up) {
                                         game_state.keyboard_input.up_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.up_pressed = false;
                                         } else {
                                             game_state.keyboard_input.up_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.up_pressed = false;
                                             game_state.keyboard_input.up_down = false;
                                         }
                                     } 

                                     if (msg.wParam == vk_left) {
                                         game_state.keyboard_input.left_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.left_pressed = false;
                                         } else {
                                             game_state.keyboard_input.left_pressed = true;
                                         }

                                         if (key_up) {
                                             game_state.keyboard_input.left_pressed = false;
                                             game_state.keyboard_input.left_down = false;
                                         }
                                     }

                                     if (msg.wParam == vk_down) {
                                         game_state.keyboard_input.down_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.down_pressed = false;
                                         } else {
                                             game_state.keyboard_input.down_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.down_pressed = false;
                                             game_state.keyboard_input.down_down = false;
                                         }

                                     } 

                                     if (msg.wParam == vk_right) {
                                         game_state.keyboard_input.right_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.right_pressed = false;
                                         } else {
                                             game_state.keyboard_input.right_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.right_pressed = false;
                                             game_state.keyboard_input.right_down = false;
                                         }

                                     } 

                                     if (msg.wParam == vk_escape) {
                                         game_state.keyboard_input.escape_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.escape_pressed = false;
                                         } else {
                                             game_state.keyboard_input.escape_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.escape_pressed = false;
                                             game_state.keyboard_input.escape_down = false;
                                         }

                                     } 

                                     if (msg.wParam == vk_space) {
                                         game_state.keyboard_input.space_down = true;
                                         if (previously_down) {
                                             game_state.keyboard_input.space_pressed = false;
                                         } else {
                                             game_state.keyboard_input.space_pressed = true;
                                         }
                                         if (key_up) {
                                             game_state.keyboard_input.space_pressed = false;
                                             game_state.keyboard_input.space_down = false;
                                         }
                                     }

                                 }break;
                case WM_QUIT: {
                                  OutputDebugString("WM close in loop\n");
                                  game_state.running = false;
                              }break;
            }
            DispatchMessage(&msg);
        }
        main_loop(&game_state);
        bitmap_info.bmiHeader.biWidth = game_state.pixel_buffer.width;
        bitmap_info.bmiHeader.biHeight= game_state.pixel_buffer.height;

        HDC hdc = GetDC( hwnd);
        if (!StretchDIBits(
                    hdc,
                    0,
                    0,
                    game_state.pixel_buffer.width,
                    game_state.pixel_buffer.height,
                    0,
                    0,
                    game_state.pixel_buffer.width,
                    game_state.pixel_buffer.height,
                    game_state.pixel_buffer.data,
                    &bitmap_info,
                    DIB_RGB_COLORS,
                    SRCCOPY)) {
            OutputDebugString("Error stretch dibits!\n");
            return -1;
        }
        ReleaseDC(hwnd, hdc);
    }


    return 0;
}
