import pandas as pd
from pandas import DataFrame

def drop_column(data: DataFrame, columns_to_delete: list) -> DataFrame:
    for column in columns_to_delete:
        data = data.drop(data.columns[[column]], axis=1)
    return data

def load_data(data_path: str) -> DataFrame:
    return pd.read_csv(data_path, sep=' ', header=None)

def load_and_drop_data(data_path: str, columns_to_delete: list) -> DataFrame:
    return drop_column(load_data(data_path), columns_to_delete)
