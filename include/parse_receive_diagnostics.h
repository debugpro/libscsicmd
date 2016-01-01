/* Copyright 2015 Baruch Even
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef LIBSCSICMD_RECEIVE_DIAGNOSTICS_H
#define LIBSCSICMD_RECEIVE_DIAGNOSTICS_H

#include <stdint.h>

#define RECV_DIAG_MIN_LEN 4

static inline uint8_t recv_diag_get_page_code(uint8_t *data)
{
	return data[0];
}

static inline uint8_t recv_diag_get_page_code_specific(uint8_t *data)
{
	return data[1];
}

static inline uint16_t recv_diag_get_len(uint8_t *data)
{
	return (data[2] << 8) | data[3];
}

static inline uint8_t *recv_diag_data(uint8_t *data)
{
	return data + RECV_DIAG_MIN_LEN;
}

static inline bool recv_diag_is_valid(uint8_t *data, unsigned data_len)
{
	if (data_len < RECV_DIAG_MIN_LEN)
		return false;
	if ((unsigned)recv_diag_get_len(data) + RECV_DIAG_MIN_LEN > data_len)
		return false;
	return true;
}

#endif
