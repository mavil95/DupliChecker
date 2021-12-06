#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pMessage = new QMessageBox(this);
    m_pMessage->setDefaultButton(QMessageBox::Ok);
    m_pFirstEqualNames = new vector<QString>;
    m_pSecondEqualNames = new vector<QString>;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pFirstEqualNames;
    delete m_pSecondEqualNames;
}

void MainWindow::on_ProcessButton_clicked()
{
    /// This function compare all files from two scpecified directories and show all equal files

    // clearing last result and create new directories from input lines
    m_pFirstEqualNames->clear();
    m_pSecondEqualNames->clear();
    QDir firstDir(ui->FirstFolderLine->displayText());
    QDir secondDir(ui->SecondFolderLine->displayText());

    // Checking that both directories exists
    if (firstDir.exists())
        qDebug() << "First directory path" << firstDir.absolutePath();
    else
    {
        showDirectoryDoesntExistMessage("First");
        return;
    }
    if (secondDir.exists())
        qDebug() << "Second directory path" << secondDir.absolutePath();
    else
    {
        showDirectoryDoesntExistMessage("Second");
        return;
    }

    // Creating file list from both directories, compare all files that has same size and then fill result vector
    QFileInfoList firstList(getFileList(&firstDir));
    QFileInfoList secondList(getFileList(&secondDir));
    for (int i = 0; i < firstList.size(); i++)
    {
        for (int j = 0; j < secondList.size(); j++)
        {
            if (firstList.at(i).size() == secondList.at(j).size())
            {
                m_fFirstFile.setFileName(firstList.at(i).absoluteFilePath());
                m_fSecondFile.setFileName(secondList.at(j).absoluteFilePath());
                if (isFilesEqual(&m_fFirstFile, &m_fSecondFile))
                {
                    m_pFirstEqualNames->push_back(m_fFirstFile.fileName());
                    m_pSecondEqualNames->push_back(m_fSecondFile.fileName());
                }
            }
        }
    }

    // Show result message
    if (m_pFirstEqualNames->empty())
    {
        m_pMessage->setText("There is no equal files");
        m_pMessage->show();
    }
    else
    {
        QString resultString;
        int i = 0;
        for (auto it = m_pFirstEqualNames->begin(); it != m_pFirstEqualNames->end(); it++)
        {
            resultString += "\"" + m_pFirstEqualNames->at(i) + "\" equal \"" + m_pSecondEqualNames->at(i) + "\"\n";
            i++;
        }
        m_pMessage->setText(resultString);
        m_pMessage->show();
        qDebug() << "Process comlete";
    }

}

void MainWindow::showDirectoryDoesntExistMessage(const QString dir)
{
    /// This function shows warning
    QString tempStr(dir + " directory doesn't exist.");
    m_pMessage->setText(tempStr);
    m_pMessage->show();
}

QFileInfoList MainWindow::getFileList(QDir *dir)
{
    /// This function returns file list from directory
    dir->setFilter(QDir::Files | QDir::Readable | QDir::NoSymLinks);
    dir->setSorting(QDir::Unsorted);
    QFileInfoList list = dir->entryInfoList();
    return list;
}

bool MainWindow::isFilesEqual(QFile *first, QFile *second)
{
    /// This function check equality of two files and return true if its both equal, otherwise return false
    /// Comparing of files less than 100kB is byte - by - byte
    /// Comparing other files is string - by - string
    /// Both files in this function are ALWAYS has same size

    qDebug() << "Checking equality of files";

    // Try to open both files
    if (!first->isOpen())
        first->open(QIODevice::ReadOnly);
    if (!second->isOpen())
        second->open(QIODevice::ReadOnly);

    if (!first->isOpen() || !second->isOpen())
    {
        qDebug() << "Cant open one of files";
        return false;
    }

    // setting read type for file
    // readLine function read symbols if 1, and read strings if 0
    int typeofRead = 1;
    if (first->size() > 102400)
        typeofRead = 0;

    // Comparing files through text stream
    QTextStream in1(first), in2(second);
    while (!in1.atEnd() && !in2.atEnd())
    {
        QString tempStr1 = in1.readLine(typeofRead);
        QString tempStr2 = in2.readLine(typeofRead);
        if (tempStr1 != tempStr2)
        {
            first->close();
            second->close();
            return false;
        }
    }

    first->close();
    second->close();
    return true;
}
