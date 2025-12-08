#pragma once

#include <stddef.h>
#include <stdint.h>

typedef int (* block_set_config_t)(int selector, size_t val0, size_t val1, size_t val2, size_t val3);
typedef int (* block_get_config_t)(int selector);
typedef int (* block_get_attribute_t)(int attribute);
typedef int (* block_cmd_t)(int cmd);
typedef int (* block_read_t)(uint64_t lba, void * data);
typedef int (* block_write_t)(uint64_t lba, void * data);

enum {
	BLOCK_CMD_LOCK = 0,
};

enum {
	BLOCK_ATTRIBUTE_POWER_ON_HOURS = 0,
	BLOCK_ATTRIBUTE_TEMPERATURE,
	BLOCK_ATTRIBUTE_ERROR_COUNT,
	BLOCK_ATTRIBUTE_SPINUP_TIME,
	BLOCK_ATTRIBUTE_POWER_CYCLE_COUNT,
};

/* functions:
	function 0 = set config
	function 1 = get config
	function 2 = get attribute
	function 3 = cmd
	function 4 = read
	function 5 = write
*/

#define BLOCK_SET_CONFIG (0)
#define BLOCK_GET_CONFIG (1)
#define BLOCK_GET_ATTRIBUTE (2)
#define BLOCK_CMD (3)
#define BLOCK_READ (4)
#define BLOCK_WRITE (5)
