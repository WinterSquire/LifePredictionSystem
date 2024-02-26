#ifndef LIFEPREDICTIONSYSTEM_KNNRESULT_H
#define LIFEPREDICTIONSYSTEM_KNNRESULT_H

#include "../../core/base.h"

namespace Model {
    namespace KNN {
        struct Result {
            vector<double> n_neighbors;
            vector<double> rmse;
            vector<double> total_score;
        };
    }
}

#endif //LIFEPREDICTIONSYSTEM_KNNRESULT_H
