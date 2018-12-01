
#ifndef __GED_GE_H__
#define __GED_GE_H__

#include <linux/types.h>

#include <ged_type.h>

int ged_ge_init(void);
int ged_ge_exit(void);
int ged_ge_alloc(int region_num, uint32_t *region_sizes);
int ged_ge_get(int ge_fd, int region_id, int u32_offset, int u32_size, uint32_t *output_data);
int ged_ge_set(int ge_fd, int region_id, int u32_offset, int u32_size, uint32_t *input_data);

#endif
