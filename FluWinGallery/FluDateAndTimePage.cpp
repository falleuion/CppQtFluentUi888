#include "FluDateAndTimePage.h"

FluDateAndTimePage::FluDateAndTimePage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText("Date & Time");

    auto calendarDatePickerCard = new FluHCard(QPixmap("./res/ControlImages/CalendarDatePicker.png"), "CalendarDatePicker", "A control that lets users pick a date value using a calendar.");
    calendarDatePickerCard->setKey("CalendarDatePickerPage");
    getFWScrollView()->getMainLayout()->addWidget(calendarDatePickerCard);
    connect(calendarDatePickerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto calendarViewCard = new FluHCard(QPixmap("./res/ControlImages/CalendarView.png"), "CalendarView", "A control that presents aa calendar for a user to choose a date from.");
    calendarViewCard->setKey("CalendarViewPage");
    getFWScrollView()->getMainLayout()->addWidget(calendarViewCard);
    connect(calendarViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto datePickerCard = new FluHCard(QPixmap("./res/ControlImages/DatePicker.png"), "DatePicker", "A control that lets a user pick a date value.");
    datePickerCard->setKey("DatePickerPage");
    getFWScrollView()->getMainLayout()->addWidget(datePickerCard);
    connect(datePickerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto timePickerCard = new FluHCard(QPixmap("./res/ControlImages/TimePicker.png"), "TimePicker", "A configurable control that lets a user pick a time value.");
    timePickerCard->setKey("TimePickerPage");
    getFWScrollView()->getMainLayout()->addWidget(timePickerCard);
    connect(timePickerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluDateAndTimePage.qss", this);
}

void FluDateAndTimePage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluDateAndTimePage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/dark/FluDateAndTimePage.qss", this);
    }
}
