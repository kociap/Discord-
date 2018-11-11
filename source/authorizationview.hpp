#ifndef AUTHORIZATIONVIEW_HPP
#define AUTHORIZATIONVIEW_HPP

#include <QWebEngineView>

class Authorization_View : public QWebEngineView {
    Q_OBJECT

public:
    Authorization_View(QWidget* parent = nullptr);

private slots:
    void on_url_changed(QUrl const&);
};

#endif // !AUTHORIZATIONVIEW_HPP
