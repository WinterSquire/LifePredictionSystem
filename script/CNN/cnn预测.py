import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.neighbors import KNeighborsRegressor
from sklearn.metrics import mean_squared_error

def preprocess_and_predict(train_data_path, test_data_path, drop_columns, k_neighbors=15, weights='distance', p=2):
    """
    参数:
    train_data_path: str, 训练数据文件的路径。
    test_data_path: str, 测试数据文件的路径。
    drop_columns: list, 需要从数据中删除的列索引。
    k_neighbors: int, KNN模型中的邻居数量。
    weights: str, KNN模型中权重的类型，'uniform' 或 'distance'。
    p: int, Minkowski距离的幂参数。
    
    返回值:
    rmse: float, 预测的均方根误差。
    """
    
    # 加载训练数据
    train_data = pd.read_csv(train_data_path, sep=',')
    train_data = train_data.drop(train_data.columns[[19]], axis=1) # 假设需要删除的列是第20列
    new_column_names = [str(i) for i in range(19)]  # 重命名列名
    train_data.columns = new_column_names
    train_data = train_data.drop(columns=[str(drop_columns[i]) for i in range(len(drop_columns))])

    train_data.iloc[:, -1] = np.where(train_data.iloc[:, -1] > 125, 125, train_data.iloc[:, -1])

    # 数据归一化
    data_to_normalize = train_data.iloc[:,:-1]
    scaler = MinMaxScaler()
    normalized_data = scaler.fit_transform(data_to_normalize)
    train_data.iloc[:, :-1] = normalized_data

    # 加载测试数据，并进行相同的预处理步骤
    test_data = pd.read_csv(test_data_path, sep=',', header=None)
    test_data.columns = new_column_names
    test_data = test_data.drop(columns=[str(drop_columns[i]) for i in range(len(drop_columns))])
    test_data.iloc[:, -1] = np.where(test_data.iloc[:, -1] > 125, 125, test_data.iloc[:, -1])

    data_to_normalize = test_data.iloc[:, :-1]
    normalized_data = scaler.transform(data_to_normalize)  # 注意这里用的是transform而不是fit_transform
    test_data.iloc[:, :-1] = normalized_data

    # 准备训练和测试数据
    X_train = train_data.iloc[:,:-1]
    y_train = train_data.iloc[:,-1]
    X_test = test_data.iloc[:,:-1]
    y_test = test_data.iloc[:,-1]

    # KNN回归模型
    knn_regressor = KNeighborsRegressor(n_neighbors=k_neighbors, weights=weights, p=p)
    knn_regressor.fit(X_train, y_train)
    y_pred = knn_regressor.predict(X_test)

    # 计算RMSE
    rmse = np.sqrt(mean_squared_error(y_test, y_pred))
    
    return rmse

