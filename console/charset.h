
enum
{
  CODEPAGE_IBM866, 

  CODEPAGE_CP1251, 

  CODEPAGE_KOI8_R, 

  CODEPAGE_KOI8_U, 

};

extern char convert_to_printable_char (ucs2_type ucs2, unsigned int codepage);
