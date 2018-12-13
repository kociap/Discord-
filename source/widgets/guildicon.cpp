#include "guildicon.hpp"
#include "ui_guildicon.h"

Guild_icon::Guild_icon(QWidget* parent) : QWidget(parent), ui(new Ui::Guild_icon), parent(parent) {
    ui->setupUi(this);
}

Guild_icon::Guild_icon(Guild_icon const& icon) : QWidget(icon.parent), parent(icon.parent), guild_name(icon.guild_name) {}

Guild_icon::Guild_icon(Guild_icon&& icon) : QWidget(icon.parent), parent(icon.parent), guild_name(std::move(icon.guild_name)) {}

Guild_icon::~Guild_icon() {
    delete ui;
}

void Guild_icon::set_name(QString const& name) {
    guild_name = name;
}
