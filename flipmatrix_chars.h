#pragma once

#include <stdint.h>

// Definicje znaków dla wyświetlacza FlipMatrix
// Każdy znak jest reprezentowany jako tablica bajtów, gdzie każdy bajt to kolumna
// Pierwszy bajt to szerokość znaku, następne to dane kolumn

// Wielkie litery A-Z
static const uint8_t char_Q[] = {5, 0x3e, 0x41, 0x51, 0x21, 0x5e};  // Q
static const uint8_t char_W[] = {5, 0x3f, 0x40, 0x38, 0x40, 0x3f};  // W
static const uint8_t char_E[] = {5, 0x7f, 0x49, 0x49, 0x49, 0x41};  // E
static const uint8_t char_R[] = {5, 0x7f, 0x09, 0x19, 0x29, 0x46};  // R
static const uint8_t char_T[] = {5, 0x01, 0x01, 0x7f, 0x01, 0x01};  // T
static const uint8_t char_Y[] = {5, 0x03, 0x04, 0x78, 0x04, 0x03};  // Y
static const uint8_t char_U[] = {5, 0x3f, 0x40, 0x40, 0x40, 0x3f};  // U
static const uint8_t char_I[] = {3, 0x41, 0x7f, 0x41};             // I
static const uint8_t char_O[] = {5, 0x3e, 0x41, 0x41, 0x41, 0x3e};  // O
static const uint8_t char_P[] = {5, 0x7f, 0x09, 0x09, 0x09, 0x06};  // P
static const uint8_t char_A[] = {5, 0x7e, 0x09, 0x09, 0x09, 0x7e};  // A
static const uint8_t char_S[] = {5, 0x46, 0x49, 0x49, 0x49, 0x31};  // S
static const uint8_t char_D[] = {5, 0x7f, 0x41, 0x41, 0x41, 0x3e};  // D
static const uint8_t char_F[] = {5, 0x7f, 0x09, 0x09, 0x09, 0x01};  // F
static const uint8_t char_G[] = {5, 0x3e, 0x41, 0x41, 0x51, 0x73};  // G
static const uint8_t char_H[] = {5, 0x7f, 0x08, 0x08, 0x08, 0x7f};  // H
static const uint8_t char_J[] = {5, 0x20, 0x40, 0x41, 0x3f, 0x01};  // J
static const uint8_t char_K[] = {5, 0x7f, 0x08, 0x14, 0x22, 0x41};  // K
static const uint8_t char_L[] = {5, 0x7f, 0x40, 0x40, 0x40, 0x40};  // L
static const uint8_t char_Z[] = {5, 0x61, 0x51, 0x49, 0x45, 0x43};  // Z
static const uint8_t char_X[] = {5, 0x63, 0x14, 0x08, 0x14, 0x63};  // X
static const uint8_t char_C[] = {5, 0x3e, 0x41, 0x41, 0x41, 0x22};  // C
static const uint8_t char_V[] = {5, 0x1f, 0x20, 0x40, 0x20, 0x1f};  // V
static const uint8_t char_B[] = {5, 0x7f, 0x49, 0x49, 0x49, 0x36};  // B
static const uint8_t char_N[] = {5, 0x7f, 0x04, 0x08, 0x10, 0x7f};  // N
static const uint8_t char_M[] = {5, 0x7f, 0x02, 0x0c, 0x02, 0x7f};  // M

