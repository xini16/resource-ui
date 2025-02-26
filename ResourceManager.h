#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Resource.h"
#include <QObject>

class ResourceManager : public QObject {
    Q_OBJECT

public:
    explicit ResourceManager(QObject *parent = nullptr);
    QList<Resource *> getRootResources() const;

public slots: 
    void addResource(Resource *parent, const QString &name, const ResourceType type);
    void deleteResource(Resource *resource);
    void renameResource(Resource *resource, const QString &newName);
    void sortResources(const QString &criteria, const QString &sortOrder);
    void createTestData();

signals:
    void resourceUpdated(); 

private:
    QList<Resource *> rootResources;
};

#endif // RESOURCEMANAGER_H
