
/* USB Power delivery module */

#ifndef __CROS_EC_USB_PD_H
#define __CROS_EC_USB_PD_H

#include "mtk_typec.h"

/* PD Host command timeout */
#define PD_HOST_COMMAND_TIMEOUT_US SECOND

enum pd_transmit_type {
	PD_TX_SOP = 0,
	PD_TX_SOP_PRIME = 1,
	PD_TX_SOP_PRIME_PRIME = 2,
	PD_TX_HARD_RESET = 3,
	PD_TX_CABLE_RESET = 4,
	PD_TX_SOP_DEBUG_PRIME = 5,
	PD_TX_SOP_DEBUG_PRIME_PRIME = 6,
	PD_TX_BIST_MODE_2 = 7
};

enum pd_transmit_complete {
	PD_TX_COMPLETE_SUCCESS =   0,
	PD_TX_COMPLETE_DISCARDED = 1,
	PD_TX_COMPLETE_FAILED =    2,
};


enum pd_rx_errors {
	PD_RX_ERR_INVAL = -1,           /* Invalid packet */
	PD_RX_ERR_HARD_RESET = -2,      /* Got a Hard-Reset packet */
	PD_RX_ERR_CRC = -3,             /* CRC mismatch */
	PD_RX_ERR_ID = -4,              /* Invalid ID number */
	PD_RX_ERR_UNSUPPORTED_SOP = -5, /* Unsupported SOP */
	PD_RX_ERR_CABLE_RESET = -6      /* Got a Cable-Reset packet */
};

/* --- PD data message helpers --- */
#define PDO_MAX_OBJECTS   7
#define PDO_MODES (PDO_MAX_OBJECTS - 1)

/* PDO : Power Data Object */
#define PDO_TYPE_FIXED    (0 << 30)
#define PDO_TYPE_BATTERY  (1 << 30)
#define PDO_TYPE_VARIABLE (2 << 30)
#define PDO_TYPE_MASK     (3 << 30)

#define PDO_FIXED_DUAL_ROLE (1 << 29) /* Dual role device */
#define PDO_FIXED_HIGHER_CAP  (1 << 28) /* High Capability(SNK) */
#define PDO_FIXED_USB_SUSPEND  (1 << 28) /* USB Suspend Supported(SRC) */
#define PDO_FIXED_EXTERNAL  (1 << 27) /* Externally powered */
#define PDO_FIXED_COMM_CAP  (1 << 26) /* USB Communications Capable */
#define PDO_FIXED_DATA_SWAP (1 << 25) /* Data role swap command supported */
#define PDO_FIXED_PEAK_CURR_MSK (0x3 << 20) /* Peak current */
#define PDO_FIXED_PEAK_CURR_OFST (20) /* [21..20] Peak current */
#define PDO_FIXED_VOLT_MSK (0x3FF << 10)
#define PDO_FIXED_VOLT_OFST (10) /* [19..10] Voltage in 50mV units */
#define PDO_FIXED_CURR_MSK (0x3FF << 0)
#define PDO_FIXED_CURR_OFST (0) /* [9..0] Maximum Current in 10mA units */
#define PDO_FIXED_VOLT(mv)  (((mv)/50) << 10) /* Voltage in 50mV units */
#define PDO_FIXED_CURR(ma)  (((ma)/10) << 0)  /* Max current in 10mA units */

#define PDO_FIXED(mv, ma, flags) (PDO_FIXED_VOLT(mv) | \
				  PDO_FIXED_CURR(ma) | (flags) | \
				  PDO_TYPE_FIXED)

#define PDO_VAR_MAX_VOLT_MSK (0x3FF << 20)
#define PDO_VAR_MAX_VOLT_OFST (20) /* [29..20] Maximum Voltage in 50mV units */
#define PDO_VAR_MIN_VOLT_MSK (0x3FF << 10)
#define PDO_VAR_MIN_VOLT_OFST (10) /* [19..10] Minimum Voltage in 50mV units */
#define PDO_VAR_CURR_MSK (0x3FF << 0)
#define PDO_VAR_CURR_OFST (0) /* [9..0] Maximum Current in 10mA units */

#define PDO_VAR_MAX_VOLT(mv) ((((mv) / 50) & 0x3FF) << 20)
#define PDO_VAR_MIN_VOLT(mv) ((((mv) / 50) & 0x3FF) << 10)
#define PDO_VAR_OP_CURR(ma)  ((((ma) / 10) & 0x3FF) << 0)

#define PDO_VAR(min_mv, max_mv, op_ma) \
				(PDO_VAR_MIN_VOLT(min_mv) | \
				 PDO_VAR_MAX_VOLT(max_mv) | \
				 PDO_VAR_OP_CURR(op_ma)   | \
				 PDO_TYPE_VARIABLE)

