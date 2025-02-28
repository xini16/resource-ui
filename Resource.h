#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <vector>
#include <utensil.h>

class Resource {
public:
    
    Resource(const std::string &name, ResourceType type, Resource *parent = nullptr);
    ~Resource();
    std::string getName() const;
    std::string getTag() const;
    std::vector<Resource *> getChildren() const;
    Resource *getParent() const;
    ResourceType getType() const;
    bool isFolder() const;

    void setName(const std::string &name);
    void setTag(const std::string &tag);
    void setType(ResourceType type);
    void addChild(Resource *child);
    void removeChild(Resource *child);
    bool hasChildren() const;

private:
    std::string name;
    std::string tag;
    Resource *parent;
    std::vector<Resource *> children;
    ResourceType type;
};

#endif // RESOURCE_H
