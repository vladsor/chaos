#include "charset.h"

typedef struct
{
  ucs2_type ucs2;
  char character;
} translation_table_type;

#include "ucs2_to_koi8_r.table"

char convert_to_printable_char (ucs2_type ucs2, unsigned int codepage)
{
  int i;

  if (codepage != CODEPAGE_KOI8_R)
  {
    return 0;
  }

  for (i = 0 ; i < koi8_r_table_size ; i++)
  {
    if (ucs2_to_koi8_r_table[i].ucs2 == ucs2)
    {
      return ucs2_to_koi8_r_table[i].character;
    }
  }
  return 0;
}
