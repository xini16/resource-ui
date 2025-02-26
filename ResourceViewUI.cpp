#include "ResourceViewUI.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QCursor>

ResourceViewUI::ResourceViewUI(ResourceManager *resourceManager, QWidget *parent) 
    : QWidget(parent), resourceManager(resourceManager) {
    mainLayout = new QVBoxLayout(this);

    resourceList = new QTreeWidget(this);
    resourceList->setHeaderHidden(true);
    resourceList->setSelectionMode(QAbstractItemView::SingleSelection);
    resourceList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(resourceList, &QTreeWidget::customContextMenuRequested, this, &ResourceViewUI::showContextMenu);

    mainLayout->addWidget(resourceList);
    setLayout(mainLayout);
    connect(resourceList, &QTreeWidget::itemClicked, this, &ResourceViewUI::onResourceSelected);
    connect(resourceManager, &ResourceManager::resourceUpdated, this, &ResourceViewUI::updateView);
    updateView();
}

void ResourceViewUI::updateView() {
    resourceList->clear();

    for (auto *resource : resourceManager->getRootResources()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(resourceList);
        item->setText(0, resource->getName());

        populateTree(item, resource); 
    }
}

void ResourceViewUI::populateTree(QTreeWidgetItem *parentItem, Resource *resource) {
    for (auto *child : resource->getChildren()) {
        QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
        childItem->setText(0, child->getName());

        parentItem->addChild(childItem); 

        populateTree(childItem, child); 
    }
}


void ResourceViewUI::onResourceSelected() {
    if (resourceList->currentItem()) {
        Resource *selectedResource = getResourceFromItem(resourceList->currentItem());
        if (selectedResource) {
            emit resourceSelected(selectedResource); // 发出选中资源的信号
        }
    }
}

Resource* ResourceViewUI::getResourceFromItem(QTreeWidgetItem *item) {
    if (!item) return nullptr;

    for (auto *resource : resourceManager->getRootResources()) {
        if (resource->getName() == item->text(0)) {
            return resource;
        }
        Resource *childResource = findResourceInChildren(resource, item->text(0));
        if (childResource) {
            return childResource;
        }
    }
    return nullptr;
}

Resource* ResourceViewUI::findResourceInChildren(Resource *parent, const QString &name) {
    for (auto *child : parent->getChildren()) {
        if (child->getName() == name) {
            return child;
        }
        Resource *result = findResourceInChildren(child, name);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

void ResourceViewUI::showContextMenu(const QPoint &pos) {
    QTreeWidgetItem *selectedItem = resourceList->itemAt(pos);
    if (!selectedItem) return;

    QMenu contextMenu;
    
// wait for further enhancements

    contextMenu.exec(resourceList->mapToGlobal(pos));
}

