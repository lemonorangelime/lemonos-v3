#pragma once

#include <stddef.h>

typedef int (* camera_reset_t)(); // reset camera to defaults (i.e. when your done)
typedef int (* camera_set_config_t)(int selector, size_t val0, size_t val1, size_t val2, size_t val3);
typedef int (* camera_get_config_t)(int selector);
typedef int (* camera_capture_t)(void * data, size_t size);

enum {
	CAMERA_CONFIG_SPECTRUM = 0,
	CAMERA_CONFIG_XRESOLUTION,
	CAMERA_CONFIG_YRESOLUTION,
	CAMERA_CONFIG_ZOOM,
	CAMERA_CONFIG_FOCUS,
	CAMERA_CONFIG_EXPOSURE,
	CAMERA_CONFIG_INTEREST,
	CAMERA_CONFIG_IRIS,
	CAMERA_CONFIG_GAMMA,
	CAMERA_CONFIG_CONTRAST,
	CAMERA_CONFIG_SHARPNESS,
	CAMERA_CONFIG_VIDEO,
};

enum {
	CAMERA_SPECTRUM_VISIBLE = 0,
	CAMERA_SPECTRUM_MICROWAVE,
	CAMERA_SPECTRUM_INFRARED,
	CAMERA_SPECTRUM_ULTRAVIOLET,
	CAMERA_SPECTRUM_XRAY,
	CAMERA_SPECTRUM_GAMMA, // are gamma ray sensors a thing?
};

/* functions:
	function 0 = camera reset
	function 1 = set config
	function 2 = get config
	function 3 = capture
*/

#define CAMERA_RESET (0)
#define CAMERA_SET_CONFIG (1)
#define CAMERA_GET_CONFIG (2)
#define CAMERA_CAPTURE (3)
