#include "CNNParser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

vector<double> getVector(const QJsonObject& json, const char* key) {
    vector<double> result;
    auto array = json[key].toArray();

    for (auto item: array) {
        result.push_back(item.toDouble());
    }

    return result;
}

Model::Result Model::CNN::Parse(const char* str) {
    QString jsonStr(str);

    auto jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());

    // 检查是否解析成功
    if (jsonDocument.isNull()) {
        LOG("Failed to parse JSON data.");
        return Model::Result{};
    }

    // 获取 JSON 对象
    auto jsonObject = jsonDocument.object();

    return Model::Result{
            {
                    getVector(jsonObject, "mse"),
                    getVector(jsonObject, "loss"),
            },{
                    getVector(jsonObject, "val_mse"),
                    getVector(jsonObject, "val_loss"),
            },
            jsonObject["mean_mse"].toDouble(),
            jsonObject["total_score"].toDouble()
    };
}