@echo off
set mirror=https://pypi.tuna.tsinghua.edu.cn/simple
set packages=numpy pandas scikit-learn tensorflow

python\python -m pip install %packages% -i %mirror%

echo Done!
