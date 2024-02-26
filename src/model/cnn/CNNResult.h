#ifndef LIFEPREDICTIONSYSTEM_CNNRESULT_H
#define LIFEPREDICTIONSYSTEM_CNNRESULT_H

#include "../../core/base.h"

namespace Model {
    namespace CNN {
        struct Result {
            struct {
                vector<double> mse;
                vector<double> loss;
            }sel, val;
            double mean_mse;
            double total_score;
        };
    }
}

#endif //LIFEPREDICTIONSYSTEM_CNNRESULT_H
