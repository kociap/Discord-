#include "driftuistyle.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QMenuBar>
#include <QPainter>
#include <QPropertyAnimation>
#include <QProxyStyle>
#include <QPushButton>
#include <QStyleOption>
#include <QThread>
#include <QTimer>
#include <QWidget>
#include <QtMath>

DriftUIStyle::DriftUIStyle() : QCommonStyle() {}

int DriftUIStyle::styleHint(StyleHint sh,
                            const QStyleOption* opt,
                            const QWidget* widget,
                            QStyleHintReturn* hret) const {
  switch (sh) {
    default:
      return QCommonStyle::styleHint(sh, opt, widget, hret);
  }
}

int DriftUIStyle::layoutSpacing(QSizePolicy::ControlType,
                                QSizePolicy::ControlType,
                                Qt::Orientation,
                                const QStyleOption*,
                                const QWidget*) const {
  return 5;
}

/*
 * This function returns different sizes (in pixel units), for various metrics.
 * It includes stuff like margins, frame (border) widths, and miscellanous
 * oddities like menu overlap.
 *
 * Basically, fine control for sizes of different areas.
 */
int DriftUIStyle::pixelMetric(PixelMetric pm,
                              const QStyleOption* opt,
                              const QWidget* widget) const {
  switch (pm) {
    case PM_MenuBarHMargin: {
      return 3;
    }
    case PM_MenuBarVMargin: {
      return 5;
    }
    case PM_MenuBarItemSpacing: {
      return 2;
    }
    case PM_MenuButtonIndicator: {
      return 1;
    }
    case PM_MenuPanelWidth: {
      return 2;
    }
    case PM_SubMenuOverlap: {
      return -1;
    }
    case PM_MenuVMargin: {
      return 1;
    }
    default:
      return QCommonStyle::pixelMetric(pm, opt, widget);
  }
}

/*
 * This function returns a 2D size for something based on it's contents.
 * For example you can add a fake padding for a QPushButton by adding another
 * QSize onto the content size provided.
 */
QSize DriftUIStyle::sizeFromContents(ContentsType type,
                                     const QStyleOption* opt,
                                     const QSize& contentsSize,
                                     const QWidget* widget) const {
  switch (type) {
    case CT_MenuBarItem: {
      return contentsSize + QSize(8, 1);
    }
    case CT_MenuItem: {
      auto ret =
          QCommonStyle::sizeFromContents(type, opt, contentsSize, widget) -
          QSize(0, 4);
      auto rOpt = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
      if (rOpt->menuItemType == QStyleOptionMenuItem::SubMenu)
        ret += QSize(10, 0);
      return ret;
    }
    default:
      return QCommonStyle::sizeFromContents(type, opt, contentsSize, widget);
  }
}

/*
 * This prepares UI elements.
 * You can set up animations, fonts, and other widget details here.
 */
void DriftUIStyle::polish(QWidget* w) {
  // Use roboto font
  w->setFont(QFont("Roboto", 9));

  if (qobject_cast<QMenuBar*>(w))
    w->setAttribute(Qt::WA_MouseTracking);

  if (qobject_cast<QPushButton*>(w))
    w->setAttribute(Qt::WA_Hover);

  if (QMenu* menu = qobject_cast<QMenu*>(w)) {
    w->setAttribute(Qt::WA_TranslucentBackground);
    w->setWindowFlags(w->windowFlags() | Qt::FramelessWindowHint |
                      Qt::WindowSystemMenuHint | Qt::NoDropShadowWindowHint);
    w->setAttribute(Qt::WA_Hover);
    w->setAttribute(Qt::WA_MouseTracking);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(w);
    w->setGraphicsEffect(effect);
  }
}

/*
 * This function modifies a palette to fit the style.
 * In this case, however, Drift UI uses a custom palette class, as the QPalette
 * is somewhat restrictive.
 */
void DriftUIStyle::polish(QPalette& pal) {
  pal.setColor(QPalette::Window, QColor(47, 47, 47));
  pal.setColor(QPalette::Text, QColor(221, 221, 221));
  pal.setColor(QPalette::ButtonText, QColor(221, 221, 221));
}

void DriftUIStyle::drawPrimitive(PrimitiveElement pe,
                                 const QStyleOption* opt,
                                 QPainter* p,
                                 const QWidget* widget) const {
  switch (pe) {
    case PE_FrameWindow: {
      break;
    }
    case PE_PanelMenuBar: {
      break;
    }
    case PE_FrameMenu: {
      p->save();

      p->setRenderHint(QPainter::Antialiasing, true);

      QPainterPath shape;
      shape.addRoundedRect(opt->rect.marginsRemoved(QMargins(1, 1, 1, 1)), 3,
                           3);

      p->strokePath(shape, QPen(QColor(21, 21, 21), 2));

      p->restore();

      break;
    }
    case PE_PanelMenu: {
      p->save();

      p->setRenderHint(QPainter::Antialiasing, true);

      QPainterPath shape;
      shape.addRoundedRect(opt->rect, 3, 3);

      p->fillPath(shape, QColor(36, 36, 36));

      p->restore();

      break;
    }
    case PE_FrameFocusRect: {
      p->save();

      p->setBrush(QBrush(QColor(25, 94, 231)));
      p->drawRoundedRect(opt->rect.marginsAdded(QMargins(1, 1, 1, 1)), 2, 2);

      p->restore();

      break;
    }
    default:
      return QCommonStyle::drawPrimitive(pe, opt, p, widget);
  }
}

