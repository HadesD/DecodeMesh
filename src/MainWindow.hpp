#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QThread>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_browseFileBtn_clicked();

    void on_browseDirBtn_clicked();

  private:
    Ui::MainWindow *ui;
    QThread m_loadDirThread;
};

#endif // MAINWINDOW_HPP
