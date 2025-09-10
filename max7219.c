#include "max7219.h"
#include "flipmatrix_chars.h"
#include <string.h>

#define TAG "MAX7219"

void max7219_write_register(MAX7219* max7219, uint8_t reg, uint8_t data) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    uint8_t tx_data[2] = {reg, data};

    furi_hal_spi_acquire(max7219->spi);

    if(!furi_hal_spi_bus_tx(max7219->spi, tx_data, 2, max7219->timeout)) {
        FURI_LOG_E(TAG, "SPI TX failed");
    }

    furi_hal_spi_release(max7219->spi);
}

bool max7219_init(MAX7219* max7219) {
    furi_check(max7219);

    max7219->spi = &furi_hal_spi_bus_handle_external;
    max7219->timeout = 1000;
    max7219->initialized = false;

    // Clear matrix buffer
    memset(max7219->matrix_buffer, 0, MAX7219_MATRIX_SIZE);

    // Initialize SPI bus handle
    furi_hal_spi_bus_handle_init(max7219->spi);

    // Initialize MAX7219 registers
    max7219->initialized = true; // Set before calling write_register

    max7219_write_register(max7219, MAX7219_REG_SHUTDOWN, MAX7219_SHUTDOWN_MODE);
    max7219_write_register(max7219, MAX7219_REG_DISPLAYTEST, MAX7219_DISPLAYTEST_OFF);
    max7219_write_register(max7219, MAX7219_REG_DECODEMODE, MAX7219_DECODE_NONE);
    max7219_write_register(max7219, MAX7219_REG_SCANLIMIT, MAX7219_SCAN_8_DIGITS);
    max7219_write_register(max7219, MAX7219_REG_INTENSITY, MAX7219_INTENSITY_MAX / 2);

    // Clear display
    max7219_clear_display(max7219);

    // Enable normal operation
    max7219_write_register(max7219, MAX7219_REG_SHUTDOWN, MAX7219_NORMAL_MODE);

    FURI_LOG_I(TAG, "MAX7219 initialized");
    return true;
}

void max7219_deinit(MAX7219* max7219) {
    furi_check(max7219);

    if(max7219->initialized) {
        max7219_write_register(max7219, MAX7219_REG_SHUTDOWN, MAX7219_SHUTDOWN_MODE);
        furi_hal_spi_bus_handle_deinit(max7219->spi);
        max7219->initialized = false;
        FURI_LOG_I(TAG, "MAX7219 deinitialized");
    }
}

void max7219_test_display(MAX7219* max7219) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    FURI_LOG_I(TAG, "Testing MAX7219 display");

    // Turn on all LEDs in a simple pattern
    max7219_write_register(max7219, MAX7219_REG_DIGIT0, 0xFF);
    max7219_write_register(max7219, MAX7219_REG_DIGIT1, 0x81);
    max7219_write_register(max7219, MAX7219_REG_DIGIT2, 0x81);
    max7219_write_register(max7219, MAX7219_REG_DIGIT3, 0x81);
    max7219_write_register(max7219, MAX7219_REG_DIGIT4, 0x81);
    max7219_write_register(max7219, MAX7219_REG_DIGIT5, 0x81);
    max7219_write_register(max7219, MAX7219_REG_DIGIT6, 0x81);
    max7219_write_register(max7219, MAX7219_REG_DIGIT7, 0xFF);
}

// ====== HAL Functions Implementation ======

void max7219_clear_display(MAX7219* max7219) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    // Clear buffer
    memset(max7219->matrix_buffer, 0, MAX7219_MATRIX_SIZE);

    // Clear hardware display
    for(uint8_t i = 0; i < MAX7219_MATRIX_SIZE; i++) {
        max7219_write_register(max7219, MAX7219_REG_DIGIT0 + i, 0x00);
    }
}

void max7219_set_pixel(MAX7219* max7219, uint8_t row, uint8_t col, bool state) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    if(row >= MAX7219_MATRIX_SIZE || col >= MAX7219_MATRIX_SIZE) {
        FURI_LOG_W(TAG, "Pixel coordinates out of bounds: (%d,%d)", row, col);
        return;
    }

    if(state) {
        max7219->matrix_buffer[row] |= (1 << col);
    } else {
        max7219->matrix_buffer[row] &= ~(1 << col);
    }

    // Update only the affected row
    max7219_write_register(max7219, MAX7219_REG_DIGIT0 + row, max7219->matrix_buffer[row]);
}

