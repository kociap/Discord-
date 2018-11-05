#ifndef AUTHORIZATIONVIEW_HPP
#define AUTHORIZATIONVIEW_HPP

#include <QWebEngineView>

class AuthorizationView : public QWebEngineView {
    Q_OBJECT

public:
    AuthorizationView(QWidget *parent = nullptr);

private slots:
    void onURLChanged(QUrl const &);
};

#endif // !AUTHORIZATIONVIEW_HPP
