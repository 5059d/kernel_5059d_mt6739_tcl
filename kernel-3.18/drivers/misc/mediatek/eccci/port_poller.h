
#ifndef __PORT_POLLER_H__
#define __PORT_POLLER_H__

#include "ccci_core.h"

struct port_md_status_poller {
	unsigned long long latest_poll_start_time;
	unsigned int md_status_poller_flag;
	struct timer_list md_status_poller;
	struct timer_list md_status_timeout;
};
#endif	/* __PORT_POLLER_H__ */
