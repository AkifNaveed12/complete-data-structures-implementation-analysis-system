#ifndef HASHING_VIEW_H
#define HASHING_VIEW_H

#include "ModulePanel.h"
#include "../../core/hashing/hash.h"
#include "../../gui/GlobalGuiNotifier.h"
#include <QThread>
#include <QLabel>
#include <QVBoxLayout>

class HashWorker : public QObject {
    Q_OBJECT
public:
    enum Op { InsertChaining, InsertProbing, DisplayChaining, DisplayProbing };
    HashWorker(HashChaining* hc, HashLinearProbe* hp, Op op, int key=0)
        : m_hc(hc), m_hp(hp), m_op(op), m_key(key) {}

public slots:
    void run() {
        switch (m_op) {
            case InsertChaining: m_hc->insert(m_key); break;
            case DisplayChaining: m_hc->display(); break;
            case InsertProbing: m_hp->insert(m_key); break;
            case DisplayProbing: m_hp->display(); break;
        }
        emit finished();
    }
signals:
    void finished();
private:
    HashChaining* m_hc; HashLinearProbe* m_hp; Op m_op; int m_key;
};

class HashingView : public ModulePanel {
    Q_OBJECT
public:
    explicit HashingView(QWidget* parent = nullptr);

private slots:
    void onRun();
    void onReset();
    void onStep(int n, const QString& msg) { logStep(n, msg); }
    void onResult(const QString& msg) { logResult(msg); }
    void onError(const QString& msg) { logError(msg); }
    void onHeader(const QString& mod, const QString& op) { logHeader(mod, op); }
    void onWorkerFinished();
    void onOpSelected(int row);

private:
    HashChaining* m_hc;
    HashLinearProbe* m_hp;
    QThread* m_thread = nullptr;
    HashWorker* m_worker = nullptr;
};

#endif
