#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>
#include <QResizeEvent>
#include <QLabel>

#include "../FluUtils/FluUtils.h"
#include "FluPushButton.h"
#include "FluStyleButton.h"
#include "FluVSplitLine.h"

// note: parent can't be null.
// can use window()
class FluMessageBox : public QDialog
{
    Q_OBJECT
  public:
    FluMessageBox(QString title, QString info, QWidget* parent);

    void showEvent(QShowEvent* event);

    void closeEvent(QCloseEvent* event);

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* obj, QEvent* event);

    void setCancelButtonVisible(bool isVisible);

  public slots:
    void onThemeChanged();

  protected:
    QWidget* m_parentWidget;

    QHBoxLayout* m_hBoxLayout;
    QWidget* m_windowMask;

    QFrame* m_widget;
    QVBoxLayout* m_vWidgetLayout;

    QWidget* m_contentWidget;
    QVBoxLayout* m_vContentWidgetLayout;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;

    QWidget* m_btnWidget;
    QHBoxLayout* m_hBtnLayout;
    FluPushButton* m_cancelBtn;
    FluStyleButton* m_okBtn;
};
