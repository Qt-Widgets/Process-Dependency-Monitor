#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "QMessageBox"
#include "Utils/utils.h"
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Window icon (for Linux)
    setWindowIcon(QIcon(":/res/logo.svg"));

    //Fill the menu by language actions
    ui->menuLanguage->addActions(_i18n.buildActions(ui->menuLanguage));

    /*_labelStatus = new QLabel(ui->statusBar);
    ui->statusBar->addWidget(_labelStatus);
    _labelStatus->setText(tr("Process not selected"));*/

    ui->tableWidgetResult->setColumnWidth(0, 200);
    ui->tableWidgetResult->setColumnWidth(1, 450);

    ui->tableWidgetResult->setContextMenuPolicy(Qt::CustomContextMenu);

    _itemContextMenu = new QMenu(ui->tableWidgetResult);

    QAction* action;

    action = new QAction(tr("Show in Explorer"), _itemContextMenu);
    connect(action, &QAction::triggered, this, &MainWindow::on_btnShowInExplorer_clicked);
    _itemContextMenu->addAction(action);

    _itemContextMenu->addSeparator();

    action = new QAction(tr("Copy Path"), _itemContextMenu);
    connect(action, &QAction::triggered, this, &MainWindow::copyPath);
    _itemContextMenu->addAction(action);

    action = new QAction(tr("Copy Name"), _itemContextMenu);
    connect(action, &QAction::triggered, this, &MainWindow::copyName);
    _itemContextMenu->addAction(action);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAboutSoftware_triggered()
{
    QString text =
            QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion() + "\n" +
            tr("Author: %1").arg(QCoreApplication::organizationName()) + "\n" +
            QCoreApplication::organizationDomain() + "\n" +
            tr("Qt: %1 %2").arg(qVersion()).arg(QSysInfo::buildCpuArchitecture()) + "\n" +
            tr("Build Date and Time: %1 %2").arg(__DATE__).arg(__TIME__);

    QMessageBox::about(this, tr("About Software"), text);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::changeEvent(QEvent *event){
    QMainWindow::changeEvent(event);
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        ui->menuLanguage->setIcon(_i18n.currentIcon());
        qDebug("Language changed");
    }
}

void MainWindow::on_btnSelectProcess_clicked()
{
    if (!_dialogSelectProcess)
    {
        _dialogSelectProcess = new DialogSelectProcess(this);
        _dialogSelectProcess->setModal(true);
        connect(_dialogSelectProcess, &DialogSelectProcess::pidSelected, this, &MainWindow::onPidSelected);
    }

    _dialogSelectProcess->show();
}

void MainWindow::onPidSelected(int64_t pid)
{
    _pid = pid;

    ui->tableWidgetResult->clearContents();
    ui->tableWidgetResult->setRowCount(0);

    qDebug() << "Selected PID:" << pid;

    OSProcessInfo info = OSWrapper::instance().processByPID(pid);

    setWindowTitle(
                QString("%1 - [%2 (%3)]")
                .arg(QApplication::applicationName())
                .arg(info.name)
                .arg(info.id));

    for (const OSProcessDependence& dep : info.dependencies)
    {
        int row = ui->tableWidgetResult->rowCount();

        ui->tableWidgetResult->insertRow(row);


        QTableWidgetItem* itemName = new QTableWidgetItem(dep.name);
        QTableWidgetItem* itemPath = new QTableWidgetItem(dep.fileName);

        QColor textColor;

        switch (dep.specialDir) {
        case SpecialDirs::WindowsSystem32:
            textColor = QColor(0, 0, 255);
            break;
        case SpecialDirs::WindowsSysWOW64:
            textColor = QColor(128, 0, 190);
            break;
        case SpecialDirs::Windows:
            textColor = QColor(128, 64, 128);
            break;
        case SpecialDirs::None:
            break;
        }

        if (textColor.isValid())
        {
            itemName->setTextColor(textColor);
            itemPath->setTextColor(textColor);
        }

        ui->tableWidgetResult->setItem(row, 0, itemName);
        ui->tableWidgetResult->setItem(row, 1, itemPath);
    }

    ui->btnShowInExplorer->setEnabled(ui->tableWidgetResult->currentRow() != -1);
    ui->btnUpdateList->setEnabled(pid != -1);
}

void MainWindow::on_btnShowInExplorer_clicked()
{
    int row = ui->tableWidgetResult->currentRow();

    QTableWidgetItem* item = ui->tableWidgetResult->item(row, 1);

    if (item && !item->text().isEmpty())
    {
        Utils::showInGraphicalShell(item->text());
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Internal error"));
    }
}

void MainWindow::on_tableWidgetResult_currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)
{
    ui->btnShowInExplorer->setEnabled(ui->tableWidgetResult->currentRow() != -1);
}

void MainWindow::on_tableWidgetResult_itemDoubleClicked(QTableWidgetItem *)
{
    if (ui->btnShowInExplorer->isEnabled())
    {
        on_btnShowInExplorer_clicked();
    }
}

void MainWindow::on_tableWidgetResult_customContextMenuRequested(const QPoint &)
{
    if (_itemContextMenu)
    {
        _itemContextMenu->setEnabled(ui->btnShowInExplorer->isEnabled());

        _itemContextMenu->exec(QCursor::pos());
    }
}

void MainWindow::copyPath()
{
    int row = ui->tableWidgetResult->currentRow();

    QTableWidgetItem* item = ui->tableWidgetResult->item(row, 1);

    if (item && !item->text().isEmpty())
    {
        QClipboard *p_Clipboard = QApplication::clipboard();
        p_Clipboard->setText(item->text());
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Internal error"));
    }
}

void MainWindow::copyName()
{
    int row = ui->tableWidgetResult->currentRow();

    QTableWidgetItem* item = ui->tableWidgetResult->item(row, 0);

    if (item && !item->text().isEmpty())
    {
        QClipboard *p_Clipboard = QApplication::clipboard();
        p_Clipboard->setText(item->text());
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Internal error"));
    }
}

void MainWindow::on_btnUpdateList_clicked()
{
    onPidSelected(_pid);
}

