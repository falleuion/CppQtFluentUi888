#include "FluCollectionsPage.h"

FluCollectionsPage::FluCollectionsPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText("Collections");

    auto flipViewCard = new FluHCard(QPixmap("../res/ControlImages/FlipView.png"), "FlipView", "Pressents a collection of items that the user can flip through, one item at a time.");
    flipViewCard->setKey("FlipViewPage");
    getFWScrollView()->getMainLayout()->addWidget(flipViewCard);
    connect(flipViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto listViewCard = new FluHCard(QPixmap("../res/ControlImages/ListView.png"), "ListView", "A control that presents a collection of items in a vertical list.");
    listViewCard->setKey("ListViewPage");
    getFWScrollView()->getMainLayout()->addWidget(listViewCard);
    connect(listViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto treeViewCard = new FluHCard(QPixmap("../res/ControlImages/TreeView.png"), "TreeView", "The TreeView control is a hierarchical list pattern with expanding and collapsing nodes that contain nested items.");
    treeViewCard->setKey("TreeViewPage");
    getFWScrollView()->getMainLayout()->addWidget(treeViewCard);
    connect(treeViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto tableViewCard = new FluHCard(QPixmap("../res/ControlImages/GridView.png"), "TableView", "A control taht presents a collection of items in rows and columns.");
    tableViewCard->setKey("TableViewPage");
    getFWScrollView()->getMainLayout()->addWidget(tableViewCard);
    connect(tableViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluCollectionsPage.qss", this);
}

void FluCollectionsPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluCollectionsPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/dark/FluCollectionsPage.qss", this);
    }
}
