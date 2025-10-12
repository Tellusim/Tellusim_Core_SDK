#!/usr/bin/env python3

import gzip
import struct
import pickle
import requests
import torch
import torchsummary

from tellusimd import *

device = torch.device('cpu')
if torch.cuda.is_available():
	device = torch.device('cuda')

# model
class module(torch.nn.Module):
	def __init__(self):
		super(module, self).__init__()
		self.pool = torch.nn.MaxPool2d(2, 2)
		self.conv1 = torch.nn.Conv2d(1, 16, kernel_size = 3, stride = 2, padding = 1, bias = False, device = device)
		self.norm1 = torch.nn.BatchNorm2d(16, device = device)
		self.conv2 = torch.nn.Conv2d(16, 96, kernel_size = 3, stride = 2, padding = 1, bias = False, device = device)
		self.norm2 = torch.nn.BatchNorm2d(96, device = device)
		self.linear = torch.nn.Linear(384, 10, device = device)
	def forward(self, x):
		x = x.view(-1, 1, 28, 28)
		x = self.conv1(x)
		x = torch.nn.functional.relu(x)
		x = self.pool(x)
		x = self.norm1(x)
		x = self.conv2(x)
		x = torch.nn.functional.relu(x)
		x = self.pool(x)
		x = self.norm2(x)
		x = x.view(-1, x.size(1) * x.size(2) * x.size(3))
		return self.linear(x)

# train model
if False:
	
	size = 24
	batch = 64
	epochs = 64
	
	# download data
	name = 'mnist.pkl.gz'
	if not Source.isSource(name):
		print('downloading:', name)
		data = requests.get('https://github.com/pytorch/tutorials/raw/main/_static/' + name).content
		open(name, 'wb').write(data)
	
	# load data
	data = gzip.open(name, 'rb')
	((x_train, y_train), (x_valid, y_valid), _) = pickle.load(data, encoding = 'latin-1')
	
	# create texture
	texture = 'texture.png'
	if not Source.isSource(texture):
		print('creating:', texture)
		tile = Image()
		image = Image()
		tile.create2D(FormatRf32, 28, 28)
		image.create2D(FormatRf32, 28 * size, 28 * size)
		for y in range(size):
			for x in range(size):
				tile.setData(x_valid[size * y + x])
				image.copy(tile, Origin(28 * x, 28 * y))
		image = image.toFormat(FormatRu8n)
		image.save(texture)
	
	# create tensors
	x_train = torch.tensor(x_train, device = device)
	y_train = torch.tensor(y_train, device = device)
	
	# create model
	model = module()
	loss = torch.nn.functional.cross_entropy
	optimizer = torch.optim.Adam(model.parameters(), lr = 0.001)
	
	# train model
	for epoch in range(epochs):
		for i in range((len(y_train) - 1) // batch + 1):
			
			begin = i * batch
			end = begin + batch
			x = x_train[begin:end]
			y = y_train[begin:end]
			error = loss(model(x), y)
			
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
