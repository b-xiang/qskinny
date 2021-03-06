/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_SKINNABLE_H
#define QSK_SKINNABLE_H

#include "QskAspect.h"
#include <memory>

typedef unsigned int QRgb;
class QSizeF;
class QRectF;
class QColor;
class QFont;
class QMarginsF;
struct QMetaObject;
class QVariant;
class QDebug;

class QSGNode;

class QskControl;
class QskAnimationHint;
class QskColorFilter;
class QskBoxShapeMetrics;
class QskBoxBorderMetrics;
class QskBoxBorderColors;
class QskGradient;
class QskIntervalF;

class QskSkin;
class QskSkinlet;
class QskSkinHintTable;

class QSK_EXPORT QskSkinHintStatus
{
  public:
    enum Source
    {
        NoSource = 0,

        Skinnable,
        Skin,
        Animator
    };

    QskSkinHintStatus()
        : source( NoSource )
    {
    }

    inline bool isValid() const
    {
        return source > 0;
    }

    Source source;
    QskAspect aspect;
};

#ifndef QT_NO_DEBUG_STREAM

class QDebug;
QSK_EXPORT QDebug operator<<( QDebug, const QskSkinHintStatus& );

#endif

class QSK_EXPORT QskSkinnable
{
  public:
    QskSkinnable();
    virtual ~QskSkinnable();

    void setSkinlet( const QskSkinlet* skinlet );
    const QskSkinlet* skinlet() const;

    void setColor( QskAspect, Qt::GlobalColor );
    void setColor( QskAspect, QRgb );
    void setColor( QskAspect, const QColor& );
    bool resetColor( QskAspect );
    QColor color( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setMetric( QskAspect, qreal metric );
    bool resetMetric( QskAspect );
    qreal metric( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setFlagHint( QskAspect, int flag );
    bool resetFlagHint( QskAspect );
    int flagHint( QskAspect ) const;
    template< typename T > T flagHint( QskAspect, T = T() ) const;

    void setStrutSizeHint( QskAspect, const QSizeF& );
    void setStrutSizeHint( QskAspect, qreal width, qreal height );
    bool resetStrutSizeHint( QskAspect );
    QSizeF strutSizeHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setMarginHint( QskAspect, qreal );
    void setMarginHint( QskAspect, const QMarginsF& );
    bool resetMarginHint( QskAspect );
    QMarginsF marginHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setPaddingHint( QskAspect, qreal );
    void setPaddingHint( QskAspect, const QMarginsF& );
    bool resetPaddingHint( QskAspect );
    QMarginsF paddingHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setGradientHint( QskAspect, const QskGradient& );
    QskGradient gradientHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setBoxShapeHint( QskAspect, const QskBoxShapeMetrics& );
    bool resetBoxShapeHint( QskAspect );
    QskBoxShapeMetrics boxShapeHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setBoxBorderMetricsHint( QskAspect, const QskBoxBorderMetrics& );
    bool resetBoxBorderMetricsHint( QskAspect );
    QskBoxBorderMetrics boxBorderMetricsHint(
        QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setBoxBorderColorsHint( QskAspect, const QskBoxBorderColors& );
    bool resetBoxBorderColorsHint( QskAspect );
    QskBoxBorderColors boxBorderColorsHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setIntervalHint( QskAspect, const QskIntervalF& );
    QskIntervalF intervalHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setSpacingHint( QskAspect, qreal );
    bool resetSpacingHint( QskAspect );
    qreal spacingHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setAlignmentHint( QskAspect, Qt::Alignment );
    bool resetAlignmentHint( QskAspect );
    Qt::Alignment alignmentHint( QskAspect, Qt::Alignment = Qt::Alignment() ) const;

    void setFontRole( QskAspect, int role );
    int fontRole( QskAspect, QskSkinHintStatus* = nullptr ) const;

    QFont effectiveFont( QskAspect ) const;

    void setGraphicRole( QskAspect, int role );
    int graphicRole( QskAspect, QskSkinHintStatus* = nullptr ) const;

    QskColorFilter effectiveGraphicFilter( QskAspect ) const;

    void setAnimationHint( QskAspect, QskAnimationHint );
    QskAnimationHint animationHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    void setSkinHint( QskAspect, const QVariant& );
    bool resetSkinHint( QskAspect );

    QskAnimationHint effectiveAnimation( QskAspect::Type, QskAspect::Subcontrol,
        QskAspect::State, QskSkinHintStatus* status = nullptr ) const;

    QVariant effectiveSkinHint( QskAspect, QskSkinHintStatus* = nullptr ) const;
    virtual QskAspect::Placement effectivePlacement() const;

    QskSkinHintStatus hintStatus( QskAspect ) const;

    QskAspect::State skinState() const;
    const char* skinStateAsPrintable() const;
    const char* skinStateAsPrintable( QskAspect::State ) const;

    QSizeF outerBoxSize( QskAspect, const QSizeF& innerBoxSize ) const;
    QSizeF innerBoxSize( QskAspect, const QSizeF& outerBoxSize ) const;

    QRectF innerBox( QskAspect, const QRectF& outerBox ) const;
    QRectF outerBox( QskAspect, const QRectF& innerBox ) const;

    QMarginsF innerPadding( QskAspect, const QSizeF& ) const;

    const QskSkinlet* effectiveSkinlet() const;
    QskSkin* effectiveSkin() const;

    void startTransition( QskAspect,
        QskAnimationHint, QVariant from, QVariant to );

    virtual QskAspect::Subcontrol effectiveSubcontrol( QskAspect::Subcontrol ) const;

    QskControl* controlCast();
    const QskControl* controlCast() const;

    virtual QskControl* owningControl() const = 0;
    virtual const QMetaObject* metaObject() const = 0;

    void debug( QskAspect ) const;
    void debug( QskAspect::State ) const;
    void debug( QDebug, QskAspect ) const;
    void debug( QDebug, QskAspect::State ) const;

    void setSkinState( QskAspect::State, bool animated = true );
    void setSkinStateFlag( QskAspect::State, bool on = true );

  protected:
    virtual void updateNode( QSGNode* );
    virtual bool isTransitionAccepted( QskAspect ) const;

    QskSkinHintTable& hintTable();
    const QskSkinHintTable& hintTable() const;

  private:
    void startHintTransition( QskAspect,
        QskAnimationHint, QVariant from, QVariant to );

    QVariant animatedValue( QskAspect, QskSkinHintStatus* ) const;
    const QVariant& storedHint( QskAspect, QskSkinHintStatus* = nullptr ) const;

    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

template< typename T >
inline T QskSkinnable::flagHint( QskAspect aspect, T defaultValue ) const
{
    const auto& hint = effectiveSkinHint( aspect );
    if ( hint.isValid() && hint.canConvert< int >() )
        return static_cast< T >( hint.value< int >() );

    return defaultValue;
}

inline Qt::Alignment QskSkinnable::alignmentHint(
    QskAspect aspect, Qt::Alignment defaultAlignment ) const
{
    return flagHint< Qt::Alignment >( aspect | QskAspect::Alignment, defaultAlignment );
}

inline bool QskSkinnable::resetColor( QskAspect aspect )
{
    return resetSkinHint( aspect | QskAspect::Color );
}

inline bool QskSkinnable::resetMetric( QskAspect aspect )
{
    return resetSkinHint( aspect | QskAspect::Metric );
}

inline bool QskSkinnable::resetFlagHint( QskAspect aspect )
{
    return resetSkinHint( aspect | QskAspect::Flag );
}

#endif
