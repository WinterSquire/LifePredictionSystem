@echo off
set mirror=https://your-mirror-url.com

python\python -m pip install numpy -i %mirror%
python\python -m pip install pandas -i %mirror%
python\python -m pip install scikit-learn -i %mirror%
python\python -m pip install tensorflow -i %mirror%

echo Done!
