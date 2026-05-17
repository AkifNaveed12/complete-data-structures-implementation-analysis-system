#ifndef MODULE_PANEL_H
#define MODULE_PANEL_H

// ============================================================
//  ModulePanel — reusable 3-panel layout for every module.
//  Left: sidebar with operations + input.
//  Center: visualization canvas.
//  Right: step log.
//  design.md §4.3
// ============================================================

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QString>

class ModulePanel : public QWidget {
    Q_OBJECT
public:
    explicit ModulePanel(const QString& title, const QString& accentColor, QWidget* parent = nullptr);

    // Returns widgets modules should place ops into
    QListWidget* operationList() { return m_opList; }
    QWidget*     canvasArea()    { return m_canvas; }
    QTextEdit*   stepLog()       { return m_stepLog; }
    QLineEdit*   input1()        { return m_input1; }
    QLineEdit*   input2()        { return m_input2; }
    QLabel*      input1Label()   { return m_input1Label; }
    QLabel*      input2Label()   { return m_input2Label; }
    QPushButton* runButton()     { return m_runBtn; }
    QPushButton* resetButton()   { return m_resetBtn; }
    QLabel*      statusLabel()   { return m_statusLabel; }

    void logStep(int n, const QString& msg);
    void logResult(const QString& msg);
    void logError(const QString& msg);
    void logHeader(const QString& module, const QString& op);
    void clearLog();

signals:
    void runRequested();
    void resetRequested();

private:
    QString m_accent;
    QWidget*     m_canvas;
    QListWidget* m_opList;
    QTextEdit*   m_stepLog;
    QLineEdit*   m_input1;
    QLineEdit*   m_input2;
    QLabel*      m_input1Label;
    QLabel*      m_input2Label;
    QPushButton* m_runBtn;
    QPushButton* m_resetBtn;
    QLabel*      m_statusLabel;
    QLabel*      m_titleLabel;
};

#endif
