#ifndef DRIFTUISTYLE_H
#define DRIFTUISTYLE_H

#include <QCommonStyle>
#include <QMap>
#include <QPointer>
#include <QPropertyAnimation>

class DriftUIStyle : public QCommonStyle {
 public:
  DriftUIStyle();

  int styleHint(StyleHint sh,
                const QStyleOption* opt,
                const QWidget* widget,
                QStyleHintReturn* hret) const override;
  int layoutSpacing(QSizePolicy::ControlType control1,
                    QSizePolicy::ControlType control2,
                    Qt::Orientation orientation,
                    const QStyleOption* option,
                    const QWidget* widget) const override;
  int pixelMetric(PixelMetric pm,
                  const QStyleOption* opt,
                  const QWidget* widget) const override;
  QSize sizeFromContents(ContentsType type,
                         const QStyleOption* opt,
                         const QSize& contentsSize,
                         const QWidget* widget) const override;
  void polish(QWidget* widget) override;
  void polish(QPalette& pal) override;
  void drawPrimitive(PrimitiveElement element,
                     const QStyleOption* opt,
                     QPainter* p,
                     const QWidget* widget) const override;
  void drawControl(ControlElement element,
                   const QStyleOption* opt,
                   QPainter* p,
                   const QWidget* widget) const override;
  void drawComplexControl(ComplexControl cc,
                          const QStyleOptionComplex* opt,
                          QPainter* p,
                          const QWidget* widget) const override;
};

#endif  // DRIFTUISTYLE_H
