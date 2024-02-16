# 3. 性能评估和分数计算函数

# 功能描述:
#     使用模型预测测试集。
#     计算均方误差。
#     根据给定公式计算分数。
# 所需的包:
#     numpy 用于数组操作。
#     sklearn.metrics 用于计算均方误差。
# 参数列表:
#     model: 训练好的模型。
#     X_test, y_test: 测试数据的特征和目标变量。
# 返回值:
#     mse: 测试集上的均方误差。
#     total_score: 根据预测计算的总分数。

import numpy as np
from sklearn.metrics import mean_squared_error

def evaluate_model_and_calculate_score(model, X_test, y_test):
    y_pred = model.predict(X_test)
    mse = np.sqrt(mean_squared_error(y_test, y_pred))
    
    def calculate_Si(y_pred, y_test):
        Si_values = np.zeros_like(y_pred)
        for i in range(len(y_pred)):
            if y_pred[i] < y_test[i]:
                Si_values[i] = np.exp((y_test[i] - y_pred[i]) / 13) - 1
            elif y_pred[i] > y_test[i]:
                Si_values[i] = np.exp((y_pred[i] - y_test[i]) / 13) - 1
        return Si_values
    
    Si_values = calculate_Si(y_pred, y_test)
    total_score = np.sum(Si_values)
    
    return mse, total_score
