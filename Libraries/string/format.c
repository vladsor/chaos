/* Abstract: String library functions. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include "string.h"

#define POINTER_OUTPUT_ENABLE

#if defined(FLOATING_POINT) && !defined(_IO_USE_DTOA)

static char *exponent (register char *p, register int exp, int fmtch)
{
  register char *t;
  char expbuf[MAXEXP];

  *p++ = fmtch;
  if (exp < 0) 
  {
    exp = -exp;
    *p++ = '-';
  }
  else
  {
    *p++ = '+';
  }

  t = expbuf + MAXEXP;

  if (exp > 9) 
  {
    do 
    {
      *--t = to_char(exp % 10);
    } while ((exp /= 10) > 9);

    *--t = to_char(exp);

    for (; t < expbuf + MAXEXP; *p++ = *t++);
  }
  else 
  {
    *p++ = '0';
    *p++ = to_char(exp);
  }

  return p;
}

static char * round (
    double fract, 
    int *exp,
    register char *start, 
    register char *end,
    char ch, 
    int *signp)
{
  double tmp;

  if (fract)
  {
    (void) modf (fract * 10, &tmp);
  }
  else
  {
    tmp = to_digit(ch);
  }

  if (tmp > 4)
  {
    for (;; --end) 
    {
      if (*end == '.')
      {
	--end;
      }

      if (++*end <= '9')
      {
	break;
      }

      (*end) = '0';

      if (end == start) 
      {
	if (exp) 
	{
	  /* e/E; increment exponent */
	  (*end) = '1';
	  ++(*exp);
	}
	else 
	{
	  /* f; add extra digit */
	  *(--end) = '1';
	  --start;
	}
	break;
      }
    }
  }
  /* ``"%.3f", (double)-0.0004'' gives you a negative 0. */
  else if (*signp == '-')
  {
    for (;; --end) 
    {
      if (*end == '.')
      {
	--end;
      }

      if (*end != '0')
      {
	break;
      }

      if (end == start)
      {
	(*signp) = 0;
      }
    }
  }

  return (start);
}

