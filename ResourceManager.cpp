#include "ResourceManager.h"
#include "iostream"

ResourceManager::ResourceManager(QObject *parent) : QObject(parent) {}

void ResourceManager::addResource(Resource *parent, const QString &name, const ResourceType type) {
    Resource *newResource = new Resource(name, type, parent);
    if (parent) {
        parent->addChild(newResource);
    } else {
        rootResources.append(newResource);
    }
    emit resourceUpdated();
}

void ResourceManager::deleteResource(Resource *resource) {
    if (resource->getParent()) {
        resource->getParent()->removeChild(resource);
    } else {
        rootResources.removeAll(resource);
    }
    delete resource;
    emit resourceUpdated();
}

void ResourceManager::renameResource(Resource *resource, const QString &newName) {
    if (resource) {
        resource->setName(newName);
        emit resourceUpdated();
    }
}

void ResourceManager::sortResources(const QString &criteria, const QString &sortOrder) {
    std::cout << "[TestReceiver::sortResources] Received criteria = "
    << criteria.toStdString()
    << ", order = "
    << sortOrder.toStdString()
    << std::endl;    
    emit resourceUpdated();
}

QList<Resource *> ResourceManager::getRootResources() const {
    return rootResources;
}

void ResourceManager::createTestData() {
    Resource *folder1 = new Resource("Folder A", TypeA);
    Resource *folder2 = new Resource("Folder B", TypeB);

    Resource *file1 = new Resource("File A1", TypeA, folder1);
    Resource *file2 = new Resource("File B1", TypeB, folder2);

    folder1->addChild(file1);
    folder2->addChild(file2);

    rootResources.append(folder1);
    rootResources.append(folder2);

    emit resourceUpdated();
}
