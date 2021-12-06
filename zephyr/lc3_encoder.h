/*
 * Copyright (c) 2022 Bose Corporation All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIB_LIBLC3CODEC_ZEPHYR_LC3_ENCODER_H_
#define LIB_LIBLC3CODEC_ZEPHYR_LC3_ENCODER_H_

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

typedef void* Lc3Encoder_t;

#define LC3_ENCODE_ERR_FREE                             0x00
#define LC3_ENCODE_ERR_INVALID_CONFIGURATION            0x01
#define LC3_ENCODE_ERR_INVALID_BYTE_COUNT               0x02
#define LC3_ENCODE_ERR_INVALID_BITS_PER_AUDIO_SAMPLE    0x03
#define LC3_ENCODE_ERR_ENCODER_ALLOCATION               0x04

/**
 * For detailed description please see underlying LC3 codec implementation.
 * @param Fs_ Sampling frequency Hz
 * @param N_ms_ Frame duration
 * @param Nc_ Number of channels
 * @return the Encoder instance. Will be NULL if creation fails either due to invalid
 *         arguments or insufficient memory.
 */
LC3_EXTERN_C Lc3Encoder_t Lc3Encoder_create(uint16_t Fs_, lc3config_frame_duration_t N_ms_,
					    uint8_t Nc_);
LC3_EXTERN_C void Lc3Encoder_destroy(Lc3Encoder_t inst_ptr);

/**
 * For detailed description please see underlying LC3 codec implementation.
 * @return One of LC3_DECODE_ERR values listed above
 */
LC3_EXTERN_C uint16_t Lc3Encoder_run_single(Lc3Encoder_t inst_ptr, const int16_t* x_s,
                                            uint16_t byte_count, uint8_t* bytes,
                                            uint8_t channelNr);

/**
 * For detailed description please see underlying LC3 codec implementation.
 * @return One of LC3_DECODE_ERR values listed above
 */
LC3_EXTERN_C uint16_t Lc3Encoder_run_all(Lc3Encoder_t inst_ptr, const int16_t* x_s,
                                         const uint16_t* byte_count_per_channel, uint8_t* bytes);
#undef LC3_EXTERN_C

#endif /* LIB_LIBLC3CODEC_ZEPHYR_LC3_ENCODER_H_ */
