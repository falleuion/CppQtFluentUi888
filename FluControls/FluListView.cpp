#include "FluListView.h"

FluListView::FluListView(QWidget* parent /*= nullptr*/) : QListWidget(parent)
{
    setItemDelegate(new FluListViewItemDelegate);
    m_delegate = new FluScrollDelegate(this);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluListView::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluListView.qss", this);
        //  style()->polish(this);
        //    setItemDelegate(new FluListViewItemDelegate);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/dark/FluListView.qss", this);
        //  style()->polish(this);
        //  setItemDelegate(new FluListViewItemDelegate);
    }
}