// Małe litery a-z
static const uint8_t char_q[] = {4, 0x18, 0x24, 0x24, 0xfc};       // q
static const uint8_t char_w[] = {5, 0x3c, 0x40, 0x30, 0x40, 0x3c}; // w
static const uint8_t char_e[] = {4, 0x38, 0x54, 0x54, 0x18};       // e
static const uint8_t char_r[] = {4, 0x7c, 0x08, 0x04, 0x08};       // r
static const uint8_t char_t[] = {3, 0x04, 0x3f, 0x44};             // t
static const uint8_t char_y[] = {4, 0x1c, 0xa0, 0xa0, 0x7c};       // y
static const uint8_t char_u[] = {4, 0x3c, 0x40, 0x40, 0x7c};       // u
static const uint8_t char_i[] = {1, 0x7d};                         // i
static const uint8_t char_o[] = {4, 0x38, 0x44, 0x44, 0x38};       // o
static const uint8_t char_p[] = {4, 0xfc, 0x24, 0x24, 0x18};       // p
static const uint8_t char_a[] = {4, 0x20, 0x54, 0x54, 0x78};       // a
static const uint8_t char_s[] = {4, 0x48, 0x54, 0x54, 0x24};       // s
static const uint8_t char_d[] = {4, 0x38, 0x44, 0x44, 0x7f};       // d
static const uint8_t char_f[] = {4, 0x08, 0x7e, 0x09, 0x02};       // f
static const uint8_t char_g[] = {4, 0x18, 0xa4, 0xa4, 0x7c};       // g
static const uint8_t char_h[] = {4, 0x7f, 0x08, 0x04, 0x78};       // h
static const uint8_t char_j[] = {4, 0x40, 0x80, 0x80, 0x7a};       // j
static const uint8_t char_k[] = {4, 0x7f, 0x10, 0x28, 0x44};       // k
static const uint8_t char_l[] = {3, 0x41, 0x7f, 0x40};             // l
static const uint8_t char_z[] = {4, 0x44, 0x64, 0x54, 0x4c};       // z
static const uint8_t char_x[] = {4, 0x44, 0x28, 0x28, 0x44};       // x
static const uint8_t char_c[] = {4, 0x38, 0x44, 0x44, 0x28};       // c
static const uint8_t char_v[] = {4, 0x1c, 0x20, 0x40, 0x7c};       // v
static const uint8_t char_b[] = {4, 0x7f, 0x44, 0x44, 0x38};       // b
static const uint8_t char_n[] = {4, 0x7c, 0x08, 0x04, 0x78};       // n
static const uint8_t char_m[] = {5, 0x7c, 0x04, 0x78, 0x04, 0x78}; // m

// Cyfry 0-9
static const uint8_t char_0[] = {5, 0x3e, 0x51, 0x49, 0x45, 0x3e}; // 0
static const uint8_t char_1[] = {3, 0x42, 0x7f, 0x40};             // 1
static const uint8_t char_2[] = {5, 0x72, 0x49, 0x49, 0x49, 0x46}; // 2
static const uint8_t char_3[] = {5, 0x21, 0x41, 0x49, 0x4d, 0x33}; // 3
static const uint8_t char_4[] = {5, 0x18, 0x14, 0x12, 0x7f, 0x10}; // 4
static const uint8_t char_5[] = {5, 0x27, 0x45, 0x45, 0x45, 0x39}; // 5
static const uint8_t char_6[] = {5, 0x3c, 0x4a, 0x49, 0x49, 0x31}; // 6
static const uint8_t char_7[] = {5, 0x41, 0x21, 0x11, 0x09, 0x07}; // 7
static const uint8_t char_8[] = {5, 0x36, 0x49, 0x49, 0x49, 0x36}; // 8
static const uint8_t char_9[] = {5, 0x46, 0x49, 0x49, 0x29, 0x1e}; // 9

// Znaki specjalne

