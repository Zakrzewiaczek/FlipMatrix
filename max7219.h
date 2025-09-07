#pragma once

#include <furi.h>
#include <furi_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

// MAX7219 Register addresses
#define MAX7219_REG_NOOP        0x00
#define MAX7219_REG_DIGIT0      0x01
#define MAX7219_REG_DIGIT1      0x02
#define MAX7219_REG_DIGIT2      0x03
#define MAX7219_REG_DIGIT3      0x04
#define MAX7219_REG_DIGIT4      0x05
#define MAX7219_REG_DIGIT5      0x06
#define MAX7219_REG_DIGIT6      0x07
#define MAX7219_REG_DIGIT7      0x08
#define MAX7219_REG_DECODEMODE  0x09
#define MAX7219_REG_INTENSITY   0x0A
#define MAX7219_REG_SCANLIMIT   0x0B
#define MAX7219_REG_SHUTDOWN    0x0C
#define MAX7219_REG_DISPLAYTEST 0x0F

// MAX7219 values
#define MAX7219_DECODE_NONE     0x00
#define MAX7219_INTENSITY_MIN   0x00
#define MAX7219_INTENSITY_MAX   0x0F
#define MAX7219_SCAN_8_DIGITS   0x07
#define MAX7219_SHUTDOWN_MODE   0x00
#define MAX7219_NORMAL_MODE     0x01
#define MAX7219_DISPLAYTEST_OFF 0x00

// Matrix dimensions
#define MAX7219_MATRIX_SIZE 8

typedef struct {
    const FuriHalSpiBusHandle* spi;
    uint32_t timeout;
    bool initialized;
    uint8_t matrix_buffer[MAX7219_MATRIX_SIZE]; // Local buffer for pixel operations
} MAX7219;

/**
 * Initialize MAX7219 display
 * @param max7219 Pointer to MAX7219 instance
 * @return true if initialization successful
 */
bool max7219_init(MAX7219* max7219);

/**
 * Deinitialize MAX7219
 * @param max7219 Pointer to MAX7219 instance
 */
void max7219_deinit(MAX7219* max7219);

/**
 * Write register to MAX7219
 * @param max7219 Pointer to MAX7219 instance
 * @param reg Register address
 * @param data Data to write
 */
void max7219_write_register(MAX7219* max7219, uint8_t reg, uint8_t data);

/**
 * Test display - turn on all LEDs briefly
 * @param max7219 Pointer to MAX7219 instance
 */
void max7219_test_display(MAX7219* max7219);

// ====== HAL Functions for Easy Pixel Management ======

/**
 * Clear entire display and internal buffer
 * @param max7219 Pointer to MAX7219 instance
 */
void max7219_clear_display(MAX7219* max7219);

/**
 * Set pixel state in matrix buffer and update display
 * @param max7219 Pointer to MAX7219 instance
 * @param row Row (0-7)
 * @param col Column (0-7)
 * @param state true to turn on pixel, false to turn off
 */
void max7219_set_pixel(MAX7219* max7219, uint8_t row, uint8_t col, bool state);

/**
 * Get pixel state from matrix buffer
 * @param max7219 Pointer to MAX7219 instance
 * @param row Row (0-7)
 * @param col Column (0-7)
 * @return true if pixel is on, false if off
 */
bool max7219_get_pixel(MAX7219* max7219, uint8_t row, uint8_t col);

/**
 * Set entire row data
 * @param max7219 Pointer to MAX7219 instance
 * @param row Row (0-7)
 * @param data 8-bit row data
 */
void max7219_set_row(MAX7219* max7219, uint8_t row, uint8_t data);

/**
 * Set entire column data
 * @param max7219 Pointer to MAX7219 instance
 * @param col Column (0-7)
 * @param data 8-bit column data (LSB = row 0, MSB = row 7)
 */
void max7219_set_column(MAX7219* max7219, uint8_t col, uint8_t data);

/**
 * Update display with current matrix buffer
 * @param max7219 Pointer to MAX7219 instance
 */
void max7219_update_display(MAX7219* max7219);

/**
 * Set display intensity (brightness)
 * @param max7219 Pointer to MAX7219 instance
 * @param intensity Intensity level (0x00 to 0x0F)
 */
void max7219_set_intensity(MAX7219* max7219, uint8_t intensity);

/**
 * Shift display left by one column
 * @param max7219 Pointer to MAX7219 instance
 * @param wrap true to wrap around, false to shift in zeros
 */
void max7219_shift_left(MAX7219* max7219, bool wrap);

/**
 * Shift display right by one column  
 * @param max7219 Pointer to MAX7219 instance
 * @param wrap true to wrap around, false to shift in zeros
 */
void max7219_shift_right(MAX7219* max7219, bool wrap);

#ifdef __cplusplus
}
#endif
