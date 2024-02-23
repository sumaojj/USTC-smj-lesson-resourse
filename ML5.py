
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
#from tensorflow.keras import layers


model= tf.keras.Sequential([tf.keras.layers.Dense(units=25, activation='sigmoid', input_shape=(2,)),
                            tf.keras.layers.Dense(units=15, activation='sigmoid'),
                            tf.keras.layers.Dense(units=1, activation='sigmoid')])

model.compile(loss='BinaryCrossentropy')
#model.fit(X,Y, epochs=1000)
                           