int __cvt_double (
    double number, 
    register int prec, 
    int flags, 
    int *signp,
    int fmtch, 
    char *startp, 
    char *endp)
{
  register char *p, *t;
  register double fract;
  int dotrim = 0, expcnt, gformat = 0;
  double integer, tmp;

  expcnt = 0;
  if (number < 0) 
  {
    number = -number;
    *signp = '-';
  } 
  else
    *signp = 0;

  fract = modf(number, &integer);

  /* get an extra slot for rounding. */
  t = ++startp;

  /*
   * get integer portion of number; put into the end of the buffer; the
   * .01 is added for modf(356.0 / 10, &integer) returning .59999999...
   */
  for (p = endp - 1; p >= startp && integer; ++expcnt) 
  {
    tmp = modf(integer / 10, &integer);
    *p-- = to_char((int)((tmp + .01) * 10));
  }

  switch (fmtch) 
  {
    case 'f':
    case 'F':
      /* reverse integer into beginning of buffer */
      if (expcnt)
        for (; ++p < endp; *t++ = *p);
      else
        *t++ = '0';

      /*
       * if precision required or alternate flag set, add in a
       * decimal point.
       */

      if (prec || flags&ALT)
        *t++ = '.';

       /* if requires more precision and some fraction left */
      if (fract) 
      {
        if (prec)
          do {
            fract = modf(fract * 10, &tmp);
            *t++ = to_char((int)tmp);
          } while (--prec && fract);

        if (fract)
          startp = round(fract, (int *)NULL, startp, t - 1, (char)0, signp);
      }
      for (; prec--; *t++ = '0');
      break;
    case 'e':
    case 'E':
eformat:	
      if (expcnt) 
      {
			*t++ = *++p;
			if (prec || flags&ALT)
				*t++ = '.';
			/* if requires more precision and some integer left */
			for (; prec && ++p < endp; --prec)
				*t++ = *p;
			/*
			 * if done precision and more of the integer component,
			 * round using it; adjust fract so we don't re-round
			 * later.
			 */
			if (!prec && ++p < endp) {
				fract = 0;
				startp = round((double)0, &expcnt, startp,
				    t - 1, *p, signp);
			}
			/* adjust expcnt for digit in front of decimal */
			--expcnt;
		}
		/* until first fractional digit, decrement exponent */
		else if (fract) {
			/* adjust expcnt for digit in front of decimal */
			for (expcnt = -1;; --expcnt) {
				fract = modf(fract * 10, &tmp);
				if (tmp)
					break;
			}
			*t++ = to_char((int)tmp);
			if (prec || flags&ALT)
				*t++ = '.';
		}
		else {
			*t++ = '0';
			if (prec || flags&ALT)
				*t++ = '.';
		}
		/* if requires more precision and some fraction left */
		if (fract) {
			if (prec)
				do {
					fract = modf(fract * 10, &tmp);
					*t++ = to_char((int)tmp);
				} while (--prec && fract);
			if (fract)
				startp = round(fract, &expcnt, startp,
				    t - 1, (char)0, signp);
		}
		/* if requires more precision */
		for (; prec--; *t++ = '0');

		/* unless alternate flag, trim any g/G format trailing 0's */
		if (gformat && !(flags&ALT)) {
			while (t > startp && *--t == '0');
			if (*t == '.')
				--t;
			++t;
		}
		t = exponent(t, expcnt, fmtch);
		break;
	case 'g':
	case 'G':
		/* a precision of 0 is treated as a precision of 1. */
		if (!prec)
			++prec;
		/*
		 * ``The style used depends on the value converted; style e
		 * will be used only if the exponent resulting from the
		 * conversion is less than -4 or greater than the precision.''
		 *	-- ANSI X3J11
		 */
		if (expcnt > prec || (!expcnt && fract && fract < .0001)) {
			/*
			 * g/G format counts "significant digits, not digits of
			 * precision; for the e/E format, this just causes an
			 * off-by-one problem, i.e. g/G considers the digit
			 * before the decimal point significant and e/E doesn't
			 * count it as precision.
			 */
			--prec;
			fmtch -= 2;		/* G->E, g->e */
			gformat = 1;
			goto eformat;
		}
		/*
		 * reverse integer into beginning of buffer,
		 * note, decrement precision
		 */
		if (expcnt)
			for (; ++p < endp; *t++ = *p, --prec);
		else
			*t++ = '0';
		/*
		 * if precision required or alternate flag set, add in a
		 * decimal point.  If no digits yet, add in leading 0.
		 */
		if (prec || flags&ALT) {
			dotrim = 1;
			*t++ = '.';
		}
		else
			dotrim = 0;
		/* if requires more precision and some fraction left */
		if (fract) {
			if (prec) {
				/* If no integer part, don't count initial
				 * zeros as significant digits. */
				do {
					fract = modf(fract * 10, &tmp);
					*t++ = to_char((int)tmp);
				} while(!tmp && !expcnt);
				while (--prec && fract) {
					fract = modf(fract * 10, &tmp);
					*t++ = to_char((int)tmp);
				}
			}
			if (fract)
				startp = round(fract, (int *)NULL, startp,
				    t - 1, (char)0, signp);
		}
		/* alternate format, adds 0's for precision, else trim 0's */
		if (flags&ALT)
			for (; prec--; *t++ = '0');
		else if (dotrim) {
			while (t > startp && *--t == '0');
			if (*t != '.')
				++t;
		}
	}
	return (t - startp);
}

#endif /* defined(FLOATING_POINT) && !defined(_IO_USE_DTOA) */


/* Prints the given data to the output string, a la printf and
   friends. */

return_t string_print (char *output, const char *format_string, ...)
{
    va_list arguments;
    return_t return_value;
  
    va_start (arguments, format_string);
    return_value = string_print_va (output, format_string, arguments);
    va_end (arguments);
    
    return return_value;
}

/* Print a string using the previously initialised va_list
   structure. */

