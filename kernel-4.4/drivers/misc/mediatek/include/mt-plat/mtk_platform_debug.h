
#ifndef __MTK_PLATFORM_DEBUG_H__
#define __MTK_PLATFORM_DEBUG_H__

#ifdef CONFIG_MTK_PLAT_SRAM_FLAG
/* plat_sram_flag */
extern int set_sram_flag_lastpc_valid(void);
extern int set_sram_flag_dfd_valid(void);
extern int set_sram_flag_etb_user(unsigned int etb_id, unsigned int user_id);

#define ETB_USER_BIG_CORE       0x0
#define ETB_USER_CM4            0x1
#define ETB_USER_AUDIO_CM4      0x2
#define ETB_USER_BUS_TRACER     0x3
#define ETB_USER_MCSIB_TRACER   0x4
#endif

#ifdef CONFIG_MTK_DFD_INTERNAL_DUMP
extern int dfd_setup(void);
#endif

#endif /* __MTK_PLATFORM_DEBUG_H__ */
