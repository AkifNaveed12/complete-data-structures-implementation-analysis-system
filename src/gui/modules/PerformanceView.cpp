#include "PerformanceView.h"
#include "../../analysis/performance.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>

PerformanceView::PerformanceView(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* vl = new QVBoxLayout(this);
    vl->setContentsMargins(24, 24, 24, 24);
    vl->setSpacing(16);

    QLabel* title = new QLabel("Performance Report");
    title->setStyleSheet("font-size:24px; font-weight:bold; color:#FFF176;");
    vl->addWidget(title);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(5);
    m_table->setHorizontalHeaderLabels({"Module", "Operation", "Steps", "Comparisons", "Complexity"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setStyleSheet(R"(
        QTableWidget { background:#1e1e2e; color:#e8e8f0; border:1px solid #2a2a3e; gridline-color:#2a2a3e; }
        QHeaderView::section { background:#1a1a2e; color:#8888aa; padding:8px; border:none; border-bottom:1px solid #2a2a3e; border-right:1px solid #2a2a3e; font-weight:bold; }
        QTableWidget::item { padding:4px 8px; border-bottom:1px solid #2a2a3e; }
    )");
    vl->addWidget(m_table);

    QPushButton* btn = new QPushButton("Refresh Data", this);
    btn->setStyleSheet("QPushButton { background:#FFF176; color:#0d0d0d; border-radius:6px; padding:8px 16px; font-weight:bold; } QPushButton:hover { background:#ffee58; }");
    connect(btn, &QPushButton::clicked, this, &PerformanceView::refresh);
    
    QHBoxLayout* bl = new QHBoxLayout();
    bl->addStretch();
    bl->addWidget(btn);
    vl->addLayout(bl);

    refresh();
}

void PerformanceView::refresh() {
    const auto& logs = Performance::getLogs();
    m_table->setRowCount(logs.size());
    for (size_t i = 0; i < logs.size(); i++) {
        m_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(logs[i].module)));
        m_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(logs[i].operation)));
        m_table->setItem(i, 2, new QTableWidgetItem(QString::number(logs[i].steps)));
        m_table->setItem(i, 3, new QTableWidgetItem(QString::number(logs[i].comparisons)));
        m_table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(logs[i].complexity)));
    }
}
