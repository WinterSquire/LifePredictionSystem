import pandas as pd
from pandas import DataFrame
import numpy as np

def drop_column(data: DataFrame, columns_to_delete: list) -> DataFrame:
    for column in columns_to_delete:
        data = data.drop(data.columns[[column]], axis=1)
    return data

def load_data(data_path: str, columns_to_delete: list) -> DataFrame:
    data = pd.read_csv(data_path, sep=' ', header=None)
    data = drop_column(data, columns_to_delete)
    return data

def calculate_si(y_pred, y_test) -> float:
    result = np.zeros_like(y_pred)
    for i in range(len(y_pred)):
        if y_pred[i]<y_test[i]:
            result[i] = np.exp((y_test[i]-y_pred[i])/13)-1
        elif y_pred[i]>y_test[i]:
            result[i] = np.exp((y_pred[i]-y_test[i])/13)-1
    return result