#define PDO_BATT_MAX_VOLT_MSK (0x3FF << 20)
#define PDO_BATT_MAX_VOLT_OFST (20) /* [29..20] Maximum Voltage in 50mV units */
#define PDO_BATT_MIN_VOLT_MSK (0x3FF << 10)
#define PDO_BATT_MIN_VOLT_OFST (10) /* [19..10] Minimum Voltage in 50mV units */
#define PDO_BATT_PWR_MSK (0x3FF << 0)
#define PDO_BATT_PWR_OFST (0) /* [9..0] Maximum Current in 10mA units */

#define PDO_BATT_MAX_VOLT(mv) ((((mv) / 50) & 0x3FF) << 20)
#define PDO_BATT_MIN_VOLT(mv) ((((mv) / 50) & 0x3FF) << 10)
#define PDO_BATT_OP_POWER(mw) ((((mw) / 250) & 0x3FF) << 0)

#define PDO_BATT(min_mv, max_mv, op_mw) \
				(PDO_BATT_MIN_VOLT(min_mv) | \
				 PDO_BATT_MAX_VOLT(max_mv) | \
				 PDO_BATT_OP_POWER(op_mw) | \
				 PDO_TYPE_BATTERY)

/* RDO : Request Data Object */
#define RDO_OBJ_POS(n)             (((n) & 0x7) << 28)
#define RDO_POS(rdo)               (((rdo) >> 28) & 0x7)
#define RDO_GIVE_BACK              (1 << 27)
#define RDO_CAP_MISMATCH           (1 << 26)
#define RDO_COMM_CAP               (1 << 25)
#define RDO_NO_SUSPEND             (1 << 24)
#define RDO_FIXED_VAR_OP_CURR(ma)  ((((ma) / 10) & 0x3FF) << 10)
#define RDO_FIXED_VAR_MAX_CURR(ma) ((((ma) / 10) & 0x3FF) << 0)

#define RDO_BATT_OP_POWER(mw)      ((((mw) / 250) & 0x3FF) << 10)
#define RDO_BATT_MAX_POWER(mw)     ((((mw) / 250) & 0x3FF) << 10)

#define RDO_FIXED(n, op_ma, max_ma, flags) \
				(RDO_OBJ_POS(n) | (flags) | \
				RDO_FIXED_VAR_OP_CURR(op_ma) | \
				RDO_FIXED_VAR_MAX_CURR(max_ma))


#define RDO_BATT(n, op_mw, max_mw, flags) \
				(RDO_OBJ_POS(n) | (flags) | \
				RDO_BATT_OP_POWER(op_mw) | \
				RDO_BATT_MAX_POWER(max_mw))

/* BDO : BIST Data Object */
#define BDO_MODE_RECV       (0 << 28)
#define BDO_MODE_TRANSMIT   (1 << 28)
#define BDO_MODE_COUNTERS   (2 << 28)
#define BDO_MODE_CARRIER0   (3 << 28)
#define BDO_MODE_CARRIER1   (4 << 28)
#define BDO_MODE_CARRIER2   (5 << 28)
#define BDO_MODE_CARRIER3   (6 << 28)
#define BDO_MODE_EYE        (7 << 28)
#define BDO_MODE_TEST_DATA  (8 << 28)


#define BDO(mode, cnt)      ((mode) | ((cnt) & 0xFFFF))

#define SVID_DISCOVERY_MAX 36

/* Timers */
#define PD_T_SEND_SOURCE_CAP  (150*1) /* tTypeCSendSourceCap: 100ms-200ms */
#define PD_T_SINK_WAIT_CAP    (420*1) /* tTypeCSinkWaitCap: 310ms-620ms */
#define PD_T_SRC_TRANSITION    (30*1) /* tSrcTransition: 25ms-35ms */
#define PD_T_SOURCE_ACTIVITY   (45*1) /* tSourceActivity: 40ms-50ms */
#define PD_T_SENDER_RESPONSE   (27*1) /* tSenderResponse: 24ms-30ms */
#define PD_T_SWAP_SOURCE_START (50*1) /* tSwapSourceStart: 20ms- */
#define PD_T_PS_TRANSITION    (500*1) /* tPSTransition: 450ms-550ms */
#define PD_T_PS_SOURCE_ON     (460*1) /* tPSSourceOn: 390ms-480ms */
#define PD_T_PS_SOURCE_OFF    (880*1) /* tPSSourceOff: 750ms-920ms */
#define PD_T_PS_HARD_RESET     (25*1) /* tPSHardReset: 25ms-35ms */
#define PD_T_ERROR_RECOVERY    (25*1) /* 25ms */
#define PD_T_NO_ACTIVITY    (1000*1)
#if 0
#define PD_T_CC_DEBOUNCE       (100*1) /* between 100ms and 200ms */
/* DRP_SNK + DRP_SRC must be between 50ms and 100ms with 30%-70% duty cycle */
#define PD_T_DRP_SNK           (40*1) /* toggle time for sink DRP */
#define PD_T_DRP_SRC           (30*1) /* toggle time for source DRP */
#define PD_T_DEBOUNCE          (15*1) /* between 10ms and 20ms */
#endif
#define PD_T_SINK_ADJ          (55*1) /* between PD_T_DEBOUNCE and 60ms */
#define PD_T_SRC_RECOVER      (900*1) /* between 660ms and 1000ms */
#define PD_T_SRC_RECOVER_MAX (1000*1) /* 1000ms */
#define PD_T_SRC_TURN_ON      (275*1) /* 275ms */
#define PD_T_SAFE_0V          (650*1) /* 650ms */
#define PD_T_NO_RESPONSE     (5500*1) /* between 4.5s and 5.5s */
#define PD_T_BIST_TRANSMIT     (45*1) /* 50ms (used for task_wait arg) */
#define PD_T_BIST_RECEIVE      (60*1) /* 60ms (max time to process bist) */
#define PD_T_VCONN_SOURCE_ON  (100*1) /* 100ms */
#if 0
#define PD_T_TRY_SRC          (125*1) /* Max time for Try.SRC state */
#define PD_T_TRY_WAIT         (600*1) /* Max time for TryWait.SNK state */
#endif

