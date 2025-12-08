#include <hw/display/pxa2xx_lcd.h>
#include <hw/system/pxa2xx.h>
#include <module.h>

int pxa2xx_lcd_init() {
}

module_t _pxa2xx_lcd = {
	.name = "pxa2xx_lcd",
	.init = pxa2xx_lcd_init
};
