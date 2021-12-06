/*
 * Copyright (c) 2022 Bose Corporation All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIB_LIBLC3CODEC_ZEPHYR_LC3_DECODER_H_
#define LIB_LIBLC3CODEC_ZEPHYR_LC3_DECODER_H_

/* This file is a c-wrapper for the c++ LC3 lib. Please refer to the C++ API documentation
 * for a full description of the API.
 * General usage:
 * 1) Call _create to allocate memory for the c++ object using the c++-lib allocation mechanism.
 * 2) Use the wrapper functions as needed passing the allocated object as first parameter.
 * 3) After usage call _destroy to free up the memory.
 *    Invalid usage of the object reference after a call to _destroy cannot be detected and will
 *    most likely result in a crash. */

#include <stdint.h>
#include "lc3_config.h"

#ifdef __cplusplus
#define LC3_EXTERN_C extern "C"
#else
#define LC3_EXTERN_C
#endif

typedef void* Lc3Decoder_t;

#define LC3_DECODE_ERR_FREE                             0x00
#define LC3_DECODE_ERR_INVALID_CONFIGURATION            0x01
#define LC3_DECODE_ERR_INVALID_BYTE_COUNT               0x02
#define LC3_DECODE_ERR_INVALID_X_OUT_SIZE               0x03
#define LC3_DECODE_ERR_INVALID_BITS_PER_AUDIO_SAMPLE    0x04
#define LC3_DECODE_ERR_DECODER_ALLOCATION               0x05

/**
 * For detailed description please see underlying LC3 codec implementation.
 * @param Fs_ Sampling frequency Hz
 * @param N_ms_ Frame duration
 * @return the Encoder instance. Will be NULL if creation fails either due to invalid
 *         arguments or insufficient memory.
 */
LC3_EXTERN_C Lc3Decoder_t Lc3Decoder_create(uint16_t Fs_, lc3config_frame_duration_t N_ms_);
LC3_EXTERN_C void Lc3Decoder_destroy(Lc3Decoder_t inst_ptr);

/**
 * Decode a single frame of 16 bit audio for one channel.
 * For detailed description please see underlying LC3 codec implementation.
 * Multi channel decoding can be achieved by multiple calls to this function.
 * The library also have support for multi channel decoding and additional
 * wrapper functions can be added to expose this feature.
 
 * @param inst_ptr The decoder instance
 * @param bytes The data to decode (the data shall be for the relevant channel only.
 * @param byte_count Amount of data (implicitly determines the bit-rate)
 * @param BFI Bad Frame Indicator
 * @param x_out Output buffer
 * @param x_out_size size of output buffer
 * @param BEC_detect output argument - bit errors detected != 0 means bit errors were
 *                                     detected and PLC was used to generate data.
 * @return One of LC3_DECODE_ERR values listed above
 */
LC3_EXTERN_C uint8_t Lc3Decoder_run(Lc3Decoder_t inst_ptr, const uint8_t* bytes,
                                    uint16_t byte_count, uint8_t BFI,
                                    int16_t* x_out, uint16_t x_out_size, uint8_t *BEC_detect);
#undef LC3_EXTERN_C

#endif /* LIB_LIBLC3CODEC_ZEPHYR_LC3_DECODER_H_ */
