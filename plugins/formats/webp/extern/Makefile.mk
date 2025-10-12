TARGET = libwebp.a

PREFIX = libwebp.git

SRCS = $(shell find $(PREFIX)/src -name \*.c -print0 | sort -z | xargs -r0)

SRCS += $(shell find $(PREFIX)/sharpyuv -name \*.c -print0 | sort -z | xargs -r0)

CFLAGS += -I$(PREFIX)
