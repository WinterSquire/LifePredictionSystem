import os

from ModelSet.data import *
from ModelSet.CNN.model_process import process

def cnn(test_data_path: str) -> str:
    column_to_delete = [26, 4, 4, 7, 11, 16, 17, 17, 0, 0, 0, 0, 3]

    test_data = drop_column(load_data(data_path, ' ', None), column_to_delete)
    train_data = drop_column(load_data(data_path, ' ', None), column_to_delete)

    result = process(train_data, test_data)

    return str(result).replace('\'', '\"')
