#ifndef MENUBARUI_H
#define MENUBARUI_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMenu>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include "Resource.h"

class MenuBarUI : public QWidget {
    Q_OBJECT

public:
    explicit MenuBarUI(QWidget *parent = nullptr);
    Resource* selectedResource;

signals:
    void addResource(Resource *parent, const QString &name, const ResourceType type);
    void renameResource(Resource *resource, const QString &newName);
    void sortResources(const QString &criteria, const QString &sortOrder);
    void deleteResource(Resource *resource);

public slots:
    void onDeleteResource();
    void onRenameResource();

private:
    QToolButton *addButton;
    QToolButton *sortButton;
    QString criteria;
    QString sortOrder;
    void sortbuttonClicked();
    QPushButton *renameButton;
    QPushButton *deleteButton;
    QMenu *addMenu;

};

#endif // MENUBARUI_H
