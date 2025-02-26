#include "Resource.h"

Resource::Resource(const QString &name, const ResourceType type, Resource *parent)
    : name(name), type(type), parent(parent) {}

QString Resource::getName() const {
    return name;
}

QString Resource::getTag() const {
    return tag;
}

ResourceType Resource::getType() const {
    return type;
}

QList<Resource *> Resource::getChildren() const {
    return children;
}

Resource *Resource::getParent() const {
    return parent;
}

bool Resource::isFolder() const {
    return !children.isEmpty();
}

void Resource::setName(const QString &name) {
    this->name = name;
}

void Resource::setTag(const QString &tag) {
    this->tag = tag;
}

void Resource::setType(ResourceType newType) {
    type = newType;
}

void Resource::addChild(Resource *child) {
    if (!children.contains(child)) {
        children.append(child);
        child->parent = this;
    }
}

void Resource::removeChild(Resource *child) {
    children.removeAll(child);
}

bool Resource::hasChildren() const {
    return !children.isEmpty();
}
