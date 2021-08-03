#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"
#include "diagramview.h"
#include "diagramitem.h"

#include <QMainWindow>

class QGraphicsView;

class QButtonGroup;
class QAbstractButton;
class QToolBox;
class QToolButton;
class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void buttonGroupClicked(QAbstractButton* button);
    void onSaveAsJson();
    void onOpenDiagram();

private:
    void createSideMenu();
    void createActions();
    void createMenus();
    QToolButton* createSideMenuDiagramButton(const QString& text,
                                             DiagramItem::DiagramType type);
    QToolButton* createSideMenuButton(const QString& text,
                                      const QPixmap& pixmap);

private:
    DiagramScene* scene_;
    DiagramView*  view_;

    QButtonGroup* buttonGroup_;
    QToolButton*  saveJsonButton_;
    QToolButton*  loadFromJsonButton_;
    QFrame*       sideMenu_;

    QAction* deleteAction_;
    QAction* selectAllAction_;
    QAction* copyAction_;
    QAction* pasteAction_;

    QAction* saveAsJsonAction_;
    QAction* openDiagramAction_;

    QMenu* itemMenu_;
    QMenu* fileMenu_;
};

#endif // MAINWINDOW_H
