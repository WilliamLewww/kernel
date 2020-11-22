#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void sleep(uint32_t count) {
  while(1) {
    asm volatile("nop");
    count--;
    if (count <= 0) {
      break;
    }
  }
}

char get_input() {
  char ch = 0;
  while ((ch = inb(0x60)) != 0) {
    if (ch > 0) {
      return ch;
    }
  }
  return ch;
}

void kernel_main(void) {
  char keycode = get_input();
  
  uint16_t* terminal_buffer = (uint16_t*) 0xB8000;
  for (uint32_t y = 0; y < 25; y++) {
    for (uint32_t x = 0; x < 80; x++) {
      terminal_buffer[y * 80 + x] = keycode | (uint16_t)VGA_COLOR_LIGHT_CYAN << 8;
    }
  }
}