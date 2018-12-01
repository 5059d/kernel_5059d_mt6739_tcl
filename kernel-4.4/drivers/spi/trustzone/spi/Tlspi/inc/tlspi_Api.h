
#ifndef TLSPI_H_
#define TLSPI_H_

#include "tci.h"
#include "spi.h"

#define CMD_SPI_SEND		1
#define CMD_SPI_CONFIG		2
#define CMD_SPI_DEBUG		3
#define CMD_SPI_TEST		4

#define EXIT_ERROR			((uint32_t)(-1))

typedef struct {
		tciCommandHeader_t	header;		/*< Command header */
		uint32_t			len;		/*< Length of data to process or buffer */
		uint32_t			respLen;	/**< Length of response buffer */
} tl_cmd_t;
typedef struct {
	tciResponseHeader_t	header;	/*< Response header */
	uint32_t	len;
} tl_rsp_t;
typedef struct {
	union {
		tl_cmd_t		cmd_spi;
		tl_rsp_t		rsp_spi;
	};
	const void	*tx_buf;
	void		*rx_buf;
	uint32_t	len;
	uint32_t	is_dma_used;

	uint32_t	tx_dma;	/*dma_addr_t*/
	uint32_t	rx_dma;	/*dma_addr_t*/
	uint32_t	is_transfer_end;

	struct mt_tl_chip_conf	*tl_chip_config;

	uint32_t	cs_change;
	/*uint8_t	bits_per_word;*/
	/*uint16_t	delay_usecs;*/
	/*uint32_t	speed_hz;*/
} tciSpiMessage_t;

#define TL_SPI_UUID {0x09, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

#endif/*TLSPI_H_*/
