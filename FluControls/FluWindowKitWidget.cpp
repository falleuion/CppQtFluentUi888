#include "FluWindowKitWidget.h"
#include <QWKWidgets/widgetwindowagent.h>

#include <QLabel>
#include "FluWindowkitButton.h"
#include "FluWindowKitTitleBar.h"
#include "../FluUtils/FluUtils.h"

#include <QStyleOption>

FluWindowKitWidget::FluWindowKitWidget(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
    setWindowIcon(QIcon("./res/Tiles/GalleryIcon.ico"));
    setWindowTitle("windowkit widget");
    resize(800, 600);

    auto agent = new QWK::WidgetWindowAgent(this);
    agent->setup(this);

    auto titleLabel = new QLabel;
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText("WindowKit Widget.");

#ifndef Q_OS_MAC
    auto iconButton = new FluWindowkitButton();
    iconButton->setObjectName("iconButton");
    iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto minButton = new FluWindowkitButton();
    minButton->setObjectName("minButton");
    minButton->setProperty("systemButton", true);
    minButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeMinimize));
    minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto maxButton = new FluWindowkitButton();
    maxButton->setCheckable(true);
    maxButton->setObjectName("maxButton");
    maxButton->setProperty("systemButton", true);
    maxButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeMaximize));
    maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto closeButton = new FluWindowkitButton();
    closeButton->setObjectName("closeButton");
    closeButton->setProperty("systemButton", true);
    closeButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose));
    closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#endif

    auto titleBar = new FluWindowKitTitleBar;
    titleBar->setFixedHeight(35);
#ifndef Q_OS_MAC
    titleBar->setIconButton(iconButton);
    titleBar->setMinButton(minButton);
    titleBar->setMaxButton(maxButton);
    titleBar->setCloseButton(closeButton);
#endif
    titleBar->setTitleLabel(titleLabel);
    titleBar->setHostWidget(this);
    agent->setTitleBar(titleBar);

    // contentLayout;
    m_contentLayout = new QHBoxLayout;
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLayout->setSpacing(0);

    // mainLayout;
    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setSpacing(0);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->addWidget(titleBar, Qt::AlignTop);
    m_vMainLayout->addLayout(m_contentLayout, 1);
    setLayout(m_vMainLayout);

#ifndef Q_OS_MAC
    agent->setSystemButton(QWK::WindowAgentBase::WindowIcon, iconButton);
    agent->setSystemButton(QWK::WindowAgentBase::Minimize, minButton);
    agent->setSystemButton(QWK::WindowAgentBase::Maximize, maxButton);
    agent->setSystemButton(QWK::WindowAgentBase::Close, closeButton);
#endif

#ifndef Q_OS_MAC
    connect(titleBar, &FluWindowKitTitleBar::minimizeRequested, this, &QWidget::showMinimized);
    connect(titleBar, &FluWindowKitTitleBar::maximizeRequested, this, [this, maxButton](bool max) {
        if (max)
        {
            showMaximized();
        }
        else
        {
            showNormal();
        }

        emulateLeaveEvent(maxButton);
    });

    connect(titleBar, &FluWindowKitTitleBar::closeRequested, this, &QWidget::close);
#endif  // !Q_OS_MAC

#ifdef Q_OS_WIN
    // setAttribute(Qt::WA_TranslucentBackground);
    // agent->setWindowAttribute(QStringLiteral("acrylic-material"), true);
    // style()->polish(this);
#endif
}

void FluWindowKitWidget::emulateLeaveEvent(QWidget *widget)
{
    Q_ASSERT(widget);
    if (!widget)
    {
        return;
    }
    QTimer::singleShot(0, widget, [widget]() {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        const QScreen *screen = widget->screen();
#else
	        const QScreen *screen = widget->windowHandle()->screen();
#endif
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos))
        {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover))
            {
                const QPoint localPos = widget->mapFromGlobal(globalPos);
                const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
                static constexpr const auto oldPos = QPoint{};
                const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 4, 0))
                const auto event = new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
                Q_UNUSED(localPos);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 3, 0))
	                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, globalPos, oldPos, modifiers);
	                Q_UNUSED(scenePos);
#else
	                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, oldPos, modifiers);
	                Q_UNUSED(scenePos);
#endif
                QCoreApplication::postEvent(widget, event);
            }
        }
    });
}
