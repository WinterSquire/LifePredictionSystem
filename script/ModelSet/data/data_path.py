import os

def get_train_data_path() -> str:
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), 'train.txt')