return_t string_print_va (
    char *output, 
    const char *format_string,
    va_list arguments)
{
  int input_index = 0;
  int output_index = 0;
  int flags;
  int field_width;
  bool done;

#ifdef FLOATING_POINT
  /* temporary negative sign for floats */
  char softsign;

  /* double precision arguments %[eEfgG] */
  double _double;		

  /* integer value of exponent */
  int expt;
  
  /* character count for expstr */
  int expsize;

  /* actual number of digits returned by cvt */
  int ndig;

  /* buffer for exponent string */
  char expstr[7];
#endif

  /* Minimum number of digits for integers; maximum number of chars
     for string. */

  int precision;                

  if (format_string == NULL)
  {
    output[output_index] = '\0';
    return STRING_RETURN_INVALID_ARGUMENT;
  }

  /* Main parser loop. */

  while (format_string[input_index] != '\0')
  {
    switch (format_string[input_index])
    {
      /* Percent sign means we get a formatting code as the next
         character. */

      case '%':
      {
        input_index++;
        flags = 0;
        done = FALSE;

        /* Now, some formatting stuff can be given. Let's parse
           it. */

        while (!done)
        {
          switch (format_string[input_index])
          {
            case '-':
            {
              flags |= STRING_LEFT;
              break;
            }
            
            case '+':
            {
              flags |= STRING_PLUS;
              break;
            }
            
            case ' ':
            {
              flags |= STRING_SPACE;
              break;
            }
            
            case '#':
            {
              flags |= STRING_SPECIAL;
              break;
            }

            case '0':
            {
              flags |= STRING_ZERO_PAD;
              break;
            }
            
            default:
            {
              done = TRUE;
              break;
            }
          }

          if (!done)
          {
            input_index++;
          }
        }

        /* Okay, time for a 'field width' mayhaps? */
        
        field_width = -1;
        if (format_string[input_index] >= '0' && 
            format_string[input_index] <= '9')
        {
          int characters;

          string_to_number (&format_string[input_index], &field_width,
                            &characters);
          input_index += characters;
        }

        /* Perhaps a 'precision' too? */

        precision = -1;
        if (format_string[input_index] == '.') 
        {
          input_index++;

          if (format_string[input_index] >= '0' &&
              format_string[input_index] <= '9')
          {
            int characters;

            string_to_number (&format_string[input_index], &precision,
                              &characters);
            input_index += characters;
          }

          if (precision < 0)
            precision = 0;
        }

        /* After this, we might get on or more 'l' characters. They
           can be ignored for now. */

        while (format_string[input_index] == 'l')
        {
          input_index++;
        }
        
        /* Now, find which type of print out this is. */

        switch (format_string[input_index])
        {
	  /* Character */  
	
	  case 'c':
	  {
	    char character = va_arg (arguments, int);
	    
	    if (character != '\0')
	    {
	      output[output_index++] = character;
	    }
	    
	    break;
	  }
	  
          /* String. */
          
          case 's':
          {
            char *temporary_string = va_arg (arguments, char *);
            int index = 0;
            int length;

            if (temporary_string == NULL)
            {
              temporary_string = (char *) "(null)";
            }
            
            length = string_length (temporary_string);            

            /* If this string should be right-padded, just do it. */

            if (!((flags & STRING_LEFT) == STRING_LEFT))
            {
              for (; length < field_width; field_width--)
              {
                output[output_index++] = ' ';
              }
            }

            if (precision <= 0)
            {
                precision = length;
            }

            while (temporary_string[index] != '\0' && index < precision)
            {
              output[output_index++] = temporary_string[index++];
            }

            /* Left-padded, just do it. */

            for (; length < field_width; field_width--)
            {
              output[output_index++] = ' ';
            }
            
            break;
          }
          
          /* Signed number. */
        
          case 'i':
          case 'd':
          {
            char string[11];
            signed number = va_arg (arguments, signed);
            int index = 0;
            
            flags |= STRING_SIGN;
            number_to_string (string, number, 10, field_width, precision, 
                              flags);
            
            while (string[index] != '\0')
            {
              output[output_index++] = string[index++];
            }
            
            break;
          }
          
          /* Unsigned number. */
          
          case 'u':
          {
            char string[11];
            int index = 0;
            
            number_to_string (string, va_arg (arguments, unsigned), 10,
                              field_width, precision, flags);
            
            while (string[index] != '\0')
            {
              output[output_index++] = string[index++];
            }
            
            break;
          }
          
          /* Hexadecimal number. */
          
          case 'X':
          {
            flags |= STRING_LARGE;
          }

          case 'x':
          {
            char string[9];
            int index = 0;
            
            number_to_string (string, va_arg (arguments, unsigned), 16,
                              field_width, precision, flags);
            
            while (string[index] != '\0')
            {
              output[output_index++] = string[index++];
            }
            
            break;
          }

#ifdef POINTER_OUTPUT_ENABLE
          case 'P':
          {
            flags |= STRING_LARGE;
          }

          case 'p':
          {
            char string[5];
            int index;
            unsigned int pointer;

            /* Ignoring most flags */
            flags &= STRING_LARGE;

            pointer = va_arg (arguments, unsigned);
            number_to_string (string, HIGH_16 (pointer), 16, 4, 4, flags);

            for (index = 0 ; index < 4 ; index++)
            {
              output[output_index++] = string[index];
            }
            
            output[output_index++] = ':';

            number_to_string (string, LOW_16 (pointer), 16, 4, 4, flags);

            for (index = 0 ; index < 4 ; index++)
            {
              output[output_index++] = string[index];
            }
            break;
          }

#endif

#ifdef FLOATING_POINT
          case 'e':
          case 'E':
          case 'f':
          case 'F':
          case 'g':
          case 'G':
	  {
            _double = va_arg(ap, double);
#ifdef _IO_USE_DTOA
            {
              int fmt_flags = 0;
              int fill = ' ';
              if (flags & ALT)
                fmt_flags |= _IO_SHOWPOINT;
              if (flags & LADJUST)
                fmt_flags |= _IO_LEFT;
              else if (flags & ZEROPAD)
				fmt_flags |= _IO_INTERNAL, fill = '0';

              n = _IO_outfloat(_double, fp, ch, width,
					     prec < 0 ? DEFPREC : prec,
					     fmt_flags, sign, fill);
              if (n < 0)
                goto error;
              ret += n;
            }
            /* CHECK ERROR! */
            continue;
#else
            /*
             * don't do unrealistic precision; just pad it with
             * zeroes later, so buffer size stays rational.
             */
            if (prec > MAXFRACT) 
	    {
              if ((ch != 'g' && ch != 'G') || (flags&ALT))
                fpprec = prec - MAXFRACT;
              prec = MAXFRACT;
            } else if (prec == -1)
              prec = DEFPREC;
             /* __cvt_double may have to round up before the
                 "start" of its buffer, i.e.
                 ``intf("%.2f", (double)9.999);'';
                 if the first character is still NUL, it did.
                 softsign avoids negative 0 if _double < 0 but
                 no significant digits will be shown. */
            cp = buf;
            *cp = '\0';
            size = __cvt_double(_double, prec, flags, &softsign,
					    ch, cp, buf + sizeof(buf));
            if (softsign)
              sign = '-';
            if (*cp == '\0')
              cp++;
            break;
#endif
          }
#endif /* FLOATING_POINT */
          
          /* %% generates one percent sign. */

          case '%':
          {
            output[output_index++] = '%';;
            break;
          }

          /* Ignore anything else - it is simply unsupported. */

          default:
          {
            break;
          }
        }
        break;
      }
      
      /* All regular characters are just printed out. */
      
      default:
      {
        output[output_index++] = format_string[input_index];
        break;
      }
      
    }
    input_index++;
  }    

    output[output_index] = '\0';
  
    return STRING_RETURN_SUCCESS;
}

