#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "open the file");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){

        QMessageBox::warning(this,"warning", "Can NOT open File" + file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionnew_triggered()
{
    // clear screen
        currentFile.clear();
        //create new text window
        ui->textEdit->setText(QString());
}

void MainWindow::on_actionSave_triggered()
{
    //save
    QString filename = QFileDialog::getSaveFileName(this, "Save the file");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){

        QMessageBox::warning(this,"warning", "Can NOT Save File" + file.errorString());
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);

    //copy text in textedit widget convert to plain text
    QString text = ui-> textEdit -> toPlainText();

    //write to file then close file
    out << text;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui ->textEdit-> copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui ->textEdit-> paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui -> textEdit -> undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui -> textEdit -> redo();
}
