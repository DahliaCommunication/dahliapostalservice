#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWebEngineView>

#include "brain.hpp"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void init_postal_customer_parameters();
    void start();

private:
    QBoxLayout* layout;

    QWidget* address_and_connect_section_widget;
    QBoxLayout* address_and_connect_section_layout;
        QLineEdit* postal_office_address_line;
        QPushButton* connect_to_postal_office_button;

    QWebEngineView* web_view;

    int connection_status;

    brain* customer_brain;

public slots:
    void toggle_connect(bool var);
};

#endif // WIDGET_H
