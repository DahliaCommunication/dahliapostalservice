#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    connection_status = 0;
}

Widget::~Widget()
{
    delete layout;
}

void Widget::start()
{
    //Widget layout
    layout = new QBoxLayout(QBoxLayout::TopToBottom, 0);
    layout->setMargin(0);
    this->setLayout(layout);

    //Address and Connect Section
    address_and_connect_section_widget = new QWidget(nullptr);
    address_and_connect_section_layout = new QBoxLayout(QBoxLayout::LeftToRight, nullptr);
    address_and_connect_section_layout->setMargin(0);
    address_and_connect_section_widget->setStyleSheet(QString("QWidget{margin:5px 0 5px 0}"));
    address_and_connect_section_widget->setLayout(address_and_connect_section_layout);
    /* Postal Office Address Line */
    postal_office_address_line = new QLineEdit(nullptr);
    postal_office_address_line->setPlaceholderText(QString("Postal Office Address"));
    postal_office_address_line->setMaximumHeight(50);

    /* Post Office Connect Button */
    connect_to_postal_office_button = new QPushButton(QString("Connect to office"), nullptr);
    connect_to_postal_office_button->setMaximumHeight(50);
    connect_to_postal_office_button->setStyleSheet(QString("QWidget{padding:5px;}"));

    /* Add Widgets (in order) to section */
    address_and_connect_section_layout->addWidget(postal_office_address_line);
    address_and_connect_section_layout->addWidget(connect_to_postal_office_button);

    /* Add section to widget layout */
    layout->addWidget(address_and_connect_section_widget);

    //Visual Display
    web_view = new QWebEngineView(nullptr);
    layout->addWidget(web_view);

    /** Signals and Slots **/
    QObject::connect(connect_to_postal_office_button, SIGNAL(clicked(bool)), this, SLOT(toggle_connect(bool)));
}

void Widget::toggle_connect(bool var)
{
    if(0 == connection_status)
    {
        if(postal_office_address_line->text().length() > 0)
        {
            connection_status = 1;
            postal_office_address_line->setDisabled(1);
            connect_to_postal_office_button->setDisabled(1);
            connect_to_postal_office_button->setText(QString("Connecting"));
        }
    }
}
