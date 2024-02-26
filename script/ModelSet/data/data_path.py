import os

def get_cnn_train_data_path() -> str:
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), 'train.txt')

def get_knn_train_data_path() -> str:
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), 'train0-40.csv')