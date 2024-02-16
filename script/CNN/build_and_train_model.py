# 2. 构建和训练模型函数

# 功能描述:
#     构建卷积神经网络 (CNN) 模型。
#     编译并训练模型。
# 所需的包:
#     tensorflow.keras 用于构建和训练模型。
# 参数列表:
#     X_train, y_train: 训练数据的特征和目标变量。
#     X_test, y_test: 测试数据的特征和目标变量。
#     epochs: 训练周期数。
#     batch_size: 批处理大小。
# 返回值:
#     model: 训练好的模型。
#     history: 训练历史记录

from tensorflow.keras.models import Sequential  
from tensorflow.keras.layers import Conv1D, MaxPooling1D, Flatten, Dense, Dropout  
from tensorflow.keras.optimizers import SGD
from tensorflow.keras.regularizers import l2

def build_and_train_model(X_train, y_train, X_test, y_test, epochs=50, batch_size=32):
    model = Sequential()  
    model.add(Conv1D(128, kernel_size=4, activation='tanh', input_shape=(X_train.shape[1], 1), kernel_regularizer=l2(0.001)))  
    model.add(MaxPooling1D(pool_size=2))  
    model.add(Conv1D(128, kernel_size=4, activation='tanh'))  
    model.add(MaxPooling1D(pool_size=2))
    model.add(Flatten())  
    model.add(Dense(4, activation='tanh', kernel_regularizer=l2(0.001))) 
    model.add(Dropout(0.1))  
    model.add(Dense(1, activation='linear'))  

    optimizer = SGD(learning_rate=0.001)
    model.compile(loss='mse', optimizer=optimizer, metrics=['mse'])
    history = model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, validation_data=(X_test, y_test))
    
    return model, history
