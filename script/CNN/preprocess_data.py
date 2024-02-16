# 数据预处理函数
# 功能描述:
#   读取训练和测试数据。
#   删除指定的列。
#   分离特征和目标变量。
# 所需的包:
#   pandas 用于数据处理。
# 参数列表:
#   train_file_path: 训练数据文件路径。
#   test_file_path: 测试数据文件路径。
#   columns_to_drop: 需要从数据中删除的列索引列表。
# 返回值:
#   X_train, y_train: 训练数据的特征和目标变量。
#   X_test, y_test: 测试数据的特征和目标变量。


import pandas as pd

def preprocess_data(train_file_path, test_file_path, columns_to_drop):
    # 读取数据
    train_data = pd.read_csv(train_file_path, sep=' ', header=None)
    test_data = pd.read_csv(test_file_path, sep=' ', header=None)
    
    # 删除指定的列
    train_data.drop(columns_to_drop, axis=1, inplace=True)
    test_data.drop(columns_to_drop, axis=1, inplace=True)
    
    # 分离特征和目标变量
    X_train, y_train = train_data.iloc[:, :-1], train_data.iloc[:, -1]
    X_test, y_test = test_data.iloc[:, :-1], test_data.iloc[:, -1]
    
    return X_train, y_train, X_test, y_test
