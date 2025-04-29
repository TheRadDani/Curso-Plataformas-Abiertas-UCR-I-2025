# train_tflite_model.py
import numpy as np
import tensorflow as tf

# Generate sine wave data
X = np.linspace(0, 2*np.pi, 1000).astype(np.float32)
y = np.sin(X).astype(np.float32)

# Create TensorFlow model
model = tf.keras.Sequential([
    tf.keras.layers.InputLayer(input_shape=(1,)),
    tf.keras.layers.Dense(8, activation='relu'),
    tf.keras.layers.Dense(1)
])

# Compile and train
model.compile(optimizer='adam', loss='mse')
model.fit(X, y, epochs=100, batch_size=32)

# Convert to TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()

# Save model
with open('sine_model.tflite', 'wb') as f:
    f.write(tflite_model)