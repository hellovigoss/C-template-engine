#ifndef _D_TRACE_BACK_H
#define _D_TRACE_BACK_H

#include <execinfo.h>
#include <ucontext.h>


/* display_trace -- show the trace at calling this function */
static inline void display_trace( void )
{
	#define MAX_TRACE_SIZE	32
	int		itr, trace_size;
	void	*trace[ MAX_TRACE_SIZE ];
	char	**messages = NULL;

	trace_size = backtrace( trace, MAX_TRACE_SIZE );
	messages = backtrace_symbols( trace, trace_size );

	printf( "the stack trace is :\n" );
	for( itr = 0; itr < trace_size; itr ++ )
		printf( "[%d] %s\n", itr, messages[ itr ] );

	free( messages );
}

/* fault_handler -- fault handler, print the trace and exit */
void fault_handler( int sig, siginfo_t *info, void *ucontext )
{
	/* this structure mirrors the one found in /usr/include/asm/ucontext.h */
	typedef struct _sig_ucontext {
		unsigned long     uc_flags;
		struct ucontext   *uc_link;
		stack_t           uc_stack;
		struct sigcontext uc_mcontext;
		sigset_t          uc_sigmask;
	} sig_ucontext_t;

	sig_ucontext_t *uc = ( sig_ucontext_t * )ucontext;
	printf( "SIGNAL %d ( %s ) !!! address %p from %p\n", sig, strsignal( sig ), info->si_addr, ( void * )uc->uc_mcontext.eip );
	display_trace( );

	_exit( sig );
}

/* exit_handler -- handler for program exit */
void exit_handler( void )
{
	printf( "EXIT !!!\n" );
	display_trace( );
}

/* register_fault_handler -- register the handlers for crash backtrace */
void init_environments( void )
{
	struct sigaction	sa;

	// register the signal handlers, to show the trace at fault
	sa.sa_sigaction = ( void *)fault_handler;
	sigemptyset( &sa.sa_mask );
	sa.sa_flags = SA_RESTART | SA_SIGINFO;

	sigaction( SIGSEGV	, &sa, NULL );
	sigaction( SIGABRT	, &sa, NULL );
	sigaction( SIGBUS	, &sa, NULL );
	sigaction( SIGILL	, &sa, NULL );
	sigaction( SIGFPE	, &sa, NULL );

	// register my exit function, to show what happened before exiting
	atexit( exit_handler );
}

#endif
