#pragma once

#include "project.h"
#include <stdint.h>

/* Defines for DMA_A */
#define DMA_A_BYTES_PER_BURST 2
#define DMA_A_REQUEST_PER_BURST 1
#define DMA_A_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_A_DST_BASE (CYDEV_PERIPH_BASE)

/* Variable declarations for DMA_A */
uint8 DMA_A_Chan;
uint8 DMA_A_TD[1];

/* Defines for DMA_B */
#define DMA_B_BYTES_PER_BURST 2
#define DMA_B_REQUEST_PER_BURST 1
#define DMA_B_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_B_DST_BASE (CYDEV_PERIPH_BASE)

/* Variable declarations for DMA_B */
uint8 DMA_B_Chan;
uint8 DMA_B_TD[1];

#define DMA_A_Filter_BYTES_PER_BURST 2
#define DMA_A_Filter_REQUEST_PER_BURST 1
#define DMA_A_Filter_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_A_Filter_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_A_Filter */
uint8 DMA_A_Filter_Chan;
uint8 DMA_A_Filter_TD[1];

#define DMA_B_Filter_BYTES_PER_BURST 2
#define DMA_B_Filter_REQUEST_PER_BURST 1
#define DMA_B_Filter_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_B_Filter_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_B_Filter */
uint8 DMA_B_Filter_Chan;
uint8 DMA_B_Filter_TD[1];

/* DMA Configuration for DMA_A */
#define DMA_A_CHAN_INIT(DSIZE)                                                                              \
    DMA_A_Chan = DMA_A_DmaInitialize(DMA_A_BYTES_PER_BURST, DMA_A_REQUEST_PER_BURST,                        \
        HI16(DMA_A_SRC_BASE), HI16(DMA_A_DST_BASE));                                                        \
    DMA_A_TD[0] = CyDmaTdAllocate();                                                                        \
    CyDmaTdSetConfiguration(DMA_A_TD[0], DSIZE * 2, DMA_A_TD[0], DMA_A__TD_TERMOUT_EN);                     \
    CyDmaTdSetAddress(DMA_A_TD[0], LO16((uint32)ADC_SAR_A_SAR_WRK0_PTR), LO16((uint32)Filter_STAGEA_PTR));  \
    CyDmaChSetInitialTd(DMA_A_Chan, DMA_A_TD[0]);                                                           \
    CyDmaChEnable(DMA_A_Chan, 1);                                                                           \
    
    /* DMA Configuration for DMA_B */
#define DMA_B_CHAN_INIT(DSIZE) \
    DMA_B_Chan = DMA_B_DmaInitialize(DMA_B_BYTES_PER_BURST, DMA_B_REQUEST_PER_BURST, \
        HI16(DMA_B_SRC_BASE), HI16(DMA_B_DST_BASE)); \
    DMA_B_TD[0] = CyDmaTdAllocate(); \
    CyDmaTdSetConfiguration(DMA_B_TD[0], DSIZE * 2, DMA_B_TD[0], DMA_B__TD_TERMOUT_EN); \
    CyDmaTdSetAddress(DMA_B_TD[0], LO16((uint32)ADC_SAR_B_SAR_WRK0_PTR), LO16((uint32)Filter_STAGEB_PTR)); \
    CyDmaChSetInitialTd(DMA_B_Chan, DMA_B_TD[0]); \
    CyDmaChEnable(DMA_B_Chan, 1);

#define DMA_A_FILTER_INIT(DSIZE, DST) \
    DMA_A_Filter_Chan = DMA_A_Filter_DmaInitialize(DMA_A_Filter_BYTES_PER_BURST, DMA_A_Filter_REQUEST_PER_BURST, \
        HI16(DMA_A_Filter_SRC_BASE), HI16(DMA_A_Filter_DST_BASE));\
    DMA_A_Filter_TD[0] = CyDmaTdAllocate();\
    CyDmaTdSetConfiguration(DMA_A_Filter_TD[0], DSIZE * 2, DMA_A_Filter_TD[0], DMA_A_Filter__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);\
    CyDmaTdSetAddress(DMA_A_Filter_TD[0], LO16((uint32)Filter_HOLDA_PTR), LO16((uint32)DST));\
    CyDmaChSetInitialTd(DMA_A_Filter_Chan, DMA_A_Filter_TD[0]);\
    CyDmaChEnable(DMA_A_Filter_Chan, 1);

#define DMA_B_FILTER_INIT(DSIZE, DST) \
    DMA_B_Filter_Chan = DMA_B_Filter_DmaInitialize(DMA_B_Filter_BYTES_PER_BURST, DMA_B_Filter_REQUEST_PER_BURST, \
        HI16(DMA_B_Filter_SRC_BASE), HI16(DMA_B_Filter_DST_BASE));\
    DMA_B_Filter_TD[0] = CyDmaTdAllocate();\
    CyDmaTdSetConfiguration(DMA_B_Filter_TD[0], DSIZE * 2, DMA_B_Filter_TD[0], DMA_B_Filter__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);\
    CyDmaTdSetAddress(DMA_B_Filter_TD[0], LO16((uint32)Filter_HOLDB_PTR), LO16((uint32)DST));\
    CyDmaChSetInitialTd(DMA_B_Filter_Chan, DMA_B_Filter_TD[0]);\
    CyDmaChEnable(DMA_B_Filter_Chan, 1);