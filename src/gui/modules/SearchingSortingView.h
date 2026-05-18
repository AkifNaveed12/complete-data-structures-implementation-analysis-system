#ifndef SEARCHING_SORTING_VIEW_H
#define SEARCHING_SORTING_VIEW_H

#include "ModulePanel.h"
#include "../../core/searching_sorting/searching.h"
#include "../../core/searching_sorting/sorting.h"
#include "../../gui/GlobalGuiNotifier.h"
#include <QThread>
#include <QLabel>
#include <QVBoxLayout>

class SSWorker : public QObject {
    Q_OBJECT
public:
    enum Op { LSearch, BSearch, Bubble, Selection, Insertion, Merge, Quick };
    SSWorker(Op op, int key=0) : m_op(op), m_key(key) {}

public slots:
    void run() {
        int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 33};
        int n = 10;
        switch (m_op) {
            case LSearch: Searching::linearSearch(arr, n, m_key); break;
            case BSearch: {
                // binary search requires a sorted array
                int sortedArr[] = {11, 12, 22, 25, 33, 34, 45, 64, 88, 90};
                Searching::binarySearch(sortedArr, n, m_key);
                break;
            }
            case Bubble: Sorting::bubbleSort(arr, n); break;
            case Selection: Sorting::selectionSort(arr, n); break;
            case Insertion: Sorting::insertionSort(arr, n); break;
            case Merge: Sorting::mergeSort(arr, n); break;
            case Quick: Sorting::quickSort(arr, n); break;
        }
        emit finished();
    }
signals:
    void finished();
private:
    Op m_op; int m_key;
};

class SearchingSortingView : public ModulePanel {
    Q_OBJECT
public:
    explicit SearchingSortingView(QWidget* parent = nullptr);

private slots:
    void onRun();
    void onReset() { clearLog(); }
    void onStep(int n, const QString& msg) { logStep(n, msg); }
    void onResult(const QString& msg) { logResult(msg); }
    void onError(const QString& msg) { logError(msg); }
    void onHeader(const QString& mod, const QString& op) { logHeader(mod, op); }
    void onWorkerFinished();
    void onOpSelected(int row);

private:
    QThread* m_thread = nullptr;
    SSWorker* m_worker = nullptr;
};

#endif
