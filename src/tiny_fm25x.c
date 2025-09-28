#if defined(FM25V10) || defined(FM25V05) || defined(FM25W256)
#include <stdio.h>

#include "tiny_api.h"
#include "tiny_fm25x.h"

#if defined(FM25V10) || defined(FM25V05)
void ty_fm25x_read_id(ty_fm25x_id_t *buf) {
  uint8_t *ptr = (uint8_t *)buf;
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_RDID);
  for (int i = 9; i > 0; i--) {
    ptr[i] = ty_spi_access(ty_fm25x_OPCODE_NOP);
  }
  ty_spi_select(false);
}

void ty_fm25x_printf_id(const ty_fm25x_id_t *id) {
  const uint8_t *ptr = (uint8_t *)id;
  for (int i = 9; i > 0; i--) {
    printf("0x%0X ", ptr[i]);
  }
  putchar('\n');
  puts("Manufacture ID: 0x");
  for (int i = 9; i > 2; i--) {
    printf("%0X", ptr[i]);
  }
  putchar('\n');
  printf("Framily: %d\n", id->framily);
  printf("Density: %d\n", id->density);
  printf("SUB    : %d\n", id->sub);
  printf("REV    : %d\n", id->rev);
  printf("RSVD   : %d\n", id->rsvd);
}
#endif

uint8_t ty_fm25x_read_status(void) {
  uint8_t reg = 0;
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_RDSR);
  reg = ty_spi_access(ty_fm25x_OPCODE_NOP);
  ty_spi_select(false);
  return reg;
}

void ty_fm25x_printf_status(uint8_t reg) {
  printf("FRAM 0x%0X WPEN %d\tBP0 %d\tBP1 %d\t WEL %d\n", reg,
         ((reg & ty_fm25x_REG_WPEN_MASK) != 0),
         ((reg & ty_fm25x_REG_BP0_MASK) != 0),
         ((reg & ty_fm25x_REG_BP1_MASK) != 0),
         ((reg & ty_fm25x_REG_WEL_MASK) != 0));
}

void ty_fm25x_wrtie_enable(bool status) {
  ty_spi_select(true);
  ty_spi_access(status ? ty_fm25x_OPCODE_WREN : ty_fm25x_OPCODE_WRDI);
  ty_spi_select(false);
}

int ty_fm25x_write_all(uint8_t repeat) {
  uint8_t reg = ty_fm25x_read_status();
  if ((reg & ty_fm25x_REG_WEL_MASK) == 0) {
    return -1;
  }
  ty_delay_ms(10);
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_WRITE);
  for (uint32_t i = 0; i < ty_fm25x_ADDR_BYTES; i++) {
    ty_spi_access(0x00);
  }
  for (uint32_t i = 0; i < ty_fm25x_CAPACITY; i++) {
    ty_spi_access(repeat);
  }
  ty_delay_ms(10);
  ty_spi_select(false);
  return 0;
}

int ty_fm25x_puts(uint32_t addr, const uint8_t *bytes, int len) {
  uint8_t reg = ty_fm25x_read_status();
  if ((reg & ty_fm25x_REG_WEL_MASK) == 0) {
    return -1;
  }
  ty_delay_ms(10);
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_WRITE);
  for (uint32_t i = 0; i < ty_fm25x_ADDR_BYTES; i++) {
    ty_spi_access(((uint8_t *)&addr)[sizeof(uint32_t) - 1 - i]);
  }
  for (uint32_t i = 0; i < len; i++) {
    ty_spi_access(bytes[i]);
  }
  ty_delay_ms(10);
  ty_spi_select(false);
  return len;
}

int ty_fm25x_puts_open(uint32_t addr) {
  uint8_t reg = ty_fm25x_read_status();
  if ((reg & ty_fm25x_REG_WEL_MASK) == 0) {
    return -1;
  }
  ty_delay_ms(10);
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_WRITE);
  for (uint32_t i = 0; i < ty_fm25x_ADDR_BYTES; i++) {
    ty_spi_access(((uint8_t *)&addr)[sizeof(uint32_t) - 1 - i]);
  }
  return 0;
}

int ty_fm25x_puts_close(void) {
  ty_spi_select(false);
  return 0;
}

int ty_fm25x_gets(uint32_t addr, uint8_t *bytes, int len) {
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_READ);
  for (uint32_t i = 0; i < ty_fm25x_ADDR_BYTES; i++) {
    ty_spi_access(((uint8_t *)&addr)[sizeof(uint32_t) - 1 - i]);
  }
  for (uint32_t i = 0; i < len; i++) {
    bytes[i] = ty_spi_access(ty_fm25x_OPCODE_NOP);
  }
  ty_delay_ms(10);
  ty_spi_select(false);
  return len;
}

int ty_fm25x_gets_open(uint32_t addr) {
  ty_spi_select(true);
  ty_spi_access(ty_fm25x_OPCODE_READ);
  for (uint32_t i = 0; i < ty_fm25x_ADDR_BYTES; i++) {
    ty_spi_access(((uint8_t *)&addr)[sizeof(uint32_t) - 1 - i]);
  }
  return 0;
}

int ty_fm25x_gets_close(void) {
  ty_spi_select(false);
  return 0;
}
#endif