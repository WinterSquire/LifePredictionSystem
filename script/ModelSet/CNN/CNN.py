import os

from ModelSet.data import *
from ModelSet.CNN.model_process import process

def cnn(test_data_path: str) -> str:
    column_to_delete = [26, 4, 4, 7, 11, 16, 17, 17, 0, 0, 0, 0, 3]

    test_data = load_and_drop_data(test_data_path, column_to_delete)
    train_data = load_and_drop_data(get_train_data_path(), column_to_delete)

    result = process(train_data, test_data)

    return str(result).replace('\'', '\"')
