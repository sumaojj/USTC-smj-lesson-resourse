import copy,math
import numpy as np  
import matplotlib.pyplot as plt
np.set_printoptions(precision=2) # set the print precision to 2 decimal places

X_train = np.array([[2104, 5, 1, 45], [1416, 3, 2, 40], [852, 2, 1, 35]])
y_train = np.array([460, 232, 178])

def calculate_cost(X, y, w, b):
    n = len(X)
    total_cost = 0.0
    for i in range(n):
        total_cost += (y[i] - (np.dot(w,X[i]) + b))**2
    return total_cost/2*n

def update_weights(X, y, w, b, learning_rate):
    dw = np.zeros(len(X[0]))
    db = 0
    n = len(X)
    for i in range(n):
        dw += -X[i] * (y[i] - (np.dot(w,X[i]) + b))
        db += -(y[i] - (np.dot(w,X[i]) + b))
    w -= (1.0/n) * learning_rate * dw
    b -= (1.0/n) * learning_rate * db
    return w, b

def train(X, y, w, b, learning_rate, iters):
    cost_history = []
    for i in range(iters):
        w, b = update_weights(X, y, w, b, learning_rate)
        cost = calculate_cost(X, y, w, b)
        cost_history.append(cost)
    return w, b, cost_history

w = np.zeros(len(X_train[0]))
b = 0
learning_rate = 0.0000001
iters = 100000
w, b, cost_history = train(X_train, y_train, w, b, learning_rate, iters)
print(w, b)