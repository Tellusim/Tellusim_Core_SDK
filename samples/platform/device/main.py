#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import sys

from tellusimd import *

# create app
app = App(sys.argv)
if not app.create(): exit(1)

# create context
context = Context(app.platform, app.device)
if not context.create(): exit(1)

# create device
device = Device(context)
if not device: exit(1)

# device name
Log.printf(Log.Message, '%s (%s)\n', device.name, device.platform_name)
if device.vendor: Log.printf(Log.Message, 'Vendor: %s\n', device.vendor)
if device.version: Log.printf(Log.Message, 'Version: %s\n', device.version)

# device features
Log.printf('%s\n', device.features)

# finish context
context.finish()
