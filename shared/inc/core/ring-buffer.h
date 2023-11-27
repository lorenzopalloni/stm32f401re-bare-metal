#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "stdint.h"
#include "stdbool.h"

typedef struct {
  uint8_t *buffer;
  uint32_t mask;
  uint32_t read_index;
  uint32_t write_index;
} ring_buffer_t;

void ring_buffer_setup(ring_buffer_t *rb, uint8_t *buffer, uint32_t size);
bool ring_buffer_empty(ring_buffer_t *rb);
bool ring_buffer_read(ring_buffer_t *rb, uint8_t *byte);
bool ring_buffer_write(ring_buffer_t *rb, uint8_t byte);

#endif  // RING_BUFFER_H
