#ifndef PERFORMANCE_VIEW_H
#define PERFORMANCE_VIEW_H

#include <QWidget>
#include <QTableWidget>

class PerformanceView : public QWidget {
    Q_OBJECT
public:
    explicit PerformanceView(QWidget* parent = nullptr);
    void refresh();

private:
    QTableWidget* m_table;
};

#endif
