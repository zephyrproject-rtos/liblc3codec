/*
 * Copyright (c) 2022 Bose Corporation All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIB_LIBLC3CODEC_ZEPHYR_LC3_CONFIG_H_
#define LIB_LIBLC3CODEC_ZEPHYR_LC3_CONFIG_H_

/* This file is a c-wrapper for the c++ LC3 lib. Please refer to the C++ API documentation
 * for a full description of the API.
 * General usage:
 * 1) Call _create to allocate memory for the c++ object using the c++-lib allocation mechanism.
 * 2) Use the wrapper functions as needed passing the allocated object as first parameter.
 * 3) After usage call _destroy to free up the memory.
 *    Invalid usage of the object reference after a call to _destroy cannot be detected and will
 *    most likely result in a crash. */

#include <stdint.h>

#ifdef __cplusplus
#define LC3_EXTERN_C extern "C"
#else
#define LC3_EXTERN_C
#endif

typedef void* Lc3Config_t;

typedef enum
{
    lc3config_duration_10ms,
    lc3config_duration_7p5ms
} lc3config_frame_duration_t;


/**
 * For detailed description please see underlying LC3 codec implementation.
 * @param Fs_ Sampling frequency Hz
 * @param N_ms_ Frame duration
 * @param Nc_ Number of channels
 * @return the Config instance
 */
LC3_EXTERN_C Lc3Config_t Lc3Config_create(uint16_t Fs_, lc3config_frame_duration_t N_ms_,
                                          uint8_t Nc_);
LC3_EXTERN_C void Lc3Config_destroy(Lc3Config_t inst_ptr);
LC3_EXTERN_C uint16_t Lc3Config_getByteCountFromBitrate(Lc3Config_t inst_ptr, uint32_t bitrate);
LC3_EXTERN_C uint32_t Lc3Config_getBitrateFromByteCount(Lc3Config_t inst_ptr, uint16_t nbytes);

#undef LC3_EXTERN_C

#endif /* LIB_LIBLC3CODEC_ZEPHYR_LC3_CONFIG_H_ */