#if 0
/* number of edges and time window to detect CC line is not idle */
#define PD_RX_TRANSITION_COUNT  3
#define PD_RX_TRANSITION_WINDOW 20 /* between 12us and 20us */
#endif

/* from USB Type-C Specification Table 5-1 */
#define PD_T_AME (1*SECOND) /* timeout from UFP attach to Alt Mode Entry */

/* VDM Timers ( USB PD Spec Rev2.0 Table 6-30 )*/
#define PD_T_VDM_BUSY         (100*1) /* tVDMBusy >50ms */
#define PD_T_VDM_E_MODE        (25*1) /* tVDMEnterMode/tVDMExitMode <25ms */
#define PD_T_VDM_RCVR_RSP      (15*1) /* tVDMReceiverResponse <15ms */
#define PD_T_VDM_SNDR_RSP      (30*1) /* tVDMSenderResponse 24~30ms */
#define PD_T_VDM_WAIT_MODE_E  (50*1) /* tVDMWaitModeEntry/tVDMWaitModeExit 40~50ms */

struct typec_hba;

/* function table for entered mode */
struct amode_fx {
	int (*status)(struct typec_hba *hba, uint32_t *payload);
	int (*config)(struct typec_hba *hba, uint32_t *payload);
};

/* function table for alternate mode capable responders */
struct svdm_response {
	int (*identity)(struct typec_hba *hba, uint32_t *payload);
	int (*svids)(struct typec_hba *hba, uint32_t *payload);
	int (*modes)(struct typec_hba *hba, uint32_t *payload);
	int (*enter_mode)(struct typec_hba *hba, uint32_t *payload);
	int (*exit_mode)(struct typec_hba *hba, uint32_t *payload);
	struct amode_fx *amode;
};

struct svdm_svid_data {
	uint16_t svid;
	int mode_cnt;
	uint32_t mode_vdo[PDO_MODES];
};

struct svdm_amode_fx {
	uint16_t svid;
	int (*enter)(struct typec_hba *hba, uint32_t mode_caps);
	int (*status)(struct typec_hba *hba, uint32_t *payload);
	int (*config)(struct typec_hba *hba, uint32_t *payload);
	void (*post_config)(struct typec_hba *hba);
	int (*attention)(struct typec_hba *hba, uint32_t *payload);
	void (*exit)(struct typec_hba *hba);
};

/* defined in <board>/usb_pd_policy.c */
/* All UFP_U should have */
extern const struct svdm_response svdm_rsp;
/* All DFP_U should have */
extern const struct svdm_amode_fx supported_modes[];
extern const int supported_modes_cnt;

/* DFP data needed to support alternate mode entry and exit */
struct svdm_amode_data {
	const struct svdm_amode_fx *fx;
	/* VDM object position */
	int opos;
	/* mode capabilities specific to SVID amode. */
	struct svdm_svid_data *data;
};

enum hpd_event {
	hpd_none,
	hpd_low,
	hpd_high,
	hpd_irq,
};

/* DisplayPort flags */
#define DP_FLAGS_DP_ON              (1 << 0) /* Display port mode is on */
#define DP_FLAGS_HPD_HI_PENDING     (1 << 1) /* Pending HPD_HI */

/* supported alternate modes */
enum pd_alternate_modes {
	PD_AMODE_DISPLAYPORT,
#ifdef CONFIG_RT7207_ADAPTER
	PD_AMODE_RT7207,
#endif
	/* not a real mode */
	PD_AMODE_COUNT,
};

