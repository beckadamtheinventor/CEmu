/*
 * Copyright (c) 2015-2020 CE Programming.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CEMUCORE_H
#define CEMUCORE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum cemucore_signal
{
    CEMUCORE_SIGNAL_LCD_FRAME,
    CEMUCORE_SIGNAL_SOFT_CMD,
} cemucore_signal_t;

typedef enum cemucore_create_flags
{
#ifndef CEMUCORE_NOTHREADS
    CEMUCORE_CREATE_FLAG_THREADED = 1 << 0,
#endif
} cemucore_create_flags_t;

typedef enum cemucore_prop
{
    CEMUCORE_PROP_REG,
    CEMUCORE_PROP_REG_SHADOW,
    CEMUCORE_PROP_KEY,
    CEMUCORE_PROP_GPIO_ENABLE,
} cemucore_prop_t;

typedef enum cemucore_reg
{
    /* 8-bit registers */
    CEMUCORE_REG_F,
    CEMUCORE_REG_A,
    CEMUCORE_REG_C,
    CEMUCORE_REG_B,
    CEMUCORE_REG_BCU,
    CEMUCORE_REG_E,
    CEMUCORE_REG_D,
    CEMUCORE_REG_DEU,
    CEMUCORE_REG_L,
    CEMUCORE_REG_H,
    CEMUCORE_REG_HLU,
    CEMUCORE_REG_IXL,
    CEMUCORE_REG_IXH,
    CEMUCORE_REG_IXU,
    CEMUCORE_REG_IYL,
    CEMUCORE_REG_IYH,
    CEMUCORE_REG_IYU,
    CEMUCORE_REG_R,

    /* 16-bit registers */
    CEMUCORE_REG_AF,
    CEMUCORE_REG_BC,
    CEMUCORE_REG_DE,
    CEMUCORE_REG_HL,
    CEMUCORE_REG_IX,
    CEMUCORE_REG_IY,
    CEMUCORE_REG_SPS,
    CEMUCORE_REG_I,

    /* 24-bit registers */
    CEMUCORE_REG_UBC,
    CEMUCORE_REG_UDE,
    CEMUCORE_REG_UHL,
    CEMUCORE_REG_UIX,
    CEMUCORE_REG_UIY,
    CEMUCORE_REG_SPL,
    CEMUCORE_REG_PC,
    CEMUCORE_REG_RPC,
} cemucore_reg_t;

typedef struct cemucore cemucore_t;

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*cemucore_signal_handler_t)(cemucore_signal_t, void *);

cemucore_t *cemucore_create(cemucore_create_flags_t, cemucore_signal_handler_t, void *);
void cemucore_destroy(cemucore_t *);

int32_t cemucore_get(const cemucore_t *, cemucore_prop_t, int32_t);
void cemucore_set(cemucore_t *, cemucore_prop_t, int32_t, int32_t);

void cemucore_sleep(cemucore_t *);
void cemucore_wake(cemucore_t *);

/* !!! DEPRECATED API !!! */
typedef enum {
    TI84PCE = 0,
    TI83PCE = 1
} ti_device_t;
ti_device_t get_device_type(void);
uint8_t mem_peek_byte(uint32_t addr);
void emu_set_lcd_ptrs(uint32_t **dat, uint32_t **dat_end, int width, int height, uint32_t addr, uint32_t control, bool mask);
#define DBG_MASK_READ  1
#define DBG_MASK_WRITE 2
#define DBG_MASK_EXEC  4
typedef struct {
    uint8_t addr[0x10000];
} debug_t;
extern debug_t debug;
typedef struct {
    uint32_t control, upbase;
} lcd_t;
extern lcd_t lcd;
void emu_lcd_drawmem(void *output, void *data, void *data_end, uint32_t control, int size, int spi);
#define LCD_WIDTH 320
#define LCD_HEIGHT 240
#include <stdio.h>
FILE *fopen_utf8(const char *filename, const char *mode);

#ifdef __cplusplus
}
#endif

#endif
