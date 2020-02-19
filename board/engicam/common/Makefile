# Copyright (C) 2016 Amarula Solutions B.V.
#
# SPDX-License-Identifier:	GPL-2.0+
#

ifdef AMARULA
obj-y := board.o
obj-$(CONFIG_SPL_BUILD) += spl.o
else
# necessary to create built-in.o
obj-y := mmc.o
endif