/* Policy structure for driving alternate mode */
struct pd_policy {
	/* index of svid currently being operated on */
	int svid_idx;
	/* count of svids discovered */
	int svid_cnt;
	/* SVDM identity info (Id, Cert Stat, 0-4 Typec specific) */
	uint32_t identity[PDO_MAX_OBJECTS - 1];
	/* supported svids & corresponding vdo mode data */
	struct svdm_svid_data svids[SVID_DISCOVERY_MAX];
	/*  active modes */
	struct svdm_amode_data amodes[PD_AMODE_COUNT];
	/* Next index to insert DFP alternate mode into amodes */
	int amode_idx;
};


#define VDO_MAX_SIZE 7
#define VDO(vid, type, custom)				\
	(((vid) << 16) |				\
	 ((type) << 15) |				\
	 ((custom) & 0x7FFF))

#define VDO_SVDM_TYPE     (1 << 15)
#define VDO_SVDM_VERS(x)  (x << 13)
#define VDO_OPOS(x)       (x << 8)
#define VDO_CMDT(x)       (x << 6)
#define VDO_OPOS_MASK     VDO_OPOS(0x7)
#define VDO_CMDT_MASK     VDO_CMDT(0x3)

#define CMDT_INIT     0
#define CMDT_RSP_ACK  1
#define CMDT_RSP_NAK  2
#define CMDT_RSP_BUSY 3


/* reserved for SVDM ... for Google UVDM */
#define VDO_SRC_INITIATOR (0 << 5)
#define VDO_SRC_RESPONDER (1 << 5)

#define CMD_DISCOVER_IDENT  1
#define CMD_DISCOVER_SVID   2
#define CMD_DISCOVER_MODES  3
#define CMD_ENTER_MODE      4
#define CMD_EXIT_MODE       5
#define CMD_ATTENTION       6
#define CMD_DP_STATUS      16
#define CMD_DP_CONFIG      17

#define VDO_CMD_VENDOR(x)    (((10 + (x)) & 0x1f))

#if 0
/* ChromeOS specific commands */
#define VDO_CMD_VERSION      VDO_CMD_VENDOR(0)
#define VDO_CMD_SEND_INFO    VDO_CMD_VENDOR(1)
#define VDO_CMD_READ_INFO    VDO_CMD_VENDOR(2)
#define VDO_CMD_REBOOT       VDO_CMD_VENDOR(5)
#define VDO_CMD_FLASH_ERASE  VDO_CMD_VENDOR(6)
#define VDO_CMD_FLASH_WRITE  VDO_CMD_VENDOR(7)
#define VDO_CMD_ERASE_SIG    VDO_CMD_VENDOR(8)
#define VDO_CMD_PING_ENABLE  VDO_CMD_VENDOR(10)
#define VDO_CMD_CURRENT      VDO_CMD_VENDOR(11)
#define VDO_CMD_FLIP         VDO_CMD_VENDOR(12)
#define VDO_CMD_GET_LOG      VDO_CMD_VENDOR(13)
#define VDO_CMD_CCD_EN       VDO_CMD_VENDOR(14)
#endif

#define PD_VDO_VID(vdo)  ((vdo) >> 16)
#define PD_VDO_SVDM(vdo) (((vdo) >> 15) & 1)
#define PD_VDO_OPOS(vdo) (((vdo) >> 8) & 0x7)
#define PD_VDO_CMD(vdo)  ((vdo) & 0x1f)
#define PD_VDO_CMDT(vdo) (((vdo) >> 6) & 0x3)

#define VDO_INDEX_HDR     0
#define VDO_INDEX_IDH     1
#define VDO_INDEX_CSTAT   2
#define VDO_INDEX_CABLE   3
#define VDO_INDEX_PRODUCT 3
#define VDO_INDEX_AMA     4
#define VDO_I(name) VDO_INDEX_##name

#define IDH_PTYPE_UNDEF  0
#define IDH_PTYPE_HUB    1
#define IDH_PTYPE_PERIPH 2
#define IDH_PTYPE_PCABLE 3
#define IDH_PTYPE_ACABLE 4
#define IDH_PTYPE_AMA    5

#define VDO_IDH(usbh, usbd, ptype, is_modal, vid)		\
	((usbh) << 31 | (usbd) << 30 | ((ptype) & 0x7) << 27	\
	 | (is_modal) << 26 | ((vid) & 0xffff))

#define PD_IDH_PTYPE(vdo) (((vdo) >> 27) & 0x7)
#define PD_IDH_VID(vdo)   ((vdo) & 0xffff)
#define PD_IDH_USB_HOST(vdo) (((vdo) >> 31) & 0x1)
#define PD_IDH_USB_DEVICE(vdo) (((vdo) >> 30) & 0x1)
#define PD_IDH_MODAL(vdo) (((vdo) >> 26) & 0x1)

#define VDO_CSTAT(tid)    ((tid) & 0xfffff)
#define PD_CSTAT_TID(vdo) ((vdo) & 0xfffff)

#define VDO_PRODUCT(pid, bcd) (((pid) & 0xffff) << 16 | ((bcd) & 0xffff))
#define PD_PRODUCT_PID(vdo) (((vdo) >> 16) & 0xffff)
#define PD_PRODUCT_BCD(vdo) (((vdo) >> 0) & 0xffff)

