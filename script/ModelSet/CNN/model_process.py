from tensorflow.keras.optimizers import Adam, RMSprop
from tensorflow.keras.models import Sequential, load_model
from tensorflow.keras.layers import Conv1D, MaxPooling1D, Flatten, Dense, Dropout
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
from tensorflow.keras.regularizers import l2
from keras.optimizers import SGD
import numpy as np

def build_cnn_model(column_count: int) -> Sequential:
    model = Sequential()
    model.add(Conv1D(128, kernel_size=4, activation='tanh', input_shape=(column_count, 1), kernel_regularizer=l2(0.001)))
    model.add(MaxPooling1D(pool_size=2))
    model.add(Conv1D(128, kernel_size=4, activation='tanh'))
    model.add(MaxPooling1D(pool_size=2))
    model.add(Flatten())
    model.add(Dense(4, activation='tanh',kernel_regularizer=l2(0.001))) # 添加全连接层
    model.add(Dropout(0.1))  # 添加Dropout层
    model.add(Dense(1, activation='linear'))
    optimizer = SGD(learning_rate=0.001)
    model.compile(loss='mse', optimizer=optimizer, metrics=['mse'])
    return model

def calculate_Si(y_pred,y_test):
    Si_values=np.zeros_like(y_pred)
    for i in range(len(y_pred)):
        if y_pred[i]<y_test[i]:
            Si_values[i]=np.exp((y_test[i]-y_pred[i])/13)-1
        elif y_pred[i]>y_test[i]:
            Si_values[i]=np.exp((y_pred[i]-y_test[i])/13)-1
    return Si_values

def process(train_data, test_data) -> dict:
    x_test, y_test = test_data.iloc[:, :-1], test_data.iloc[:, -1]
    x_train, y_train = train_data.iloc[:, :-1], train_data.iloc[:, -1]

    model = build_cnn_model(x_train.shape[1])

    history = model.fit(x_train, y_train, epochs=50, batch_size=32, validation_data=(x_test, y_test))
    result = history.history.copy()

    y_pred = model.predict(x_test)

    mse = np.sqrt(mean_squared_error(y_test, y_pred))
    total_score = np.sum(calculate_Si(y_pred, y_test))

    result['mean_mse'] = float(mse)
    result['total_score'] = float(total_score)

    return result
