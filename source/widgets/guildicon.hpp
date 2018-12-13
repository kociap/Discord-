#ifndef GUILDICON_HPP
#define GUILDICON_HPP

#include <QWidget>

namespace Ui {
    class Guild_icon;
}

class Guild_icon : public QWidget {
    Q_OBJECT

public:
    explicit Guild_icon(QWidget* parent);
    Guild_icon(Guild_icon const&);
    Guild_icon(Guild_icon&&);
    ~Guild_icon();

    void set_name(QString const&);

private:
    Ui::Guild_icon* ui;
    QWidget* parent;
    QString guild_name;
};

#endif // !GUILDICON_HPP