#define CABLE_ATYPE 0
#define CABLE_BTYPE 1
#define CABLE_CTYPE 2
#define CABLE_PLUG       0
#define CABLE_RECEPTACLE 1
#define CABLE_CURR_1A5   0
#define CABLE_CURR_3A    1
#define CABLE_CURR_5A    2
#define CABLE_USBSS_U2_ONLY  0
#define CABLE_USBSS_U31_GEN1 1
#define CABLE_USBSS_U31_GEN2 2
#define VDO_CABLE(hw, fw, cbl, gdr, lat, term, tx1d, tx2d, rx1d, rx2d, cur, vps, sopp, usbss) \
	(((hw) & 0x7) << 28 | ((fw) & 0x7) << 24 | ((cbl) & 0x3) << 18	\
	 | (gdr) << 17 | ((lat) & 0x7) << 13 | ((term) & 0x3) << 11	\
	 | (tx1d) << 10 | (tx2d) << 9 | (rx1d) << 8 | (rx2d) << 7	\
	 | ((cur) & 0x3) << 5 | (vps) << 4 | (sopp) << 3		\
	 | ((usbss) & 0x7))

#define PD_CABLE_HW_VER(vdo) (((vdo) >> 28) & 0xf)
#define PD_CABLE_FW_VER(vdo) (((vdo) >> 24) & 0xf)
#define PD_CABLE_CABLE_TYPE(vdo) (((vdo) >> 18) & 0x3)
#define PD_CABLE_PLUG_OR_REC(vdo) (((vdo) >> 17) & 0x1)
#define PD_CABLE_LATENCY(vdo) (((vdo) >> 13) & 0xf)
#define PD_CABLE_TERM_TYPE(vdo) (((vdo) >> 11) & 0x3)
#define PD_CABLE_SSTX1(vdo) (((vdo) >> 10) & 0x1)
#define PD_CABLE_SSTX2(vdo) (((vdo) >> 9) & 0x1)
#define PD_CABLE_SSRX1(vdo) (((vdo) >> 8) & 0x1)
#define PD_CABLE_SSRX2(vdo) (((vdo) >> 7) & 0x1)
#define PD_CABLE_VBUS_CAP(vdo) (((vdo) >> 5) & 0x3)
#define PD_CABLE_VBUS_THRO(vdo) (((vdo) >> 4) & 0x1)
#define PD_CABLE_SOP_PP(vdo) (((vdo) >> 3) & 0x1)
#define PD_CABLE_USB_SPEED(vdo) (((vdo) >> 0) & 0x3)

#define VDO_AMA(hw, fw, tx1d, tx2d, rx1d, rx2d, vcpwr, vcr, vbr, usbss) \
	(((hw) & 0x7) << 28 | ((fw) & 0x7) << 24			\
	 | (tx1d) << 11 | (tx2d) << 10 | (rx1d) << 9 | (rx2d) << 8	\
	 | ((vcpwr) & 0x3) << 5 | (vcr) << 4 | (vbr) << 3		\
	 | ((usbss) & 0x7))

#define PD_VDO_AMA_VCONN_REQ(vdo) (((vdo) >> 4) & 1)
#define PD_VDO_AMA_VBUS_REQ(vdo)  (((vdo) >> 3) & 1)

#define AMA_VCONN_PWR_1W   0
#define AMA_VCONN_PWR_1W5  1
#define AMA_VCONN_PWR_2W   2
#define AMA_VCONN_PWR_3W   3
#define AMA_VCONN_PWR_4W   4
#define AMA_VCONN_PWR_5W   5
#define AMA_VCONN_PWR_6W   6
#define AMA_USBSS_U2_ONLY  0
#define AMA_USBSS_U31_GEN1 1
#define AMA_USBSS_U31_GEN2 2
#define AMA_USBSS_BBONLY   3

#define VDO_SVID(svid0, svid1) (((svid0) & 0xffff) << 16 | ((svid1) & 0xffff))
#define PD_VDO_SVID_SVID0(vdo) ((vdo) >> 16)
#define PD_VDO_SVID_SVID1(vdo) ((vdo) & 0xffff)

#if 0
#define VDO_MODE_GOOGLE(mode) (mode & 0xff)

#define MODE_GOOGLE_FU 1 /* Firmware Update mode */
#endif

#define VDO_MODE_CNT_DISPLAYPORT 1

#define VDO_MODE_DP(snkp, srcp, usb, gdr, sign, sdir)			\
	(((snkp) & 0xff) << 16 | ((srcp) & 0xff) << 8			\
	 | ((usb) & 1) << 7 | ((gdr) & 1) << 6 | ((sign) & 0xF) << 2	\
	 | ((sdir) & 0x3))
#define PD_DP_PIN_CAPS(x) ((((x) >> 6) & 0x1) ? (((x) >> 16) & 0x3f)	\
			   : (((x) >> 8) & 0x3f))

