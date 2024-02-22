#ifndef LIFEPREDICTIONSYSTEM_MODELRESULT_H
#define LIFEPREDICTIONSYSTEM_MODELRESULT_H

#include "../core/base.h"

namespace Model {
    struct Result {
        struct {
            vector<double> mse;
            vector<double> loss;
        }sel, val;
        double mean_mse;
        double total_score;
    };
}

#endif //LIFEPREDICTIONSYSTEM_MODELRESULT_H
