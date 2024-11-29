#include "FluGalleryWindow.h"
#include "FluAEmptyPage.h"
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluControls/FluMessageBox.h"
#include <QApplication>
#include <QTimer>

FRAMELESSHELPER_USE_NAMESPACE

FluGalleryWindow::FluGalleryWindow(QWidget *parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt WinUI3 Gallery Dev");

#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Gallery");
#endif

    setWindowIcon(QIcon("./res/Tiles/GalleryIcon.ico"));

    // resize
    resize(1200, 800);

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(48);

    QString qss = FluStyleSheetUitls::getQssByFileName("./StyleSheet/light/FluGalleryWindow.qss");
    setStyleSheet(qss);

    m_navView = new FluVNavigationView(this);
    m_sLayout = new FluStackedLayout;

    // if nav long will be short, short will be long after clicked it.
    // m_navView->onMenuItemClicked();

    m_contentLayout->addWidget(m_navView);
    //  m_contentLayout->addSpacing(20);
    m_contentLayout->addLayout(m_sLayout, 1);

    //  auto homePage = new FluHomePage(this);
    //  m_sLayout->addWidget(homePage);

    //  auto aEmptyPage = new FluAEmptyPage(this);
    //  m_sLayout->addWidget(aEmptyPage);

    // home
    makeHomeNavItem();

    // design guidance
    makeDesignGuidanceNavItem();

    // samples
    makeSamplesNavItem();

    // basic input
    makeBasicInputNavItem();

    // collections
    makeCollectionsNavItem();

    // date & time
    makDateTimeNavItem();

    // dialogs & flyouts
    makeDialogsFlyouts();

    // layout
    makeLayoutNavItem();

    // media
    makeMediaNavItem();

    // menus & toolbars
    makeMenuToolBarsNavItem();

    // navigation
    makeNavigationNavItem();

    // srolling

    makeScrollingNavItem();

    // status & info

    makeStatusInfoNavItem();

    // text
    makeTextNavItem();

    // settings
    makeSettingsNavItem();

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });

    ///* connect(m_titleBar->closeButton(), &QPushButton::clicked, [=]() { FluMessageBox messageBox;
    //     messageBox.exec();
    // });*/

#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    FluThemeUtils::getUtils()->setTheme(FluTheme::Light);
    QTimer::singleShot(500, [=]() { m_navView->onThemeChanged(); });
#endif
}

void FluGalleryWindow::makeHomeNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Home, "Home", this);
    m_navView->addItemToMidLayout(item);

    auto homePage = new FluHomePage;
    m_sLayout->addWidget("HomePage", homePage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() {
        m_sLayout->setCurrentWidget("HomePage");

        //  FluMessageBox messageBox("Close Gallery Window?", "choose \"Ok\" to close. choose \"Cancel\" do nothing.", this);
        // int nExec = messageBox.exec();
    });

    connect(homePage, &FluHomePage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });
}

void FluGalleryWindow::makeDesignGuidanceNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Design, "Design guidance", this);
    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(FluAwesomeType::FontSize, "Typography", item);
    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(FluAwesomeType::EmojiTabSymbols, "Icons", item);
    // FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem(FluAwesomeType::Color, "Colors", item);

    item->addItem(item1);
    item->addItem(item2);
    // item->addItem(item3);
    m_navView->addItemToMidLayout(item);

    auto typographyPage = new FluTypeographyPage;
    m_sLayout->addWidget("TypographyPage", typographyPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("TypographyPage"); });

    auto iconsPage = new FluIconsPage;
    m_sLayout->addWidget("IconsPage", iconsPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("IconsPage"); });
}

void FluGalleryWindow::makeSamplesNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::AllApps, "All samples", this);
    m_navView->addItemToMidLayout(item);

    auto allSamplesPage = new FluAllSamplesPage;
    m_sLayout->addWidget("AllSamplesPage", allSamplesPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("AllSamplesPage"); });

    connect(allSamplesPage, &FluAllSamplesPage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });
}

