#include "max7219.h"
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

    FURI_LOG_D(TAG, "Display cleared");
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
    FURI_LOG_D(TAG, "Intensity set to: %d", intensity);
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
