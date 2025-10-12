#!/usr/bin/env python3

import struct
import torch
import torchvision
import torchsummary

from tellusimd import *

device = torch.device('cpu')
if torch.cuda.is_available():
	device = torch.device('cuda')

# model
class module(torch.nn.Module):
	def __init__(self):
		super(module, self).__init__()
		self.encoder = torch.nn.Sequential(
			torch.nn.Conv2d(3, 16, kernel_size = 5, stride = 3, padding = 2, bias = False, device = device),
			torch.nn.SiLU(),
			torch.nn.BatchNorm2d(16, device = device),
			torch.nn.Conv2d(16, 32, kernel_size = 3, stride = 2, padding = 2, bias = False, device = device),
			torch.nn.SiLU(),
			torch.nn.BatchNorm2d(32, device = device),
			torch.nn.Conv2d(32, 32, kernel_size = 3, stride = 2, padding = 1, bias = False, device = device),
			torch.nn.SiLU(),
			torch.nn.BatchNorm2d(32, device = device),
			torch.nn.Conv2d(32, 16, kernel_size = 3, stride = 1, padding = 1, bias = False, device = device),
			torch.nn.SiLU(),
		)
		self.decoder = torch.nn.Sequential(
			torch.nn.ConvTranspose2d(16, 32, kernel_size = 3, stride = 1, padding = 1, bias = False, device = device),
			torch.nn.SiLU(),
			torch.nn.ConvTranspose2d(32, 32, kernel_size = 3, stride = 2, padding = 1, bias = False, device = device),
			torch.nn.SiLU(),
			torch.nn.ConvTranspose2d(32, 16, kernel_size = 3, stride = 2, padding = 1, bias = False, device = device),
			torch.nn.SiLU(),
			torch.nn.ConvTranspose2d(16, 3, kernel_size = 5, stride = 3, padding = 1, output_padding = 1, bias = False, device = device),
			torch.nn.Sigmoid(),
		)
	def forward(self, x):
		x = self.encoder(x)
		x = self.decoder(x)
		return x

# train model
if False:
	
	size = 64
	batch = 64
	epochs = 128
	
	# load texture
	image = torchvision.io.read_image('texture.jpg').to(dtype = torch.float, device = device) / 255.0
	
	# create tiles
	width = image.shape[2] // size
	height = image.shape[1] // size
	tiles = torch.zeros((width * height, 3, size, size), device = device)
	for y in range(height):
		for x in range(width):
			tiles[width * y + x] = torchvision.transforms.functional.crop(image, size * x, size * y, size, size)
	
	# permute tiles
	indices = torch.randperm(tiles.shape[0])
	tiles = tiles[indices].view(tiles.size())
	
	# create model
	model = module()
	loss = torch.nn.MSELoss()
	optimizer = torch.optim.Adam(model.parameters(), lr = 0.001)
	
	# train model
	for epoch in range(epochs):
		for i in range((tiles.shape[0] - 1) // batch + 1):
			
			begin = i * batch
			end = begin + batch
			x = tiles[begin:end]
			error = loss(model(x), x)
			
			# save model
			if i == 0:
				torch.save(model, 'model.pth')
				print(error)
			
			error.backward()
			optimizer.step()
			optimizer.zero_grad()

# load model
model = torch.load('model.pth', map_location = 'cpu').eval()
print(torchsummary.summary(model))
model_state = model.state_dict()

# export weights
file = open('model.bin', 'wb')

# write header
offset = 0
alignment = 64
for name in model_state:
	tensor = model_state[name]
	if not tensor.shape: continue
	file.write(struct.pack('B', len(tensor.shape)))
	for size in tensor.shape: file.write(struct.pack('H', size))
	file.write(struct.pack('I', offset))
	file.write(struct.pack('{}s'.format(len(name) + 1), name.encode('utf-8')))
	print(name, list(tensor.shape), tensor.numel())
	offset += align(tensor.numel(), alignment)

# end of header
file.write(struct.pack('B', 0xff))
file.write(struct.pack('I', offset))

# write weights
for name in model_state:
	tensor = model_state[name]
	if not tensor.shape: continue
	tensor = tensor.detach().cpu().view(-1).numpy()
	file.write(struct.pack('f' * len(tensor), *tensor))
	for i in range(len(tensor), align(len(tensor), alignment)):
		file.write(struct.pack('f', 0.0))
