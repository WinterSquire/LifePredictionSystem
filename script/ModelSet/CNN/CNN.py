from ModelSet.data import *
from ModelSet.CNN.model_process import process

def cnn(test_data_path: str) -> str:
    train_data_path, column_to_delete = get_cnn_data()

    test_data = drop_column(load_data(test_data_path, ' ', None), column_to_delete)
    train_data = drop_column(load_data(train_data_path, ' ', None), column_to_delete)

    result = process(train_data, test_data)

    return str(result).replace('\'', '\"')
