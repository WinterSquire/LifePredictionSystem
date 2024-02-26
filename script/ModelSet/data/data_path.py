import os

def get_cnn_train_data_path() -> str:
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), 'train.txt')

def get_knn_train_data_path(index: int = 0) -> str:
    files = [
        '0-40.txt',
        '40-80.txt',
        '80-125.txt',
        '125+.txt',
    ]

    return os.path.join(os.path.dirname(os.path.abspath(__file__)), files[index])
