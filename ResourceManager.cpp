#include "ResourceManager.h"
#include "iostream"

ResourceManager::ResourceManager(QObject *parent) : QObject(parent) {}

void ResourceManager::addResource(Resource *parent, const std::string &name, const ResourceType type) {
    Resource *newResource = new Resource(name, type, parent);
    if (parent) {
        parent->addChild(newResource);
    } else {
        rootResources.push_back(newResource);
    }
    emit resourceUpdated();
}

void ResourceManager::deleteResource(Resource *resource) {
    if (resource->getParent()) {
        resource->getParent()->removeChild(resource);
    } else {
        auto it = std::find(rootResources.begin(), rootResources.end(), resource);
        if (it != rootResources.end()) {
            rootResources.erase(it);
        }
    }
    delete resource;
    emit resourceUpdated();
}

void ResourceManager::renameResource(Resource *resource, const std::string &newName) {
    if (resource) {
        resource->setName(newName);
        emit resourceUpdated();
    }
}

void ResourceManager::sortResources(const std::string &criteria, const sortOrder &order) {
    // std::cout << "[TestReceiver::sortResources] Received criteria = "
    // << criteria()
    // << ", order = "
    // << sortOrder()
    // << std::endl;    
    emit resourceUpdated();
}

void ResourceManager::removeChild(Resource *child) {
    for (auto *parent : rootResources) {
        if (parent->hasChildren() && std::find(parent->getChildren().begin(), parent->getChildren().end(), child) != parent->getChildren().end()) {
            parent->removeChild(child);
            break;
        }
    }
    emit resourceUpdated();
}

void ResourceManager::addChild(Resource *parent, Resource *child) {
    if (parent && child) {
        parent->addChild(child);
    }
    emit resourceUpdated();
}

std::vector<Resource *> ResourceManager::getRootResources() const {
    return rootResources;
}

void ResourceManager::createTestData() {
    Resource *folder1 = new Resource("Folder A", TypeA);
    Resource *folder2 = new Resource("Folder B", TypeB);

    Resource *file1 = new Resource("File A1", TypeA, folder1);
    Resource *file2 = new Resource("File B1", TypeB, folder2);

    folder1->addChild(file1);
    folder2->addChild(file2);

    rootResources.push_back(folder1);
    rootResources.push_back(folder2);

    emit resourceUpdated();
}
