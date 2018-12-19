#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QDirIterator>
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

  connect(&m_loadDirThread, &QThread::started, [=](){
    QDirIterator dirIt(
          opennedPath, {"*.mesh", "*.MESH"},
          QDir::Files, QDirIterator::Subdirectories
          );

    while (dirIt.hasNext())
    {
      auto _file = dirIt.next();
      const auto& _filePath = _file;
      MeshEncoded meshFile(_filePath);

      if (!meshFile.open(QIODevice::ReadOnly))
      {
        continue;
      }
    }
    LOG_DEBUG("Loaded Dir");
    m_loadDirThread.quit();
  });
  if (m_loadDirThread.isRunning())
  {
    m_loadDirThread.quit();
  }
  m_loadDirThread.start();
}
