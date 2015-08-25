#include <stdio.h>
#include <syscall.h>

static void read_line (char line[], size_t);
static bool backspace (char **pos, char line[]);


int
main (int argc, char **argv)
{
  char command[10];

  //printf("Starting PintOS shell");

  read_line (command, 10);
  printf("Got command\n");

  int pid = exec(command);
  printf("%d", pid);

  return EXIT_SUCCESS;
}

static void
read_line (char line[], size_t size)
{
  char *pos = line;
  int val;

  for (;pos < line + size - 1;)
    {
      char c, d;
      c = (char) read (STDIN_FILENO, &d, 1);
      val = (int) c;

      if(val == 13)
        return;
	
      switch (c)
        {
        case '\r':
          *pos = '\0';
          return;

        case '\b':
          backspace (&pos, line);
          break;

        case ('U' - 'A') + 1:       /* Ctrl+U. */
          while (backspace (&pos, line))
            continue;
          break;

        default:
          /* Add character to line. */
          if (pos < line + size - 1)
            {
	      putchar(c);
              *pos++ = c;
            }
	  else
	    {
		return;
	    }
          break;
        }
    }
}

static bool
backspace (char **pos, char line[])
{
  if (*pos > line)
    {
      /* Back up cursor, overwrite character, back up
         again. */
      printf ("\b \b");
      (*pos)--;
      return true;
    }
  else
    return false;
}

                    
