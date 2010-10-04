/*
  This file is part of the kholidays library.

  Copyright 2010 John Layt <john@layt.net>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef KHOLIDAYS_HOLIDAYREGIONSELECTOR_H
#define KHOLIDAYS_HOLIDAYREGIONSELECTOR_H

#include "kholidays_export.h"

#include <QtGui/QTreeWidget>

class QString;
class QStringList;

namespace KHolidays {

class HolidayRegion;

class KHOLIDAYS_EXPORT HolidayRegionSelector : public QWidget
{
  Q_OBJECT
  Q_PROPERTY( QAbstractItemView::SelectionMode primarySelectionMode READ primarySelectionMode WRITE setSelectionMode )
  Q_PROPERTY( bool hideSearch READ searchHidden WRITE setSearchHidden )
  Q_PROPERTY( bool hideDescription READ descriptionHidden WRITE setDescriptionHidden )
  Q_PROPERTY( bool hideLanguage READ languageHidden WRITE setLanguageHidden )
  Q_PROPERTY( QStringList languageFilter READ languageFilter WRITE setLanguageFilter )

public:
  /**
   * Describes the Selection Status of the Holiday Region.
   */
  enum SelectionStatus {
    RegionHidden,             ///< The Holiday Region is not displayed
    RegionDisabled,           ///< The Holiday Region is not available for selection
    RegionNotSelected,        ///< The Holiday Region is not selected
    RegionSelected,           ///< The Holiday Region is selected
    RegionSelectedSecondary   ///< The Holiday Region is selected for Days Off
  };

  /**
   * Constructs a default Holiday Region selection widget.
   *
   * This widget will automatically be populated with all available Holiday Regions, will
   * display all available features including a serach bar and various details columns, and will
   * operate in Multi Selection mode.  If you require fewer details or regions displayed or to
   * operate in single or no selection mode, then you must configure these after the widget is
   * created.
   *
   * By default a Primary and Secondary selection are available to the user.  This is normally
   * used with the Primary selection meaning a Holiday Region is to be used and the Secondary
   * selection meaning to use the Holiday Region for Days Off.  These selection modes can be
   * overridden or disabled, or the text displayed for them modifed if required.
   *
   * @param parent The parent widget.
   */
  explicit HolidayRegionSelector( QWidget *parent = 0 );

  /**
   * Destructor
   */
  virtual ~HolidayRegionSelector();

  /**
   * Return a list of all Holiday Regions available
   *
   * @return List of all Holiday Region Codes
   */
  QStringList holidayRegions() const;

  /**
   * Set what selection modes to use.
   *
   * The Primary Selection mode determines how many Holiday Regions can be selected:
   *  - If NoSelection mode then the widget is display only and the user cannot select any
   *    holiday region
   *  - If SingleSelection mode then only a single Holiday Region can be chosen
   *  - If MultiSelection mode then several Holiday Regions can be chosen
   *
   * The Secondary Selection mode determines if a secondary selection can be made when the Primary
   * Selection mode is MultiSelection, this is normally used to select that a Holiday Region is to be
   * used for Days Off or preferred to other Holiday Regions in some manner:
   *  - If NoSelection then the Secondary Selection is disabled and not displayed
   *  - If SingleSelection mode then only a single Holiday Region can be chosen
   *  - If MultiSelection mode then several Holiday Regions can be chosen
   *
   * @param primarySelectionMode The Primary selection mode to use
   * @param secondarySelectionMode The Secondary (Days Off) selection mode to use
   */
  void setSelectionMode( QAbstractItemView::SelectionMode primarySelectionMode,
                         QAbstractItemView::SelectionMode secondarySelectionMode
                         = QAbstractItemView::MultiSelection );

  /**
   * Returns the current Primary Selection mode
   *
   * @see setSelectionMode
   * @return The current Primary Selection mode
   */
  QAbstractItemView::SelectionMode primarySelectionMode() const;

  /**
   * Returns the current Secondary Selection mode.
   *
   * @see setSelectionMode
   * @return The current Secondary Selection mode
   */
  QAbstractItemView::SelectionMode secondarySelectionMode() const;

  /**
   * Set the text to display for the Primary Selection.
   *
   * By default the Primary Selection is displayed as "Select" but may be overridden if required.
   *
   * @see setSelectionMode
   * @see primarySelectionMode
   * @param headerText The text to display in the header
   * @param headerToolTip The text to display in the header ToolTip
   * @param headerWhatsThis The text to display in the header WhatsThis
   * @param itemText The text to display in the item
   * @param itemToolTip The text to display in the item ToolTip
   * @param itemWhatsThis The text to display in the item WhatsThis
   */
  void setPrimarySelectionText( const QString &headerText,
                                const QString &headerToolTip,
                                const QString &headerWhatsThis,
                                const QString &itemText,
                                const QString &itemToolTip,
                                const QString &itemWhatsThis );

  /**
   * Set the text to display for the Secondary Selection.
   *
   * By default the Secondary Selection is displayed as "Days Off" but may be overridden if
   * required.
   *
   * @see setSelectionMode
   * @see secondarySelectionMode
   * @param headerText The text to display in the header
   * @param headerToolTip The text to display in the header ToolTip
   * @param headerWhatsThis The text to display in the header WhatsThis
   * @param itemText The text to display in the item
   * @param itemToolTip The text to display in the item ToolTip
   * @param itemWhatsThis The text to display in the item WhatsThis
   */
  void setSecondarySelectionText( const QString &headerText,
                                  const QString &headerToolTip,
                                  const QString &headerWhatsThis,
                                  const QString &itemText,
                                  const QString &itemToolTip,
                                  const QString &itemWhatsThis );

  /**
   * Set the Selection Status for a Holiday Region
   *
   * @see holidayRegionStatus
   * @param holidayRegionCode The Holiday Region to set the Status for
   * @param status The Selection Status of the Holiday Region
   */
  void setHolidayRegionStatus( const QString &holidayRegionCode,
                               HolidayRegionSelector::SelectionStatus status = RegionSelected );

  /**
   * Return the current Selection Status for a Holiday Region
   *
   * @see setHolidayRegionStatus
   * @see holidayRegionsStatus
   * @param holidayRegionCode The Holiday Region required
   * @return The current Selection Status for the Holiday Region
   */
  HolidayRegionSelector::SelectionStatus holidayRegionStatus( const QString &holidayRegionCode ) const;

  /**
   * Return the current Selection Status for all Holiday Regions
   *
   * @see setHolidayRegionStatus
   * @see holidayRegionStatus
   * @see selection
   * @return A QHash of all Holiday Regions and their current Selection Status
   */
  QHash<QString, HolidayRegionSelector::SelectionStatus> holidayRegionsStatus() const;

  /**
   * Returns currently selected Holiday Regions with their Selection Status
   *
   * @see holidayRegionsStatus
   * @see primarySelection
   * @see secondarySelection
    * @return A QHash of selected Holiday Regions and their current Selection Status
   */
  QHash<QString, HolidayRegionSelector::SelectionStatus> selection() const;

  /**
   * Returns all Holiday Regions with a Primary Selection Status
   *
   * @see selection
   * @see secondarySelection
   * @return A QStringList of Primary Selection Holiday Regions
   */
  QStringList primarySelection() const;

  /**
   * Returns all Holiday Regions with a Secondary Selection Status
   *
   * @see selection
   * @see primarySelection
   * @return A QStringList of Secondary Selection Holiday Regions
   */
  QStringList secondarySelection() const;

  /**
   * Clear the currently selection status of all Holiday Regions
   */
  void clearSelection();

  /**
   * Set a language filter on the Holiday Regions to be displayed.
   *
   * Only Holiday Regions in a language included in the filter will be displayed in the widget,
   * i.e. all other Holiday Regions will have a SelectionStatus of RegionHidden.
   *
   * Setting a null list disables the display filter, i.e. all Holiday Regions are displayed.
   *
   * @see languageFilter
   * @param languages A list of languages to filter for
   */
  void setLanguageFilter( const QStringList &languages );

  /**
   * Return the current language filter, a null list implies no filter is set.
   *
   * @see setLanguageFilter
   * @return The list of languages currently being displayed
   */
  QStringList languageFilter() const;

  /**
   * Set if the search line to be hidden or displayed
   *
   * @see searchHidden
   * @param hideSearch If the search is to be hidden
   */
  void setSearchHidden( bool hideSearch );

  /**
   * Return if the search line is currently hidden.
   *
   * @see setSearchHidden
   * @return If the search line is hidden
   */
  bool searchHidden() const;

  /**
   * Set if the Holiday Region Language field is to be hidden or displayed
   *
   * @see languageHidden
   * @param hideLanguage If the language field is to be hidden
   */
  void setLanguageHidden( bool hideLanguage );

  /**
   * Return if the Holiday Region Language field is currently hidden.
   *
   * @see setLanguageHidden
   * @return If the language field is hidden
   */
  bool languageHidden() const;

  /**
   * Set if the Holiday Region Description field is to be hidden or displayed
   *
   * @see descriptionHidden
   * @param hideDescription If the description field is to be hidden
   */
  void setDescriptionHidden( bool hideDescription );

  /**
   * Return if the Holiday Region Description field is currently hidden.
   *
   * @see setDescriptionHidden
   * @return If the description field is hidden
   */
  bool descriptionHidden() const;

private Q_SLOTS:

  void itemChanged( QTreeWidgetItem *item, int column );

private:
  class Private;
  Private* const d;
};

}

#endif // KHOLIDAYS_HOLIDAYREGIONSELECTOR_H
