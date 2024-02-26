# 加载库
import pandas as pd 
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.neighbors import KNeighborsRegressor
from sklearn.metrics import mean_squared_error

# 定义自定义评分函数
def calculate_Si(y_pred, y_test):
    Si_values = np.zeros_like(y_pred)
    for i in range(len(y_pred)):
        if y_pred[i] < y_test[i]:
            Si_values[i] = np.exp((y_test[i] - y_pred[i]) / 13) - 1
        elif y_pred[i] > y_test[i]:
            Si_values[i] = np.exp((y_pred[i] - y_test[i]) / 13) - 1
    return Si_values

def _data_trim(data, exception_list):
    # 调整数据
    data = data.drop(data.columns[[26]], axis=1)
    data.iloc[:, -1] = np.where(data.iloc[:, -1] > 125, 125, data.iloc[:, -1]) 
    data = data.drop(data.columns[[4]], axis=1)
    data = data.drop(data.columns[[4]], axis=1)
    data = data.drop(data.columns[[7]], axis=1)
    data = data.drop(data.columns[[11]], axis=1)
    data = data.drop(data.columns[[16]], axis=1)
    data = data.drop(data.columns[[17]], axis=1)
    data = data.drop(data.columns[[17]], axis=1)
    data = data.drop(data.columns[[0]], axis=1)
    data = data.drop(data.columns[[0]], axis=1)
    
    # 删除不需要的列
    for i in range(len(exception_list)):
        data = data.drop(data.columns[[exception_list[i] - i - 1]], axis=1)
    
    return data

# 归一化
def _data_normalization(data):
    # 选取除最后一列的数据
    data_to_normalize = data.iloc[:, :-1]
    # 创建 MinMaxScaler
    scaler = MinMaxScaler()
    # 调用 fit_transform 进行归一化
    normalized_data = scaler.fit_transform(data_to_normalize)
    # 将归一化后的数据替换回原数据中的对应位置
    data.iloc[:, :-1] = normalized_data
    return data

def KNN(test_path: str, train_path: str, exception_list: list) -> dict:
    # 读取数据
    train_data = _data_trim(pd.read_csv(train_path, sep=' ', header=None), exception_list)
    test_data = _data_trim(pd.read_csv(test_path, sep=' ', header=None), exception_list)

    # 归一化数据
    train_data = _data_normalization(train_data)
    test_data = _data_normalization(test_data)

    #knn预测
    X1          = test_data.iloc[:,:-1]
    X           = train_data.iloc[:,:-1]
    realrul     = test_data.iloc[:,-1]
    prediction  = train_data.iloc[:,-1]

    n_neighbors = [3,5,7,9,11,13,15]
    result_rmse = []
    result_total_score = []

    #n_neighbors取3,5,7,9,11,13,15
    for n in n_neighbors:
        # 使用带有权重的 KNN 回归模型
        knn_regressor = KNeighborsRegressor(n_neighbors=n,weights='distance',p=2)  # 设置权重为距离的倒数
        knn_regressor.fit(X,prediction)  # 拟合模型
        
        # 进行预测
        y_pred = knn_regressor.predict(X1)  # 使用测试数据进行预测
        
        # 计算均方误差
        rmse = np.sqrt(mean_squared_error(realrul, y_pred))
        
        # 计算自定义评分
        Si_values = calculate_Si(y_pred, realrul)  # 注意这里使用 realrul 作为真实值
        total_score = np.sum(Si_values)

        result_rmse.append(rmse)
        result_total_score.append(total_score)

    return {'n': n_neighbors, 'rmse': result_rmse, 'total_score': result_total_score}