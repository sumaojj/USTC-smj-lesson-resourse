#Pytorch foundamentals 1


import math,copy
import numpy as np
import matplotlib.pyplot as plt
#print("I'm excited to learn more about pyTorch")
import torch
#print(torch.__version__)

#scalar
scalar = torch.tensor(7)
print(scalar)
print(scalar.ndim)
print(scalar.item())#get the value of the scalar as a python number

#vector
vector = torch.tensor([1,2,3,4])
print(vector)
print(vector.ndim)
print(vector.size())

#Matrix
matrix = torch.tensor([[1,2,3],[4,5,6]])
print(matrix)
print(matrix.ndim)
print(matrix.size())

#Tensor
tensor = torch.tensor([[[1,2,3],[4,5,6]],[[7,8,9],[10,11,12]]]) 
print(tensor)
print(tensor.ndim)
print(tensor.size())
print(tensor.dtype)
print(tensor.device)

#Start with random numbers -> look at data -> update random numbers -> look at data -> update random numbers...
#create a tensor with random numbers and the shape of the tensor is 2x3
x = torch.rand(2,3)
#print(x)
#Create a tensor with zeros and the shape of the tensor is 2x3
x = torch.zeros(2,3)
#Create a tensor with ones and the shape of the tensor is 2x3
x = torch.ones(2,3)

#In deep learning, data (images, text, video, audio, protein structures, etc) gets represented as tensors
#Basic operations omitted (just as in numpy)

#Matrix multiplication
#@ similar to np.dot
tensor1 = torch.tensor([1,2,3])
print(tensor1@tensor1)
print(torch.matmul(tensor1,tensor1))

#using tensor.T to transpose a tensor
tensor2 = torch.tensor([[1,2,3],[4,5,6]])
print(tensor2.T)