import os
import sys

if __package__ == '':
    path = os.path.dirname(os.path.dirname(__file__))
    sys.path.insert(0, path)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit(0)

    model = sys.argv[1]
    test_data_path = os.path.abspath(sys.argv[2])

    print(f'model: {model}')
    print(f'test_data_path(abs): {test_data_path}')

    if model == 'cnn':
        from ModelSet.CNN import cnn
        cnn(test_data_path)
    elif model == 'knn':
        from ModelSet.KNN import knn
        knn(test_data_path)
    else:
        print(f'Unknown Model Type: {model}')

    sys.exit(0)