void DriftUIStyle::drawControl(ControlElement element,
                               const QStyleOption* opt,
                               QPainter* p,
                               const QWidget* widget) const {
  switch (element) {
    case CE_PushButton: {
      int x, y, w, h;

      opt->rect.getRect(&x, &y, &w, &h);

      p->save();

      auto rOpt = qstyleoption_cast<const QStyleOptionButton*>(opt);

      QLinearGradient fillGradient(x, y, x, y + h);

      bool hover = opt->state & State_MouseOver;
      bool sunken = opt->state & State_Sunken;

      if (sunken) {
        fillGradient.setColorAt(0.0, QColor(48, 48, 48));
        fillGradient.setColorAt(1.0, QColor(64, 64, 64));
      } else if (hover) {
        fillGradient.setColorAt(0.0, QColor(55, 55, 55));
        fillGradient.setColorAt(1.0, QColor(64, 64, 64));
      } else {
        fillGradient.setColorAt(0.0, QColor(64, 64, 64));
        fillGradient.setColorAt(1.0, QColor(55, 55, 55));
      }

      p->setRenderHint(QPainter::Antialiasing, true);

      QPainterPath shape;
      shape.addRoundedRect(
          QRect(x, y, w, h).marginsRemoved(QMargins(1, 1, 1, 1)), 4, 4);

      p->fillPath(shape, fillGradient);
      p->strokePath(shape, QPen(QColor(21, 21, 21), 2));

      p->drawText(
          rOpt->rect.center() + QPoint(rOpt->fontMetrics.width(rOpt->text) / -2,
                                       (rOpt->fontMetrics.capHeight() / 2) + 2),
          rOpt->text);

      p->restore();

      break;
    }
    case CE_MenuBarEmptyArea: {
      p->save();

      p->setRenderHint(QPainter::Antialiasing, true);

      QPainterPath shape;
      shape.addRoundedRect(opt->rect.marginsRemoved(QMargins(5, 5, 5, 5)), 3,
                           3);

      p->fillPath(shape, QColor(36, 36, 36));
      p->strokePath(shape, QPen(QColor(21, 21, 21), 2));

      p->restore();

      break;
    }
    case CE_MenuBarItem: {
      p->save();

      auto rOpt = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);

      bool highlight =
          (rOpt->state & State_MouseOver) || (rOpt->state & State_Selected);

      p->setRenderHint(QPainter::Antialiasing, true);

      if (highlight) {
        QPainterPath shape;
        shape.addRoundedRect(rOpt->rect, 3, 3);
        p->fillPath(shape, QColor(25, 94, 231));
      } else {
        QPainterPath shape;
        shape.addRoundedRect(rOpt->rect, 3, 3);
        p->fillPath(shape, QColor(36, 36, 36));
      }

      p->drawText(
          rOpt->rect.center() + QPoint(rOpt->fontMetrics.width(rOpt->text) / -2,
                                       (rOpt->fontMetrics.capHeight() / 2) + 2),
          rOpt->text);

      p->restore();

      break;
    }
    case CE_MenuItem: {
      p->save();

      auto rOpt = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);

      bool highlight =
          (rOpt->state & State_MouseOver) || (rOpt->state & State_Selected);

      p->setRenderHint(QPainter::Antialiasing, true);

      if (highlight) {
        QPainterPath shape;
        shape.addRoundedRect(rOpt->rect.marginsRemoved(QMargins(1, 1, 1, 1)), 2,
                             2);
        p->fillPath(shape, QColor(25, 94, 231));
      } else {
        QPainterPath shape;
        shape.addRoundedRect(rOpt->rect, 3, 3);
        p->fillPath(shape, QColor(36, 36, 36));
      }

      QFontMetrics metrics = opt->fontMetrics;
      QString text = rOpt->text;
      auto textPoint = opt->rect.center();
      textPoint.setX(opt->rect.bottomLeft().x() + 5);
      textPoint.setY(textPoint.y() + (metrics.capHeight() / 2) + 1);

      QString firstPart = text;
      QString secondPart;

      if (text.contains('\t')) {
        auto split = text.split('\t');
        firstPart = split[0] + '\t';
        secondPart = split[1];
      }

      p->setPen(opt->palette.color(QPalette::BrightText));
      p->drawText(textPoint, firstPart);
      QColor blended = opt->palette.color(QPalette::BrightText);
      blended.setAlpha(100);
      p->setPen(blended);
      p->drawText(textPoint + QPoint(opt->fontMetrics.width(firstPart), 0),
                  secondPart);

      if (rOpt->menuItemType == QStyleOptionMenuItem::SubMenu) {
        QPainterPath arrow;
        arrow.moveTo(opt->rect.topRight() - QPoint(8, -5));
        arrow.lineTo(opt->rect.topRight() + QPoint(-2, opt->rect.height() / 2));
        arrow.lineTo(opt->rect.bottomRight() - QPoint(8, 5));
        arrow.translate(-2, 0);
        p->fillPath(arrow, opt->palette.color(QPalette::BrightText));
      }

      p->restore();

      break;
    }
    default:
      return QCommonStyle::drawControl(element, opt, p, widget);
  }
}

void DriftUIStyle::drawComplexControl(ComplexControl cc,
                                      const QStyleOptionComplex* opt,
                                      QPainter* p,
                                      const QWidget* widget) const {
  switch (cc) {
    default:
      return QCommonStyle::drawComplexControl(cc, opt, p, widget);
  }
}
