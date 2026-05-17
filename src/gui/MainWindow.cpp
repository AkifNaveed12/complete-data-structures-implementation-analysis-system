#include "MainWindow.h"
#include "modules/ModulePanel.h"
#include "modules/ArrayView.h"
#include "modules/LinkedListView.h"
#include "modules/StackQueueView.h"
#include "modules/TreeView.h"
#include "modules/PerformanceView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QTabWidget>

// ============================================================
// Module accent colors — design.md §2.3
// ============================================================
static const struct { const char* name; const char* accent; } MODULE_DEFS[] = {
    { "Linear Structures",   "#4FC3F7" },
    { "Stack & Queue",       "#FFB74D" },
    { "Trees",               "#81C784" },
    { "Graph Algorithms",    "#E57373" },
    { "Searching & Sorting", "#CE93D8" },
    { "Hashing",             "#4DB6AC" },
    { "Performance Report",  "#FFF176" },
};
static const int NUM_MODULES = 7;

// ============================================================
// Constructor
// ============================================================
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("CDSIAS \xe2\x80\x94 Data Structure Laboratory");
    setMinimumSize(1100, 720);
    applyGlobalStyles();

    m_pages = new QStackedWidget(this);
    setCentralWidget(m_pages);

    setupSplash();      // m_pages index 0
    setupDashboard();   // m_pages index 1

    m_pages->setCurrentIndex(0);
}

MainWindow::~MainWindow() {}

// ============================================================
// SPLASH  (index 0)
// ============================================================
void MainWindow::setupSplash() {
    QWidget* splash = new QWidget();
    splash->setObjectName("splashPage");

    QVBoxLayout* vl = new QVBoxLayout(splash);
    vl->setAlignment(Qt::AlignCenter);
    vl->setSpacing(14);
    vl->addStretch(2);

    QLabel* icon = new QLabel("{  }", splash);
    icon->setObjectName("splashIcon");
    icon->setAlignment(Qt::AlignCenter);
    vl->addWidget(icon);

    QLabel* title = new QLabel("CDSIAS", splash);
    title->setObjectName("splashTitle");
    title->setAlignment(Qt::AlignCenter);
    vl->addWidget(title);

    QLabel* sub = new QLabel("Data Structure Laboratory", splash);
    sub->setObjectName("splashSubtitle");
    sub->setAlignment(Qt::AlignCenter);
    vl->addWidget(sub);

    QLabel* tag = new QLabel("Comprehensive DS Implementation & Analysis", splash);
    tag->setObjectName("splashTagline");
    tag->setAlignment(Qt::AlignCenter);
    vl->addWidget(tag);

    vl->addSpacing(36);

    QPushButton* btn = new QPushButton("\xe2\x96\xb6   Start System", splash);
    btn->setObjectName("splashStartBtn");
    btn->setFixedWidth(220);
    connect(btn, &QPushButton::clicked, this, &MainWindow::showDashboard);

    QHBoxLayout* row = new QHBoxLayout();
    row->addStretch(); row->addWidget(btn); row->addStretch();
    vl->addLayout(row);
    vl->addSpacing(10);

    QLabel* ver = new QLabel("Version 1.0.0  \xc2\xb7  Akif Naveed  \xc2\xb7  Arslan Shafiq", splash);
    ver->setObjectName("splashVersion");
    ver->setAlignment(Qt::AlignCenter);
    vl->addWidget(ver);

    vl->addStretch(3);

    m_pages->addWidget(splash);
}

