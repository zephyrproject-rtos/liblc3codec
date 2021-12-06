/*
 * Copyright (c) 2022 Bose Corporation All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Lc3Encoder.hpp"
#include "Lc3Config.hpp"
#include "lc3_encoder.h"
#include <cstddef>

Lc3Encoder_t Lc3Encoder_create(uint16_t Fs_, lc3config_frame_duration_t N_ms_, uint8_t Nc_)
{
	Lc3Encoder *inst;
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

	inst = new Lc3Encoder(Lc3Config(Fs_, duration, Nc_));

	return inst;
}

void Lc3Encoder_destroy(Lc3Encoder_t inst_ptr)
{
	if (inst_ptr != NULL) {
		Lc3Encoder *inst = static_cast<Lc3Encoder*>(inst_ptr);
		delete inst;
	}
}

uint16_t Lc3Encoder_run_single(Lc3Encoder_t inst_ptr, const int16_t *x_s, uint16_t byte_count,
			       uint8_t *bytes, uint8_t channelNr)
{
	if (inst_ptr == NULL) {
		return 0;
	}

	Lc3Encoder *inst = static_cast<Lc3Encoder*>(inst_ptr);

	return inst->run(x_s, byte_count, bytes, channelNr);
}

uint16_t Lc3Encoder_run_all(Lc3Encoder_t inst_ptr, const int16_t *x_s,
		const uint16_t *byte_count_per_channel, uint8_t *bytes)
{
	if (inst_ptr == NULL) {
		return 0;
	}

	Lc3Encoder *inst = static_cast<Lc3Encoder*>(inst_ptr);

	return inst->run(x_s, byte_count_per_channel, bytes);
}
