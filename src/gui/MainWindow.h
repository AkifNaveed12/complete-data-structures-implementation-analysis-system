#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QPropertyAnimation>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchModule(int index);
    void showDashboard();

private:
    void setupTopBar();
    void setupSidebar();
    void setupModules();
    void setupDashboard();
    void applyGlobalStyles();
    void setupSplash();

    // Top-level pages
    QStackedWidget* m_pages;     // 0 = splash, 1 = dashboard

    // Dashboard components
    QWidget*        m_dashboard;
    QListWidget*    m_sidebar;
    QStackedWidget* m_moduleStack;

    // Top bar
    QLabel*         m_breadcrumb;
};

#endif
