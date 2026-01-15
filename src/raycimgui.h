#pragma once

#include "raylib.h"

#ifndef NO_FONT_AWESOME
    #include "fontawesome/FA6FreeSolidFontData.h"
    #include "fontawesome/IconsFontAwesome6.h"
    #ifndef FONT_AWESOME_ICON_SIZE
        #define FONT_AWESOME_ICON_SIZE 11
    #endif
#endif

// High level API. This API is designed in the style of raylib and meant to work with reaylib code.
// It will manage it's own ImGui context and call common ImGui functions (like NewFrame and Render) for you
// for a lower level API that matches the other ImGui platforms, please see imgui_impl_raylib.h

/// <summary>
/// Sets up ImGui, loads fonts and themes
/// Calls ImGui_ImplRaylib_Init and sets the theme. Will install Font awesome by default
/// </summary>
/// <param name="darkTheme">when true(default) the dark theme is used, when false the light theme is used</param>
void rligSetup(bool darkTheme);

/// <summary>
/// Starts a new ImGui Frame
/// Calls ImGui_ImplRaylib_NewFrame, ImGui_ImplRaylib_ProcessEvents, and ImGui::NewFrame together
/// </summary>
void rligBegin(void);

/// <summary>
/// Ends an ImGui frame and submits all ImGui drawing to raylib for processing.
/// Calls ImGui:Render, an d ImGui_ImplRaylib_RenderDrawData to draw to the current raylib render target
/// </summary>
void rligEnd(void);

/// <summary>
/// Cleanup ImGui and unload font atlas
/// Calls ImGui_ImplRaylib_Shutdown
/// </summary>
void rligShutdown(void);

// Advanced StartupAPI

/// <summary>
/// Custom initialization. Not needed if you call rligSetup. Only needed if you want to add custom setup code.
/// must be followed by rligEndInitImGui
/// Called by ImGui_ImplRaylib_Init, and does the first part of setup, before fonts are rendered
/// </summary>
void rligBeginInitImGui(void);

/// <summary>
/// End Custom initialization. Not needed if you call rligSetup. Only needed if you want to add custom setup code.
/// must be proceeded by rligBeginInitImGui
/// Called by ImGui_ImplRaylib_Init and does the second part of setup, and renders fonts.
/// </summary>
void rligEndInitImGui(void);

// Advanced Update API

/// <summary>
/// Starts a new ImGui Frame with a specified delta time
/// </summary>
/// <param name="dt">delta time, any value < 0 will use raylib GetFrameTime</param>
void rligBeginDelta(float deltaTime);

// ImGui Image API extensions
// Purely for convenience in working with raylib textures as images.
// If you want to call ImGui image functions directly, simply pass them the pointer to the texture.

/// <summary>
/// Draw a texture as an image in an ImGui Context
/// Uses the current ImGui Cursor position and the full texture size.
/// </summary>
/// <param name="image">The raylib texture to draw</param>
void rligImage(const Texture *image);

/// <summary>
/// Draw a texture as an image in an ImGui Context at a specific size
/// Uses the current ImGui Cursor position and the specified width and height
/// The image will be scaled up or down to fit as needed
/// </summary>
/// <param name="image">The raylib texture to draw</param>
/// <param name="width">The width of the drawn image</param>
/// <param name="height">The height of the drawn image</param>
void rligImageSize(const Texture *image, int width, int height);

/// <summary>
/// Draw a texture as an image in an ImGui Context at a specific size
/// Uses the current ImGui Cursor position and the specified size
/// The image will be scaled up or down to fit as needed
/// </summary>
/// <param name="image">The raylib texture to draw</param>
/// <param name="size">The size of drawn image</param>
void rligImageSizeV(const Texture* image, Vector2 size);

/// <summary>
/// Draw a portion texture as an image in an ImGui Context at a defined size
/// Uses the current ImGui Cursor position and the specified size
/// The image will be scaled up or down to fit as needed
/// </summary>
/// <param name="image">The raylib texture to draw</param>
/// <param name="destWidth">The width of the drawn image</param>
/// <param name="destHeight">The height of the drawn image</param>
/// <param name="sourceRect">The portion of the texture to draw as an image. Negative values for the width and height will flip the image</param>
void rligImageRect(const Texture* image, int destWidth, int destHeight, Rectangle sourceRect);

/// <summary>
/// Draws a render texture as an image an ImGui Context, automatically flipping the Y axis so it will show correctly on screen
/// </summary>
/// <param name="image">The render texture to draw</param>
void rligImageRenderTexture(const RenderTexture* image);

/// <summary>
/// Draws a render texture as an image an ImGui Context, automatically flipping the Y axis so it will show correctly on screen
/// Fits the render texture to the available content area
/// </summary>
/// <param name="image">The render texture to draw</param>
/// <param name="center">When true the image will be centered in the content area</param>
void rligImageRenderTextureFit(const RenderTexture* image, bool center);

/// <summary>
/// Draws a texture as an image button in an ImGui context. Uses the current ImGui cursor position and the full size of the texture
/// </summary>
/// <param name="name">The display name and ImGui ID for the button</param>
/// <param name="image">The texture to draw</param>
/// <returns>True if the button was clicked</returns>
bool rligImageButton(const char* name, const Texture* image);

/// <summary>
/// Draws a texture as an image button in an ImGui context. Uses the current ImGui cursor position and the specified size.
/// </summary>
/// <param name="name">The display name and ImGui ID for the button</param>
/// <param name="image">The texture to draw</param>
/// <param name="size">The size of the button</param>
/// <returns>True if the button was clicked</returns>
bool rligImageButtonSize(const char* name, const Texture* image, Vector2 size);
