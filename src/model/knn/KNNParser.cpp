#include "KNNParser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

static vector<double> getVector(const QJsonObject& json, const char* key) {
    vector<double> result;
    auto array = json[key].toArray();

    for (auto item: array) {
        result.push_back(item.toDouble());
    }

    return result;
}

Model::KNN::Result Model::KNN::Parse(const char *str) {
    QString jsonStr(str);

    auto jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());

    // 检查是否解析成功
    if (jsonDocument.isNull()) {
        LOG("Failed to parse JSON data.");
        return {};
    }

    auto jsonObject = jsonDocument.object();

    return {
        getVector(jsonObject, "n"),
        getVector(jsonObject, "rmse"),
        getVector(jsonObject, "total_score")
    };
}