#define MODE_DP_PIN_A 0x01
#define MODE_DP_PIN_B 0x02
#define MODE_DP_PIN_C 0x04
#define MODE_DP_PIN_D 0x08
#define MODE_DP_PIN_E 0x10
#define MODE_DP_PIN_F 0x20

/* Pin configs B/D/F support multi-function */
#define MODE_DP_PIN_MF_MASK 0x2a
/* Pin configs A/B support BR2 signaling levels */
#define MODE_DP_PIN_BR2_MASK 0x3
/* Pin configs C/D/E/F support DP signaling levels */
#define MODE_DP_PIN_DP_MASK 0x3c

#define MODE_DP_V13  0x1
#define MODE_DP_GEN2 0x2

#define MODE_DP_SNK  0x1
#define MODE_DP_SRC  0x2
#define MODE_DP_BOTH 0x3

#define VDO_DP_STATUS(irq, lvl, amode, usbc, mf, en, lp, conn)		\
	(((irq) & 1) << 8 | ((lvl) & 1) << 7 | ((amode) & 1) << 6	\
	 | ((usbc) & 1) << 5 | ((mf) & 1) << 4 | ((en) & 1) << 3	\
	 | ((lp) & 1) << 2 | ((conn & 0x3) << 0))

#define PD_VDO_DPSTS_HPD_IRQ(x) (((x) >> 8) & 1)
#define PD_VDO_DPSTS_HPD_LVL(x) (((x) >> 7) & 1)
#define PD_VDO_DPSTS_MF_PREF(x) (((x) >> 4) & 1)
#define PD_VDO_DPSTS_CONNECT(x) (((x) >> 0) & 3)


/* Per DisplayPort Spec v1.3 Section 3.3 */
#define HPD_USTREAM_DEBOUNCE_LVL (2*1)
#define HPD_USTREAM_DEBOUNCE_IRQ (250)
#define HPD_DSTREAM_DEBOUNCE_IRQ (750)  /* between 500-1000us */

#define VDO_DP_CFG(pin, sig, cfg) \
	(((pin) & 0xff) << 8 | ((sig) & 0xf) << 2 | ((cfg) & 0x3))

#define PD_DP_CFG_DPON(x) (((x & 0x3) == 1) || ((x & 0x3) == 2))
#define PD_DP_CFG_PIN(x) ((((x) >> 8) & 0xff) ? (((x) >> 8) & 0xff) \
					      : (((x) >> 16) & 0xff))

#if 0
#define USB_PD_HW_DEV_ID_RESERVED    0
#define USB_PD_HW_DEV_ID_ZINGER      1
#define USB_PD_HW_DEV_ID_MINIMUFFIN  2
#define USB_PD_HW_DEV_ID_DINGDONG    3
#define USB_PD_HW_DEV_ID_HOHO        4
#define USB_PD_HW_DEV_ID_HONEYBUNS   5

#define VDO_INFO(id, id_minor, ver, is_rw) ((id_minor) << 26 \
				  | ((id) & 0x3ff) << 16 \
				  | ((ver) & 0x7fff) << 1 \
				  | ((is_rw) & 1))
#define VDO_INFO_HW_DEV_ID(x)    ((x) >> 16)
#define VDO_INFO_SW_DBG_VER(x)   (((x) >> 1) & 0x7fff)
#define VDO_INFO_IS_RW(x)        ((x) & 1)

#define HW_DEV_ID_MAJ(x) (x & 0x3ff)
#define HW_DEV_ID_MIN(x) ((x) >> 10)
#endif

/* USB-IF SIDs */
#define USB_SID_PD          0xff00 /* power delivery */
#define USB_SID_DISPLAYPORT 0xff01

#define CONFIG_USB_PID 0x0000
#define CONFIG_USB_BCD_DEV 0x0100 /* v 0.01 */

#define USB_VID_MEDIATEK 0x0e8d

/* USB Vendor ID assigned to Google Inc. */
#define USB_VID_GOOGLE 0x18d1

/* Other Vendor IDs */
#define USB_VID_APPLE  0x05ac

#define MTK_XID 2950

/* Timeout for message receive in microseconds */
#define USB_PD_RX_TMOUT_US 1800

/* --- Protocol layer functions --- */

