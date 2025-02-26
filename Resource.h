#ifndef RESOURCE_H
#define RESOURCE_H
#include <QString>
#include <QList>

enum ResourceType {
    TypeA,
    TypeB,
    TypeC
};

class Resource {
public:
    
    Resource(const QString &name, ResourceType type, Resource *parent = nullptr);
    QString getName() const;
    QString getTag() const;
    QList<Resource *> getChildren() const;
    Resource *getParent() const;
    ResourceType getType() const;
    bool isFolder() const;

    void setName(const QString &name);
    void setTag(const QString &tag);
    void setType(ResourceType type);
    void addChild(Resource *child);
    void removeChild(Resource *child);
    bool hasChildren() const;

private:
    QString name;
    QString tag;
    Resource *parent;
    QList<Resource *> children;
    ResourceType type;
};

#endif // RESOURCE_H
