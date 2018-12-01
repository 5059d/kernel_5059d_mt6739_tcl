


#ifndef _AUDIO_CODEC_63xx_H
#define _AUDIO_CODEC_63xx_H

struct mtk_codec_ops {
	int (*enable_dc_compensation)(bool enable);
	int (*set_lch_dc_compensation)(int value);
	int (*set_rch_dc_compensation)(int value);

	int (*set_ap_dmic)(bool enable);

	int (*set_hp_impedance_ctl)(bool enable);
};

void audckbufEnable(bool enable);

void SetAnalogSuspend(bool bEnable);

int set_codec_ops(struct mtk_codec_ops *ops);

#ifdef CONFIG_MTK_ACCDET
extern void accdet_late_init(unsigned long a);
#endif

#endif
