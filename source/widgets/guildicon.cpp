#include "guildicon.hpp"
#include "QImage"
#include "source/discordclient.hpp"
#include "ui_guildicon.h"

Guild_icon::Guild_icon(QWidget* parent, discord::Image const& icn) : QWidget(parent), ui(new Ui::Guild_icon), parent(parent) {
    ui->setupUi(this);

    uchar data[128 * 128];
    std::copy(icn.data.begin(), icn.data.end(), data);

    QImage image(data, 128, 128, QImage::Format_ARGB32_Premultiplied);
    QPixmap pix = QPixmap::fromImage(image);
    QIcon qicon(pix);

    ui->pushButton->setIcon(qicon);
    ui->pushButton->setIconSize(QSize(128, 128));
}

Guild_icon::Guild_icon(Guild_icon const& icon) : QWidget(icon.parent), parent(icon.parent), guild_name(icon.guild_name) {}

Guild_icon::Guild_icon(Guild_icon&& icon) : QWidget(icon.parent), parent(icon.parent), guild_name(std::move(icon.guild_name)) {}

Guild_icon::~Guild_icon() {
    delete ui;
}

void Guild_icon::set_name(QString const& name) {
    guild_name = name;
    ui->pushButton->setText(name);
}
