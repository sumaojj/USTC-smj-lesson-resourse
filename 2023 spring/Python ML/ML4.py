import math,copy
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

x_train = np.array([0,1],[2,3],[4,5],[6,7],[8,9],[10,11])
y_train = np.array([0,  0, 0, 1, 1, 1])

layer_1= tf.keras.layers.Dense(units=3, activation='sigmoid', input_shape=(2,))
layer_2= tf.keras.layers.Dense(units=1, activation='sigmoid')

model = tf.keras.Sequential([layer_1, layer_2])
model.compile(optimizer=tf.keras.optimizers.SGD(learning_rate=0.1), loss='mean_squared_error')

model.fit(x_train, y_train, epochs=1000)

#set initial weights
layer_1.set_weights([np.array([[1, 1, 1], [1, 1, 1]]), np.array([0, 0, 0])])
layer_2.set_weights([np.array([[1], [1], [1]]), np.array([0])])

x_new = np.array([0, 1])
y_new = model.predict(x_new)