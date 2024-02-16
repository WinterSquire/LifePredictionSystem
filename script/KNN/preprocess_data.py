#  1. 数据预处理函数
# 功能描述:
#     读取数据。
#     删除指定的列。
#     对目标变量进行上限处理。
# 所需的包:
#     pandas 用于数据处理。
#     numpy 用于数值计算。
# 参数列表:
#     file_path: 数据文件的路径。
#     columns_to_drop: 需要从数据中删除的列索引列表。
#     target_column_index: 目标变量列的索引。
#     target_upper_limit: 目标变量的上限值。
# 返回值:
#     data: 预处理后的数据。

import pandas as pd
import numpy as np

def preprocess_data(file_path, columns_to_drop, target_column_index, target_upper_limit):
    data = pd.read_csv(file_path, sep=',')
    data.drop(columns_to_drop, axis=1, inplace=True)
    data.iloc[:, target_column_index] = np.where(data.iloc[:, target_column_index] > target_upper_limit, target_upper_limit, data.iloc[:, target_column_index])
    return data
