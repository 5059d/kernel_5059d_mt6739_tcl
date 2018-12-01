
#if !defined(__MRDUMP_MINI_H__)
struct mrdump_mini_extra_misc {
	void (*dump_func)(unsigned long *, unsigned long *);
	const char *dump_name;
	unsigned long max_size;
};
#ifdef CONFIG_MODULES
static char modules_info_buf[MODULES_INFO_BUF_SIZE];
extern int save_modules(char *mbuf, int mbufsize);
#endif
int mrdump_mini_init(void);
extern raw_spinlock_t logbuf_lock;
extern unsigned long *stack_trace;
extern void get_kernel_log_buffer(unsigned long *addr, unsigned long *size, unsigned long *start);
extern void get_hang_detect_buffer(unsigned long *addr, unsigned long *size, unsigned long *start);
#if defined(CONFIG_TRUSTY_LOG)
extern void get_gz_log_buffer(unsigned long *addr, unsigned long *size, unsigned long *start);
#endif
/* extern void get_android_log_buffer(unsigned long *addr, unsigned long *size, unsigned long *start, int type); */
extern struct ram_console_buffer *ram_console_buffer;
#endif
