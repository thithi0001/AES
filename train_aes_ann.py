from mylib import *
import numpy as np
import tensorflow as tf
from sklearn.model_selection import train_test_split

# Hàm chuẩn bị dữ liệu cho mô hình
def prepare_data(num_samples=10000):
    # Tạo dữ liệu ngẫu nhiên cho các khối 16 byte
    inputs = np.random.randint(0, 256, (num_samples, 16), dtype=np.uint8)
    
    # Tạo nhãn cho các bước sub_bytes, mix_columns và key expansion
    sub_bytes_outputs = np.array([sub_bytes(block) for block in inputs])
    mix_columns_outputs = np.array([nhanCot_encrypt(block) for block in inputs])
    
    # Tạo dữ liệu cho key expansion (giả sử key là 16 byte)
    keys = np.random.randint(0, 256, (num_samples, 16), dtype=np.uint8)
    key_expansion_outputs = np.array([key_expansion(key, 4, 10) for key in keys])
    
    # Kết hợp dữ liệu đầu vào và nhãn
    X = np.concatenate((inputs, keys), axis=1)  # Kết hợp input và key
    y = np.concatenate((sub_bytes_outputs, mix_columns_outputs, key_expansion_outputs), axis=1)
    
    return X, y

# Huấn luyện mô hình ANN
def train_model(X, y):
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(128, activation='relu', input_shape=(X.shape[1],)),
        tf.keras.layers.Dense(256, activation='relu'),
        tf.keras.layers.Dense(y.shape[1])  # Đầu ra tương ứng với kích thước nhãn
    ])
    
    model.compile(optimizer='adam', loss='mean_squared_error')
    model.fit(X, y, epochs=10, batch_size=32, validation_split=0.2)
    
    return model

# Chạy mã nguồn
if __name__ == "__main__":
    X, y = prepare_data()
    model = train_model(X, y)