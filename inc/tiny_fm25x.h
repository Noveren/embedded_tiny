#ifndef __TINY_FM25X_H_
#define __TINY_FM25X_H_

#if defined(FM25V10) || defined(FM25V05) || defined(FM25W256)
#else
#error "Please select the specific device. FM25V10, FM25V05, FM25W256"
#endif

#include <stdbool.h>
#include <stdint.h>

#if defined(FM25V10)
#define ty_fm25x_ADDR_WIDTH 17
#elif defined(FM25V05)
#define ty_fm25x_ADDR_WIDTH 16
#elif defined(FM25W256)
#define ty_fm25x_ADDR_WIDTH 15
#endif

#define ty_fm25x_ADDR_BYTES ((ty_fm25x_ADDR_WIDTH + 7) / 8)

#if (ty_fm25x_ADDR_BYTES > 4)
#error "Invalid `ty_fm25x_ADDR_WIDTH`"
#endif

#define ty_fm25x_ADDR_MASK (0xFFFFFFFF >> (32 - ty_fm25x_ADDR_WIDTH))
#define ty_fm25x_CAPACITY (ty_fm25x_ADDR_MASK + 1)

#if defined(FM25V10) || defined(FM25V05)

// FM25V05  7F7F7F7F7F7FC22300h
// FM25V10  7F7F7F7F7F7FC22400h
// FM25VN10 7F7F7F7F7F7FC22401h

// FIXME: packed
typedef struct {
  uint8_t manufacture_id[7];
  uint16_t framily : 3;
  uint16_t density : 5;
  uint16_t sub : 2;
  uint16_t rev : 3;
  uint16_t rsvd : 3;
} ty_fm25x_id_t;

extern void ty_fm25x_read_id(ty_fm25x_id_t *buf);
extern void ty_fm25x_printf_id(const ty_fm25x_id_t *id);

#endif

typedef enum {
  ty_fm25x_OPCODE_NOP = 0x00,
  ty_fm25x_OPCODE_WREN = 0x06,
  ty_fm25x_OPCODE_WRDI = 0x04,
  ty_fm25x_OPCODE_RDSR = 0x05,
  ty_fm25x_OPCODE_WRSR = 0x01,
  ty_fm25x_OPCODE_READ = 0x03,
  ty_fm25x_OPCODE_WRITE = 0x02,
#if defined(FM25V10) || defined(FM25V05)
  ty_fm25x_OPCODE_FSTRD = 0x0B,
  ty_fm25x_OPCODE_SLEEP = 0xB9,
  ty_fm25x_OPCODE_RDID = 0x9F,
#endif
#if defined(FM25V10)
  bsp_fm25_Opcode_SNR = 0xC3,
#endif
} ty_fm25x_OPCODE;

#define ty_fm25x_REG_WPEN_POS 7
#define ty_fm25x_REG_WPEN_MASK (0x01 << ty_fm25x_REG_WPEN_POS)
#define ty_fm25x_REG_BP1_POS 3
#define ty_fm25x_REG_BP1_MASK (0x01 << ty_fm25x_REG_BP1_POS)
#define ty_fm25x_REG_BP0_POS 2
#define ty_fm25x_REG_BP0_MASK (0x01 << ty_fm25x_REG_BP0_POS)
#define ty_fm25x_REG_WEL_POS 1
#define ty_fm25x_REG_WEL_MASK (0x01 << ty_fm25x_REG_WEL_POS)

extern uint8_t ty_fm25x_read_status(void);
extern void ty_fm25x_printf_status(uint8_t reg);
extern void ty_fm25x_wrtie_enable(bool status);
extern int ty_fm25x_write_all(uint8_t repeat);
extern int ty_fm25x_puts(uint32_t addr, const uint8_t *bytes, int len);
extern int ty_fm25x_puts_open(uint32_t addr);
extern int ty_fm25x_puts_close(void);
extern int ty_fm25x_gets(uint32_t addr, uint8_t *bytes, int len);
extern int ty_fm25x_gets_open(uint32_t addr);
extern int ty_fm25x_gets_close(void);

#endif