/*
 * Copyright (c) 2022 Bose Corporation All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Lc3Config.hpp"
#include "lc3_config.h"
#include <cstddef>

Lc3Config_t Lc3Config_create(uint16_t Fs_, lc3config_frame_duration_t N_ms_, uint8_t Nc_)
{
	Lc3Config *inst;
	Lc3Config::FrameDuration duration;

	switch (N_ms_) {
	case lc3config_duration_7p5ms:
		duration = Lc3Config::FrameDuration::d7p5ms;
		break;
	case lc3config_duration_10ms:
		duration = Lc3Config::FrameDuration::d10ms;
		break;
	default:
		/* Not all compilers understand that the enum only have two entries
		 * and therefore warns about potential uninitialized value in duration.
		 * This code is dead code. */
		return NULL;
	}

	inst = new Lc3Config(Fs_, duration, Nc_);

	return inst;
}

void Lc3Config_destroy(Lc3Config_t inst_ptr)
{
	if (inst_ptr != NULL) {
		Lc3Config *inst = static_cast<Lc3Config*>(inst_ptr);
		delete inst;
	}
}

uint16_t Lc3Config_getByteCountFromBitrate(Lc3Config_t inst_ptr, uint32_t bitrate)
{
	if (inst_ptr == NULL) {
		return 0;
	}

	Lc3Config *inst = static_cast<Lc3Config*>(inst_ptr);

	return inst->getByteCountFromBitrate(bitrate);
}

uint32_t getBitrateFromByteCount(Lc3Config_t inst_ptr, uint16_t nbytes)
{
	if (inst_ptr == NULL) {
		return 0;
	}

	Lc3Config *inst = static_cast<Lc3Config*>(inst_ptr);

	return inst->getBitrateFromByteCount(nbytes);
}
