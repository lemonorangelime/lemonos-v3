#pragma once

typedef int (* device_init_t)();
typedef int (* device_set_state_t)();

typedef struct {
	char * name;
	int type;

	device_set_state_t set_state;
	void * functions[16];
} device_t;

enum {
// device types
	DEVICE_VENDOR_SPECIFIC = 0, // no defined functions
	DEVICE_DISPLAY = 1, // see devices/display.h
	DEVICE_BLOCK = 2, // see devices/block.h
	DEVICE_NIC = 3, // see devices/nic.h (ethernet / ...)
	DEVICE_THERMOMETRE = 4, // see devices/thermometre.h
	DEVICE_AUDIO = 5, // see devices/audio.h
	DEVICE_SERIAL = 6, // see devices/serial.h (this includes UART devices)
	DEVICE_80211 = 7, // see devices/802.11.h
	DEVICE_BLUETOOTH = 8, // see devices/bluetooth.h
	DEVICE_POINTER = 9, // see devices/pointer.h (mouse / touchscreen / pen / lightgun)
	DEVICE_IRDA = 10, // see devices/irda.h (infrared line of sight communications)
	DEVICE_POWER = 11, // see devices/power.h
	DEVICE_USB = 12, // see devices/usb.h
	DEVICE_GPIO = 13, // see devices/gpio.h
	DEVICE_CLOCK = 14, // see devices/clock.h
	DEVICE_GPU = 15, // see devices/gpu.h
	DEVICE_CRYPTO = 16, // see devices/crypto.h (TPM / Quantum RNG devices / encryption accelerators)
	DEVICE_RDMA = 17, // see devices/rdma.h
	DEVICE_LED = 18, // see devices/led.h
	DEVICE_SWITCH = 19, // see devices/switch.h (this includes buttons)
	DEVICE_PANEL = 20, // see devices/panel.h (IBM Panel)
	DEVICE_KEYBOARD = 21, // see devices/keyboard.h (this includes side buttons / home buttons on mobile devices)
	DEVICE_RADIO = 22, // see devices/radio.h (SDR)
	DEVICE_CAMERA = 23, // see devices/camera.h
	DEVICE_GNSS = 24, // see devices/gnss.h
	DEVICE_TACHOMETRE = 25, // see devices/tachometre.h
	DEVICE_GYROSCOPE = 26, // see devices/gyroscope.h
	DEVICE_ALTIMETRE = 27, // see devices/altimetre.h
	DEVICE_BAROMETRE = 28, // see devices/barometre.h
	DEVICE_ACCELEROMETRE = 29, // see devices/accelerometre.h
	DEVICE_MAGNETOMETRE = 30, // see devices/magnetometre.h
	DEVICE_OXIMETRE = 31, // see devices/oximetre.h
	DEVICE_PULSOMETRE = 32, // see devices/pulsometre.h
	DEVICE_PROXOMETRE = 33, // see devices/proxometre.h
	DEVICE_BATTERY = 34, // see devices/battery.h
	DEVICE_COMPASS = 35, // see devices/compass.h
	DEVICE_FINGERPRINT = 36, // see devices/fingerprint.h
	DEVICE_NFC = 37, // see devices/nfc.h
	DEVICE_CELLULAR = 38, // see devices/cellular.h
	DEVICE_VIBROMETRE = 39, // see devices/vibrometre.h
	DEVICE_POST = 40, // see devices/post.h (think 8-segment BIOS post code display, arguably a "panel")
	DEVICE_JOYSTICK = 41, // see devices/joystick.h (joysticks should also create a pointer device for "mouse emulation" mode)
	DEVICE_ELECTROMYOGRAPH = 42, // see devices/electromyograph.h
	DEVICE_SPECTOMETRE = 43, // see devices/spectometre.h
	DEVICE_POLLUTOMETRE = 44, // see devices/pollutometre.h
	DEVICE_KINESIMETRE = 45, // see devices/kinesimetre.h
	DEVICE_CHASSIS_INTRUSION = 46, // see devices/chassis_intrusion.h (battery cover / ATX panel / ...)
	DEVICE_FAN = 47, // see devices/fan.h
	DEVICE_LIQUIDOMETRE = 48, // see devices/liquidometre.h
	DEVICE_WHEEL = 49, // see devices/wheel.h
	DEVICE_PRINDL = 50, // see devices/prindl.h
	DEVICE_PEDAL = 51, // see devices/pedal.h
	DEVICE_RUMBLER = 52, // see devices/rumbler.h
	DEVICE_RADOMETRE = 53, // see devices/radometre.h
	DEVICE_TASTOMETRE = 54, // see devices/tastometre.h
	DEVICE_SMELLOMETRE = 55, // see devices/smellometre.h
	DEVICE_MASSOMETRE = 56, // see devices/massometre.h
	DEVICE_BREATHALYSER = 57, // see devices/breathalyser.h
	DEVICE_ANEMOMETRE = 58, // see devices/anemometre.h
	DEVICE_HYDROMETER = 59, // see devices/hydrometre.h
	DEVICE_PUMP = 60, // see devices/pump.h (water pump)
	DEVICE_BARCODE = 61, // see devices/barcode.h
	DEVICE_SKELETON = 62, // see devices/skeleton.h (skeletal tracker, think VR hand / finger tracking)
	DEVICE_COIN_ACCEPTOR = 63, // see devices/coin_acceptor.h
	DEVICE_MAGSTRIPE = 64, // see devices/magstripe.h
	DEVICE_REMOTE = 65, // see devices/remote.h (infrared remote. this is different from DEVICE_IRDA, which is for line of sight P2P communications)
	DEVICE_MICROWAVE = 66, // see devices/microwave.h
	DEVICE_CAN = 67, // see devices/can.h
	DEVICE_PSU = 68, // see devices/psu.h (power output, see DEVICE_POWER for input)
	DEVICE_FPGA = 69, // see devices/fpga.h
	DEVICE_MODEM = 70, // see devices/modem.h
	DEVICE_PWM = 71, // see devices/pwm.h
	DEVICE_COPROCESSOR = 72, // see devices/coprocessor.h (coprocessors other than SMP cores, think xeon phi / nvidia tesla)
	DEVICE_GLUCOMETRE = 73, // see devices/glucometre.h
	DEVICE_TABLET = 74, // see devices/tablet.h
	DEVICE_PRINTER = 75, // see devices/printer.h
	DEVICE_BALANCE_BOARD = 76, // see devices/balance_board.h
	DEVICE_SONAR = 77, // see devices/sonar.h
	DEVICE_NEURAL_IMPULSE = 78, // see devices/neural_impulse.h
	DEVICE_PHYSICS_PROCESSOR = 79, // see devices/physics_processor.h
	DEVICE_WELDER = 80, // see devices/welder.h (see Branson 2000 ultrasonic welder)
	DEVICE_3D_PRINTER = 81, // see devices/3d_printer.h
	DEVICE_NEURAL_PROCESSOR = 82, // see devices/neural_processor.h
	DEVICE_BRAILLE = 83, // see devices/braille.h
	DEVICE_LIDAR = 84, // see devices/lidar.h
	DEVICE_CETRIFUGE = 85, // see devices/centrifuge.h
	DEVICE_AIRBAG = 86, // see devices/airbag.h
	DEVICE_SPARK_PLUG = 87, // see devices/spark_plug.h
	DEVICE_ENGINE = 88, // see devices/engine.h
	DEVICE_SONOMETRE = 89, // see devices/sonometre.h
	DEVICE_PSYCHOGALVANOMETRE = 90, // see devices/psychogalvanometre.h
	DEVICE_GESTURE_DETECTOR = 91, // see devices/gesture_detector.h
	DEVICE_MULTIMETRE = 92, // see devices/multimetre.h
};

enum {
	DEVICE_EERR = -1,
	DEVICE_EDISABLED = -2,
// -16 : -254 == device driver specific error codes
	DEVICE_ENOT_IMPLIMENTED = -255,
	DEVICE_EBUSY = -256,
	DEVICE_EINVALID = -257,
	DEVICE_EIO = -258,
	DEVICE_EPERM = -259,
	DEVICE_ENOMEM = -260,
	DEVICE_ENXIO = -261,
	DEVICE_ETYPE = -262,
};

void device_init();
