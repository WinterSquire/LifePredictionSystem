# 2. 归一化处理函数

# 功能描述:
#     对数据进行归一化处理。
# 所需的包:
#     sklearn.preprocessing 用于归一化处理。
# 参数列表:
#     data: 需要归一化处理的数据。
# 返回值:
#     data: 归一化处理后的数据。


from sklearn.preprocessing import MinMaxScaler

def normalize_data(data):
    scaler = MinMaxScaler()
    data_to_normalize = data.iloc[:, :-1]
    normalized_data = scaler.fit_transform(data_to_normalize)
    data.iloc[:, :-1] = normalized_data
    return data
