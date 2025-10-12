#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import math

from tellusimd import *

print("\n10 Hello Image\n")

# create Image interface
image = Image()

###############################################################################
#
# Fast Image info
#
###############################################################################

# fast operation without content loading
image.info("image.png")
print(image.description)

###############################################################################
#
# Basic Image operations
#
###############################################################################

# load Image from file
image.load("image.png")
print(image.description)

# swap red and blue components
image.swap(0, 2)

# rotate image by 90 degrees CCW
image = image.getRotated(-1)

# convert image to RGBA format
image = image.toFormat(FormatRGBAu8n)

# crop image
image = image.getRegion(Region(40, 150, 64, 94))

# upscale image using default Cubic filter
image = image.getResized(image.size * 4)

# create mipmap chain using default mipmap filter
image = image.getMipmapped(Image.FilterMip, Image.FlagGamma)

# save image
image.save("test_basic.dds")
print(image.description)

###############################################################################
#
# ImageSampler interface
#
###############################################################################

# create new image
image.create2D(FormatRGBu8n, 512, 256)

# create image sampler from the first image layer
sampler = ImageSampler(image)

# fill image
color = ImageColor(255)
for y in range(image.height):
	for x in range(image.width):
		v = ((x ^ y) & 255) / 32.0
		color.r = int(math.cos(Pi * 1.0 + v) * 127.5 + 127.5)
		color.g = int(math.cos(Pi * 0.5 + v) * 127.5 + 127.5)
		color.b = int(math.cos(Pi * 0.0 + v) * 127.5 + 127.5)
		sampler.set2D(x, y, color)

# save image
image.save("test_xor.png")
print(image.description)

###############################################################################
#
# Cube images
#
###############################################################################

# create Cube image
image.createCube(FormatRGBu8n, 128)
print(image.description)

# clear image
for face in range(0, 6, 3):
	ImageSampler(image, Slice(Face(face + 0))).clear(ImageColor(255, 0, 0))
	ImageSampler(image, Slice(Face(face + 1))).clear(ImageColor(0, 255, 0))
	ImageSampler(image, Slice(Face(face + 2))).clear(ImageColor(0, 0, 255))

# convert to 2D panorama
# it will be horizonal cross without Panorama flag
image = image.toType(Image.Type2D, Image.FlagPanorama)

image.save("test_panorama.png")
print(image.description)

###############################################################################
#
# Image compression
#
###############################################################################

# load and resize Image
image.load("image.png")
image = image.getResized(image.size * 2)

# create mipmaps
image = image.getMipmapped()

# compress image to BC1 format
image_bc1 = image.toFormat(FormatBC1RGBu8n)
image_bc1.save("test_bc1.dds")
print(image_bc1.description)

# compress image to BC7 format
image_bc7 = image.toFormat(FormatBC7RGBAu8n)
image_bc7.save("test_bc7.dds")
print(image_bc7.description)

# compress image to ASTC4x4 format
image_astc44 = image.toFormat(FormatASTC44RGBAu8n)
image_astc44.save("test_astc44.ktx")
print(image_astc44.description)

# compress image to ASTC8x8 format
image_astc88 = image.toFormat(FormatASTC88RGBAu8n)
image_astc88.save("test_astc88.ktx")
print(image_astc88.description)

###############################################################################
#
# NumPy
#
###############################################################################

import numpy

# load image and convert to float32 format
image.load("image.png")
image = image.toFormat(FormatRGBf32)

# create array with specified dimension and format
array = numpy.zeros(shape = ( image.width, image.height, 3 ), dtype = numpy.float32)

# copy image data into the array
image.getData(array)

# set inverted data into the image
image.setData(1.0 - array)

# save inverted image
image.save("test_numpy.dds")
print(image.description)
