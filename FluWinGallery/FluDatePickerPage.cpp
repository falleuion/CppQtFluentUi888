#include "FluDatePickerPage.h"

FluDatePickerPage::FluDatePickerPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("DatePicker");
    m_infoLabel->setText(
        "Use a DatePickerto let users set a date in your app for example to schedule an appointment The DatePicker displays three controls for month date andyearThese controls are easy to use with touch or mouse and they can be styled and "
        "configured in several different ways");

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle("A simple DatePicker with a header.");
    displayBox1->getCodeExpander()->setCodeByPath("../code/DatePickerPageCode1.md");
    auto datePicker = new FluDatePicker;
    displayBox1->getBodyLayout()->addWidget(datePicker);

    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluDatePickerPage.qss", this);
}

void FluDatePickerPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluDatePickerPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/dark/FluDatePickerPage.qss", this);
    }
}
