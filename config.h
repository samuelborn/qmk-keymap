// This file defines the hardware specific settings
// use ./keymaps/default/config.h for keymap specific settings
#pragma once

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0   // USART TX pin
#define SERIAL_USART_RX_PIN GP1   // USART RX pin
#define SERIAL_USART_PIN_SWAP     // Swap TX and RX pins if keyboard is master halve.
#define EE_HANDS // Split handedness via eeprom

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
