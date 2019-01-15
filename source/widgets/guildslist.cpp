#include "guildslist.hpp"
#include "discord/urls.hpp"
#include "ui_guildslist.h"

Guilds_list::Guilds_list(QWidget* parent) : QWidget(parent), ui(new Ui::Guilds_list) {
    ui->setupUi(this);
}

Guilds_list::~Guilds_list() {
    delete ui;
}

void Guilds_list::add_guild(discord::Guild const& guild) {
    /*guild_icons.emplace_back(this);
    guild_icons.back().set_name(QString::fromStdString(guild.name));
    auto item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, &guild_icons.back());*/
}

QListWidget* Guilds_list::get_list_widget() const {
    return ui->listWidget;
}
