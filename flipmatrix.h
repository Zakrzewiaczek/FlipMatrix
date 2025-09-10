#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_box.h>
#include <gui/modules/text_input.h>
#include <gui/modules/variable_item_list.h>
#include <dialogs/dialogs.h>
#include "max7219.h"

// Constants
#define FLIPMATRIX_TEXT_INPUT_MAX_LEN 30

typedef enum {
    FlipMatrixMainMenuScene,
    FlipMatrixConnectScene,
    FlipMatrixConnectedMenuScene,
    FlipMatrixTextInputScene,
    FlipMatrixTextDisplayScene,
    FlipMatrixFlashingTextInputScene,
    FlipMatrixFlashingTextDisplayScene,
    FlipMatrixImageDisplayScene,
    FlipMatrixSettingsScene,
    FlipMatrixHowToConnectScene,
    FlipMatrixAboutScene,
    FlipMatrixSceneCount,
} FlipMatrixScene;

typedef enum {
    FlipMatrixSubmenuView,
    FlipMatrixWidgetView,
    FlipMatrixTextBoxView,
    FlipMatrixTextInputView,
    FlipMatrixVariableItemListView,
} FlipMatrixView;

typedef struct App {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Widget* widget;
    TextBox* text_box;
    TextInput* text_input;
    VariableItemList* variable_item_list;
    FuriString* text_box_store;
    char text_input_buffer[FLIPMATRIX_TEXT_INPUT_MAX_LEN + 1]; // +1 for null terminator
    FuriString* file_path; // Path to selected .mtx file
    DialogsApp* dialogs;
    MAX7219* max7219;
    bool matrix_connected;
    
    // Animation state for scrolling text
    FuriTimer* scroll_timer;
    int16_t scroll_position;
    FuriString* scroll_text;
    bool scroll_active;
    
    // Animation state for flashing text
    FuriTimer* flash_timer;
    size_t flash_current_char;
    FuriString* flash_text;
    bool flash_active;
    
    // Settings
    uint8_t brightness; // 0-15
    uint8_t scroll_speed; // 0=Slow, 1=Medium, 2=Fast
    uint8_t scroll_direction; // 0=Horizontal, 1=Vertical
} App;

typedef enum {
    FlipMatrixMainMenuSceneConnect,
    FlipMatrixMainMenuSceneHowToConnect,
    FlipMatrixMainMenuSceneAbout,
} FlipMatrixMainMenuSceneIndex;

typedef enum {
    FlipMatrixConnectedMenuSceneTextDisplay,
    FlipMatrixConnectedMenuSceneFlashingText,
    FlipMatrixConnectedMenuSceneImageDisplay,
    FlipMatrixConnectedMenuSceneSettings,
} FlipMatrixConnectedMenuSceneIndex;

typedef enum {
    FlipMatrixMainMenuSceneConnectEvent,
    FlipMatrixMainMenuSceneHowToConnectEvent,
    FlipMatrixMainMenuSceneAboutEvent,
} FlipMatrixMainMenuEvent;

typedef enum {
    FlipMatrixConnectedMenuSceneTextDisplayEvent,
    FlipMatrixConnectedMenuSceneFlashingTextEvent,
    FlipMatrixConnectedMenuSceneImageDisplayEvent,
    FlipMatrixConnectedMenuSceneSettingsEvent,
} FlipMatrixConnectedMenuEvent;

// Text constants
#define FLIPMATRIX_HOW_TO_CONNECT_TEXT                  \
    "How to Connect MAX7219\n\n"                        \
    "Wiring:\n"                                         \
    "Flipper Pin 2 (MOSI) \n -> Display Pin DIN\n\n"    \
    "Flipper Pin 4 (CS)   \n -> Display Pin CS\n\n"     \
    "Flipper Pin 5 (SCK)  \n -> Display Pin SCK\n\n"    \
    "Flipper Pin 9 (3V3)  \n -> Display Pin VCC\n\n"    \
    "Flipper Pin 8 (GND)  \n -> Display Pin GND\n\n\n"  \
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
void flipmatrix_connected_menu_callback(void* context, uint32_t index);
void flipmatrix_main_menu_scene_on_enter(void* context);
bool flipmatrix_main_menu_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_main_menu_scene_on_exit(void* context);
void flipmatrix_connect_scene_on_enter(void* context);
bool flipmatrix_connect_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_connect_scene_on_exit(void* context);
void flipmatrix_connected_menu_scene_on_enter(void* context);
bool flipmatrix_connected_menu_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_connected_menu_scene_on_exit(void* context);
void flipmatrix_text_display_scene_on_enter(void* context);
bool flipmatrix_text_display_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_text_display_scene_on_exit(void* context);
void flipmatrix_image_display_scene_on_enter(void* context);
bool flipmatrix_image_display_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_image_display_scene_on_exit(void* context);
void flipmatrix_load_and_display_fmtx_file(void* context);
void flipmatrix_settings_scene_on_enter(void* context);
bool flipmatrix_settings_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_settings_scene_on_exit(void* context);
void flipmatrix_how_to_connect_scene_on_enter(void* context);
bool flipmatrix_how_to_connect_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_how_to_connect_scene_on_exit(void* context);
void flipmatrix_about_scene_on_enter(void* context);
bool flipmatrix_about_scene_on_event(void* context, SceneManagerEvent event);
void flipmatrix_about_scene_on_exit(void* context);
