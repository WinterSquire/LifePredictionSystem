from ModelSet.data import *
from .model_process import KNN

def knn(test_data_path: str, index: int = 0) -> str:
    columns_to_delete = [
        [1, 2, 6],
        [1, 2, 6, 8, 12, 13, 15],
        [1, 2, 3, 6, 7, 8, 10, 11, 12, 15, 16],
        [6],
    ]

    result = KNN(test_data_path, get_knn_train_data_path(index), columns_to_delete[index])

    return str(result).replace('\'', '\"')


