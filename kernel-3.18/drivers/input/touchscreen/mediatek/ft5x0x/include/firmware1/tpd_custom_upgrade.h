
#ifndef TOUCHPANEL_UPGRADE_H__
#define TOUCHPANEL_UPGRADE_H__



/*#define CTP_DETECT_SUPPLIER_THROUGH_GPIO  1*/

#ifdef TPD_ALWAYS_UPGRADE_FW
#undef TPD_ALWAYS_UPGRADE_FW
#endif


#define TPD_SUPPLIER_0		0
#define TPD_SUPPLIER_1		1
#define TPD_SUPPLIER_2		2
#define TPD_SUPPLIER_3		3

#define TPD_FW_VER_0		0x00
#define TPD_FW_VER_1		0x11  /* ht tp   0   1 (choice 0) */
#define TPD_FW_VER_2            0x00
#define TPD_FW_VER_3            0x10  /* zxv tp  0   0 */


static unsigned char TPD_FW[] = {
#include "FT5436I_V0x22_20150526_app.i"
};
#ifdef CTP_DETECT_SUPPLIER_THROUGH_GPIO
static unsigned char TPD_FW0[] = {
#include "FT5436I_V0x22_20150526_app.i"
};

static unsigned char TPD_FW1[] = {
 /* #include "ft5x0x_fw_6127_ht.i" */
#include "FT5436I_V0x22_20150526_app.i"
};

static unsigned char TPD_FW2[] = {
#include "FT5436I_V0x22_20150526_app.i"
};

static unsigned char TPD_FW3[] = {
/* #include "ft5x0x_fw_6127_zxv.i" */
#include "FT5436I_V0x22_20150526_app.i"
};
#endif /* CTP_DETECT_SUPPLIER_THROUGH_GPIO */
#endif /* TOUCHPANEL_UPGRADE_H__ */
