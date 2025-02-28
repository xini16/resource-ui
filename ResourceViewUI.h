#ifndef RESOURCEVIEWUI_H
#define RESOURCEVIEWUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDragMoveEvent> 
#include <QDropEvent>   
#include <QMimeData>
#include <QTreeWidget>
#include <QMenu>
class Resource;
class ResourceManager;

class ResourceViewUI : public QWidget {
    Q_OBJECT

public:
    explicit ResourceViewUI(ResourceManager *resourceManager, QWidget *parent = nullptr);

signals:
    void resourceSelected(Resource* resource);
    void removeChild(Resource* resource);
    void addChild(Resource* parent, Resource* child);

private slots:
    void updateView();        
    void showContextMenu(const QPoint &pos); 
    void onResourceSelected();

private:
    void populateTree(QTreeWidgetItem *parentItem, Resource *resource); 
    Resource* getResourceFromItem(QTreeWidgetItem *item);
    Resource* findResourceInChildren(Resource *parent, const std::string &name); 
    ResourceManager *resourceManager;
    QVBoxLayout *mainLayout;
    QTreeWidget *resourceList;
    Resource* selectedResource;
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

};

#endif // RESOURCEVIEWUI_H
