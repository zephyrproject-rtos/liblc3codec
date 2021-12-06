/*
 * Copyright (c) 2022 Bose Corporation All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Lc3Decoder.hpp"
#include "Lc3Config.hpp"
#include "lc3_decoder.h"
#include <cstddef>

Lc3Decoder_t Lc3Decoder_create(uint16_t Fs_, lc3config_frame_duration_t N_ms_)
{
	Lc3Decoder *inst;
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

	inst = new Lc3Decoder(Fs_, duration);

	return inst;
}

void Lc3Decoder_destroy(Lc3Decoder_t inst_ptr)
{
	if (inst_ptr != NULL) {
		Lc3Decoder *inst = static_cast<Lc3Decoder*>(inst_ptr);
		delete inst;
	}
}

uint8_t Lc3Decoder_run(Lc3Decoder_t inst_ptr, const uint8_t *bytes, uint16_t byte_count,
		       uint8_t BFI, int16_t *x_out, uint16_t x_out_size, uint8_t *BEC_detect)
{
	if (inst_ptr == NULL) {
		return 0;
	}

	Lc3Decoder *inst = static_cast<Lc3Decoder*>(inst_ptr);
	uint8_t tmp_BEC_detect;
	uint8_t res;

	res = inst->run(bytes, byte_count, BFI, x_out, x_out_size, tmp_BEC_detect, 0);
	*BEC_detect = tmp_BEC_detect;

	return res;
}
