#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineFullScreenRequest>
#include <QWebEngineSettings>
#include <QDebug>
#include <QScreen>
#include <QWebEngineProfile>

// Implement the custom web engine page
CustomWebEnginePage::CustomWebEnginePage(QObject *parent)
    : QWebEnginePage(parent)
{
    // Handle fullscreen requests
    connect(this, &QWebEnginePage::fullScreenRequested, this, [this](QWebEngineFullScreenRequest request) {
        request.accept();  // Accept the fullscreen request
        emit fullScreenRequested(request.toggleOn());
    });
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    webView(new QWebEngineView(this)),
    page(new CustomWebEnginePage(this))
{
    ui->setupUi(this);

    // Set the User-Agent to mimic the latest Chrome browser
    QString chromeUserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.5938.92 Safari/537.36";
    webView->page()->profile()->setHttpUserAgent(chromeUserAgent);

    setupWebView();
    setupWindowPosition();

    // Connect fullscreen requests to handler
    connect(page, &CustomWebEnginePage::fullScreenRequested, this, &MainWindow::handleFullScreenRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWebView()
{
    // Set the custom web page
    webView->setPage(page);
    setCentralWidget(webView);

    // Enable fullscreen support
    webView->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    // Load the desired webpage
    webView->load(QUrl("https://areena.yle.fi/tv"));


}

void MainWindow::setupWindowPosition()
{
    // Center the window on the screen
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        const QRect screenGeometry = screen->geometry();
        const int x = (screenGeometry.width() - this->width()) / 2;
        const int y = (screenGeometry.height() - this->height()) / 2;
        this->move(x, y);
    } else {
        qWarning() << "No primary screen available.";
    }
}

void MainWindow::handleFullScreenRequest(bool fullscreen)
{
    if (fullscreen) {
        showFullScreen();  // Enter fullscreen mode
    } else {
        showNormal();      // Exit fullscreen mode
    }
}
