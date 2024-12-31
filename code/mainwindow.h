#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "packagemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNavigateToAddPackageTab();
    void onAddPackageClicked();
    void onClearTable();
    void onRemoveSelectedPackages();
    void onSignOutSelectedPackages();

private:
    Ui::MainWindow *ui;

    bool showConfirmationDialog(const QString title, const QString message);
};

#endif // MAINWINDOW_H

