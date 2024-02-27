import os

def get_cnn_train_data_path() -> str:
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), 'train.txt')

def get_cnn_data() -> (str, list):
    return get_cnn_train_data_path(), [26, 4, 4, 7, 11, 16, 17, 17, 0, 0, 0, 0, 3]

def get_knn_train_data_path(index: int = 0) -> str:
    files = [
        '0-40.txt',
        '40-80.txt',
        '80-125.txt',
        '125+.txt',
    ]

    return os.path.join(os.path.dirname(os.path.abspath(__file__)), files[index])

def get_knn_train_data_columns_to_delete(index: int = 0) -> list:
    columns_to_delete = [
        [1, 2, 6],
        [1, 2, 6, 8, 12, 13, 15],
        [1, 2, 3, 6, 7, 8, 10, 11, 12, 15, 16],
        [6],
    ]

    return columns_to_delete[index]

def get_knn_data(index: int = 0) -> (str, list):
    return get_knn_train_data_path(index), get_knn_train_data_columns_to_delete(index)
