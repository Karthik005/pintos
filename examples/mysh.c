#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>

static void read_line (char line[], size_t);
static bool backspace (char **pos, char line[]);


int
main (int argc, char **argv)
{
  printf("Starting shell");
  putchar('\n');
  while(1){
  char command[80];
  // puts("");
  if (!strcmp (command, "exit"))
        break;
  read_line (command, 10);
  //printf("%s command", command);
  //printf("Got command");

  int pid = exec(command);
  wait(pid);
  }

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

                    
