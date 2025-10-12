TARGET = libonnxpb.a

PREFIX = nanopb.git

SRCS = $(PREFIX)/onnx_pb.c \
	$(PREFIX)/pb_common.c \
	$(PREFIX)/pb_decode.c \

CFLAGS += -I$(PREFIX) -Wno-deprecated
