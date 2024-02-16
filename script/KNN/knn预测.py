data=pd.read_csv(r"E:\大创\train0-40.csv",sep=',')

data = data.drop(data.columns[[19]], axis=1)
new_column_names = ['0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18'] # 替换成你想要的新列名
data.columns = new_column_names
data = data.drop(data.columns[[0]], axis=1)

#以下根据任务进行删列
data = data.drop(data.columns[[1]], axis=1)
data = data.drop(data.columns[[1]], axis=1)
data = data.drop(data.columns[[4]], axis=1)

data.iloc[:, -1] = np.where(data.iloc[:, -1] > 125, 125, data.iloc[:, -1])
import numpy as np
from sklearn.preprocessing import MinMaxScaler
# 选取前 13 列的数据
data_to_normalize = data.iloc[:,:-1]
# 创建 MinMaxScaler
scaler = MinMaxScaler()
# 调用 fit_transform 进行归一化
normalized_data = scaler.fit_transform(data_to_normalize)
# 将归一化后的数据替换回原数据中的对应位置
data.iloc[:, :-1] = normalized_data
print(data)

data1=pd.read_csv(r"C:\Users\user\随机森林40三分类周期留class_test0.csv",sep=',',header=None)
data1.columns = new_column_names
import numpy as np
data1 = data1.drop(data1.columns[[0]], axis=1)


#以下根据任务进行删列
data1 = data1.drop(data1.columns[[1]], axis=1)
data1 = data1.drop(data1.columns[[1]], axis=1)
data1 = data1.drop(data1.columns[[4]], axis=1)

data1.iloc[:, -1] = np.where(data1.iloc[:, -1] > 125, 125, data1.iloc[:, -1])
import numpy as np
from sklearn.preprocessing import MinMaxScaler
# 选取前 13 列的数据
data_to_normalize = data1.iloc[:, :-1]
# 创建 MinMaxScaler
scaler = MinMaxScaler()
# 调用 fit_transform 进行归一化
normalized_data = scaler.fit_transform(data_to_normalize)
# 将归一化后的数据替换回原数据中的对应位置
data1.iloc[:, :-1] = normalized_data
print(data1)

#knn预测
X1=data1.iloc[:,:-1]
X=data.iloc[:,:-1]
y_test=data1.iloc[:,-1]
y_train=data.iloc[:,-1]

from sklearn.neighbors import KNeighborsRegressor
from sklearn.metrics import mean_squared_error


# 使用带有权重的 KNN 回归模型

knn_regressor = KNeighborsRegressor(n_neighbors=15,weights='distance',p=2)  # 设置权重为距离的倒数
knn_regressor.fit(X,y_train )  # 拟合模型

# 进行预测
y_pred = knn_regressor.predict(X1)  # 使用测试数据进行预测

# 计算均方误差
rmse = np.sqrt(mean_squared_error(y_test, y_pred))
print("均方误差 (RMSE)",rmse)



