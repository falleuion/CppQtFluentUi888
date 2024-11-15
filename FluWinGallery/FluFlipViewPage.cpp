#include "FluFlipViewPage.h"

FluFlipViewPage::FluFlipViewPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("FlipView");
    m_infoLabel->setText("The FlipView lets you flip through a collection of items.one at a time.it's great for displaying images from a gallery, pages of a magazine or similar items.");

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle("A simple FlipView with items declared inline.");
    displayBox1->getCodeExpander()->setCodeByPath("../code/FlipViewPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(300);

    auto hFlipView = new FluHFlipView(displayBox1);
    hFlipView->move(50, 50);
    hFlipView->addPixmap(QPixmap("../res/SampleMedia/cliff.jpg"));
    hFlipView->addPixmap(QPixmap("../res/SampleMedia/grapes.jpg"));
    hFlipView->addPixmap(QPixmap("../res/SampleMedia/LandscapeImage8.jpg"));
    hFlipView->addPixmap(QPixmap("../res/SampleMedia/sunset.jpg"));

    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle("vertical FlipView");
    displayBox2->getCodeExpander()->setCodeByPath("../code/FlipViewPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(300);

    auto vFlipView = new FluVFlipView(displayBox2);
    vFlipView->move(50, 50);
    vFlipView->addPixmap(QPixmap("../res/SampleMedia/cliff.jpg"));
    vFlipView->addPixmap(QPixmap("../res/SampleMedia/grapes.jpg"));
    vFlipView->addPixmap(QPixmap("../res/SampleMedia/LandscapeImage8.jpg"));
    vFlipView->addPixmap(QPixmap("../res/SampleMedia/sunset.jpg"));

    m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);
    FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluFlipViewPage.qss", this);
}

void FluFlipViewPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/light/FluFlipViewPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("./StyleSheet/dark/FluFlipViewPage.qss", this);
    }
}
