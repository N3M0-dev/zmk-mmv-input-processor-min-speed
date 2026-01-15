/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr/device.h>
#include <zephyr/input/input.h>

/**
 * @brief Configuration for minimum speed input processor
 */
struct zip_min_speed_config {
    /** Event type to process (e.g., INPUT_EV_REL for relative movement) */
    uint16_t type;
    
    /** Array of codes to apply minimum speed to */
    const uint16_t *codes;
    
    /** Number of codes in the array */
    size_t codes_len;
    
    /** Minimum absolute value - values below this will be boosted */
    int32_t min_value;
};

/**
 * @brief Runtime data for minimum speed input processor
 */
struct zip_min_speed_data {
    /** Reserved for future use */
    uint8_t reserved;
};