static const uint8_t char_underscore[] = {5, 0x40, 0x40, 0x40, 0x40, 0x40};               // _
static const uint8_t char_exclamation[] = {1, 0x5f};               // !
static const uint8_t char_at[] = {5, 0x3e, 0x41, 0x5d, 0x59, 0x4e}; // @
static const uint8_t char_hash[] = {5, 0x14, 0x7f, 0x14, 0x7f, 0x14}; // #
static const uint8_t char_dollar[] = {5, 0x24, 0x2a, 0x7f, 0x2a, 0x12}; // $
static const uint8_t char_percent[] = {5, 0x23, 0x13, 0x08, 0x64, 0x62}; // %
static const uint8_t char_caret[] = {5, 0x04, 0x02, 0x01, 0x02, 0x04}; // ^
static const uint8_t char_ampersand[] = {5, 0x36, 0x49, 0x56, 0x20, 0x50}; // &
static const uint8_t char_asterisk[] = {5, 0x2a, 0x1c, 0x7f, 0x1c, 0x2a}; // *
static const uint8_t char_left_paren[] = {3, 0x1c, 0x22, 0x41};    // (
static const uint8_t char_right_paren[] = {3, 0x41, 0x22, 0x1c};   // )
static const uint8_t char_tilde[] = {4, 0x02, 0x01, 0x02, 0x01};   // ~
static const uint8_t char_plus[] = {5, 0x08, 0x08, 0x3e, 0x08, 0x08}; // +
static const uint8_t char_minus[] = {4, 0x08, 0x08, 0x08, 0x08};   // -
static const uint8_t char_equals[] = {4, 0x14, 0x14, 0x14, 0x14};  // =
static const uint8_t char_left_bracket[] = {3, 0x7f, 0x41, 0x41}; // [
static const uint8_t char_right_bracket[] = {3, 0x41, 0x41, 0x7f}; // ]
static const uint8_t char_left_brace[] = {4, 0x08, 0x36, 0x41, 0x41}; // {
static const uint8_t char_right_brace[] = {4, 0x41, 0x41, 0x36, 0x08}; // }
static const uint8_t char_period[] = {2, 0x60, 0x60};              // .
static const uint8_t char_comma[] = {2, 0x80, 0x70};               // ,
static const uint8_t char_semicolon[] = {2, 0x80, 0x68};           // ;
static const uint8_t char_backtick[] = {3, 0x03, 0x07, 0x08};      // `
static const uint8_t char_apostrophe[] = {3, 0x08, 0x07, 0x03};    // '
static const uint8_t char_space[] = {3, 0x00, 0x00, 0x00};         // ' ' (spacja)

// Struktura do mapowania znaków
typedef struct {
    char character;
    const uint8_t* data;
} char_map_t;

// Tablica mapowania znaków
static const char_map_t character_map[] = {
    // Wielkie litery
    {'Q', char_Q}, {'W', char_W}, {'E', char_E}, {'R', char_R}, {'T', char_T},
    {'Y', char_Y}, {'U', char_U}, {'I', char_I}, {'O', char_O}, {'P', char_P},
    {'A', char_A}, {'S', char_S}, {'D', char_D}, {'F', char_F}, {'G', char_G},
    {'H', char_H}, {'J', char_J}, {'K', char_K}, {'L', char_L}, {'Z', char_Z},
    {'X', char_X}, {'C', char_C}, {'V', char_V}, {'B', char_B}, {'N', char_N},
    {'M', char_M},
    
    // Małe litery
    {'q', char_q}, {'w', char_w}, {'e', char_e}, {'r', char_r}, {'t', char_t},
    {'y', char_y}, {'u', char_u}, {'i', char_i}, {'o', char_o}, {'p', char_p},
    {'a', char_a}, {'s', char_s}, {'d', char_d}, {'f', char_f}, {'g', char_g},
    {'h', char_h}, {'j', char_j}, {'k', char_k}, {'l', char_l}, {'z', char_z},
    {'x', char_x}, {'c', char_c}, {'v', char_v}, {'b', char_b}, {'n', char_n},
    {'m', char_m},
    
    // Cyfry
    {'0', char_0}, {'1', char_1}, {'2', char_2}, {'3', char_3}, {'4', char_4},
    {'5', char_5}, {'6', char_6}, {'7', char_7}, {'8', char_8}, {'9', char_9},
    
    // Znaki specjalne
    {'_', char_underscore}, {'!', char_exclamation}, {'@', char_at}, {'#', char_hash}, {'$', char_dollar},
    {'%', char_percent}, {'^', char_caret}, {'&', char_ampersand}, {'*', char_asterisk},
    {'(', char_left_paren}, {')', char_right_paren}, {'~', char_tilde}, {'+', char_plus},
    {'-', char_minus}, {'=', char_equals}, {'[', char_left_bracket}, {']', char_right_bracket},
    {'{', char_left_brace}, {'}', char_right_brace}, {'.', char_period}, {',', char_comma},
    {';', char_semicolon}, {'`', char_backtick}, {'\'', char_apostrophe}, {' ', char_space}
};

#define CHARACTER_MAP_SIZE (sizeof(character_map) / sizeof(char_map_t))

// Funkcja do znajdowania danych znaku
const uint8_t* flipmatrix_get_char_data(char c);

// Funkcja do pobierania szerokości znaku
uint8_t flipmatrix_get_char_width(char c);
