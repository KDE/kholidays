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

#include <QTreeWidget>

class QString;
class QStringList;

namespace KHolidays {

class HolidayRegion;

class KHOLIDAYS_EXPORT HolidayRegionSelector : public QWidget
{
  Q_OBJECT
  Q_PROPERTY( QAbstractItemView::SelectionMode listSelectionMode
              READ selectionMode WRITE setSelectionMode )

  Q_PROPERTY( bool enableRegionUseFlags
              READ regionUseFlagsEnabled WRITE setRegionUseFlagsEnabled )

  Q_PROPERTY( bool hideSearch
              READ searchHidden WRITE setSearchHidden )

  Q_PROPERTY( bool hideDescription
              READ descriptionHidden WRITE setDescriptionHidden )

  Q_PROPERTY( bool hideLanguage
              READ languageHidden WRITE setLanguageHidden )

  Q_PROPERTY( QStringList languageFilter
              READ languageFilter WRITE setLanguageFilter )

  public:
    /**
     * Describes the Selection Status of a Holiday Region.
     */
    enum SelectionStatus {
      RegionHidden,             ///< The Holiday Region is not displayed
      RegionDisabled,           ///< The Holiday Region is not available for selection
      RegionAvailable,          ///< The Holiday Region is available for selection
      RegionSelected            ///< The Holiday Region is selected
    };

    /**
     * Describes the Usage of a Holiday Region.
     */
    enum RegionUseFlag {
      NotUsed            = 0x00,    ///< The Holiday Region is not used
      UseInformationOnly = 0x01,    ///< The Holiday Region is used for information only
      UseDaysOff         = 0x02     ///< The Holiday Region is used for Days Off
    };
    Q_DECLARE_FLAGS( RegionUseFlags, RegionUseFlag )

    /**
     * Constructs a default Holiday Region selection widget.
     *
     * This widget will automatically be populated with all available Holiday Regions,
     * will display all available features including a serach bar and various details
     * columns, and will operate in Multi Selection mode.  If you require fewer details
     * or regions displayed or to operate in single or no selection mode, then you must
     * configure these after the widget is created.
     *
     * By default multiple Region Use selections are available to the user.  This is
     * normally used to set if holidays are to be used for days off or information only.
     * These Use options can be overridden or disabled, or the text displayed modifed
     * as required.
     *
     * @param parent The parent widget.
     */
    explicit HolidayRegionSelector( QWidget *parent = Q_NULLPTR );

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
     * Set what selection mode the Region list uses.
     *
     * The Selection Mode determines how many Holiday Regions can be selected in the list:
     *  - If NoSelection mode then the widget is display only and the user cannot select any
     *    Holiday Region.
     *  - If SingleSelection mode then only a single Holiday Region can be chosen.
     *  - If MultiSelection mode then more than one Holiday Regions can be chosen.
     *
     * @see selectionMode
     * @param selectionMode The selection mode to use
     */
    void setSelectionMode( QAbstractItemView::SelectionMode selectionMode );

    /**
     * Return what selection mode the Region list uses.
     *
     * @see setSelectionMode
     * @return The selection mode used
     */
    QAbstractItemView::SelectionMode selectionMode() const;

    /**
     * Set if Region Use Flags are enabled
     *
     * If Region Use Flags are disabled then the user can only select a Region
     * with a binary on/off check box.  The selection status is set and returned
     * using the holidayRegionStatus and setHolidayRegionStatus methods.
     *
     * If the Region Use Flags are enabled then the user can select from multiple
     * options for how a Region can be used via a combo box.  The use flags are
     * set and returned using the setRegionUseFlags and regionUseFlags methods.
     *
     * @see setSelectionMode
     * @param listSelectionMode The list selection mode to use
     */
    void setRegionUseFlagsEnabled( bool enableRegionUseFlags );

    /**
     * Returns if Region Use Flags are enabled.
     *
     * @see setRegionUseFlagsEnabled
     * @return if the Region Use Flags are enabled
     */
    bool regionUseFlagsEnabled() const;

