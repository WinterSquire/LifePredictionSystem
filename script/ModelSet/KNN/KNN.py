from ModelSet.data import *
from .model_process import KNN

def knn(test_data_path: str, index: str = '0') -> str:
    train_data_path, column_list = get_knn_data(int(index))
    return str(KNN(test_data_path, train_data_path, column_list)).replace('\'', '\"')
