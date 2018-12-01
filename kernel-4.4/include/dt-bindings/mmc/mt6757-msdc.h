
#ifndef _DT_BINDINGS_MMC_MT6757_H
#define _DT_BINDINGS_MMC_MT6757_H

#define MSDC_EMMC               (0)
#define MSDC_SD                 (1)
#define MSDC_SDIO               (2)

#define MSDC_CD_HIGH            (1)
#define MSDC_CD_LOW             (0)

#define MSDC50_CLKSRC_26MHZ     (0)
#define MSDC50_CLKSRC_400MHZ    (1)
#define MSDC50_CLKSRC_200MHZ    (2)
#define MSDC50_CLKSRC_156MHZ    (3)
#define MSDC50_CLKSRC_182MHZ    (4)
/* #define MSDC50_CLKSRC_156MHZ    (5) */
#define MSDC50_CLKSRC_100MHZ    (6)
#define MSDC50_CLKSRC_624MHZ    (7)
#define MSDC50_CLKSRC_312MHZ    (8)

#define MSDC30_CLKSRC_26MHZ     (0)
#define MSDC30_CLKSRC_208MHZ    (1)
#define MSDC30_CLKSRC_100MHZ    (2)
#define MSDC30_CLKSRC_156MHZ    (3)
#define MSDC30_CLKSRC_182MHZ    (4)
/* #define MSDC30_CLKSRC_156MHZ    (5) */
#define MSDC30_CLKSRC_178MHZ    (6)
#define MSDC30_CLKSRC_200MHZ    (7)

#define MSDC_SMPL_RISING        (0)
#define MSDC_SMPL_FALLING       (1)
#define MSDC_SMPL_SEPARATE      (2)

#endif /* _DT_BINDINGS_MMC_MT6757_H */
