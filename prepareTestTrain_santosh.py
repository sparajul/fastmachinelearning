from sklearn.model_selection import train_test_split
import tensorflow.keras as keras
from numpy import load 
import numpy as np 

quark_sample 	= load('quark_leading_jet.npz')['arr_0']
gluon_sample 	= load('gluon_leading_jet.npz')['arr_0']

x_data 		= np.concatenate( (quark_sample, gluon_sample) )
x_data          = x_data.reshape(x_data.shape + (1,)).astype('float32')
x_data          /=255.

y_data          = np.array([0]*len(gluon_sample) + [1]*len(quark_sample))

y_data          = keras.utils.to_categorical(y_data,2)

x_train, x_test, y_train, y_test = train_test_split(x_data,y_data)


import h5py
h5 = h5py.File('jetImages.h5','w')
h5.create_dataset("x_train",data=x_train)
h5.create_dataset("x_test",data=x_test)
h5.create_dataset("y_train",data=y_train)
h5.create_dataset("y_test",data=y_test)
h5.close()