enum pd_states {
	PD_STATE_DISABLED = 0,
	PD_STATE_SUSPENDED = 1,
#ifdef CONFIG_USB_PD_DUAL_ROLE
	PD_STATE_SNK_UNATTACH = 2,
	PD_STATE_SNK_ATTACH = 3,
	PD_STATE_SNK_HARD_RESET_RECOVER = 4,
	PD_STATE_SNK_DISCOVERY = 5,
	PD_STATE_SNK_REQUESTED = 6,
	PD_STATE_SNK_TRANSITION = 7,
	PD_STATE_SNK_READY = 8,
	PD_STATE_SNK_SWAP_INIT = 9,
	PD_STATE_SNK_SWAP_SNK_DISABLE = 10,
	PD_STATE_SNK_SWAP_SRC_DISABLE = 11,
	PD_STATE_SNK_SWAP_STANDBY = 12,
	PD_STATE_SNK_SWAP_COMPLETE = 13,
#endif /* CONFIG_USB_PD_DUAL_ROLE */
	PD_STATE_SRC_UNATTACH = 14,
	PD_STATE_SRC_ATTACH = 15,
	PD_STATE_SRC_HARD_RESET_RECOVER = 16,
	PD_STATE_SRC_STARTUP = 17,
	PD_STATE_SRC_DISCOVERY = 18,
	PD_STATE_SRC_NEGOTIATE = 19,
	PD_STATE_SRC_ACCEPTED = 20,
	PD_STATE_SRC_POWERED = 21,
	PD_STATE_SRC_TRANSITION = 22,
	PD_STATE_SRC_READY = 23,
	PD_STATE_SRC_GET_SINK_CAP = 24,
	PD_STATE_DR_SWAP = 25,
#ifdef CONFIG_USB_PD_DUAL_ROLE
	PD_STATE_SRC_SWAP_INIT = 26,
	PD_STATE_SRC_SWAP_SNK_DISABLE = 27,
	PD_STATE_SRC_SWAP_SRC_DISABLE = 28,
	PD_STATE_SRC_SWAP_STANDBY = 29,
#ifdef CONFIG_USBC_VCONN_SWAP
	PD_STATE_VCONN_SWAP_SEND = 30,
	PD_STATE_VCONN_SWAP_INIT = 31,
	PD_STATE_VCONN_SWAP_READY = 32,
#endif /* CONFIG_USBC_VCONN_SWAP */
#endif /* CONFIG_USB_PD_DUAL_ROLE */
	PD_STATE_SOFT_RESET = 33,
	PD_STATE_HARD_RESET_SEND = 34,
	PD_STATE_HARD_RESET_EXECUTE = 35,
	PD_STATE_BIST_CMD = 36,
	PD_STATE_BIST_CARRIER_MODE_2 = 37,
	PD_STATE_BIST_TEST_DATA = 38,
	PD_STATE_HARD_RESET_RECEIVED = 39,
	PD_STATE_DISCOVERY_SOP_P = 40,
	PD_STATE_SRC_DISABLED = 41,
	PD_STATE_SNK_HARD_RESET_NOVSAFE5V = 42,
	PD_STATE_SNK_KPOC_PWR_OFF = 43,

	/* Not actual states */
	PD_STATE_NO_TIMEOUT,
	PD_STATE_COUNT,
};

#define PD_FLAGS_PING_ENABLED      (1 << 0) /* SRC_READY pings enabled */
#define PD_FLAGS_PARTNER_DR_POWER  (1 << 1) /* port partner is dualrole power */
#define PD_FLAGS_PARTNER_DR_DATA   (1 << 2) /* port partner is dualrole data */
#define PD_FLAGS_DATA_SWAPPED      (1 << 3) /* data swap complete */
#define PD_FLAGS_SNK_CAP_RECVD     (1 << 4) /* sink capabilities received */
#define PD_FLAGS_EXPLICIT_CONTRACT (1 << 6) /* explicit pwr contract in place */
#define PD_FLAGS_SFT_RST_DIS_COMM  (1 << 7) /* disable comms after soft reset */
#define PD_FLAGS_PREVIOUS_PD_CONN  (1 << 8) /* previously PD connected */
#define PD_FLAGS_CHECK_PR_ROLE     (1 << 9) /* check power role in READY */
#define PD_FLAGS_CHECK_DR_ROLE     (1 << 10)/* check data role in READY */
#define PD_FLAGS_PARTNER_EXTPOWER  (1 << 11)/* port partner has external pwr */
#define PD_FLAGS_VCONN_ON          (1 << 12)/* vconn is being sourced */
#define PD_FLAGS_TRY_SRC           (1 << 13)/* Try.SRC states are active */
#define PD_FLAGS_POWER_SWAPPED     (1 << 14)/* power swap complete */
#define PD_FLAGS_TIMEOUT           (1 << 15)/* go to timeout state */
#define PD_FLAGS_SRC_NO_PD           (1 << 16)/* SRC does not support PD */

/* Flags to clear on a disconnect */
#define PD_FLAGS_RESET_ON_DISCONNECT_MASK (PD_FLAGS_PARTNER_DR_POWER | \
					   PD_FLAGS_PARTNER_DR_DATA | \
					   PD_FLAGS_DATA_SWAPPED | \
					   PD_FLAGS_SNK_CAP_RECVD | \
					   PD_FLAGS_EXPLICIT_CONTRACT | \
					   PD_FLAGS_PREVIOUS_PD_CONN | \
					   PD_FLAGS_CHECK_PR_ROLE | \
					   PD_FLAGS_CHECK_DR_ROLE | \
					   PD_FLAGS_PARTNER_EXTPOWER | \
					   PD_FLAGS_VCONN_ON | \
					   PD_FLAGS_TRY_SRC | \
					   PD_FLAGS_TIMEOUT | \
					   PD_FLAGS_SRC_NO_PD | \
					   0)

