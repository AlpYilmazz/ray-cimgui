/**********************************************************************************************
*
*   raycimgui * ImGui-cimgui-raylib integration
*
*   The MIT License (MIT)
*   
*   Copyright (c) 2015 Stephan Dilly
*   
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*   
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*   
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <math.h>

#include "imgui_impl_raylib.h"

#include "raylib.h"
#include "rlgl.h"

#include "raycimgui.h"

static ImGuiMouseCursor CurrentMouseCursor = ImGuiMouseCursor_COUNT;
static MouseCursor MouseCursorMap[ImGuiMouseCursor_COUNT];

ImGuiContext* GlobalContext = NULL;

static const KeyboardKey RaylibKeys[] = {
    KEY_APOSTROPHE,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_ZERO,
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR,
    KEY_FIVE,
    KEY_SIX,
    KEY_SEVEN,
    KEY_EIGHT,
    KEY_NINE,
    KEY_SEMICOLON,
    KEY_EQUAL,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_SPACE,
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_TAB,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_LOCK,
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_LEFT_SHIFT,
    KEY_LEFT_CONTROL,
    KEY_LEFT_ALT,
    KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_CONTROL,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,
    KEY_KB_MENU,
    KEY_LEFT_BRACKET,
    KEY_BACKSLASH,
    KEY_RIGHT_BRACKET,
    KEY_GRAVE,
    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_DECIMAL,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT,
    KEY_KP_ADD,
    KEY_KP_ENTER,
    KEY_KP_EQUAL
};
static int RaylibKeyCount = sizeof(RaylibKeys)/sizeof(RaylibKeys[0]);

static ImGuiKey RaylibKeyToImGui(KeyboardKey key) {
    switch(key) {
    case KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
    case KEY_COMMA: return ImGuiKey_Comma;
    case KEY_MINUS: return ImGuiKey_Minus;
    case KEY_PERIOD: return ImGuiKey_Period;
    case KEY_SLASH: return ImGuiKey_Slash;
    case KEY_ZERO: return ImGuiKey_0;
    case KEY_ONE: return ImGuiKey_1;
    case KEY_TWO: return ImGuiKey_2;
    case KEY_THREE: return ImGuiKey_3;
    case KEY_FOUR: return ImGuiKey_4;
    case KEY_FIVE: return ImGuiKey_5;
    case KEY_SIX: return ImGuiKey_6;
    case KEY_SEVEN: return ImGuiKey_7;
    case KEY_EIGHT: return ImGuiKey_8;
    case KEY_NINE: return ImGuiKey_9;
    case KEY_SEMICOLON: return ImGuiKey_Semicolon;
    case KEY_EQUAL: return ImGuiKey_Equal;
    case KEY_A: return ImGuiKey_A;
    case KEY_B: return ImGuiKey_B;
    case KEY_C: return ImGuiKey_C;
    case KEY_D: return ImGuiKey_D;
    case KEY_E: return ImGuiKey_E;
    case KEY_F: return ImGuiKey_F;
    case KEY_G: return ImGuiKey_G;
    case KEY_H: return ImGuiKey_H;
    case KEY_I: return ImGuiKey_I;
    case KEY_J: return ImGuiKey_J;
    case KEY_K: return ImGuiKey_K;
    case KEY_L: return ImGuiKey_L;
    case KEY_M: return ImGuiKey_M;
    case KEY_N: return ImGuiKey_N;
    case KEY_O: return ImGuiKey_O;
    case KEY_P: return ImGuiKey_P;
    case KEY_Q: return ImGuiKey_Q;
    case KEY_R: return ImGuiKey_R;
    case KEY_S: return ImGuiKey_S;
    case KEY_T: return ImGuiKey_T;
    case KEY_U: return ImGuiKey_U;
    case KEY_V: return ImGuiKey_V;
    case KEY_W: return ImGuiKey_W;
    case KEY_X: return ImGuiKey_X;
    case KEY_Y: return ImGuiKey_Y;
    case KEY_Z: return ImGuiKey_Z;
    case KEY_SPACE: return ImGuiKey_Space;
    case KEY_ESCAPE: return ImGuiKey_Escape;
    case KEY_ENTER: return ImGuiKey_Enter;
    case KEY_TAB: return ImGuiKey_Tab;
    case KEY_BACKSPACE: return ImGuiKey_Backspace;
    case KEY_INSERT: return ImGuiKey_Insert;
    case KEY_DELETE: return ImGuiKey_Delete;
    case KEY_RIGHT: return ImGuiKey_RightArrow;
    case KEY_LEFT: return ImGuiKey_LeftArrow;
    case KEY_DOWN: return ImGuiKey_DownArrow;
    case KEY_UP: return ImGuiKey_UpArrow;
    case KEY_PAGE_UP: return ImGuiKey_PageUp;
    case KEY_PAGE_DOWN: return ImGuiKey_PageDown;
    case KEY_HOME: return ImGuiKey_Home;
    case KEY_END: return ImGuiKey_End;
    case KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
    case KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
    case KEY_NUM_LOCK: return ImGuiKey_NumLock;
    case KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
    case KEY_PAUSE: return ImGuiKey_Pause;
    case KEY_F1: return ImGuiKey_F1;
    case KEY_F2: return ImGuiKey_F2;
    case KEY_F3: return ImGuiKey_F3;
    case KEY_F4: return ImGuiKey_F4;
    case KEY_F5: return ImGuiKey_F5;
    case KEY_F6: return ImGuiKey_F6;
    case KEY_F7: return ImGuiKey_F7;
    case KEY_F8: return ImGuiKey_F8;
    case KEY_F9: return ImGuiKey_F9;
    case KEY_F10: return ImGuiKey_F10;
    case KEY_F11: return ImGuiKey_F11;
    case KEY_F12: return ImGuiKey_F12;
    case KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
    case KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
    case KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
    case KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
    case KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
    case KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
    case KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
    case KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
    case KEY_KB_MENU: return ImGuiKey_Menu;
    case KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
    case KEY_BACKSLASH: return ImGuiKey_Backslash;
    case KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
    case KEY_GRAVE: return ImGuiKey_GraveAccent;
    case KEY_KP_0: return ImGuiKey_Keypad0;
    case KEY_KP_1: return ImGuiKey_Keypad1;
    case KEY_KP_2: return ImGuiKey_Keypad2;
    case KEY_KP_3: return ImGuiKey_Keypad3;
    case KEY_KP_4: return ImGuiKey_Keypad4;
    case KEY_KP_5: return ImGuiKey_Keypad5;
    case KEY_KP_6: return ImGuiKey_Keypad6;
    case KEY_KP_7: return ImGuiKey_Keypad7;
    case KEY_KP_8: return ImGuiKey_Keypad8;
    case KEY_KP_9: return ImGuiKey_Keypad9;
    case KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
    case KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
    case KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
    case KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
    case KEY_KP_ADD: return ImGuiKey_KeypadAdd;
    case KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
    case KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
    default: return ImGuiKey_None;
    };
}

static MouseCursor ImGuiCursorToRaylib(ImGuiMouseCursor cursor) {
    switch(cursor) {
    case ImGuiMouseCursor_Arrow: return MOUSE_CURSOR_ARROW;
    case ImGuiMouseCursor_TextInput: return MOUSE_CURSOR_IBEAM;
    case ImGuiMouseCursor_Hand: return MOUSE_CURSOR_POINTING_HAND;
    case ImGuiMouseCursor_ResizeAll: return MOUSE_CURSOR_RESIZE_ALL;
    case ImGuiMouseCursor_ResizeEW: return MOUSE_CURSOR_RESIZE_EW;
    case ImGuiMouseCursor_ResizeNESW: return MOUSE_CURSOR_RESIZE_NESW;
    case ImGuiMouseCursor_ResizeNS: return MOUSE_CURSOR_RESIZE_NS;
    case ImGuiMouseCursor_ResizeNWSE: return MOUSE_CURSOR_RESIZE_NWSE;
    case ImGuiMouseCursor_NotAllowed: return MOUSE_CURSOR_NOT_ALLOWED;
    default: return MOUSE_CURSOR_DEFAULT;
    };
}

static bool LastFrameFocused = false;

static bool LastControlPressed = false;
static bool LastShiftPressed = false;
static bool LastAltPressed = false;
static bool LastSuperPressed = false;

// internal only functions
static bool rligIsControlDown() { return IsKeyDown(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL); }
static bool rligIsShiftDown() { return IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT); }
static bool rligIsAltDown() { return IsKeyDown(KEY_RIGHT_ALT) || IsKeyDown(KEY_LEFT_ALT); }
static bool rligIsSuperDown() { return IsKeyDown(KEY_RIGHT_SUPER) || IsKeyDown(KEY_LEFT_SUPER); }

typedef struct {
    int empty[0];
} ImGui_ImplRaylib_Data;

ImGui_ImplRaylib_Data* ImGui_ImplRaylib_GetBackendData() {
    return igGetCurrentContext() ? igGetPlatformIO_Nil()->Renderer_RenderState : NULL;
}

void ImGui_ImplRaylib_CreateBackendData() {
    if (!igGetCurrentContext() || igGetPlatformIO_Nil()->Renderer_RenderState)
        return;

    igGetPlatformIO_Nil()->Renderer_RenderState = MemAlloc(sizeof(ImGui_ImplRaylib_Data));
}

void ImGui_ImplRaylib_FreeBackendData() {
    if (!igGetCurrentContext())
        return;

    MemFree(igGetPlatformIO_Nil()->Renderer_RenderState);
}


Vector2 GetDisplayScale()
{
#if defined(__EMSCRIPTEN__)
    return Vector2{ 1,1 };
#else
    return GetWindowScaleDPI();
#endif
}

static const char* GetClipTextCallback(ImGuiContext* ctx)
{
    return GetClipboardText();
}

static void SetClipTextCallback(ImGuiContext* ctx, const char* text)
{
    SetClipboardText(text);
}

static void ImGuiNewFrame(float deltaTime)
{
    ImGuiIO* io = igGetIO_Nil();
    ImGui_ImplRaylib_Data* platData = ImGui_ImplRaylib_GetBackendData();
    if (!platData) {
        ImGui_ImplRaylib_CreateBackendData();
        platData = ImGui_ImplRaylib_GetBackendData();
        if (!platData) {
            return;
        }
    }

    Vector2 resolutionScale = GetDisplayScale();

#ifndef PLATFORM_DRM
    if (IsWindowFullscreen()) {
        int monitor = GetCurrentMonitor();
        io->DisplaySize.x = (float)(GetMonitorWidth(monitor));
        io->DisplaySize.y = (float)(GetMonitorHeight(monitor));
    }
    else {
        io->DisplaySize.x = (float)(GetScreenWidth());
        io->DisplaySize.y = (float)(GetScreenHeight());
    }

#if !defined(__APPLE__)
    if (!IsWindowState(FLAG_WINDOW_HIGHDPI)) {
        resolutionScale = (Vector2){ 1, 1 };
    }
#endif
#else
    io->DisplaySize.x = (float)(GetScreenWidth());
    io->DisplaySize.y = (float)(GetScreenHeight());
#endif

    io->DisplayFramebufferScale = (ImVec2){ resolutionScale.x, resolutionScale.y };

    if (deltaTime <= 0) {
        deltaTime = 0.001f;
    }

    io->DeltaTime = deltaTime;

    if (igGetIO_Nil()->BackendFlags & ImGuiBackendFlags_HasMouseCursors) {
        if ((io->ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) == 0) {
            ImGuiMouseCursor imgui_cursor = igGetMouseCursor();
            if (imgui_cursor != CurrentMouseCursor || io->MouseDrawCursor) {
                CurrentMouseCursor = imgui_cursor;
                if (io->MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None) {
                    HideCursor();
                }
                else {
                    ShowCursor();

                    if (!(io->ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange))
                    {
                        SetMouseCursor((imgui_cursor > -1 && imgui_cursor < ImGuiMouseCursor_COUNT) ? MouseCursorMap[imgui_cursor] : MOUSE_CURSOR_DEFAULT);
                    }
                }
            }
        }
    }
}

static void ImGuiTriangleVert(const ImDrawVert* idx_vert) {
    Color c = {
       .r = (unsigned char)(idx_vert->col >> 0),
       .g = (unsigned char)(idx_vert->col >> 8),
       .b = (unsigned char)(idx_vert->col >> 16),
       .a = (unsigned char)(idx_vert->col >> 24),
    };
    rlColor4ub(c.r, c.g, c.b, c.a);
    rlTexCoord2f(idx_vert->uv.x, idx_vert->uv.y);
    rlVertex2f(idx_vert->pos.x, idx_vert->pos.y);
}

static void ImGuiRenderTriangles(unsigned int count, int indexStart, const ImVector_ImDrawIdx* indexBuffer, const ImVector_ImDrawVert* vertBuffer, ImTextureID texturePtr) {
    if (count < 3) {
        return;
    }

    unsigned int textureId = (unsigned int)(texturePtr);

    rlBegin(RL_TRIANGLES);
    rlSetTexture(textureId);

    for (unsigned int i = 0; i <= (count - 3); i += 3) {
        ImDrawIdx indexA = indexBuffer->Data[indexStart + i];
        ImDrawIdx indexB = indexBuffer->Data[indexStart + i + 1];
        ImDrawIdx indexC = indexBuffer->Data[indexStart + i + 2];

        ImDrawVert vertexA = vertBuffer->Data[indexA];
        ImDrawVert vertexB = vertBuffer->Data[indexB];
        ImDrawVert vertexC = vertBuffer->Data[indexC];

        ImGuiTriangleVert(&vertexA);
        ImGuiTriangleVert(&vertexB);
        ImGuiTriangleVert(&vertexC);
    }
    rlEnd();
}

static void EnableScissor(float x, float y, float width, float height) {
    rlEnableScissorTest();
    ImGuiIO* io = igGetIO_Nil();

    ImVec2 scale = io->DisplayFramebufferScale;
#if !defined(__APPLE__)
    if (!IsWindowState(FLAG_WINDOW_HIGHDPI)) {
        scale.x = 1;
        scale.y = 1;
    }
#endif

    rlScissor((int)(x * scale.x),
        (int)((io->DisplaySize.y - (int)(y + height)) * scale.y),
        (int)(width * scale.x),
        (int)(height * scale.y));
}

static void SetupMouseCursors(void) {
    MouseCursorMap[ImGuiMouseCursor_Arrow] = MOUSE_CURSOR_ARROW;
    MouseCursorMap[ImGuiMouseCursor_TextInput] = MOUSE_CURSOR_IBEAM;
    MouseCursorMap[ImGuiMouseCursor_Hand] = MOUSE_CURSOR_POINTING_HAND;
    MouseCursorMap[ImGuiMouseCursor_ResizeAll] = MOUSE_CURSOR_RESIZE_ALL;
    MouseCursorMap[ImGuiMouseCursor_ResizeEW] = MOUSE_CURSOR_RESIZE_EW;
    MouseCursorMap[ImGuiMouseCursor_ResizeNESW] = MOUSE_CURSOR_RESIZE_NESW;
    MouseCursorMap[ImGuiMouseCursor_ResizeNS] = MOUSE_CURSOR_RESIZE_NS;
    MouseCursorMap[ImGuiMouseCursor_ResizeNWSE] = MOUSE_CURSOR_RESIZE_NWSE;
    MouseCursorMap[ImGuiMouseCursor_NotAllowed] = MOUSE_CURSOR_NOT_ALLOWED;
}

// TODO: find better approach
static ImFontConfig ImFontConfig_constructer(void) {
    return (ImFontConfig) {
        .FontDataOwnedByAtlas = true,
        .OversampleH = 0, // Auto == 1 or 2 depending on size
        .OversampleV = 0, // Auto == 1
        .GlyphMaxAdvanceX = FLT_MAX,
        .RasterizerMultiply = 1.0f,
        .RasterizerDensity = 1.0f,
        .EllipsisChar = 0,
    };
}

void SetupFontAwesome(void) {
#ifndef NO_FONT_AWESOME
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config = ImFontConfig_constructer();
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;

    icons_config.GlyphMaxAdvanceX = FLT_MAX;
    icons_config.RasterizerMultiply = 1.0f;
    icons_config.OversampleH = 2;
    icons_config.OversampleV = 1;

    icons_config.GlyphRanges = icons_ranges;

    ImGuiIO* io = igGetIO_Nil();

    float size = FONT_AWESOME_ICON_SIZE;
#if !defined(__APPLE__)
    if (!IsWindowState(FLAG_WINDOW_HIGHDPI)) {
        size *= GetDisplayScale().y;
    }

    icons_config.RasterizerMultiply = GetDisplayScale().y;
#endif

    ImFontAtlas_AddFontFromMemoryCompressedTTF(io->Fonts, (void*)fa_solid_900_compressed_data, fa_solid_900_compressed_size, size, &icons_config, icons_ranges);
#endif
}

void SetupBackend(void) {
    ImGuiIO* io = igGetIO_Nil();
    io->BackendPlatformName = "imgui_impl_raylib";
    io->BackendFlags |= ImGuiBackendFlags_HasGamepad | ImGuiBackendFlags_HasSetMousePos | ImGuiBackendFlags_RendererHasTextures;

#ifndef PLATFORM_DRM
    io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
#endif

    io->MousePos = (ImVec2){0, 0};

    ImGuiPlatformIO* platformIO = igGetPlatformIO_Nil();

    platformIO->Platform_SetClipboardTextFn = SetClipTextCallback;
    platformIO->Platform_GetClipboardTextFn = GetClipTextCallback;

    platformIO->Platform_ClipboardUserData = NULL;

    ImGui_ImplRaylib_CreateBackendData();
}

void rligEndInitImGui(void)
{
    igSetCurrentContext(GlobalContext);

    SetupFontAwesome();

    SetupMouseCursors();

    SetupBackend();
}

#if 0
static void SetupKeymap(void)
{
    if (!RaylibKeyMap.empty())
        return;

    // build up a map of raylib keys to ImGuiKeys
    RaylibKeyMap[KEY_APOSTROPHE] = ImGuiKey_Apostrophe;
    RaylibKeyMap[KEY_COMMA] = ImGuiKey_Comma;
    RaylibKeyMap[KEY_MINUS] = ImGuiKey_Minus;
    RaylibKeyMap[KEY_PERIOD] = ImGuiKey_Period;
    RaylibKeyMap[KEY_SLASH] = ImGuiKey_Slash;
    RaylibKeyMap[KEY_ZERO] = ImGuiKey_0;
    RaylibKeyMap[KEY_ONE] = ImGuiKey_1;
    RaylibKeyMap[KEY_TWO] = ImGuiKey_2;
    RaylibKeyMap[KEY_THREE] = ImGuiKey_3;
    RaylibKeyMap[KEY_FOUR] = ImGuiKey_4;
    RaylibKeyMap[KEY_FIVE] = ImGuiKey_5;
    RaylibKeyMap[KEY_SIX] = ImGuiKey_6;
    RaylibKeyMap[KEY_SEVEN] = ImGuiKey_7;
    RaylibKeyMap[KEY_EIGHT] = ImGuiKey_8;
    RaylibKeyMap[KEY_NINE] = ImGuiKey_9;
    RaylibKeyMap[KEY_SEMICOLON] = ImGuiKey_Semicolon;
    RaylibKeyMap[KEY_EQUAL] = ImGuiKey_Equal;
    RaylibKeyMap[KEY_A] = ImGuiKey_A;
    RaylibKeyMap[KEY_B] = ImGuiKey_B;
    RaylibKeyMap[KEY_C] = ImGuiKey_C;
    RaylibKeyMap[KEY_D] = ImGuiKey_D;
    RaylibKeyMap[KEY_E] = ImGuiKey_E;
    RaylibKeyMap[KEY_F] = ImGuiKey_F;
    RaylibKeyMap[KEY_G] = ImGuiKey_G;
    RaylibKeyMap[KEY_H] = ImGuiKey_H;
    RaylibKeyMap[KEY_I] = ImGuiKey_I;
    RaylibKeyMap[KEY_J] = ImGuiKey_J;
    RaylibKeyMap[KEY_K] = ImGuiKey_K;
    RaylibKeyMap[KEY_L] = ImGuiKey_L;
    RaylibKeyMap[KEY_M] = ImGuiKey_M;
    RaylibKeyMap[KEY_N] = ImGuiKey_N;
    RaylibKeyMap[KEY_O] = ImGuiKey_O;
    RaylibKeyMap[KEY_P] = ImGuiKey_P;
    RaylibKeyMap[KEY_Q] = ImGuiKey_Q;
    RaylibKeyMap[KEY_R] = ImGuiKey_R;
    RaylibKeyMap[KEY_S] = ImGuiKey_S;
    RaylibKeyMap[KEY_T] = ImGuiKey_T;
    RaylibKeyMap[KEY_U] = ImGuiKey_U;
    RaylibKeyMap[KEY_V] = ImGuiKey_V;
    RaylibKeyMap[KEY_W] = ImGuiKey_W;
    RaylibKeyMap[KEY_X] = ImGuiKey_X;
    RaylibKeyMap[KEY_Y] = ImGuiKey_Y;
    RaylibKeyMap[KEY_Z] = ImGuiKey_Z;
    RaylibKeyMap[KEY_SPACE] = ImGuiKey_Space;
    RaylibKeyMap[KEY_ESCAPE] = ImGuiKey_Escape;
    RaylibKeyMap[KEY_ENTER] = ImGuiKey_Enter;
    RaylibKeyMap[KEY_TAB] = ImGuiKey_Tab;
    RaylibKeyMap[KEY_BACKSPACE] = ImGuiKey_Backspace;
    RaylibKeyMap[KEY_INSERT] = ImGuiKey_Insert;
    RaylibKeyMap[KEY_DELETE] = ImGuiKey_Delete;
    RaylibKeyMap[KEY_RIGHT] = ImGuiKey_RightArrow;
    RaylibKeyMap[KEY_LEFT] = ImGuiKey_LeftArrow;
    RaylibKeyMap[KEY_DOWN] = ImGuiKey_DownArrow;
    RaylibKeyMap[KEY_UP] = ImGuiKey_UpArrow;
    RaylibKeyMap[KEY_PAGE_UP] = ImGuiKey_PageUp;
    RaylibKeyMap[KEY_PAGE_DOWN] = ImGuiKey_PageDown;
    RaylibKeyMap[KEY_HOME] = ImGuiKey_Home;
    RaylibKeyMap[KEY_END] = ImGuiKey_End;
    RaylibKeyMap[KEY_CAPS_LOCK] = ImGuiKey_CapsLock;
    RaylibKeyMap[KEY_SCROLL_LOCK] = ImGuiKey_ScrollLock;
    RaylibKeyMap[KEY_NUM_LOCK] = ImGuiKey_NumLock;
    RaylibKeyMap[KEY_PRINT_SCREEN] = ImGuiKey_PrintScreen;
    RaylibKeyMap[KEY_PAUSE] = ImGuiKey_Pause;
    RaylibKeyMap[KEY_F1] = ImGuiKey_F1;
    RaylibKeyMap[KEY_F2] = ImGuiKey_F2;
    RaylibKeyMap[KEY_F3] = ImGuiKey_F3;
    RaylibKeyMap[KEY_F4] = ImGuiKey_F4;
    RaylibKeyMap[KEY_F5] = ImGuiKey_F5;
    RaylibKeyMap[KEY_F6] = ImGuiKey_F6;
    RaylibKeyMap[KEY_F7] = ImGuiKey_F7;
    RaylibKeyMap[KEY_F8] = ImGuiKey_F8;
    RaylibKeyMap[KEY_F9] = ImGuiKey_F9;
    RaylibKeyMap[KEY_F10] = ImGuiKey_F10;
    RaylibKeyMap[KEY_F11] = ImGuiKey_F11;
    RaylibKeyMap[KEY_F12] = ImGuiKey_F12;
    RaylibKeyMap[KEY_LEFT_SHIFT] = ImGuiKey_LeftShift;
    RaylibKeyMap[KEY_LEFT_CONTROL] = ImGuiKey_LeftCtrl;
    RaylibKeyMap[KEY_LEFT_ALT] = ImGuiKey_LeftAlt;
    RaylibKeyMap[KEY_LEFT_SUPER] = ImGuiKey_LeftSuper;
    RaylibKeyMap[KEY_RIGHT_SHIFT] = ImGuiKey_RightShift;
    RaylibKeyMap[KEY_RIGHT_CONTROL] = ImGuiKey_RightCtrl;
    RaylibKeyMap[KEY_RIGHT_ALT] = ImGuiKey_RightAlt;
    RaylibKeyMap[KEY_RIGHT_SUPER] = ImGuiKey_RightSuper;
    RaylibKeyMap[KEY_KB_MENU] = ImGuiKey_Menu;
    RaylibKeyMap[KEY_LEFT_BRACKET] = ImGuiKey_LeftBracket;
    RaylibKeyMap[KEY_BACKSLASH] = ImGuiKey_Backslash;
    RaylibKeyMap[KEY_RIGHT_BRACKET] = ImGuiKey_RightBracket;
    RaylibKeyMap[KEY_GRAVE] = ImGuiKey_GraveAccent;
    RaylibKeyMap[KEY_KP_0] = ImGuiKey_Keypad0;
    RaylibKeyMap[KEY_KP_1] = ImGuiKey_Keypad1;
    RaylibKeyMap[KEY_KP_2] = ImGuiKey_Keypad2;
    RaylibKeyMap[KEY_KP_3] = ImGuiKey_Keypad3;
    RaylibKeyMap[KEY_KP_4] = ImGuiKey_Keypad4;
    RaylibKeyMap[KEY_KP_5] = ImGuiKey_Keypad5;
    RaylibKeyMap[KEY_KP_6] = ImGuiKey_Keypad6;
    RaylibKeyMap[KEY_KP_7] = ImGuiKey_Keypad7;
    RaylibKeyMap[KEY_KP_8] = ImGuiKey_Keypad8;
    RaylibKeyMap[KEY_KP_9] = ImGuiKey_Keypad9;
    RaylibKeyMap[KEY_KP_DECIMAL] = ImGuiKey_KeypadDecimal;
    RaylibKeyMap[KEY_KP_DIVIDE] = ImGuiKey_KeypadDivide;
    RaylibKeyMap[KEY_KP_MULTIPLY] = ImGuiKey_KeypadMultiply;
    RaylibKeyMap[KEY_KP_SUBTRACT] = ImGuiKey_KeypadSubtract;
    RaylibKeyMap[KEY_KP_ADD] = ImGuiKey_KeypadAdd;
    RaylibKeyMap[KEY_KP_ENTER] = ImGuiKey_KeypadEnter;
    RaylibKeyMap[KEY_KP_EQUAL] = ImGuiKey_KeypadEqual;
}
#endif

static void SetupGlobals(void) {
    LastFrameFocused = IsWindowFocused();
    LastControlPressed = false;
    LastShiftPressed = false;
    LastAltPressed = false;
    LastSuperPressed = false;
}

void rligBeginInitImGui(void) {
    SetupGlobals();
    if (GlobalContext == NULL) {
        GlobalContext = igCreateContext(NULL);
    }
    // SetupKeymap();

    ImGuiIO* io = igGetIO_Nil();

    ImFontConfig defaultConfig = ImFontConfig_constructer();

    const int DefaultFonSize = 13;

    defaultConfig.SizePixels = DefaultFonSize;
#if !defined(__APPLE__)
    if (!IsWindowState(FLAG_WINDOW_HIGHDPI)) {
        defaultConfig.SizePixels = ceilf(defaultConfig.SizePixels * GetDisplayScale().y);
    }

    defaultConfig.RasterizerMultiply = GetDisplayScale().y;
#endif

    defaultConfig.PixelSnapH = true;
    ImFontAtlas_AddFontDefault(io->Fonts, &defaultConfig);
}

void rligSetup(bool dark) {
    rligBeginInitImGui();

    if (dark) {
        igStyleColorsDark(NULL);
    }
    else {
        igStyleColorsLight(NULL);
    }

    rligEndInitImGui();
}

void rligBegin(void) {
    igSetCurrentContext(GlobalContext);
    rligBeginDelta(GetFrameTime());
}

void rligBeginDelta(float deltaTime) {
    igSetCurrentContext(GlobalContext);

    ImGuiNewFrame(deltaTime);
    ImGui_ImplRaylib_ProcessEvents();
    igNewFrame();
}

void rligEnd(void) {
    igSetCurrentContext(GlobalContext);
    igRender();
    ImGui_ImplRaylib_RenderDrawData(igGetDrawData());
}

void rligShutdown(void) {
    if (GlobalContext == NULL) {
        return;
    }

    igSetCurrentContext(GlobalContext);
    ImGui_ImplRaylib_Shutdown();

    igDestroyContext(GlobalContext);
    GlobalContext = NULL;
}

void rligImage(const Texture* image) {
    if (!image) {
        return;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }
    
    ImTextureRef tex_ref = { ._TexData = NULL, ._TexID = (ImTextureID)(image->id) };
    ImVec2 image_size = { (float)(image->width), (float)(image->height) };
    ImVec2 uv0 = {0, 0};
    ImVec2 uv1 = {1, 1};
    igImage(tex_ref, image_size, uv0, uv1);
}

bool rligImageButton(const char* name, const Texture* image) {
    if (!image) {
        return false;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }
    
    ImTextureRef tex_ref = { ._TexData = NULL, ._TexID = (ImTextureID)(image->id) };
    ImVec2 image_size = { (float)(image->width), (float)(image->height) };
    ImVec2 uv0 = {0, 0};
    ImVec2 uv1 = {1, 1};
    ImVec4 bg_col = {0, 0, 0, 0};
    ImVec4 tint_col = {1, 1, 1, 1};
    return igImageButton(name, tex_ref, image_size, uv0, uv1, bg_col, tint_col);
}

bool rligImageButtonSize(const char* name, const Texture* image, Vector2 size) {
    if (!image) {
        return false;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }

    ImTextureRef tex_ref = { ._TexData = NULL, ._TexID = (ImTextureID)(image->id) };
    ImVec2 image_size = { size.x, size.y };
    ImVec2 uv0 = {0, 0};
    ImVec2 uv1 = {1, 1};
    ImVec4 bg_col = {0, 0, 0, 0};
    ImVec4 tint_col = {1, 1, 1, 1};
    return igImageButton(name, tex_ref, image_size, uv0, uv1, bg_col, tint_col);
}

void rligImageSize(const Texture* image, int width, int height) {
    if (!image) {
        return;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }
    
    ImTextureRef tex_ref = { ._TexData = NULL, ._TexID = (ImTextureID)(image->id) };
    ImVec2 image_size = { (float)(width), (float)(height) };
    ImVec2 uv0 = {0, 0};
    ImVec2 uv1 = {1, 1};
    igImage(tex_ref, image_size, uv0, uv1);
}

void rligImageSizeV(const Texture* image, Vector2 size) {
    if (!image) {
        return;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }
    
    ImTextureRef tex_ref = { ._TexData = NULL, ._TexID = (ImTextureID)(image->id) };
    ImVec2 image_size = { size.x, size.y };
    ImVec2 uv0 = {0, 0};
    ImVec2 uv1 = {1, 1};
    igImage(tex_ref, image_size, uv0, uv1);
}

void rligImageRect(const Texture* image, int destWidth, int destHeight, Rectangle sourceRect) {
    if (!image) {
        return;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }
    
    ImVec2 uv0;
    ImVec2 uv1;

    if (sourceRect.width < 0)
    {
        uv0.x = -sourceRect.x / image->width;
        uv1.x = (uv0.x - (float)(fabsf(sourceRect.width) / image->width));
    }
    else
    {
        uv0.x = sourceRect.x / image->width;
        uv1.x = uv0.x + (float)(sourceRect.width / image->width);
    }

    if (sourceRect.height < 0)
    {
        uv0.y = -sourceRect.y / image->height;
        uv1.y = (uv0.y - fabsf(sourceRect.height) / image->height);
    }
    else
    {
        uv0.y = sourceRect.y / image->height;
        uv1.y = uv0.y + sourceRect.height / image->height;
    }

    ImTextureRef tex_ref = { ._TexData = NULL, ._TexID = (ImTextureID)(image->id) };
    ImVec2 image_size = { (float)(destWidth), (float)(destHeight) };
    igImage(tex_ref, image_size, uv0, uv1);
}

void rligImageRenderTexture(const RenderTexture* image) {
    if (!image) {
        return;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }
    
    rligImageRect(
        &image->texture,
        image->texture.width,
        image->texture.height,
        (Rectangle){ 0,0, (float)(image->texture.width), (float)(-image->texture.height) }
    );
}

void rligImageRenderTextureFit(const RenderTexture* image, bool center) {
    if (!image) {
        return;
    }
    
    if (GlobalContext) {
        igSetCurrentContext(GlobalContext);
    }

    ImVec2 area;
    igGetContentRegionAvail(&area);

    float scale =  area.x / image->texture.width;

    float y = image->texture.height * scale;
    if (y > area.y)
    {
        scale = area.y / image->texture.height;
    }

    int sizeX = (int)(image->texture.width * scale);
    int sizeY = (int)(image->texture.height * scale);

    if (center)
    {
        igSetCursorPosX(0);
        igSetCursorPosX(area.x/2 - sizeX/2);
        igSetCursorPosY(igGetCursorPosY() + (area.y / 2 - sizeY / 2));
    }

    rligImageRect(
        &image->texture,
        sizeX,
        sizeY,
        (Rectangle){ 0,0, (float)(image->texture.width), (float)(-image->texture.height) }
    );
}

// raw ImGui backend API
bool ImGui_ImplRaylib_Init(void)
{
    SetupGlobals();

    // SetupKeymap();

    SetupMouseCursors();

    SetupBackend();

    return true;
}


void ImGui_ImplRaylib_Shutdown()
{
    ImGuiIO* io = igGetIO_Nil();
    ImGuiPlatformIO* pio = igGetPlatformIO_Nil();

    for (int i = 0; i < pio->Textures.Size; i++) {
        ImTextureData* texture = pio->Textures.Data[i];
        if (texture->Status != ImTextureStatus_Destroyed) {
            Texture* backendData = (Texture*)texture->BackendUserData;
            if (backendData) { // && IsTextureValid(*backendData) raylib-5.5
                UnloadTexture(*backendData);
            }
            if (backendData) {
                MemFree(backendData);
            }

            texture->BackendUserData = NULL;
            texture->Status = ImTextureStatus_Destroyed;
            ImTextureData_SetTexID(texture, 0); // ImTextureID_Invalid
        }
    }

    ImGui_ImplRaylib_FreeBackendData();
}

void ImGui_ImplRaylib_NewFrame(void) {
    ImGuiNewFrame(GetFrameTime());
}

void ImGui_ImplRaylib_UpdateTexture(ImTextureData* tex) {
    switch (tex->Status) {
        case ImTextureStatus_OK:
        case ImTextureStatus_Destroyed:
        default:
            break;

        case ImTextureStatus_WantCreate:
        {
            Image img = { 0 };
            img.width = tex->Width;
            img.height = tex->Height;

            img.format = tex->Format == ImTextureFormat_Alpha8 ? PIXELFORMAT_UNCOMPRESSED_GRAYSCALE : PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
            img.mipmaps = 1;
            img.data = ImTextureData_GetPixels(tex);

            Texture* texture = (Texture*)MemAlloc(sizeof(Texture));
            *texture = LoadTextureFromImage(img);

            tex->BackendUserData = texture;
            ImTextureData_SetTexID(tex, (ImTextureID)(texture->id));
            tex->Status = ImTextureStatus_OK;
            break;
        }

        case ImTextureStatus_WantUpdates:
        {
            Texture* texture = (Texture*)tex->BackendUserData;
            if (!texture) {
                break;
            }

            UpdateTexture(*texture, ImTextureData_GetPixels(tex));

            tex->Status = ImTextureStatus_OK;
            break;
        }

        case ImTextureStatus_WantDestroy:
        {
            Texture* texture = (Texture*)tex->BackendUserData;
            if (!texture) {
                break;
            }

            UnloadTexture(*texture);
            MemFree(texture);

            tex->Status = ImTextureStatus_Destroyed;
            tex->BackendUserData = NULL;
            ImTextureData_SetTexID(tex, 0); // ImTextureID_Invalid
            break;
        }
    }
}

void ImGui_ImplRaylib_RenderDrawData(ImDrawData* draw_data) {
    if (draw_data->Textures != NULL) {
        for (int i = 0; i < draw_data->Textures->Size; i++) {
            ImTextureData* tex = draw_data->Textures->Data[i];
            if (tex->Status != ImTextureStatus_OK) {
                ImGui_ImplRaylib_UpdateTexture(tex);
            }
        }
    }

    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling();

    for (int l = 0; l < draw_data->CmdListsCount; l++) {
        ImDrawList* commandList = draw_data->CmdLists.Data[l];

        for (int cmd_i = 0; cmd_i < commandList->CmdBuffer.Size; cmd_i++) {
            ImDrawCmd* cmd = &commandList->CmdBuffer.Data[cmd_i];

            EnableScissor(
                cmd->ClipRect.x - draw_data->DisplayPos.x,
                cmd->ClipRect.y - draw_data->DisplayPos.y,
                cmd->ClipRect.z - (cmd->ClipRect.x - draw_data->DisplayPos.x),
                cmd->ClipRect.w - (cmd->ClipRect.y - draw_data->DisplayPos.y)
            );
            if (cmd->UserCallback != NULL) {
                cmd->UserCallback(commandList, cmd);
                continue;
            }

            ImTextureID texId = ImDrawCmd_GetTexID(cmd);
            ImGuiRenderTriangles(cmd->ElemCount, cmd->IdxOffset, &commandList->IdxBuffer, &commandList->VtxBuffer, texId);
            rlDrawRenderBatchActive();
        }
    }

    rlSetTexture(0);
    rlDisableScissorTest();
    rlEnableBackfaceCulling();
}

void HandleGamepadButtonEvent(ImGuiIO* io, GamepadButton button, ImGuiKey key)
{
    if (IsGamepadButtonPressed(0, button)) {
        ImGuiIO_AddKeyEvent(io, key, true);
    }
    else if (IsGamepadButtonReleased(0, button)) {
        ImGuiIO_AddKeyEvent(io, key, false);
    }
}

void HandleGamepadStickEvent(ImGuiIO* io, GamepadAxis axis, ImGuiKey negKey, ImGuiKey posKey)
{
    const float deadZone = 0.20f;

    float axisValue = GetGamepadAxisMovement(0, axis);

    ImGuiIO_AddKeyAnalogEvent(io, negKey, axisValue < -deadZone, axisValue < -deadZone ? -axisValue : 0);
    ImGuiIO_AddKeyAnalogEvent(io, posKey, axisValue > deadZone, axisValue > deadZone ? axisValue : 0);
}

bool ImGui_ImplRaylib_ProcessEvents(void)
{
    ImGuiIO* io = igGetIO_Nil();

    bool focused = IsWindowFocused();
    if (focused != LastFrameFocused) {
        ImGuiIO_AddFocusEvent(io, focused);
    }
    LastFrameFocused = focused;

    // handle the modifyer key events so that shortcuts work
    bool ctrlDown = rligIsControlDown();
    if (ctrlDown != LastControlPressed) {
        ImGuiIO_AddKeyEvent(io, ImGuiMod_Ctrl, ctrlDown);
    }
    LastControlPressed = ctrlDown;

    bool shiftDown = rligIsShiftDown();
    if (shiftDown != LastShiftPressed) {
        ImGuiIO_AddKeyEvent(io, ImGuiMod_Shift, shiftDown);
    }
    LastShiftPressed = shiftDown;

    bool altDown = rligIsAltDown();
    if (altDown != LastAltPressed) {
        ImGuiIO_AddKeyEvent(io, ImGuiMod_Alt, altDown);
    }
    LastAltPressed = altDown;

    bool superDown = rligIsSuperDown();
    if (superDown != LastSuperPressed) {
        ImGuiIO_AddKeyEvent(io, ImGuiMod_Super, superDown);
    }
    LastSuperPressed = superDown;

    // walk the keymap and check for up and down events
    // for (const auto keyItr : RaylibKeyMap) {
    for (int i = 0; i < RaylibKeyCount; i++) {
        KeyboardKey key = RaylibKeys[i];
        ImGuiKey igKey = RaylibKeyToImGui(key);

        if (IsKeyReleased(key)) {
            ImGuiIO_AddKeyEvent(io, igKey, false);
        }
        else if(IsKeyPressed(key)) {
            ImGuiIO_AddKeyEvent(io, igKey, true);
        }
    }

    if (io->WantCaptureKeyboard) {
        // add the text input in order
        unsigned int pressed = GetCharPressed();
        while (pressed != 0) {
            ImGuiIO_AddInputCharacter(io, pressed);
            pressed = GetCharPressed();
        }
    }

    bool processsMouse = focused;

#if defined(RLIMGUI_ALWAYS_TRACK_MOUSE)
    processsMouse = true;
#endif

    if (processsMouse) {
        if (!io->WantSetMousePos) {
            ImGuiIO_AddMousePosEvent(io, (float)(GetMouseX()), (float)(GetMouseY()));
        }

        int mbs[][2] = {
            { MOUSE_BUTTON_LEFT, ImGuiMouseButton_Left },
            { MOUSE_BUTTON_RIGHT, ImGuiMouseButton_Right },
            { MOUSE_BUTTON_MIDDLE, ImGuiMouseButton_Middle },
            { MOUSE_BUTTON_FORWARD, ImGuiMouseButton_Middle + 1 },
            { MOUSE_BUTTON_BACK, ImGuiMouseButton_Middle + 2 },
        };
        int mbs_size = sizeof(mbs) / sizeof(mbs[0]);
        for (int mb_i = 0; mb_i < mbs_size; mb_i++) {
            int rayMouse = mbs[mb_i][0];
            int imGuiMouse = mbs[mb_i][1];

            if (IsMouseButtonPressed(rayMouse)) {
                ImGuiIO_AddMouseButtonEvent(io, imGuiMouse, true);
            }
            else if (IsMouseButtonReleased(rayMouse)) {
                ImGuiIO_AddMouseButtonEvent(io, imGuiMouse, false);
            }
        }

        {
            Vector2 mouseWheel = GetMouseWheelMoveV();
            ImGuiIO_AddMouseWheelEvent(io, mouseWheel.x, mouseWheel.y);
        }
    }
    else
    {
        ImGuiIO_AddMousePosEvent(io, FLT_MIN, FLT_MIN);
    }

    if (io->ConfigFlags & ImGuiConfigFlags_NavEnableGamepad && IsGamepadAvailable(0)) {
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_FACE_UP, ImGuiKey_GamepadDpadUp);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, ImGuiKey_GamepadDpadRight);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_FACE_DOWN, ImGuiKey_GamepadDpadDown);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_FACE_LEFT, ImGuiKey_GamepadDpadLeft);

        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_FACE_UP, ImGuiKey_GamepadFaceUp);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, ImGuiKey_GamepadFaceLeft);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_FACE_DOWN, ImGuiKey_GamepadFaceDown);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_FACE_LEFT, ImGuiKey_GamepadFaceRight);

        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_TRIGGER_1, ImGuiKey_GamepadL1);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_TRIGGER_2, ImGuiKey_GamepadL2);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_TRIGGER_1, ImGuiKey_GamepadR1);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_TRIGGER_2, ImGuiKey_GamepadR2);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_LEFT_THUMB, ImGuiKey_GamepadL3);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_RIGHT_THUMB, ImGuiKey_GamepadR3);

        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_MIDDLE_LEFT, ImGuiKey_GamepadStart);
        HandleGamepadButtonEvent(io, GAMEPAD_BUTTON_MIDDLE_RIGHT, ImGuiKey_GamepadBack);

        // left stick
        HandleGamepadStickEvent(io, GAMEPAD_AXIS_LEFT_X, ImGuiKey_GamepadLStickLeft, ImGuiKey_GamepadLStickRight);
        HandleGamepadStickEvent(io, GAMEPAD_AXIS_LEFT_Y, ImGuiKey_GamepadLStickUp, ImGuiKey_GamepadLStickDown);

        // right stick
        HandleGamepadStickEvent(io, GAMEPAD_AXIS_RIGHT_X, ImGuiKey_GamepadRStickLeft, ImGuiKey_GamepadRStickRight);
        HandleGamepadStickEvent(io, GAMEPAD_AXIS_RIGHT_Y, ImGuiKey_GamepadRStickUp, ImGuiKey_GamepadRStickDown);
    }

    return true;
}
