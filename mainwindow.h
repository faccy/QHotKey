#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString zhToJP(const QString &chinese);
    void ChineseConvertPy(QString&, QString&);


private:
    Ui::MainWindow *ui;
    QFileSystemWatcher* fileWatcher = new QFileSystemWatcher;
};
#endif // MAINWINDOW_H
