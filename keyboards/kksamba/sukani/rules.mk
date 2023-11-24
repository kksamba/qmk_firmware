# This file intentionally left blank


POINTING_DEVICE_ENABLE ?= yes
# POINTING_DEVICE_DRIVER ?= analog_joystick

# # custom analog_joystick
# # 		reference builddefs/common_features.mk
POINTING_DEVICE_DRIVER ?= custom
OPT_DEFS += -DSTM32_ADC -DHAL_USE_ADC=TRUE
SRC += pointing_device_custom.c
LIB_SRC += analog.c