bool max7219_get_pixel(MAX7219* max7219, uint8_t row, uint8_t col) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    if(row >= MAX7219_MATRIX_SIZE || col >= MAX7219_MATRIX_SIZE) {
        FURI_LOG_W(TAG, "Pixel coordinates out of bounds: (%d,%d)", row, col);
        return false;
    }

    return (max7219->matrix_buffer[row] & (1 << col)) != 0;
}

void max7219_set_row(MAX7219* max7219, uint8_t row, uint8_t data) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    if(row >= MAX7219_MATRIX_SIZE) {
        FURI_LOG_W(TAG, "Row out of bounds: %d", row);
        return;
    }

    max7219->matrix_buffer[row] = data;
    max7219_write_register(max7219, MAX7219_REG_DIGIT0 + row, data);
}

void max7219_set_column(MAX7219* max7219, uint8_t col, uint8_t data) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    if(col >= MAX7219_MATRIX_SIZE) {
        FURI_LOG_W(TAG, "Column out of bounds: %d", col);
        return;
    }

    // Set column bit in each row
    for(uint8_t row = 0; row < MAX7219_MATRIX_SIZE; row++) {
        if(data & (1 << row)) {
            max7219->matrix_buffer[row] |= (1 << col);
        } else {
            max7219->matrix_buffer[row] &= ~(1 << col);
        }
        max7219_write_register(max7219, MAX7219_REG_DIGIT0 + row, max7219->matrix_buffer[row]);
    }
}

void max7219_update_display(MAX7219* max7219) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    for(uint8_t i = 0; i < MAX7219_MATRIX_SIZE; i++) {
        max7219_write_register(max7219, MAX7219_REG_DIGIT0 + i, max7219->matrix_buffer[i]);
    }
}

void max7219_set_intensity(MAX7219* max7219, uint8_t intensity) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    if(intensity > MAX7219_INTENSITY_MAX) {
        intensity = MAX7219_INTENSITY_MAX;
        FURI_LOG_W(TAG, "Intensity clamped to maximum: %d", intensity);
    }

    max7219_write_register(max7219, MAX7219_REG_INTENSITY, intensity);
}

void max7219_shift_left(MAX7219* max7219, bool wrap) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    for(uint8_t row = 0; row < MAX7219_MATRIX_SIZE; row++) {
        uint8_t msb = (max7219->matrix_buffer[row] & 0x80) >> 7;
        max7219->matrix_buffer[row] <<= 1;

        if(wrap) {
            max7219->matrix_buffer[row] |= msb;
        }
    }

    max7219_update_display(max7219);
}

void max7219_shift_right(MAX7219* max7219, bool wrap) {
    furi_check(max7219);
    furi_check(max7219->initialized);

    for(uint8_t row = 0; row < MAX7219_MATRIX_SIZE; row++) {
        uint8_t lsb = max7219->matrix_buffer[row] & 0x01;
        max7219->matrix_buffer[row] >>= 1;

        if(wrap) {
            max7219->matrix_buffer[row] |= (lsb << 7);
        }
    }

    max7219_update_display(max7219);
}

void max7219_display_char(MAX7219* max7219, char character, int8_t x_offset, uint8_t y_offset) {
    furi_check(max7219);
    furi_check(max7219->initialized);
    
    const uint8_t* char_data = flipmatrix_get_char_data(character);
    if(char_data == NULL) return;
    
    uint8_t width = char_data[0];
    
    // Display each column of the character
    for(uint8_t col = 0; col < width; col++) {
        int8_t display_col = x_offset + col;
        
        // Skip if column is outside display bounds
        if(display_col < 0 || display_col >= MAX7219_MATRIX_SIZE) continue;
        
        uint8_t column_data = char_data[col + 1]; // +1 because first byte is width
        
        // Shift column data based on y_offset
        if(y_offset > 0) {
            column_data >>= y_offset;
        }
        
        // Clear the column first, then set new data
        max7219->matrix_buffer[display_col] = column_data;
    }
    
    max7219_update_display(max7219);
}

