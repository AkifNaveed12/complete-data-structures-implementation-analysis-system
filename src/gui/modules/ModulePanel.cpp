#include "ModulePanel.h"
#include <QFrame>
#include <QScrollArea>

ModulePanel::ModulePanel(const QString& title, const QString& accentColor, QWidget* parent)
    : QWidget(parent), m_accent(accentColor)
{
    setObjectName("modulePanel");

    QHBoxLayout* outerLayout = new QHBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    // ============================================================
    // LEFT SIDEBAR — operations + input + run/reset
    // ============================================================
    QWidget* sidebar = new QWidget(this);
    sidebar->setObjectName("moduleSidebar");
    sidebar->setFixedWidth(220);

    QVBoxLayout* sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(12, 16, 12, 16);
    sideLayout->setSpacing(10);

    m_titleLabel = new QLabel(title, this);
    m_titleLabel->setObjectName("sidebarTitle");

    m_opList = new QListWidget(this);
    m_opList->setObjectName("opList");
    m_opList->setFrameShape(QFrame::NoFrame);

    m_input1Label = new QLabel("Value:", this);
    m_input1Label->setObjectName("inputLabel");
    m_input1 = new QLineEdit(this);
    m_input1->setObjectName("inputField");
    m_input1->setPlaceholderText("Enter value...");

    m_input2Label = new QLabel("Index:", this);
    m_input2Label->setObjectName("inputLabel");
    m_input2 = new QLineEdit(this);
    m_input2->setObjectName("inputField");
    m_input2->setPlaceholderText("Enter index...");
    m_input2->hide();
    m_input2Label->hide();

    m_runBtn = new QPushButton("▶  Run", this);
    m_runBtn->setObjectName("runBtn");

    m_resetBtn = new QPushButton("↺  Reset", this);
    m_resetBtn->setObjectName("resetBtn");

    m_statusLabel = new QLabel("", this);
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setWordWrap(true);

    sideLayout->addWidget(m_titleLabel);
    sideLayout->addWidget(m_opList);
    sideLayout->addWidget(m_input1Label);
    sideLayout->addWidget(m_input1);
    sideLayout->addWidget(m_input2Label);
    sideLayout->addWidget(m_input2);
    sideLayout->addWidget(m_runBtn);
    sideLayout->addWidget(m_resetBtn);
    sideLayout->addWidget(m_statusLabel);
    sideLayout->addStretch();

    // ============================================================
    // CENTER — canvas area
    // ============================================================
    QWidget* centerWrapper = new QWidget(this);
    centerWrapper->setObjectName("canvasWrapper");
    QVBoxLayout* centerLayout = new QVBoxLayout(centerWrapper);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(0);

    m_canvas = new QWidget(centerWrapper);
    m_canvas->setObjectName("vizCanvas");
    m_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    centerLayout->addWidget(m_canvas);

    // ============================================================
    // RIGHT — step log
    // ============================================================
    QWidget* logPanel = new QWidget(this);
    logPanel->setObjectName("logPanel");
    logPanel->setFixedWidth(280);

    QVBoxLayout* logLayout = new QVBoxLayout(logPanel);
    logLayout->setContentsMargins(12, 16, 12, 16);
    logLayout->setSpacing(8);

    QLabel* logTitle = new QLabel("Operation Log", this);
    logTitle->setObjectName("logTitle");

    m_stepLog = new QTextEdit(this);
    m_stepLog->setObjectName("stepLog");
    m_stepLog->setReadOnly(true);
    m_stepLog->setFrameShape(QFrame::NoFrame);

    logLayout->addWidget(logTitle);
    logLayout->addWidget(m_stepLog);

    outerLayout->addWidget(sidebar);
    outerLayout->addWidget(centerWrapper, 1);
    outerLayout->addWidget(logPanel);

    connect(m_runBtn,   &QPushButton::clicked, this, &ModulePanel::runRequested);
    connect(m_resetBtn, &QPushButton::clicked, this, &ModulePanel::resetRequested);

    // Dynamic accent styling
    setStyleSheet(QString(R"(
        QWidget#moduleSidebar {
            background-color: #141414;
            border-right: 1px solid #2a2a3e;
        }
        QLabel#sidebarTitle {
            color: %1;
            font-size: 16px;
            font-weight: bold;
            padding-bottom: 6px;
        }
        QListWidget#opList {
            background-color: #1a1a2e;
            border: 1px solid #2a2a3e;
            border-radius: 8px;
            color: #e8e8f0;
            font-size: 13px;
        }
        QListWidget#opList::item { padding: 9px; }
        QListWidget#opList::item:selected {
            background-color: #252540;
            color: %1;
            border-left: 3px solid %1;
        }
        QListWidget#opList::item:hover { background-color: #1e1e2e; }
        QLabel#inputLabel {
            color: #8888aa;
            font-size: 12px;
        }
        QLineEdit#inputField {
            background-color: #1e1e2e;
            color: #e8e8f0;
            border: 1px solid #2a2a3e;
            border-radius: 8px;
            padding: 8px 12px;
            font-size: 14px;
        }
        QLineEdit#inputField:focus { border: 1px solid %1; }
        QPushButton#runBtn {
            background-color: %1;
            color: #0d0d0d;
            border: none;
            border-radius: 8px;
            padding: 10px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton#runBtn:hover { background-color: %1; opacity: 0.85; }
        QPushButton#resetBtn {
            background-color: transparent;
            color: #e8e8f0;
            border: 1px solid #2a2a3e;
            border-radius: 8px;
            padding: 10px;
            font-size: 13px;
        }
        QPushButton#resetBtn:hover { background-color: #1e1e2e; }
        QLabel#statusLabel { color: #8888aa; font-size: 12px; }
        QWidget#canvasWrapper { background-color: #0d0d0d; }
        QWidget#vizCanvas { background-color: #0d0d0d; }
        QWidget#logPanel {
            background-color: #141414;
            border-left: 1px solid #2a2a3e;
        }
        QLabel#logTitle {
            color: #8888aa;
            font-size: 13px;
            font-weight: bold;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        QTextEdit#stepLog {
            background-color: #141414;
            color: #e8e8f0;
            font-family: "Consolas", monospace;
            font-size: 12px;
            border: none;
        }
    )").arg(accentColor));
}

void ModulePanel::logStep(int n, const QString& msg) {
    m_stepLog->append(QString("<span style='color:#8888aa;'>Step %1:</span> %2").arg(n).arg(msg.toHtmlEscaped()));
}

void ModulePanel::logResult(const QString& msg) {
    QString formattedMsg = msg.toHtmlEscaped();
    if (formattedMsg.contains("\nOperation Count:")) {
        formattedMsg.replace("\nOperation Count:", "</span><br><span style='color:#FFB74D; font-weight:bold;'>Operation Count:");
    }
    m_stepLog->append(QString("<span style='color:#69F0AE; font-weight:bold;'>✔ Result: %1</span>").arg(formattedMsg));
    m_stepLog->append("");
}

void ModulePanel::logError(const QString& msg) {
    m_stepLog->append(QString("<span style='color:#FF5370; font-weight:bold;'>✘ Error: %1</span>").arg(msg.toHtmlEscaped()));
    m_stepLog->append("");
}

void ModulePanel::logHeader(const QString& module, const QString& op) {
    m_stepLog->append(QString("<span style='color:%1; font-weight:bold;'>[%2] %3</span>")
        .arg(m_accent).arg(module.toHtmlEscaped()).arg(op.toHtmlEscaped()));
}

void ModulePanel::clearLog() {
    m_stepLog->clear();
}
