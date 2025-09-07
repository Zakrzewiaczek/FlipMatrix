#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_box.h>
#include "max7219.h"

typedef enum {
    FlipMatrixMainMenuScene,
    FlipMatrixConnectScene,
    FlipMatrixHowToConnectScene,
    FlipMatrixAboutScene,
    FlipMatrixSceneCount,
} FlipMatrixScene;

typedef enum {
    FlipMatrixSubmenuView,
    FlipMatrixWidgetView,
    FlipMatrixTextBoxView,
} FlipMatrixView;

typedef struct App {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Widget* widget;
    TextBox* text_box;
    FuriString* text_box_store;
    MAX7219* max7219;
    bool matrix_connected;
} App;

typedef enum {
    FlipMatrixMainMenuSceneConnect,
    FlipMatrixMainMenuSceneHowToConnect,
    FlipMatrixMainMenuSceneAbout,
} FlipMatrixMainMenuSceneIndex;

typedef enum {
    FlipMatrixMainMenuSceneConnectEvent,
    FlipMatrixMainMenuSceneHowToConnectEvent,
    FlipMatrixMainMenuSceneAboutEvent,
} FlipMatrixMainMenuEvent;

// Text constants
#define FLIPMATRIX_HOW_TO_CONNECT_TEXT                  \
    "How to Connect MAX7219\n\n"                        \
    "Wiring:\n"                                         \
    "Flipper Pin 2 (MOSI) -> Display Pin DIN\n"         \
    "Flipper Pin 4 (CS)   -> Display Pin CS\n"          \
    "Flipper Pin 5 (SCK)  -> Display Pin SCK\n"         \
    "Flipper Pin 9 (3V3)  -> Display Pin VCC\n"         \
    "Flipper Pin 8 (GND)  -> Display Pin GND\n\n"       \
    "Note: Make sure connections are secure and correct polarity!"

#define FLIPMATRIX_ABOUT_TEXT                                                                                                      \
    "About FlipMatrix\n\n"                                                                                                         \
    "Version: 1.0.0\n"                                                                                                             \
    "Author: @Zakrzewiaczek\n\n"                                                                                                   \
    "FlipMatrix is a MAX7219 LED matrix display controller for Flipper Zero. Control 8x8 LED matrices with SPI communication.\n\n" \
    "Features:\n"                                                                                                                  \
    "• MAX7219 SPI communication\n"                                                                                                \
    "• 8x8 LED matrix control\n"                                                                                                   \
    "• Real-time pixel manipulation\n"                                                                                             \
    "• Hardware SPI interface\n"                                                                                                   \
    "• Easy connection setup\n\n"                                                                                                  \
    "Compatible with standard MAX7219 modules.\n\n"                                                                                \
    "Enjoy creating LED patterns!"

// Function declarations
void flipmatrix_menu_callback(void* context, uint32_t index);
void flipmatrix_main_menu_scene_on_enter(void* context);
bool flipmatrix_main_menu_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_main_menu_scene_on_exit(void* context);
void flipmatrix_connect_scene_on_enter(void* context);
bool flipmatrix_connect_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_connect_scene_on_exit(void* context);
void flipmatrix_how_to_connect_scene_on_enter(void* context);
bool flipmatrix_how_to_connect_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_how_to_connect_scene_on_exit(void* context);
void flipmatrix_about_scene_on_enter(void* context);
bool flipmatrix_about_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_about_scene_on_exit(void* context);
