#pragma once

#include <stddef.h>
#include <stdint.h>

typedef int (* thermometre_get_attribute_t)(int selector);

enum {
	THERMOMETRE_ATTRIBUTE_TEMPERATURE = 0,
	THERMOMETRE_ATTRIBUTE_UNIT,
};

enum {
	THERMOMETRE_UNIT_CELSIUS,
	THERMOMETRE_UNIT_KELVIN,
	THERMOMETRE_UNIT_JOULE,
	THERMOMETRE_UNIT_BTU,
	THERMOMETRE_UNIT_CALORIE, // nobody using this
	THERMOMETRE_UNIT_WATT,
};


/* functions:
	function 0 = get attribute
*/

#define THERMOMETRE_GET_ATTRIBUTE (0)
