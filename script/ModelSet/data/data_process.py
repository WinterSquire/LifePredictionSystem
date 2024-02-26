import pandas as pd
from pandas import DataFrame

def reindex_column(data: DataFrame) -> DataFrame:
    data.columns = [str(i) for i in range(len(data.columns))]
    return data

def drop_column(data: DataFrame, columns_to_delete: list) -> DataFrame:
    for column in columns_to_delete:
        data = data.drop(data.columns[[column]], axis=1)
    return data

def load_data(data_path: str, sep = None, header = "infer") -> DataFrame:
    return pd.read_csv(data_path, sep=sep, header=header)