void FluGalleryWindow::makeBasicInputNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::CheckboxComposite, "Basic input", this);
    auto basicInputPage = new FluBasicInputPage;
    m_sLayout->addWidget("BasicInputPage", basicInputPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("BasicInputPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("InputValidation", item);
    item1->enableThisItem(false);

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("Button", item);
    auto buttonPage = new FluButtonPage;
    item2->setKey("ButtonPage");
    m_sLayout->addWidget("ButtonPage", buttonPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ButtonPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("DropDownButton", item);
    item3->setKey("DropDownButtonPage");
    auto dropDownPage = new FluDropDownButtonPage;
    m_sLayout->addWidget("DropDownButtonPage", dropDownPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("DropDownButtonPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("HyperLinkButton", item);
    item4->setKey("HyperLinkButtonPage");
    auto hyperLinkButtonPage = new FluHyperLinkButtonPage;
    m_sLayout->addWidget("HyperLinkButtonPage", hyperLinkButtonPage);
    connect(item4, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("HyperLinkButtonPage"); });

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("RepeatButton", item);
    item5->setKey("RepeatButtonPage");
    auto repeatButtonPage = new FluRepeatButtonPage;
    m_sLayout->addWidget("RepeatButtonPage", repeatButtonPage);
    connect(item5, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("RepeatButtonPage"); });

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("ToggleButton", item);
    item6->setKey("ToggleButtonPage");
    auto toggleButtonPage = new FluToggleButtonPage;
    m_sLayout->addWidget("ToggleButtonPage", toggleButtonPage);
    connect(item6, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ToggleButtonPage"); });

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("SplitButton", item);
    item7->setKey("SplitButtonPage");
    auto splitButtonPage = new FluSplitButtonPage;
    m_sLayout->addWidget("SplitButtonPage", splitButtonPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("SplitButtonPage"); });

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem("ToggleSplitButton", item);

    FluVNavigationIconTextItem *item9 = new FluVNavigationIconTextItem("CheckBox", item);
    item9->setKey("CheckBoxPage");
    auto checkBoxPage = new FluCheckBoxPage;
    m_sLayout->addWidget("CheckBoxPage", checkBoxPage);
    connect(item9, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CheckBoxPage"); });

    FluVNavigationIconTextItem *item10 = new FluVNavigationIconTextItem("ColorPicker", item);

    FluVNavigationIconTextItem *item11 = new FluVNavigationIconTextItem("ComboBox", item);
    item11->setKey("ComboBoxPage");
    auto comboBoxPage = new FluComboBoxPage;
    m_sLayout->addWidget("ComboBoxPage", comboBoxPage);
    connect(item11, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ComboBoxPage"); });

    FluVNavigationIconTextItem *item12 = new FluVNavigationIconTextItem("RadioButton", item);
    item12->setKey("RadioButtonPage");
    auto radioButtonPage = new FluRadioButtonPage;
    m_sLayout->addWidget("RadioButtonPage", radioButtonPage);
    connect(item12, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("RadioButtonPage"); });

    FluVNavigationIconTextItem *item13 = new FluVNavigationIconTextItem("RatingControl", item);
    item13->setKey("RatingControlPage");
    auto ratingControlPage = new FluRatingControlPage;
    m_sLayout->addWidget("RatingControlPage", ratingControlPage);
    connect(item13, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("RatingControlPage"); });

    FluVNavigationIconTextItem *item14 = new FluVNavigationIconTextItem("Slider", item);
    item14->setKey("SliderPage");
    auto sliderPage = new FluSliderPage;
    m_sLayout->addWidget("SliderPage", sliderPage);
    connect(item14, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("SliderPage"); });

    FluVNavigationIconTextItem *item15 = new FluVNavigationIconTextItem("ToggleSwitch", item);
    item15->setKey("ToggleSwitchPage");
    auto toggleSwitchPage = new FluToggleSwitchPage;
    m_sLayout->addWidget("ToggleSwitchPage", toggleSwitchPage);
    connect(item15, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ToggleSwitchPage"); });

    connect(basicInputPage, &FluBasicInputPage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    item->addItem(item9);
    item->addItem(item10);
    item->addItem(item11);
    item->addItem(item12);
    item->addItem(item13);
    item->addItem(item14);
    item->addItem(item15);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeCollectionsNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::TiltDown, "Connections", this);
    item->setKey("ConnectionsPage");
    auto collectionsPage = new FluCollectionsPage;
    m_sLayout->addWidget("CollectionsPage", collectionsPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CollectionsPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("FlipView", item);
    item1->setKey("FlipViewPage");

    auto flipViewPage = new FluFlipViewPage;
    m_sLayout->addWidget("FlipViewPage", flipViewPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("FlipViewPage"); });

    // FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("GridView", item);
    // FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("ItemsView", item);
    // FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("ListBox", item);

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("ListView", item);
    item5->setKey("ListViewPage");

    auto listViewPage = new FluListViewPage;
    m_sLayout->addWidget("ListViewPage", listViewPage);
    connect(item5, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ListViewPage"); });

    // FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("PullToRefresh", item);
    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("TreeView", item);
    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem("TableView", item);
    item8->setKey("TableViewPage");
    auto tableViewPage = new FluTableViewPage;
    m_sLayout->addWidget("TableViewPage", tableViewPage);
    connect(item8, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("TableViewPage"); });

    connect(collectionsPage, &FluCollectionsPage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    // item->addItem(item2);
    // item->addItem(item3);
    // item->addItem(item4);
    item->addItem(item5);
    // item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makDateTimeNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Calendar, "Date & time", this);
    item->setKey("DateAndTimePage");
    auto dateAndTimePage = new FluDateAndTimePage;
    m_sLayout->addWidget("DateAndTimePage", dateAndTimePage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("DateAndTimePage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("CalendarDatePicker", item);
    item1->setKey("CalendarDatePickerPage");
    auto calendarDatePickerPage = new FluCalendarDatePickerPage;
    m_sLayout->addWidget("CalendarDatePickerPage", calendarDatePickerPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CalendarDatePickerPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("CalendarView", item);
    item2->setKey("CalendarViewPage");
    auto calendarViewPage = new FluCalendarViewPage;
    m_sLayout->addWidget("CalendarViewPage", calendarViewPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("CalendarViewPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("DatePicker", item);
    item3->setKey("DatePickerPage");
    auto datePickerPage = new FluDatePickerPage;
    m_sLayout->addWidget("DatePickerPage", datePickerPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("DatePickerPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("TimePicker", item);
    item4->setKey("TimePickerPage");
    auto timePickerPage = new FluTimePickerPage;
    m_sLayout->addWidget("TimePickerPage", timePickerPage);
    connect(item4, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("TimePickerPage"); });

    connect(dateAndTimePage, &FluDateAndTimePage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);

    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeDialogsFlyouts()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Comment, "Dialogs & flyouts", this);
    item->setKey("");
    auto dialogAndFlyoutPage = new FluDialogsAndFlyoutsPage;
    m_sLayout->addWidget("DialogsAndFlyoutsPage", dialogAndFlyoutPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("DialogsAndFlyoutsPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("ContentDialog", item);
    item1->setKey("ContentDialogPage");

    auto contentDialogPage = new FluContentDialogPage;
    m_sLayout->addWidget("ContentDialogPage", contentDialogPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ContentDialogPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("Flyout", item);
    item2->setKey("FlyoutPage");

    auto flyoutPage = new FluFlyoutPage;
    m_sLayout->addWidget("FlyoutPage", flyoutPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("FlyoutPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("TeachingTip", item);
    item3->setKey("TeachingTipPage");

    connect(dialogAndFlyoutPage, &FluDialogsAndFlyoutsPage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeLayoutNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::PreviewLink, "Layout", this);
    item->setKey("LayoutPage");
    auto layoutPage = new FluLayoutPage;
    m_sLayout->addWidget("LayoutPage", layoutPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("LayoutPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("Border", item);
    item1->setKey("BorderPage");
    auto borderPage = new FluBorderPage;
    m_sLayout->addWidget("BorderPage", borderPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("BorderPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("Canvas", item);
    item2->setKey("CanvasPage");

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("Expander", item);
    item3->setKey("ExpanderPage");
    auto expanderPage = new FluExpanderPage;
    m_sLayout->addWidget("ExpanderPage", expanderPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ExpanderPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("ItemsRepeater", item);
    item4->setKey("ItemsRepeaterPage");

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("Grid", item);
    item5->setKey("GridPage");

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("RadioButtons", item);
    item6->setKey("RadioButtonsPage");
    auto radioButtonsPage = new FluRadioButtonsPage;
    m_sLayout->addWidget("RadioButtonsPage", radioButtonsPage);
    connect(item6, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("RadioButtonsPage"); });

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("RelativePanel", item);
    item7->setKey("RelativePanelPage");

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem("SplitView", item);
    item8->setKey("SplitViewPage");

    FluVNavigationIconTextItem *item9 = new FluVNavigationIconTextItem("StackPanel", item);
    item9->setKey("StackPanelPage");

    FluVNavigationIconTextItem *item10 = new FluVNavigationIconTextItem("VariableSizedWrapGrid", item);
    item10->setKey("VariableSizedWrapGridPage");

    FluVNavigationIconTextItem *item11 = new FluVNavigationIconTextItem("Viewbox", item);
    item11->setKey("ViewboxPage");

    connect(layoutPage, &FluLayoutPage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    item->addItem(item9);
    item->addItem(item10);
    item->addItem(item11);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeMediaNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Calendar, "Media", this);
    item->setKey("MediaPage");
    auto mediaPage = new FluMediaPage;
    m_sLayout->addWidget("MediaPage", mediaPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("MediaPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("AnimatedVisualPlayer", item);
    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("Capture Element / Camera Preview", item);
    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("Image", item);
    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("mediaPalyerElement", item);
    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("PersonPicture", item);
    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("Sound", item);
    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("WebView2", item);

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeSettingsNavItem()
{
    FluVNavigationSettingsItem *item = new FluVNavigationSettingsItem(FluAwesomeType::Settings, "Setting", this);
    m_navView->addItemToBottomLayout(item);

    auto settingsPage = new FluSettingPage;
    m_sLayout->addWidget("SettingPage", settingsPage);
    connect(item, &FluVNavigationSettingsItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("SettingPage"); });
}

void FluGalleryWindow::makeMenuToolBarsNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Save, "Menus & toolbars", this);
    item->setKey("MenusAndToolBarsPage");
    auto menusAndToolBarsPage = new FluMenuAndToolBarsPage;
    m_sLayout->addWidget("MenusAndToolBarsPage", menusAndToolBarsPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("MenusAndToolBarsPage"); });

    //  FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem("XamlUICommand", item);
    //  FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem("StandardUICommand", item);
    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("AppBarButton", item);
    item3->setKey("AppBarButtonPage");
    auto appBarButtonPage = new FluAppBarButtonPage;
    m_sLayout->addWidget("AppBarButtonPage", appBarButtonPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("AppBarButtonPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("AppBarSeparator", item);
    item4->setKey("AppBarSeparator");

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("AppBarToggleButton", item);
    item5->setKey("AppBarToggleButton");
    auto appBarToggleButtonPage = new FluAppBarToggleButtonPage;
    m_sLayout->addWidget("AppBarToggleButtonPage", appBarToggleButtonPage);
    connect(item5, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("AppBarToggleButtonPage"); });

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("CommandBar", item);
    item6->setKey("CommandBarPage");

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("MenuBar", item);
    item7->setKey("MenuBarPage");
    auto menuBarPage = new FluMenuBarPage;
    m_sLayout->addWidget("MenuBarPage", menuBarPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("MenuBarPage"); });

    FluVNavigationIconTextItem *item8 = new FluVNavigationIconTextItem("CommandBarFlyout", item);
    item8->setKey("CommandBarFlyoutPage");

    FluVNavigationIconTextItem *item9 = new FluVNavigationIconTextItem("MenuFlyout", item);
    item9->setKey("MenuFlyoutPage");

    FluVNavigationIconTextItem *item10 = new FluVNavigationIconTextItem("SwipeControl", item);
    item10->setKey("SwipeControlPage");

    connect(menusAndToolBarsPage, &FluMenuAndToolBarsPage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    // item->addItem(item1);
    //  item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    item->addItem(item8);
    item->addItem(item9);
    item->addItem(item10);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeNavigationNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::BookmarksMirrored, "Navigation", this);
    item->setKey("NavigationPage");
    auto navigationPage = new FluNavigationPage;
    m_sLayout->addWidget("NavigationPage", navigationPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("NavigationPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("BreadcrumbBar", item);
    item1->setKey("BreadcrumbBarPage");

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("NavigationView", item);
    item2->setKey("NavigationViewPage");

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("Pivot", item);
    item3->setKey("PivotPage");
    auto pivotPage = new FluPivotPage;
    m_sLayout->addWidget("PivotPage", pivotPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("PivotPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("TabView", item);
    item4->setKey("TabViewPage");

    connect(navigationPage, &FluNavigationPage::clickedHCard, [=](QString key) {
        // LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeScrollingNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Sort, "Scrolling", this);
    item->setKey("ScrollingPage");
    auto scrollingPage = new FluScrollingPage;
    m_sLayout->addWidget("ScrollingPage", scrollingPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ScrollingPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("AnnotatedScrollBar", item);
    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("PipsPager", item);

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("ScrollView", item);
    item3->setKey("ScrollViewPage");
    auto scrollViewPage = new FluScrollViewPage;
    m_sLayout->addWidget("ScrollViewPage", scrollViewPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ScrollViewPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("ScrollViewer", item);
    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("SemanticZoom", item);

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeStatusInfoNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Reminder, "Status & info", this);
    item->setKey("StatusAndInfoPage");
    auto statusAndInfoPage = new FluStatusAndInfoPage;
    m_sLayout->addWidget("StatusAndInfoPage", statusAndInfoPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("StatusAndInfoPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("InfoBadge", item);
    item1->setKey("InfoBadgePage");
    auto infoBadgePage = new FluInfoBadgePage;
    m_sLayout->addWidget("InfoBadgePage", infoBadgePage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("InfoBadgePage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("InfoBar", item);
    item2->setKey("InfoBarPage");

    auto infoBarPage = new FluInfoBarPage;
    m_sLayout->addWidget("InfoBarPage", infoBarPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("InfoBarPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("progressBar", item);
    item3->setKey("ProgressBarPage");
    auto progressBarPage = new FluProgressBarPage;
    m_sLayout->addWidget("ProgressBarPage", progressBarPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ProgressBarPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("progressRing", item);
    item4->setKey("ProgressRingPage");

    auto progressRingPage = new FluProgressRingPage;
    m_sLayout->addWidget("ProgressRingPage", progressRingPage);
    connect(item4, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("ProgressRingPage"); });

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("ToolTip", item);
    item5->setKey("ProgressRingPage");

    connect(statusAndInfoPage, &FluStatusAndInfoPage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::makeTextNavItem()
{
    FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Font, "Text", this);
    item->setKey("TextPage");
    auto textPage = new FluTextPage;
    m_sLayout->addWidget("TextPage", textPage);
    connect(item, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("TextPage"); });

    FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("AutoSuggestBox", item);
    item1->setKey("AutoSuggestBoxPage");
    auto autoSuggestBoxPage = new FluAutoSuggestBoxPage;
    m_sLayout->addWidget("AutoSuggestBoxPage", autoSuggestBoxPage);
    connect(item1, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("AutoSuggestBoxPage"); });

    FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("NumberBox", item);
    item2->setKey("NumberBoxPage");
    auto numberBoxPage = new FluNumberBoxPage;
    m_sLayout->addWidget("NumberBoxPage", numberBoxPage);
    connect(item2, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("NumberBoxPage"); });

    FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("PasswordBox", item);
    item3->setKey("PasswordBoxPage");
    auto passwordBoxPage = new FluPasswordBoxPage;
    m_sLayout->addWidget("PasswordBoxPage", passwordBoxPage);
    connect(item3, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("PasswordBoxPage"); });

    FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("RichEditBox", item);
    item4->setKey("RichEditBoxPage");

    FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("RichTextBlock", item);
    item5->setKey("RichTextBlockPage");

    FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("TextBlock", item);
    item6->setKey("TextBlockPage");

    FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("TextBox", item);
    item7->setKey("TextBoxPage");
    auto textBoxPage = new FluTextBoxPage;
    m_sLayout->addWidget("TextBoxPage", textBoxPage);
    connect(item7, &FluVNavigationIconTextItem::itemClicked, [=]() { m_sLayout->setCurrentWidget("TextBoxPage"); });

    connect(textPage, &FluTextPage::clickedHCard, [=](QString key) {
        LOG_DEBUG << key;
        auto item = m_navView->getItemByKey(key);
        if (item != nullptr && item->getItemType() == FluVNavigationItemType::IconText)
        {
            auto iconTextItem = (FluVNavigationIconTextItem *)(item);
            iconTextItem->onItemClickedDirect();
            m_sLayout->setCurrentWidget(key);
        }
    });

    item->addItem(item1);
    item->addItem(item2);
    item->addItem(item3);
    item->addItem(item4);
    item->addItem(item5);
    item->addItem(item6);
    item->addItem(item7);
    m_navView->addItemToMidLayout(item);
}

void FluGalleryWindow::resizeEvent(QResizeEvent *event)
{
    if (width() > 1000)
    {
        // check it
        if (!m_navView->isLong())
            m_navView->onMenuItemClicked();
    }
    else
    {
        if (m_navView->isLong())
            m_navView->onMenuItemClicked();
    }
}

void FluGalleryWindow::closeEvent(QCloseEvent *event)
{
    // FluMessageBox messageBox("Close Gallery Window?", "choose \"Ok\" to close. choose \"Cancel\" do nothing.", this);
    //  messageBox.exec();

    // int nExec = messageBox.exec();
    // if (nExec == QDialog::Rejected)
    //{
    //     // m_titleBar->show();
    //     event->ignore();  // can't run it! has some bug.

    //   // FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(this);
    //   // helper->setTitleBarWidget(m_titleBar);
    //    return;
    //}
    // else if (nExec == QDialog::Accepted)
    //{
    //    event->accept();
    //}
}

void FluGalleryWindow::onThemeChanged()
{
    // LOG_DEBUG << "Func Beg";
    if (FluThemeUtils::isLightTheme())
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::black);
#endif
        // m_titleBar->update();
        // m_titleBar->style()->polish(m_titleBar);
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluGalleryWindow.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
    else
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
        // m_titleBar->update();
        // m_titleBar->style()->polish(m_titleBar);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);
#endif
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/dark/FluGalleryWindow.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
    // LOG_DEBUG << "Func End";
}
