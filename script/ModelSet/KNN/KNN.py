from ModelSet.data import *
from .model_process import process

def knn(test_data_path: str) -> str:
    column_to_delete = [0,1,1,4]

    train_data = drop_column(reindex_column(drop_column(load_data(get_knn_train_data_path(), sep=','), [19])), column_to_delete)
    test_data = drop_column(reindex_column(load_data(test_data_path, ',', None)), column_to_delete)

    result = process(train_data, test_data)

    return str(result).replace('\'', '\"')