
#ifndef __GED_H__
#define __GED_H__

#include "ged_type.h"

typedef enum GED_NOTIFICATION_TYPE_TAG {
	GED_NOTIFICATION_TYPE_SW_VSYNC,
	GED_NOTIFICATION_TYPE_HW_VSYNC_PRIMARY_DISPLAY,
} GED_NOTIFICATION_TYPE;

void ged_notification(GED_NOTIFICATION_TYPE eType);
int ged_set_target_fps(unsigned int target_fps, int mode);
unsigned int ged_get_cur_fps(void);
void ged_get_latest_perf_state(long long *t_cpu_remained,
				long long *t_gpu_remained,
				long *t_cpu_target,
				long *t_gpu_target);

#endif
