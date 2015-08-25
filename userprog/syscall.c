#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/input.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  int syscall_num = *(int*) (f->esp);
  uint8_t *ptr = (uint8_t*) (f->esp);
  int fd, i;
  char *buffer;
  char *progname;
  unsigned size;
  char c;

  switch(syscall_num){
	case SYS_WRITE:
		size = *(unsigned*) (f->esp + 4);
		fd = *(int*) (f->esp + 8);
		buffer = (char *) (f->esp + 72);
		printf("\n");
		puts(buffer);

	break;

	case SYS_EXIT:
		thread_exit ();
	break;

	case SYS_WAIT:
		process_wait(f->esp+4);
	break;

	case SYS_READ:
		c = input_getc();
		c = (char) c;
		//*(uint8_t*) (ptr + 24) = c;
		f->eax = (char) (c);
		printf("%c", c);
	break;

	case SYS_EXEC:
		progname = *(char **) (f->esp + 4);
		f->eax = process_execute(progname);
	break;
  } 
}
