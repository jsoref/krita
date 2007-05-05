/* This file is part of the KDE project
   Copyright (c) 2007 Casper Boemann <cbr@boemann.dk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef KOSLIDERCOMBO_H_
#define KOSLIDERCOMBO_H_

#include <QComboBox>

#include <kofficeui_export.h>

/**
 * @short A widget for double values with a popup slider
 *
 * KoSliderCombo combines a numerical input and a dropdown slider in a way that takes up as
 * little screen space as possible.
 * 
 * It allows the user to either enter a floating point value or quickly set the value using a slider
 * 
 * One signal is emitted when the value changes. The signal is even emitted when the slider
 * is moving. The second argument of the signal however tells you if the value is final or not. A
 * final value is produced by entering a value numerically or by releasing the slider.
 * 
 * The input of the numerical line edit is constrained to numbers and decimal signs.
 */
class KOFFICEUI_EXPORT KoSliderCombo : public QComboBox
{

    Q_OBJECT

public:

    /**
     * Constructor for the widget, where value is set to 0
     *
     * @param parent parent QWidget
     */
    KoSliderCombo(QWidget *parent=0);

    /**
     * Destructor
     */
    virtual ~KoSliderCombo();

    /**
     * The precision of values given as the number of digits after the period.
     * default is 2
     */
    double decimals() const;

    /**
     * The minimum value that can be entered.
     * default is 0
     */
    double minimum() const;

    /**
     * The maximum value that can be entered.
     * default is 100
     */
    double maximum() const;

    /**
     * Sets the precision of the entered values.
     * @param number the number of digits after the period
     */

    void setDecimals(int number);

    /**
     * Sets the minimum value that can be entered.
     * @param min the minimum value
     */
    void setMinimum(double min);

    /**
     * Sets the maximum value that can be entered.
     * @param max the maximum value
     */
    void setMaximum(double max);

    virtual QSize minimumSizeHint() const; ///< reimplemented from QComboBox
    virtual QSize sizeHint() const; ///< reimplemented from QComboBox

public slots:

signals:

    /**
     * Emitted every time the value changes (by calling setValue() or
     * by user interaction).
     * @param value the new value
     * @param final if the value is final ie not produced during sliding (on slider release it's final)
     */
    void valueChanged(double value, bool final);

protected:
    virtual void paintEvent(QPaintEvent *); ///< reimplemented from QComboBox
    virtual void hideEvent(QHideEvent *); ///< reimplemented from QComboBox
    virtual void changeEvent(QEvent *e); ///< reimplemented from QComboBox
    virtual void mousePressEvent(QMouseEvent *e); ///< reimplemented from QComboBox

private:
    Q_PRIVATE_SLOT(d, void sliderValueChanged(int value))
    Q_PRIVATE_SLOT(d, void sliderReleased())
    Q_PRIVATE_SLOT(d, void lineEditFinished())

    class KoSliderComboPrivate;
    KoSliderComboPrivate * const d;
};

#endif
