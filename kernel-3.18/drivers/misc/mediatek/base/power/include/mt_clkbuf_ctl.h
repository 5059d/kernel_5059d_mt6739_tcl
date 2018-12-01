
#ifndef _MT_CLK_BUF_CTL_H_
#define _MT_CLK_BUF_CTL_H_

#if defined(CONFIG_ARCH_MT6735) || defined(CONFIG_ARCH_MT6735M) || defined(CONFIG_ARCH_MT6753)

#include "../mt6735/mt_clkbuf_ctl.h"

#elif defined(CONFIG_ARCH_MT6755)

#include "../mt6755/mt_clkbuf_ctl.h"

#elif defined(CONFIG_ARCH_MT6757)

#include "../mt6757/mt_clkbuf_ctl.h"

#elif defined(CONFIG_ARCH_MT6797)

#include "../mt6797/mt_clkbuf_ctl.h"

#elif defined(CONFIG_ARCH_MT6580)

#include "../../../include/mt-plat/mt6580/include/mach/mt_clkbuf_ctl.h"

#elif defined(CONFIG_ARCH_ELBRUS)

#include "clkbuf_v1/mt_clkbuf_ctl.h"

#endif

#endif /* _MT_CLK_BUF_CTL_H_ */

