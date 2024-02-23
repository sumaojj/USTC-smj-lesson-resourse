import math,copy
import numpy as np
import matplotlib.pyplot as plt

x_train = np.array([1.0, 2.0])
y_train = np.array([300.0, 500.0])

#function to calculate the cost of the model
def calculate_cost(x, y, w, b):
    n = len(x)
    total_cost = 0.0
    for i in range(n):
        total_cost += (y[i] - (w*x[i] + b))**2
    return total_cost/2*n

#function to update the weights and bias
def update_weights(x, y, w, b, learning_rate):
    dw = 0
    db = 0
    n = len(x)
    for i in range(n):
        dw += -x[i] * (y[i] - (w*x[i] + b))
        db += -(y[i] - (w*x[i] + b))
    w -= (1.0/n) * learning_rate * dw
    b -= (1.0/n) * learning_rate * db
    return w, b

#function to train the model
def train(x, y, w, b, learning_rate, iters):
    cost_history = []
    for i in range(iters):
        w, b = update_weights(x, y, w, b, learning_rate)
        cost = calculate_cost(x, y, w, b)
        cost_history.append(cost)
    return w, b, cost_history

#initializing the weights and bias
w = 0
b = 0
learning_rate = 0.001
iters = 100000
w, b, cost_history = train(x_train, y_train, w, b, learning_rate, iters)
print(w, b)
print(calculate_cost(x_train, y_train, w, b))
