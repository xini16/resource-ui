#ifndef RESOURCEVIEWUI_H
#define RESOURCEVIEWUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QMenu>
#include "ResourceManager.h"

class ResourceViewUI : public QWidget {
    Q_OBJECT

public:
    explicit ResourceViewUI(ResourceManager *resourceManager, QWidget *parent = nullptr);

signals:
    void resourceSelected(Resource* resource);

private slots:
    void updateView();         // 更新 UI，递归填充资源
    void showContextMenu(const QPoint &pos); // 右键菜单
    void onResourceSelected();

private:
    void populateTree(QTreeWidgetItem *parentItem, Resource *resource); // 递归填充子资源
    Resource* getResourceFromItem(QTreeWidgetItem *item); // 获取 QTreeWidgetItem 对应的 Resource
    Resource* findResourceInChildren(Resource *parent, const QString &name); // 递归查找子资源
    ResourceManager *resourceManager;
    QVBoxLayout *mainLayout;
    QTreeWidget *resourceList;
    Resource* selectedResource;
};

#endif // RESOURCEVIEWUI_H
