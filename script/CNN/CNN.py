import sys
import os

# 获取脚本文件的路径
script_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(script_dir)
data_folder = os.path.abspath(os.path.join(script_dir, '../data'))

# 处理数据
import data_process
import model_process

column_to_delete = [26,4,4,7,11,16,17,17,0,0, 0,0,3]

test_data = data_process.load_data(data_folder + '/test.txt', column_to_delete)
train_data = data_process.load_data(data_folder + '/train.txt', column_to_delete)

result = model_process.process(train_data, test_data)

print(result)