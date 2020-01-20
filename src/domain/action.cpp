#include "action.h"
#include <utility>

Action::Action(int id) : id(id) {}

int Action::getId() {
    return id;
}

QString Action::getCode() {
    return code;
}

void Action::setCode(QString _code) {
    code = std::move(_code);
}

QString Action::getUrl() {
    return url;
}

void Action::setUrl(QString _url) {
    url = std::move(_url);
}

QString Action::getDescription() {
    return description;
}

void Action::setDescription(QString desc) {
    description = std::move(desc);
}
