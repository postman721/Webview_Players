#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEnginePage>

namespace Ui {
class MainWindow;
}

// Custom WebEnginePage to handle fullscreen requests
class CustomWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit CustomWebEnginePage(QObject *parent = nullptr);

signals:
    void fullScreenRequested(bool fullscreen);  // Custom signal to handle fullscreen
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebEngineView *webView;      // Web view widget
    CustomWebEnginePage *page;    // Custom web engine page

    // Private helper methods
    void setupWebView();          // Sets up the web view, including JavaScript injection
    void setupWindowPosition();   // Centers the window on the screen

private slots:
    void handleFullScreenRequest(bool fullscreen);  // Handles fullscreen requests
};

#endif // MAINWINDOW_H