#define PD_FLAGS_CBL_NO_INFO			(1 << 0)
#define PD_FLAGS_CBL_DISCOVERYING_SOP_P	(1 << 1)
#define PD_FLAGS_CBL_DISCOVERIED_SOP_P	(1 << 2)
#define PD_FLAGS_CBL_NO_RESP_SOP_P		(1 << 3)
#define PD_FLAGS_CBL_DISCOVERYING_SOP_PP	(1 << 4)
#define PD_FLAGS_CBL_DISCOVERIED_SOP_PP	(1 << 5)
#define PD_FLAGS_CBL_NO_RESP_SOP_PP		(1 << 6)

/* Control Message type */
enum pd_ctrl_msg_type {
	PD_CTRL_RESERVED = 0,
	PD_CTRL_GOOD_CRC = 1,
	PD_CTRL_GOTO_MIN = 2,
	PD_CTRL_ACCEPT = 3,
	PD_CTRL_REJECT = 4,
	PD_CTRL_PING = 5,
	PD_CTRL_PS_RDY = 6,
	PD_CTRL_GET_SOURCE_CAP = 7,
	PD_CTRL_GET_SINK_CAP = 8,
	PD_CTRL_DR_SWAP = 9,
	PD_CTRL_PR_SWAP = 10,
	PD_CTRL_VCONN_SWAP = 11,
	PD_CTRL_WAIT = 12,
	PD_CTRL_SOFT_RESET = 13,
	/* 14-15 Reserved */
};

/* Data message type */
enum pd_data_msg_type {
	/* 0 Reserved */
	PD_DATA_SOURCE_CAP = 1,
	PD_DATA_REQUEST = 2,
	PD_DATA_BIST = 3,
	PD_DATA_SINK_CAP = 4,
	/* 5-14 Reserved */
	PD_DATA_VENDOR_DEF = 15,
};

/* Protocol revision */
#define PD_REV10 0
#define PD_REV20 1

/* Power role */
#define PD_ROLE_SINK   0
#define PD_ROLE_SOURCE 1

/* Data role */
#define PD_ROLE_UFP    0
#define PD_ROLE_DFP    1

#define PD_NO_ROLE  2

/* Vconn role */
#define PD_ROLE_VCONN_OFF 0
#define PD_ROLE_VCONN_ON  1

/* Port role at startup */
#ifdef CONFIG_USB_PD_DUAL_ROLE
#define PD_ROLE_DEFAULT PD_ROLE_SINK
#else
#define PD_ROLE_DEFAULT PD_ROLE_SOURCE
#endif

/* build message header */
#define PD_HEADER(type, prole, drole, cnt) \
	((type & 0xf) | ((drole) << 5) | (PD_REV20 << 6) | ((prole) << 8) | ((cnt) << 12))

#define PD_HEADER_CNT(header)  (((header) >> 12) & 0x7)
#define PD_HEADER_TYPE(header) ((header) & 0xF)
#define PD_HEADER_ID(header)   (((header) >> 9) & 0x7)
#define PD_HEADER_ID_MSK (0x7<<9)
#define PD_HEADER_SOP(header) (((header) >> 8) & 0x1)

/* K-codes for special symbols */
#define PD_SYNC1 0x18
#define PD_SYNC2 0x11
#define PD_SYNC3 0x06
#define PD_RST1  0x07
#define PD_RST2  0x19
#define PD_EOP   0x0D

/* Minimum PD supply current  (mA) */
#define PD_MIN_MA	500

/* Minimum PD voltage (mV) */
#define PD_MIN_MV	5000

/* No connect voltage threshold for sources based on Rp */
#define PD_SRC_DEF_VNC_MV        1600
#define PD_SRC_1_5_VNC_MV        1600
#define PD_SRC_3_0_VNC_MV        2600

/* Rd voltage threshold for sources based on Rp */
#define PD_SRC_DEF_RD_THRESH_MV  200
#define PD_SRC_1_5_RD_THRESH_MV  400
#define PD_SRC_3_0_RD_THRESH_MV  800

/* Voltage threshold to detect connection when presenting Rd */
#define PD_SNK_VA_MV             250

/* --- Policy layer functions --- */

/* Request types for pd_build_request() */
enum pd_request_type {
	PD_REQUEST_VSAFE5V,
	PD_REQUEST_MAX,
};

/* Power Data Objects for the source and the sink */
extern uint32_t pd_src_pdo[];
extern int pd_src_pdo_cnt;
extern uint32_t pd_snk_pdo[];
extern int pd_snk_pdo_cnt;

#endif  /* __CROS_EC_USB_PD_H */
