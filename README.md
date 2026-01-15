# ZMK Minimum Speed Input Processor

A custom ZMK module that provides a minimum speed threshold for mouse movement inputs.

## Overview

This input processor ensures that mouse movements always start from a minimum speed you define. When you press a mouse movement key, instead of starting from zero and accelerating, the cursor will immediately move at your configured minimum speed and then accelerate according to your existing acceleration settings.

## How It Works

The processor examines each mouse movement event:
- If the value is **0** (no movement), it passes through unchanged
- If the absolute value is **below the minimum threshold**, it boosts the value to the minimum while preserving direction
- If the absolute value is **above the minimum threshold**, it passes through unchanged

For example, with a minimum value of 100:
- Input value: 0 → Output: 0 (no change)
- Input value: 50 → Output: 100 (boosted to minimum)
- Input value: -30 → Output: -100 (boosted to minimum, negative preserved)
- Input value: 150 → Output: 150 (already above minimum)

## Installation

### For GitHub Actions (Recommended)

Add the module to your `config/west.yml`:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
  projects:
    - name: zmk-mmv-input-processor-min-speed
      url: https://github.com/N3M0-dev/zmk-mmv-input-processor-min-speed
      revision: main
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
```

### For Local Builds

1. Clone this repository locally
2. Add the module to your `config/west.yml` with a local path or URL
3. Run `west update` to fetch the module

## Configuration

### 1. Enable the Module

Add to your board's `.conf` file (e.g., `eyelash_sofle.conf`):

```properties
CONFIG_ZMK_INPUT_PROCESSOR_MIN_SPEED=y
```

### 2. Define in Your Keymap

Add the processor definition in your `.keymap` file:

```c
#include <input/processors.dtsi>
#include <zephyr/dt-bindings/input/input-event-codes.h>

// ... other includes ...

/ {
    zip_min_speed_xy: zip_min_speed_xy {
        compatible = "zmk,input-processor-min-speed";
        #input-processor-cells = <0>;
        type = <INPUT_EV_REL>;
        codes = <INPUT_REL_X>, <INPUT_REL_Y>;
        min-value = <100>;  // Adjust this value to change minimum speed
        status = "okay";
    };

    // ... rest of your keymap ...
};
```

### 3. Apply to Input Listeners

Reference the processor in your input listener configuration:

```c
&mmv_input_listener { 
    input-processors = <&zip_min_speed_xy &zip_xy_scaler 2 1>; 
};
```

To change the minimum speed, modify the `min-value` property in the processor definition:
- Lower values (50-100): More subtle minimum speed
- Medium values (100-200): Noticeable minimum speed
- Higher values (200+): Aggressive minimum speed

## Custom Configuration

You can create custom instances with different settings:

```devicetree
/ {
    my_min_speed: my_min_speed {
        compatible = "zmk,input-processor-min-speed";
        #input-processor-cells = <1>;
        type = <INPUT_EV_REL>;
        codes = <INPUT_REL_X>, <INPUT_REL_Y>;
        min-value = <150>;
        status = "okay";
    };
};
```

Then use it in your input listener:

```c
&mmv_input_listener { 
    input-processors = <&my_min_speed 150>; 
};
```multiple instances with different settings:

```devicetree
/ {
    my_min_speed: my_min_speed {
        compatible = "zmk,input-processor-min-speed";
        #input-processor-cells = <0>;
        type = <INPUT_EV_REL>;
        codes = <INPUT_REL_X>, <INPUT_REL_Y>;
        min-value = <150>;
        status = "okay";
    };
};
```

Then use it in your input listener:

```c
&mmv_input_listener { 
    input-processors = <&my_min_speed &zip_xy_scaler 2 10 at a time until comfortable
4. **Consider Acceleration**: Balance with your `time-to-max-speed-ms` and `acceleration-exponent` settings

## Example Configuration

Complete example:

```c
#define ZMK_POINTING_DEFAULT_MOVE_VAL 800
#define ZMK_POINTING_DEFAULT_SCRL_VAL 20

#include <input/processors.dtsi>
#include <zephyr/dt-bindings/input/input-event-codes.h>
// ... other includes ...

/ {
    zip_min_speed_xy: zip_min_speed_xy {
        compatible = "zmk,input-processor-min-speed";
        #input-processor-cells = <0>;
        type = <INPUT_EV_REL>;
        codes = <INPUT_REL_X>, <INPUT_REL_Y>;
        min-value = <100>;
        status = "okay";
    };

    // ... rest of keymap ...
};

&mmv_input_listener { input-processors = <&zip_min_speed_xy &zip_xy_scaler 2 1>; };
&msc_input_listener { input-proce`"okay"` in your keymap definition
- Ensure the module is properly referenced in west.yml

**Problem**: Minimum speed is too aggressive
- Lower the `min-value` parameter in your processor definition
- Start with 50 and adjust upward

**Problem**: No noticeable difference
- Increase the `min-value` parameter
- Ensure the processor is listed BEFORE any scaling processors in the input-processors list

**Problem**: Mouse doesn't move at all
- Check that `CONFIG_ZMK_INPUT_PROCESSOR_MIN_SPEED=y` is in your .conf file
- Verify the processor status is "okay" in your overlay

**Problem**: Minimum speed is too aggressive
- Lower the `min-value` parameter
- Start with 50 and adjust upward

**Problem**: No noticeable difference
- Increase the `min-value` parameter
- Ensure the processor is listed BEFORE any scaling processors

## License

MIT License - See LICENSE file for details

## Contributing

Issues and pull requests welcome! This is a community-maintained module.
