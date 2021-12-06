#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ProcessButton_clicked();

private:
    void showDirectoryDoesntExistMessage(const QString dir);
    QFileInfoList getFileList(QDir *dir);
    bool isFilesEqual(QFile *first, QFile *second);

    Ui::MainWindow *ui;

    QMessageBox *m_pMessage;
    vector<QString> *m_pFirstEqualNames, *m_pSecondEqualNames;
    QFile m_fFirstFile, m_fSecondFile;
};
#endif // MAINWINDOW_H
