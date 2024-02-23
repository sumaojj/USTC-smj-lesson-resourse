import math,copy
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
#from tensorflow.python.keras.layers import Dense （is a bug）

def my_softmax(z):
    ez = np.exp(z)              #element-wise exponenial
    sm = ez/np.sum(ez)
    return(sm)

def my_cross_entropy(y, p):
    ce = -np.sum(y*np.log(p))
    return(ce)

preferred_model = Sequential(
    [ 
        Dense(25, activation = 'relu'),
        Dense(15, activation = 'relu'),
        Dense(4, activation = 'linear')   #<-- Note
    ]
)
preferred_model.compile(
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),  #<-- Note
    optimizer=tf.keras.optimizers.Adam(0.001),
)

preferred_model.fit(
    X_train,y_train,
    epochs=10
)
    