// ============================================================
// DASHBOARD  (index 1)
// ============================================================
void MainWindow::setupDashboard() {
    m_dashboard = new QWidget();
    m_dashboard->setObjectName("dashboardPage");

    QVBoxLayout* vl = new QVBoxLayout(m_dashboard);
    vl->setContentsMargins(0,0,0,0);
    vl->setSpacing(0);

    // ---- Top Bar ----
    QWidget* bar = new QWidget(m_dashboard);
    bar->setObjectName("topBar");
    bar->setFixedHeight(52);
    {
        QHBoxLayout* bl = new QHBoxLayout(bar);
        bl->setContentsMargins(20,0,20,0);
        QLabel* logo = new QLabel("CDSIAS", bar);
        logo->setObjectName("topBarLogo");
        QLabel* sep  = new QLabel("\xe2\x86\x92", bar);
        sep->setStyleSheet("color:#2a2a3e; margin: 0 4px;");
        m_breadcrumb = new QLabel("Linear Structures", bar);
        m_breadcrumb->setObjectName("topBarBreadcrumb");
        QLabel* v = new QLabel("v1.0.0", bar);
        v->setObjectName("topBarVersion");
        bl->addWidget(logo);
        bl->addWidget(sep);
        bl->addWidget(m_breadcrumb);
        bl->addStretch();
        bl->addWidget(v);
    }
    vl->addWidget(bar);

    // ---- Body ----
    QWidget* body = new QWidget(m_dashboard);
    QHBoxLayout* bl = new QHBoxLayout(body);
    bl->setContentsMargins(0,0,0,0);
    bl->setSpacing(0);

    // Sidebar
    m_sidebar = new QListWidget(body);
    m_sidebar->setObjectName("mainSidebar");
    m_sidebar->setFixedWidth(220);
    static const char* ICONS[] = { "\xe2\x96\xa3", "\xe2\x8c\x9b", "\xe2\x8c\xa1", "\xe2\x97\x88", "\xe2\x89\x8b", "#", "\xe2\x9a\xa1" };
    for (int i = 0; i < NUM_MODULES; i++) {
        m_sidebar->addItem(QString("  %1  %2").arg(ICONS[i]).arg(MODULE_DEFS[i].name));
    }
    connect(m_sidebar, &QListWidget::currentRowChanged, this, &MainWindow::switchModule);
    bl->addWidget(m_sidebar);

    // Module stack
    m_moduleStack = new QStackedWidget(body);

    // M0: Linear Structures (Array + Linked List grouped in a modern QTabWidget)
    QTabWidget* linearTabs = new QTabWidget(m_moduleStack);
    linearTabs->setStyleSheet(R"(
        QTabWidget::pane { border: none; }
        QTabBar::tab { background: #1a1a2e; color: #8888aa; padding: 12px 30px; font-size: 15px; border-top-left-radius: 6px; border-top-right-radius: 6px; margin-right: 4px; }
        QTabBar::tab:selected { background: #1e1e2e; color: #4FC3F7; font-weight: bold; border-bottom: 2px solid #4FC3F7; }
        QTabBar::tab:hover:!selected { background: #252540; }
    )");
    linearTabs->addTab(new ArrayView(linearTabs), "Array");
    linearTabs->addTab(new LinkedListView(linearTabs), "Linked List");
    m_moduleStack->addWidget(linearTabs);

    // M1: Stack & Queue
    m_moduleStack->addWidget(new StackQueueView(m_moduleStack));
    // M2: Trees
    m_moduleStack->addWidget(new TreeView(m_moduleStack));

    // M3-M5: Placeholder panels
    static const char* PH[] = {
        "Graph Algorithms", "Searching & Sorting", "Hashing"
    };
    for (int i = 0; i < 3; i++) {
        QWidget* ph = new QWidget(m_moduleStack);
        ph->setStyleSheet("background:#0d0d0d;");
        QLabel* lbl = new QLabel(
            QString("<span style='font-size:22px;font-weight:bold;color:%1;'>%2</span>"
                    "<br><br><span style='color:#444466;font-size:14px;'>Module coming in next phase</span>")
                .arg(MODULE_DEFS[i+3].accent).arg(PH[i]),
            ph);
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setTextFormat(Qt::RichText);
        QVBoxLayout* pvl = new QVBoxLayout(ph);
        pvl->addWidget(lbl);
        m_moduleStack->addWidget(ph);
    }

    // M6: Performance Report
    m_moduleStack->addWidget(new PerformanceView(m_moduleStack));

    bl->addWidget(m_moduleStack, 1);
    vl->addWidget(body, 1);

    m_pages->addWidget(m_dashboard);
    m_sidebar->setCurrentRow(0);
}

// ============================================================
// Slots
// ============================================================
void MainWindow::switchModule(int index) {
    if (index >= 0 && index < m_moduleStack->count()) {
        m_moduleStack->setCurrentIndex(index);
        m_breadcrumb->setText(MODULE_DEFS[index].name);
    }
}

void MainWindow::showDashboard() {
    m_pages->setCurrentIndex(1);
}

// ============================================================
// Global QSS — design.md §2, §7
// ============================================================
void MainWindow::applyGlobalStyles() {
    setStyleSheet(R"(
        QMainWindow, QWidget { background-color: #0d0d0d; color: #e8e8f0; }

        /* Splash */
        QLabel#splashIcon {
            color: #4FC3F7; font-size: 72px;
            font-family: "Consolas"; letter-spacing: 8px;
        }
        QLabel#splashTitle {
            color: #e8e8f0; font-size: 44px; font-weight: 700;
            font-family: "Segoe UI"; letter-spacing: 8px;
        }
        QLabel#splashSubtitle {
            color: #4FC3F7; font-size: 18px; font-weight: 600;
            font-family: "Segoe UI";
        }
        QLabel#splashTagline { color: #8888aa; font-size: 13px; }
        QPushButton#splashStartBtn {
            background-color: #4FC3F7; color: #0d0d0d;
            border: none; border-radius: 10px;
            padding: 14px 28px; font-size: 15px; font-weight: 700;
            font-family: "Segoe UI";
        }
        QPushButton#splashStartBtn:hover { background-color: #81D4FA; }
        QLabel#splashVersion { color: #444466; font-size: 11px; }

        /* Top bar */
        QWidget#topBar { background-color: #141414; border-bottom: 1px solid #2a2a3e; }
        QLabel#topBarLogo {
            color: #4FC3F7; font-size: 16px; font-weight: 700;
            font-family: "Segoe UI"; letter-spacing: 3px;
        }
        QLabel#topBarBreadcrumb { color: #8888aa; font-size: 13px; }
        QLabel#topBarVersion    { color: #444466; font-size: 11px; }

        /* Sidebar */
        QListWidget#mainSidebar {
            background-color: #141414; border: none;
            border-right: 1px solid #2a2a3e; outline: none;
            font-family: "Segoe UI";
        }
        QListWidget#mainSidebar::item {
            padding: 14px 16px; font-size: 13px;
            color: #8888aa; border-bottom: 1px solid #1e1e2e;
        }
        QListWidget#mainSidebar::item:selected {
            background-color: #1e1e2e; color: #e8e8f0;
            border-left: 3px solid #4FC3F7; padding-left: 13px;
        }
        QListWidget#mainSidebar::item:hover {
            background-color: #1a1a2e; color: #e8e8f0;
        }

        /* Scrollbars */
        QScrollBar:vertical { background:#141414; width:6px; border-radius:3px; }
        QScrollBar::handle:vertical { background:#2a2a3e; border-radius:3px; }
        QScrollBar:horizontal { background:#141414; height:6px; }
        QScrollBar::handle:horizontal { background:#2a2a3e; }
        QScrollBar::add-line, QScrollBar::sub-line { width:0; height:0; }

        /* Tooltips */
        QToolTip {
            background:#1e1e2e; color:#e8e8f0;
            border:1px solid #2a2a3e; border-radius:4px;
            padding:4px 8px; font-size:12px;
        }
    )");
}
