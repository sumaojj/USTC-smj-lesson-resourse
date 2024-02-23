import math,copy
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

#unregularization
layer1 = tf.keras.layers.Dense(units=10,  activation='relu')
layer2 = tf.keras.layers.Dense(units=10, activation='relu')
layer3 = tf.keras.layers.Dense(units=10, activation='relu')

model = tf.keras.Sequential([layer1, layer2, layer3])

#regularization
layer1 = tf.keras.layers.Dense(units=10,  activation='relu', kernel_regularizer=tf.keras.regularizers.l2(0.01))
layer2 = tf.keras.layers.Dense(units=10, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(0.01))
layer3 = tf.keras.layers.Dense(units=10, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(0.01))

