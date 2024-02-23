import os
import sys

if __package__ == '':
    path = os.path.dirname(os.path.dirname(__file__))
    sys.path.insert(0, path)

if __name__ == '__main__':
    from ModelSet.CNN import cnn
    cnn('./script/data/test.txt')
