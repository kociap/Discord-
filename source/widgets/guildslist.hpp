#ifndef GUILDSLIST_HPP
#define GUILDSLIST_HPP

#include "guildicon.hpp"
#include "source/discord/guild.hpp"
#include <QWidget>
#include <vector>

namespace Ui {
    class Guilds_list;
}

class QListWidget;

class Guilds_list : public QWidget {
    Q_OBJECT

public:
    explicit Guilds_list(QWidget* parent);
    ~Guilds_list();

    void add_guild(discord::Guild const& guild);
    QListWidget* get_list_widget() const;

private:
    std::vector<Guild_icon> guild_icons;
    Ui::Guilds_list* ui;
};

#endif // !GUILDSLIST_HPP
