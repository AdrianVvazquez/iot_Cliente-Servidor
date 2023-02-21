#include <stdio.h>

int main(void) {
    unsigned char *buffer;

    serialize_int(*buffer, 69);

    printf("%s", buffer);
    return 0;
}

unsigned char *serialize_int(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 8;
  buffer[1] = value >> 8;
  buffer[2] = value >> 8;
  buffer[3] = value >> 32;
  buffer[4] = value >> 8;
  return buffer;
}

unsigned char *serialize_char(unsigned char *buffer, char value)
{
  buffer[0] = value;
  return buffer + 1;
}

// unsigned char * serialize_temp(unsigned char *buffer, struct temp *value)
// {
//   buffer = serialize_int(buffer, value->a);
//   buffer = serialize_char(buffer, value->b);
//   return buffer;
// }