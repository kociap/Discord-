#include "guildslist.hpp"
#include "ui_guildslist.h"

Guilds_list::Guilds_list(QWidget* parent) : QWidget(parent), ui(new Ui::Guilds_list) {
    ui->setupUi(this);
}

Guilds_list::~Guilds_list() {
    delete ui;
}

void Guilds_list::add_guild(QString const& name) {
    guild_icons.emplace_back(this);
    guild_icons.back().set_name(name);
}
