#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QFileDialog>

#include "MeshEncoded.hpp"
#include "Log.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_browseFileBtn_clicked()
{
  static auto opennedPath(QCoreApplication::applicationDirPath());
  opennedPath = QFileDialog::getOpenFileName(
        this, "Open File", opennedPath, "Mesh file (*.mesh)"
        );
  if (opennedPath.isEmpty())
  {
    return;
  }

  auto meshDecodedFile = new MeshEncoded(opennedPath);
  LOG(opennedPath);
  if (!meshDecodedFile->open(QIODevice::ReadOnly))
  {
    delete meshDecodedFile;
    return;
  }
  delete meshDecodedFile;
}

void MainWindow::on_browseDirBtn_clicked()
{
  static auto opennedPath(QCoreApplication::applicationDirPath());
  opennedPath = QFileDialog::getExistingDirectory(
        nullptr, "Choose Extract Directory", opennedPath
        );

  if (opennedPath.isEmpty())
  {
    return;
  }

  QStringList meshDecodedFileNames = QDir(opennedPath).entryList({
                                                                   "*.mesh",
                                                                   "*.MESH",
                                                                   "**\\*.mesh",
                                                                   "**\\*.MESH"
                                                                 }, QDir::Files
                                                                 );
  for (const auto& _file : meshDecodedFileNames)
  {
    const auto& _filePath = opennedPath + '/' + _file;
//    LOG_DEBUG(_filePath);
    MeshEncoded meshFile(_filePath);

    if (!meshFile.open(QIODevice::ReadOnly))
    {
      continue;
    }
  }
}