#define STD_SIZE	0
#define SHORT_SIZE	1
#define LONG_SIZE	2

int string_scan (char *input, char *format_string, ...)
{
  va_list arguments;
  int result;
    
  va_start (arguments, format_string);
  result = string_scan_va (input, format_string, arguments);
  va_end (arguments);
    
  return (result);
}

int string_scan_va (char *input, char *format_string, va_list arguments)
{
  /* FIXME: change names */
  int scanned = 0, size = 0;
  bool suppress = FALSE;
  int w = 0, flag = 0, l = 0;
  char c, *c_ptr;
  long int n1, *n1l;    
  int *n1b;
  short int *n1s;
  long unsigned n2, *n2l;
  bool parsing = FALSE;
  unsigned *n2b;
  short unsigned *n2s;
  double n3, *n3l;
  float *n3s;
  unsigned int count;

  while (*format_string != 0) 
  {
    if (*format_string != '%' && !parsing)
    {
      /* No token detected */
      format_string++;
    }
    else 
    {
      /* We need to make a conversion */
      if (*format_string == '%')
      {
        format_string++;
        parsing = TRUE;
	size = STD_SIZE;
	suppress = FALSE;
	w = 0;
	flag = 0;
	l = 0;
      }
      
      /* Parse token */
      switch (*format_string) 
      {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        {
          if (parsing) 
	  {
	    string_to_unsigned_int (format_string, &w, 10, &count);

	    /* We use SPACE_PAD to parse %10s
	       commands where the number is the
	       maximum number of char to store!
	     */
	     flag |= SPACE_PAD;
	     format_string += count - 1;
	  }
	  break;
        } /* case '1'..'0' */

        case 'c':
        {
          c = *input++;
	  c_ptr = va_arg (arguments, char *);
	  *c_ptr = c;
	  scanned++;
	  parsing = FALSE;
	  break;
        } /* case 'c' */
      
        case 's':
        {
          c_ptr = va_arg (arguments, char *);
	  
	  while (*input != 0 && char_is_space (*input))
	  {
	    input++;
	  }
	  l = 0;
	  
	  while (*input != 0 && !char_is_space (*input)) 
	  {
	    if (!(flag & SPACE_PAD))
	    {
	      *c_ptr++ = *input;
	    }
	    else if (l < w) 
	    {
	      *c_ptr++ = *input;
	      l++;
	    }
	    input++;	     
	  } /* while (*input != 0 && !isspace(*input)) */

	  *c_ptr = 0;
	  scanned++;
	  parsing = FALSE;
	  break;
        } /* case 's' */
      
        case 'i':
        case 'd':
        {
          input = string_scn (input, "1234567890-+");
	  string_to_signed_int (input, (int *) &n1, 10, &count);
	  input += count;
	  
	  if (!suppress)
	  {
	    switch (size) 
	    {
	      case STD_SIZE:
	      {
	        n1b = va_arg (arguments, int *);
	        *n1b = (int) n1;
	        break;
	      }
	    
	      case LONG_SIZE:
	      {
	        n1l = va_arg (arguments, long int *);
	        *n1l = n1;
	        break;
	      }
	    
	      case SHORT_SIZE:
	      {
	        n1s = va_arg (arguments, short int *);
                *n1s = (short) n1;
	        break;
	      }
	    } /* switch (size) */

	    scanned++;
	  } /* if (!suppress) */

	  parsing = FALSE;
          break;
        } /* case 'i', 'd' */
      
        case 'u':
        {
          input = string_scn (input, "1234567890");
          string_to_unsigned_int (input, (unsigned int *) &n2, 10, &count);
          input += count;
	
          if (!suppress)
	  {
	    switch (size) 
	    {
	      case STD_SIZE:
	      {
	        n2b = va_arg (arguments, unsigned *);
	 	*n2b = (unsigned) n2;
		break;
	      }
	      
	      case LONG_SIZE:
	      {
	        n2l = va_arg (arguments, long unsigned *);
		*n2l = n2;
		break;
	      }
	      
	      case SHORT_SIZE:
	      {
	        n2s = va_arg (arguments, short unsigned *);
		*n2s = (short) n2;
		break;
	      }
	    } /* switch (size) */

	    scanned++;
	  } /* if (!suppress) */

          parsing = FALSE;
          break;
        } /* case 'u' */

        case 'x':
        {
          input = string_scn (input, "1234567890xabcdefABCDEF");
	  string_to_unsigned_int (input, (unsigned int *) &n2, 16, &count);
	  input += count;
	
	  if (!suppress) 
	  {
	    switch (size) 
	    {				  
	      case STD_SIZE:
	      {
	        n2b = va_arg (arguments, unsigned *);
		*n2b = (unsigned) n2;
		break;
	      }
	      
	      case LONG_SIZE:
	      {
	        n2l = va_arg (arguments, long unsigned *);
		*n2l = n2;
		break;
	      }
	      
	      case SHORT_SIZE:
	      {
	        n2s = va_arg(arguments, short unsigned *);
		*n2s = (short) n2;
		break;
	      }
	    } /* switch (size) */

	    scanned++;
	  } /* if (!suppress) */

	  parsing = FALSE;
	  break;
        } /* case 'x' */

        case 'f':
        case 'g':
        case 'e':
        {
          input = string_scn (input, "1234567890.e+-");
	  string_to_double (input, &n3, &count);
	  input += count;
	
	  if (!suppress)
	  {			       
	    switch (size)
	    {
       	      case STD_SIZE:
	      {
	        n3l = va_arg (arguments, double *);
	        *n3l = n3;
	        break;
	      }
	      
	      case LONG_SIZE:
	      {
	        n3l = va_arg(arguments, double *);
	        *n3l = n3;
	        break;
	      }
	      
	      case SHORT_SIZE:
	      {
	        n3s = va_arg(arguments, float *);
	        *n3s = (float)(n3);
	        break;
	      }
	    } /* switch (size) */

	    scanned++;
	  } /* if (!suppress) */

	  parsing = FALSE;
	  break;
	} /* case 'f', 'g', 'e' */
	
	case 'l':
	{
	  size = LONG_SIZE;
	  break;
	} /* case 'l' */
	
	case 'n':
	{
	  size = SHORT_SIZE;
	  break;
	} /* case 'n' */
	
	case '*':
	{
	  suppress = TRUE;
	  break;
	} /* case '*' */
	
	default:
	{
	  parsing = FALSE;
	  break;
	} /* default */

      } /* switch (*format_string) */

      format_string++;
    } /* if (*format_string != '%' && !parsing) */

  } /* while (*format_string != 0) */
  
  return scanned;
}