    /**
     * Set the Selection Status for a Holiday Region.
     *
     * @see selectionStatus
     * @param holidayRegionCode The Holiday Region to set the Status for
     * @param status The Selection Status of the Holiday Region
     */
    void setSelectionStatus( const QString &holidayRegionCode,
                             HolidayRegionSelector::SelectionStatus status );

    /**
     * Returns the current Selection Status for a Holiday Region.
     *
     * @see setSelectionStatus
     * @param holidayRegionCode The Holiday Region required
     * @return The current Selection Status for the Holiday Region
     */
    HolidayRegionSelector::SelectionStatus selectionStatus(
      const QString &holidayRegionCode ) const;

    /**
     * Returns the current Selection Status for all Holiday Regions.
     *
     * @see setSelectionStatus
     * @return A QHash of all Holiday Regions and their current Selection Status
     */
    QHash<QString, HolidayRegionSelector::SelectionStatus> selectionStatus() const;

    /**
     * Returns the list of Holiday Regions with a required Selection Status,
     * defults to returning all selected Regions.
     *
     * @see setSelectionStatus
     * @see selectionStatus
     * @param selectionStatus The selection status to match, defaults to RegionSelected
     * @return A list of selected Holiday Regions
     */
    QStringList selection( HolidayRegionSelector::SelectionStatus selectionStatus =
                           HolidayRegionSelector::RegionSelected ) const;

    /**
     * Returns the list of Holiday Regions with a required Region Use Flag.
     *
     * @see setRegionUseFlags
     * @see regionUseFlags
     * @param regionUseFlags The Region Use flags to match
     * @return A list of matching Holiday Regions
     */
    QStringList selection( HolidayRegionSelector::RegionUseFlags regionUseFlags ) const;

    /**
     * Clear the current Selection Status of all Holiday Regions including Region Use Flags.
     *
     * @see setSelectionStatus
     * @see selectionStatus
     * @see selection
     */
    void clearSelection();

    /**
     * Set the Region Use Flags for a Holiday Region.
     *
     * @see regionUseFlags
     * @param holidayRegionCode The Holiday Region to set the Use Flags for
     * @param regionUseFlags The Use Flags for the Holiday Region
     */
    void setRegionUseFlags( const QString &holidayRegionCode,
                            HolidayRegionSelector::RegionUseFlags regionUseFlags );

    /**
     * Returns the current Region Use Flags for a Holiday Region.
     *
     * @see setRegionUseFlags
     * @param holidayRegionCode The Holiday Region required
     * @return The current Use Flags for the Holiday Region
     */
    HolidayRegionSelector::RegionUseFlags regionUseFlags( const QString &holidayRegionCode ) const;

    /**
     * Returns the current Region Use Flags for all Holiday Regions.
     *
     * @see setRegionUseFlags
     * @return A QHash of Holiday Regions and their current Region Use Flags
     */
    QHash<QString, HolidayRegionSelector::RegionUseFlags> regionUseFlags() const;

    /**
     * Set a language filter on the Holiday Regions to be displayed.
     *
     * Only Holiday Regions in a language included in the filter will be
     * displayed in the widget, i.e. all other Holiday Regions will have
     * a SelectionStatus of RegionHidden.
     *
     * Setting a null list disables the display filter, i.e. all Holiday
     * Regions are displayed.
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
     * Set if the search line to be hidden or displayed.
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
     * Set if the Holiday Region Language field is to be hidden or displayed.
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
     * Set if the Holiday Region Description field is to be hidden or displayed.
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
    void itemChanged( int index );

  Q_SIGNALS:
    void selectionChanged();

  private:
    class Private;
    Private *const d;
};

} // namespace KHolidays

Q_DECLARE_OPERATORS_FOR_FLAGS( KHolidays::HolidayRegionSelector::RegionUseFlags )

#endif // KHOLIDAYS_HOLIDAYREGIONSELECTOR_H