void max7219_display_text_horizontal(MAX7219* max7219, const char* text, int16_t x_offset, uint8_t y_offset, uint8_t spacing) {
    furi_check(max7219);
    furi_check(max7219->initialized);
    
    // Clear display first
    max7219_clear_display(max7219);
    
    int16_t current_x = x_offset;
    
    for(size_t i = 0; text[i] != '\0'; i++) {
        const uint8_t* char_data = flipmatrix_get_char_data(text[i]);
        if(char_data == NULL) continue;
        
        uint8_t width = char_data[0];
        
        // Display each column of the character
        for(uint8_t col = 0; col < width; col++) {
            int16_t display_col = current_x + col;
            
            // Skip if column is outside display bounds
            if(display_col < 0 || display_col >= MAX7219_MATRIX_SIZE) continue;
            
            uint8_t column_data = char_data[col + 1]; // +1 because first byte is width
            
            // Shift column data based on y_offset
            if(y_offset > 0) {
                column_data >>= y_offset;
            }
            
            // Set the pixel data
            max7219->matrix_buffer[display_col] = column_data;
        }
        
        // Move to next character position
        current_x += width + spacing;
        
        // Stop if we're way past the display
        if(current_x > MAX7219_MATRIX_SIZE + 10) break;
    }
    
    max7219_update_display(max7219);
}

void max7219_display_text_vertical(MAX7219* max7219, const char* text, uint8_t x_offset, int16_t y_offset, uint8_t spacing) {
    furi_check(max7219);
    furi_check(max7219->initialized);
    
    // Clear display first
    max7219_clear_display(max7219);
    
    int16_t current_y = y_offset;
    
    for(size_t i = 0; text[i] != '\0'; i++) {
        const uint8_t* char_data = flipmatrix_get_char_data(text[i]);
        if(char_data == NULL) continue;
        
        uint8_t width = char_data[0];
        
        // For vertical display, we need to render character rotated 90 degrees
        // Each row of the original character becomes a column in vertical display
        for(uint8_t col = 0; col < width; col++) {
            uint8_t column_data = char_data[col + 1]; // +1 because first byte is width
            
            // Draw each bit of this column as a horizontal line
            for(uint8_t bit = 0; bit < 8; bit++) {
                if(column_data & (1 << bit)) {
                    int16_t display_row = current_y + bit;
                    int16_t display_col = x_offset + col;
                    
                    // Skip if outside display bounds
                    if(display_row < 0 || display_row >= MAX7219_MATRIX_SIZE) continue;
                    if(display_col < 0 || display_col >= MAX7219_MATRIX_SIZE) continue;
                    
                    // Set pixel in matrix buffer
                    max7219->matrix_buffer[display_col] |= (1 << display_row);
                }
            }
        }
        
        // Move to next character position (move down by character height + spacing)
        current_y += 8 + spacing; // Characters are 8 pixels tall
        
        // Stop if we're way past the display
        if(current_y > MAX7219_MATRIX_SIZE + 10) break;
    }
    
    max7219_update_display(max7219);
}

uint8_t max7219_get_char_width(char character) {
    return flipmatrix_get_char_width(character);
}

uint16_t max7219_get_text_width(const char* text, uint8_t spacing) {
    uint16_t total_width = 0;
    
    for(size_t i = 0; text[i] != '\0'; i++) {
        uint8_t char_width = flipmatrix_get_char_width(text[i]);
        total_width += char_width;
        
        // Add spacing between characters (but not after the last one)
        if(text[i + 1] != '\0') {
            total_width += spacing;
        }
    }
    
    return total_width;
}

uint16_t max7219_get_text_height(const char* text, uint8_t spacing) {
    uint16_t total_height = 0;
    
    for(size_t i = 0; text[i] != '\0'; i++) {
        // Characters are 8 pixels tall
        total_height += 8;
        
        // Add spacing between characters (but not after the last one)
        if(text[i + 1] != '\0') {
            total_height += spacing;
        }
    }
    
    return total_height;
}
