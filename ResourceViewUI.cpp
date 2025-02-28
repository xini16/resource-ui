#include "ResourceViewUI.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "ResourceManager.h"

ResourceViewUI::ResourceViewUI(ResourceManager *resourceManager, QWidget *parent) 
    : QWidget(parent), resourceManager(resourceManager) {
    mainLayout = new QVBoxLayout(this);

    resourceList = new QTreeWidget(this);
    resourceList->setHeaderHidden(true);
    resourceList->setSelectionMode(QAbstractItemView::SingleSelection);
    resourceList->setContextMenuPolicy(Qt::CustomContextMenu);
    resourceList->setDragEnabled(true);      
    resourceList->setAcceptDrops(true);    
    resourceList->setDropIndicatorShown(true); 
    resourceList->setSelectionMode(QAbstractItemView::SingleSelection);
    resourceList->setDefaultDropAction(Qt::MoveAction);
    resourceList->viewport()->setAcceptDrops(true);
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
        QTreeWidgetItem *insertBeforeItem = new QTreeWidgetItem(resourceList);
        insertBeforeItem->setFlags(insertBeforeItem->flags() & ~Qt::ItemIsSelectable); 
        insertBeforeItem->setSizeHint(0, QSize(0, 2)); 
        insertBeforeItem->setBackground(0, QBrush(Qt::gray));
        QTreeWidgetItem *item = new QTreeWidgetItem(resourceList);
        item->setText(0, QString::fromStdString(resource->getName()));

        populateTree(item, resource); 
    }
}

void ResourceViewUI::populateTree(QTreeWidgetItem *parentItem, Resource *resource) {
    for (auto *child : resource->getChildren()) {
        QTreeWidgetItem *insertBeforeItem = new QTreeWidgetItem(parentItem);
        insertBeforeItem->setFlags(insertBeforeItem->flags() & ~Qt::ItemIsSelectable);
        insertBeforeItem->setSizeHint(0, QSize(0, 2));
        insertBeforeItem->setBackground(0, QBrush(Qt::gray));
        QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
        childItem->setText(0, QString::fromStdString(child->getName()));
        parentItem->addChild(insertBeforeItem);
        parentItem->addChild(childItem); 

        populateTree(childItem, child); 
    }
}


void ResourceViewUI::onResourceSelected() {
    if (resourceList->currentItem()) {
        Resource *selectedResource = getResourceFromItem(resourceList->currentItem());
        if (selectedResource) {
            emit resourceSelected(selectedResource); 
        }
    }
}

void ResourceViewUI::dragMoveEvent(QDragMoveEvent *event) {
    QTreeWidgetItem *itemUnderCursor = resourceList->itemAt(event->position().toPoint());

    if (itemUnderCursor) {
        if (itemUnderCursor->text(0).isEmpty()) {
            itemUnderCursor->setBackground(0, Qt::yellow); 
        } else {
            for (int i = 0; i < resourceList->topLevelItemCount(); i++) {
                QTreeWidgetItem *item = resourceList->topLevelItem(i);
                if (item->text(0).isEmpty()) {
                    item->setBackground(0, Qt::transparent);
                }
            }
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}


void ResourceViewUI::dropEvent(QDropEvent *event) {
    QTreeWidgetItem *itemUnderCursor = resourceList->itemAt(event->position().toPoint());
    if (itemUnderCursor && itemUnderCursor->text(0).isEmpty()) {
        Resource *targetResource = getResourceFromItem(itemUnderCursor);
        if (targetResource) {
            Resource *draggedResource = getResourceFromItem(resourceList->currentItem());
            if (draggedResource) {
                emit removeChild(draggedResource);
                emit addChild(targetResource, draggedResource);
            }
        }
        itemUnderCursor->setBackground(0, Qt::transparent);
    }
    for (int i = 0; i < resourceList->topLevelItemCount(); i++) {
        QTreeWidgetItem *item = resourceList->topLevelItem(i);
        if (item->text(0).isEmpty()) {
            item->setBackground(0, Qt::transparent);
        }
    }
}

Resource* ResourceViewUI::getResourceFromItem(QTreeWidgetItem *item) {
    if (!item) return nullptr;

    for (auto *resource : resourceManager->getRootResources()) {
        if (resource->getName() == item->text(0).toStdString()) {
            return resource;
        }
        Resource *childResource = findResourceInChildren(resource, item->text(0).toStdString());
        if (childResource) {
            return childResource;
        }
    }
    return nullptr;
}

Resource* ResourceViewUI::findResourceInChildren(Resource *parent, const std::string &name) {
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

