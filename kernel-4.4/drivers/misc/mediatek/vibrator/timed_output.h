

#ifndef _LINUX_TIMED_OUTPUT_H
#define _LINUX_TIMED_OUTPUT_H

struct timed_output_dev {
	const char *name;

	/* enable the output and set the timer */
	void (*enable)(struct timed_output_dev *sdev, int timeout);

	/* returns the current number of milliseconds remaining on the timer */
	int (*get_time)(struct timed_output_dev *sdev);

	/* private data */
	struct device *dev;
	int index;
	int state;
};

extern int timed_output_dev_register(struct timed_output_dev *dev);
extern void timed_output_dev_unregister(struct timed_output_dev *dev);

#endif
