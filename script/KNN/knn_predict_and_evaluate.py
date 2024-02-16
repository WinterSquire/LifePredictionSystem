# 3. KNN预测函数
# 功能描述:
#     使用KNN模型进行预测。
#     计算预测的均方误差。
# 所需的包:
#     sklearn.neighbors 用于KNN回归。
#     sklearn.metrics 用于计算均方误差。
# 参数列表:
#     X_train, y_train: 训练数据的特征和目标变量。
#     X_test, y_test: 测试数据的特征和目标变量。
#     n_neighbors: KNN中的邻居数。
#     weights: 权重函数。
#     p: 距离度量的参数。
# 返回值:
#     rmse: 预测的均方误差。
from sklearn.neighbors import KNeighborsRegressor
from sklearn.metrics import mean_squared_error

def knn_predict_and_evaluate(X_train, y_train, X_test, y_test, n_neighbors=15, weights='distance', p=2):
    knn_regressor = KNeighborsRegressor(n_neighbors=n_neighbors, weights=weights, p=p)
    knn_regressor.fit(X_train, y_train)
    y_pred = knn_regressor.predict(X_test)
    rmse = np.sqrt(mean_squared_error(y_test, y_pred))
    return rmse
