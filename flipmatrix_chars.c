#include "flipmatrix_chars.h"
#include <stddef.h>

// Funkcja do znajdowania danych znaku
const uint8_t* flipmatrix_get_char_data(char c) {
    for(size_t i = 0; i < CHARACTER_MAP_SIZE; i++) {
        if(character_map[i].character == c) {
            return character_map[i].data;
        }
    }
    return NULL; // Znak nie został znaleziony
}

// Funkcja do pobierania szerokości znaku
uint8_t flipmatrix_get_char_width(char c) {
    const uint8_t* char_data = flipmatrix_get_char_data(c);
    if(char_data != NULL) {
        return char_data[0]; // Pierwszy bajt to szerokość
    }
    return 0; // Znak nie został znaleziony
}

// Funkcja pomocnicza do wyświetlania pojedynczego znaku na wyświetlaczu
// Parametry:
//   c - znak do wyświetlenia
//   x_offset - pozycja X na wyświetlaczu (0-31)
//   y_offset - pozycja Y na wyświetlaczu (0-7)
//   display_buffer - bufor wyświetlacza (32x8 bitów)
void flipmatrix_draw_char(char c, uint8_t x_offset, uint8_t y_offset, uint8_t display_buffer[32][8]) {
    const uint8_t* char_data = flipmatrix_get_char_data(c);
    if(char_data == NULL) return;
    
    uint8_t width = char_data[0];
    
    // Sprawdź czy znak mieści się na wyświetlaczu
    if(x_offset + width > 32 || y_offset >= 8) return;
    
    // Wyświetl każdą kolumnę znaku
    for(uint8_t col = 0; col < width; col++) {
        uint8_t column_data = char_data[col + 1]; // +1 bo pierwszy bajt to szerokość
        
        // Wyświetl każdy bit w kolumnie
        for(uint8_t row = 0; row < 8; row++) {
            if(column_data & (1 << row)) {
                display_buffer[x_offset + col][y_offset] |= (1 << row);
            } else {
                display_buffer[x_offset + col][y_offset] &= ~(1 << row);
            }
        }
    }
}

// Funkcja do wyświetlania tekstu
// Parametry:
//   text - tekst do wyświetlenia
//   x_offset - pozycja startowa X
//   y_offset - pozycja startowa Y
//   display_buffer - bufor wyświetlacza
//   spacing - odstęp między znakami (domyślnie 1 piksel)
uint8_t flipmatrix_draw_text(const char* text, uint8_t x_offset, uint8_t y_offset, uint8_t display_buffer[32][8], uint8_t spacing) {
    uint8_t current_x = x_offset;
    
    for(size_t i = 0; text[i] != '\0'; i++) {
        // Sprawdź czy znak mieści się na wyświetlaczu
        uint8_t char_width = flipmatrix_get_char_width(text[i]);
        if(current_x + char_width > 32) {
            break; // Nie ma miejsca na kolejny znak
        }
        
        // Wyświetl znak
        flipmatrix_draw_char(text[i], current_x, y_offset, display_buffer);
        
        // Przesuń pozycję o szerokość znaku + odstęp
        current_x += char_width + spacing;
    }
    
    return current_x; // Zwróć końcową pozycję X
}

// Funkcja do wyczyszczenia bufora wyświetlacza
void flipmatrix_clear_display(uint8_t display_buffer[32][8]) {
    for(uint8_t x = 0; x < 32; x++) {
        for(uint8_t y = 0; y < 8; y++) {
            display_buffer[x][y] = 0;
        }
    }
}
