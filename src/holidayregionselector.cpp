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

#include "holidayregionselector.h"
#include "ui_holidayregionselector.h"

#include "holidayregion.h"

#include <QDebug>
#include <KLocale>
#include <KLocalizedString>
#include <KGlobal>
#include <KComboBox>

using namespace KHolidays;

class HolidayRegionSelector::Private
{
  public:
    Private( HolidayRegionSelector *q_ptr )
    {
      q = q_ptr;
    }

    ~Private()
    {
    }

    // Reorder this to change column order
    enum Column {
      RegionColumn = 0,
      LanguageColumn,
      DescriptionColumn,
      SelectColumn,
      ComboColumn
    };

    void clearSelection();
    QTreeWidgetItem *findItem( const QString &holidayRegionCode );
    void initItem( QTreeWidgetItem *listItem, HolidayRegion *region );
    QString itemRegion( QTreeWidgetItem *item );
    QString itemLanguage( QTreeWidgetItem *item );
    SelectionStatus itemSelectionStatus( QTreeWidgetItem *item );
    void setItemStatus( QTreeWidgetItem *item, SelectionStatus status );
    KComboBox *itemCombo( QTreeWidgetItem *item );
    void setItemRegionUseFlags( QTreeWidgetItem *item, RegionUseFlags regionUseFlags );
    HolidayRegionSelector::RegionUseFlags itemRegionUseFlags( QTreeWidgetItem *item );

    QAbstractItemView::SelectionMode m_selectionMode;
    bool m_enableRegionUseFlags;
    QStringList m_languageFilter;
    QStringList m_holidayRegionCodes;
    Ui::holidayRegionSelector m_ui;
    HolidayRegionSelector *q;
};

void HolidayRegionSelector::Private::clearSelection()
{
  m_ui.regionTreeWidget->blockSignals( true );
  QTreeWidgetItemIterator it( m_ui.regionTreeWidget, QTreeWidgetItemIterator::Checked );
  while ( *it ) {
    ( *it )->setCheckState( Private::SelectColumn, Qt::Unchecked );
    ( *it )->setData( Private::SelectColumn, Qt::UserRole, RegionAvailable );
    itemCombo( ( *it ) )->setCurrentIndex( 0 );
    ( *it )->setData( Private::ComboColumn, Qt::UserRole, NotUsed );
    ++it;
  }
  m_ui.regionTreeWidget->blockSignals( false );
}

QTreeWidgetItem *HolidayRegionSelector::Private::findItem( const QString &holidayRegionCode )
{
  QTreeWidgetItemIterator it( m_ui.regionTreeWidget );
  while ( *it ) {
    if ( ( *it )->data( HolidayRegionSelector::Private::RegionColumn, Qt::UserRole ) ==
         holidayRegionCode ) {
      return ( *it );
    }
    ++it;
  }
  return 0;
}

void HolidayRegionSelector::Private::initItem( QTreeWidgetItem *listItem, HolidayRegion *region )
{
  m_ui.regionTreeWidget->blockSignals( true );
  QString languageName = KLocale::global()->languageCodeToName( region->languageCode() );
  listItem->setCheckState( Private::SelectColumn, Qt::Unchecked );
  QString text = i18n( "<p>Select to use Holiday Region</p>" );
  listItem->setToolTip( Private::SelectColumn, text );
  listItem->setToolTip( Private::ComboColumn, text );
  text = i18n( "<p>Select to use Holiday Region</p>" );
  listItem->setToolTip( Private::SelectColumn, text );
  listItem->setToolTip( Private::ComboColumn, text );
  listItem->setText( Private::RegionColumn, region->name() );
  QString toolTip = i18n( "<p><b>Region:</b> %1<br/>"
                          "<b>Language:</b> %2<br/>"
                          "<b>Description:</b> %3</p>",
                          region->name(), languageName, region->description() );
  listItem->setToolTip( Private::RegionColumn, toolTip );
  listItem->setData( Private::RegionColumn, Qt::UserRole, region->regionCode() );
  listItem->setText( Private::LanguageColumn, languageName );
  listItem->setData( Private::LanguageColumn, Qt::UserRole, region->languageCode() );
  listItem->setText( Private::DescriptionColumn, region->description() );
  listItem->setToolTip( Private::DescriptionColumn, region->description() );
  KComboBox *combo = new KComboBox();
  combo->setAutoFillBackground( true );
  QString comboText = i18n( "<p>You can choose to display the Holiday Region for information only, "
                            "or to use the Holiday Region when displaying or calculating days off "
                            "such as Public Holidays.  If you choose to use the Holiday Region for "
                            "Days Off, then only those Holiday Events marked in the Holiday Region "
                            "as Days Off will be used for non-work days, Holiday Events that are "
                            "not marked in the Holiday Region as Days Off will continue to be "
                            "work days.</p>" );
  combo->setToolTip( comboText );
  comboText = i18nc( "Combobox label, Holiday Region not used", "Not Used" );
  combo->addItem( comboText, QVariant( NotUsed ) );
  comboText = i18nc( "Combobox label, use Holiday Region for information only", "Information" );
  combo->addItem( comboText, QVariant( UseInformationOnly ) );
  comboText = i18nc( "Combobox label, use Holiday Region for days off", "Days Off" );
  combo->addItem( comboText, QVariant( UseDaysOff ) );
  combo->setCurrentIndex( 0 );
  listItem->setData( Private::ComboColumn, Qt::UserRole, NotUsed );
  m_ui.regionTreeWidget->setItemWidget( listItem, ComboColumn, combo );
  connect( combo, SIGNAL(currentIndexChanged(int)),
           q, SLOT(itemChanged(int)) );
  m_ui.regionTreeWidget->blockSignals( false );
}

QString HolidayRegionSelector::Private::itemRegion( QTreeWidgetItem *item )
{
  return item->data( Private::RegionColumn, Qt::UserRole ).toString();
}

QString HolidayRegionSelector::Private::itemLanguage( QTreeWidgetItem *item )
{
  return item->data( Private::LanguageColumn, Qt::UserRole ).toString();
}

HolidayRegionSelector::SelectionStatus
HolidayRegionSelector::Private::itemSelectionStatus( QTreeWidgetItem *item )
{
  return
    ( HolidayRegionSelector::SelectionStatus )
    item->data( Private::SelectColumn, Qt::UserRole ).toInt();
}

void HolidayRegionSelector::Private::setItemRegionUseFlags( QTreeWidgetItem *item,
                                                            RegionUseFlags regionUseFlags )
{
  // Just do simple flags for now, cheat on the index
  item->setData( ComboColumn, Qt::UserRole, QVariant( regionUseFlags ) );
  if ( regionUseFlags & UseDaysOff ) {
    setItemStatus( item, RegionSelected );
    itemCombo( item )->setCurrentIndex( 2 );
  } else if ( regionUseFlags & UseInformationOnly ) {
    setItemStatus( item, RegionSelected );
    itemCombo( item )->setCurrentIndex( 1 );
  } else { // NotUsed
    setItemStatus( item, RegionAvailable );
    itemCombo( item )->setCurrentIndex( 0 );
  }
}

HolidayRegionSelector::RegionUseFlags
HolidayRegionSelector::Private::itemRegionUseFlags( QTreeWidgetItem *item )
{
  return (RegionUseFlags) item->data( ComboColumn, Qt::UserRole ).toInt();
}

KComboBox *HolidayRegionSelector::Private::itemCombo( QTreeWidgetItem *item )
{
  return static_cast<KComboBox*>( m_ui.regionTreeWidget->itemWidget( item, ComboColumn ) );
}

void HolidayRegionSelector::Private::setItemStatus( QTreeWidgetItem *item, SelectionStatus status )
{
  if ( m_selectionMode == QAbstractItemView::SingleSelection &&
       status == RegionSelected ) {
    clearSelection();
  }

  Qt::CheckState selectStatus = Qt::Unchecked;
  bool hidden = false;
  bool disabled = false;

  switch ( status ) {
  case RegionHidden:
    hidden = true;
    disabled = true;
    break;
  case RegionDisabled:
    disabled = true;
    break;
  case RegionAvailable:
    break;
  case RegionSelected:
  {
    if ( m_selectionMode != QAbstractItemView::NoSelection ) {
      selectStatus = Qt::Checked;
    }
    break;
  }
  default:
    break;
  }

  m_ui.regionTreeWidget->blockSignals( true );
  item->setData( Private::SelectColumn, Qt::UserRole, status );
  item->setCheckState( Private::SelectColumn, selectStatus );
  item->setHidden( hidden );
  item->setDisabled( disabled );
  m_ui.regionTreeWidget->blockSignals( false );
}

HolidayRegionSelector::HolidayRegionSelector( QWidget *parent ) :
  QWidget( parent ), d( new Private( this ) )
{
  d->m_ui.setupUi( this );

  // Setup the columns
  d->m_ui.regionTreeWidget->setColumnCount( 5 );
  QTreeWidgetItem *headerItem = d->m_ui.regionTreeWidget->headerItem();
  QString header = i18nc( "Header for Select column", "Select" );
  QString text = i18n( "<p>This column selects to use the Holiday Region</p>" );
  headerItem->setText( Private::SelectColumn, header );
  headerItem->setToolTip( Private::SelectColumn, text );
  headerItem->setWhatsThis( Private::SelectColumn, text );
  headerItem->setText( Private::ComboColumn, header );
  headerItem->setToolTip( Private::ComboColumn, text );
  headerItem->setWhatsThis( Private::ComboColumn, text );
  header = i18nc( "Header for Holiday Region column", "Region" );
  text = i18n( "<p>This column displays the name of the Holiday Region</p>" );
  headerItem->setText( Private::RegionColumn, header );
  headerItem->setToolTip( Private::RegionColumn, text );
  headerItem->setWhatsThis( Private::RegionColumn, text );
  header = i18nc( "Header for Language column", "Language" );
  text = i18n( "<p>This column displays the language of the Holiday Region</p>" );
  headerItem->setText( Private::LanguageColumn, header );
  headerItem->setToolTip( Private::LanguageColumn, text );
  headerItem->setWhatsThis( Private::LanguageColumn, text );
  header = i18nc( "Header for Description column", "Description" );
  text = i18n( "<p>This column displays the description of the Holiday Region</p>" );
  headerItem->setText( Private::DescriptionColumn, header );
  headerItem->setToolTip( Private::DescriptionColumn, text );
  headerItem->setWhatsThis( Private::DescriptionColumn, text );

  d->m_ui.regionTreeWidget->setSelectionMode( QAbstractItemView::NoSelection );
  d->m_ui.regionTreeWidget->setItemsExpandable( true ); //per bug 271628
  d->m_ui.regionTreeWidget->setUniformRowHeights( true );
  d->m_ui.regionTreeWidget->setAllColumnsShowFocus( true );
  connect( d->m_ui.regionTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
           this, SLOT(itemChanged(QTreeWidgetItem*,int)) );

  QMap<QString, QStringList> regionCodeMap;
  QMap<QString, HolidayRegion*> regionMap;
  foreach ( const QString &regionCode, HolidayRegion::regionCodes() ) {
    regionMap[regionCode] = new HolidayRegion( regionCode );
    QString country = regionMap[regionCode]->countryCode().split( QLatin1Char('-') ).at( 0 );
    regionCodeMap[country].append( regionCode );
  }

  QMapIterator<QString, QStringList> it( regionCodeMap );
  while ( it.hasNext() ) {
    it.next();
    // if only 1 region for country and that region is the country, then only show the country line
    // Otherwise show a non-selectable country header and list all regions below it
    QTreeWidgetItem *rootItem = new QTreeWidgetItem( d->m_ui.regionTreeWidget );
    QString country = it.key();
    if ( it.value().count() == 1 && regionMap[it.value().at( 0 )]->countryCode() == country ) {
      d->initItem( rootItem, regionMap[ it.value().at( 0 ) ] );
    } else {
      rootItem->setText( Private::RegionColumn,
                         KLocale::global()->countryCodeToName( country ) );
      d->m_ui.regionTreeWidget->setFirstItemColumnSpanned ( rootItem, true );
      foreach ( const QString &regionCode, it.value() ) {
        QTreeWidgetItem *childItem = new QTreeWidgetItem( rootItem );
        d->initItem( childItem, regionMap[ regionCode ] );
      }
    }
  }

  QMapIterator<QString, HolidayRegion*> i( regionMap );
  while ( i.hasNext() ) {
    i.next();
    delete i.value();
  }

  d->m_ui.regionTreeWidget->expandAll();
  d->m_ui.regionTreeWidget->sortItems( Private::RegionColumn, Qt::AscendingOrder );
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::SelectColumn );
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::ComboColumn );
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::RegionColumn );
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::LanguageColumn );

  // Setup search widget
  d->m_ui.searchLineWidget->searchLine()->addTreeWidget( d->m_ui.regionTreeWidget );

  // Default to MultiSelection mode with Region Use Flags
  setSelectionMode( QAbstractItemView::MultiSelection );
  setRegionUseFlagsEnabled( true );
}

HolidayRegionSelector::~HolidayRegionSelector()
{
  delete d;
}

QStringList HolidayRegionSelector::holidayRegions() const
{
  return d->m_holidayRegionCodes;
}

void HolidayRegionSelector::setSelectionMode( QAbstractItemView::SelectionMode selectionMode )
{
  d->m_selectionMode = selectionMode;

  if ( selectionMode == QAbstractItemView::NoSelection ) {
    setRegionUseFlagsEnabled( false );
  }
}

QAbstractItemView::SelectionMode HolidayRegionSelector::selectionMode() const
{
  return d->m_selectionMode;
}

void HolidayRegionSelector::setRegionUseFlagsEnabled( bool enableRegionUseFlags )
{
  d->m_enableRegionUseFlags = enableRegionUseFlags;
  d->m_ui.regionTreeWidget->setColumnHidden( Private::SelectColumn, enableRegionUseFlags );
  d->m_ui.regionTreeWidget->setColumnHidden( Private::ComboColumn, !enableRegionUseFlags );
}

bool HolidayRegionSelector::regionUseFlagsEnabled() const
{
  return d->m_enableRegionUseFlags;
}

void HolidayRegionSelector::setSelectionStatus( const QString &holidayRegionCode,
                                                HolidayRegionSelector::SelectionStatus status )
{
  QTreeWidgetItem *item = d->findItem( holidayRegionCode );
  if ( item ) {
    d->setItemStatus( item, status );
  }
}

HolidayRegionSelector::SelectionStatus
HolidayRegionSelector::selectionStatus( const QString &holidayRegionCode ) const
{
  QTreeWidgetItem *item = d->findItem( holidayRegionCode );
  if ( item ) {
    return d->itemSelectionStatus( item );
  }
  return HolidayRegionSelector::RegionHidden;
}

QHash<QString, HolidayRegionSelector::SelectionStatus>
HolidayRegionSelector::selectionStatus() const
{
  QHash<QString, HolidayRegionSelector::SelectionStatus> selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    selection.insert( d->itemRegion( ( *it ) ), d->itemSelectionStatus( ( *it ) ) );
    ++it;
  }
  return selection;
}

QStringList
HolidayRegionSelector::selection( HolidayRegionSelector::SelectionStatus selectionStatus ) const
{
  if ( selectionMode() == QAbstractItemView::NoSelection ) {
    return QStringList();
  }

  QStringList selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    if ( d->itemSelectionStatus( ( *it ) ) == selectionStatus ) {
      selection.append( d->itemRegion( ( *it ) ) );
    }
    ++it;
  }
  return selection;
}

QStringList
HolidayRegionSelector::selection( HolidayRegionSelector::RegionUseFlags regionUseFlags ) const
{
  if ( selectionMode() == QAbstractItemView::NoSelection ) {
    return QStringList();
  }

  QStringList selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    if ( d->itemRegionUseFlags( ( *it ) ) & regionUseFlags ) {
      selection.append( d->itemRegion( ( *it ) ) );
    }
    ++it;
  }
  return selection;
}

void
HolidayRegionSelector::setRegionUseFlags( const QString &holidayRegionCode,
                                          HolidayRegionSelector::RegionUseFlags regionUseFlags )
{
  QTreeWidgetItem *item = d->findItem( holidayRegionCode );
  if ( item ) {
    d->setItemRegionUseFlags( item, regionUseFlags );
  }
}

HolidayRegionSelector::RegionUseFlags
HolidayRegionSelector::regionUseFlags( const QString &holidayRegionCode ) const
{
  QTreeWidgetItem *item = d->findItem( holidayRegionCode );
  if ( item ) {
    return d->itemRegionUseFlags( item );
  }
  return HolidayRegionSelector::NotUsed;
}

QHash<QString, HolidayRegionSelector::RegionUseFlags> HolidayRegionSelector::regionUseFlags() const
{
  QHash<QString, HolidayRegionSelector::RegionUseFlags> selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    selection.insert( d->itemRegion( ( *it ) ), d->itemRegionUseFlags( ( *it ) ) );
    ++it;
  }
  return selection;
}

void HolidayRegionSelector::itemChanged( QTreeWidgetItem *item, int column )
{
  if ( column == Private::SelectColumn ) {
    if ( item->checkState( Private::SelectColumn ) == Qt::Unchecked ) {
      d->setItemStatus( item, RegionAvailable );
    } else {
      d->setItemStatus( item, RegionSelected );
    }
  }
  emit selectionChanged();
}

// The slot for the combo box when changed
void HolidayRegionSelector::itemChanged( int index )
{
  KComboBox *combo = static_cast<KComboBox*>( sender() );
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  bool found = false;
  while ( *it && !found ) {
    if ( d->itemCombo( ( *it ) ) == combo ) {
      ( *it )->setData(
        Private::ComboColumn, Qt::UserRole, d->itemCombo( ( *it ) )->itemData( index ) );
      if ( d->itemRegionUseFlags( ( *it ) ) == NotUsed )  {
        d->setItemStatus( ( *it ), RegionAvailable );
      } else {
        d->setItemStatus( ( *it ), RegionSelected );
      }
      found = true;
    }
    ++it;
  }
}

void HolidayRegionSelector::clearSelection()
{
  d->clearSelection();
}

void HolidayRegionSelector::setLanguageFilter( const QStringList &languages )
{
  // First reset to visible those languages previously hidden
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    if ( !d->m_languageFilter.contains(
           ( *it )->data( Private::LanguageColumn, Qt::UserRole ).toString() ) ) {
      d->setItemStatus( ( *it ), RegionAvailable );
    }
    ++it;
  }
  // Now hide those languages not in the new list
  d->m_languageFilter = languages;
  QTreeWidgetItemIterator it2( d->m_ui.regionTreeWidget );
  while ( *it2 ) {
    QString language = ( *it2 )->data( Private::LanguageColumn, Qt::UserRole ).toString();
    if ( d->m_languageFilter.contains( language ) ) {
      // Make sure the parent is always visible, otherwise the child is not visible
      if ( ( *it2 )->parent() &&
           ( *it2 )->parent() != d->m_ui.regionTreeWidget->invisibleRootItem() ) {
        d->setItemStatus( ( *it2 )->parent(), RegionAvailable );
      }
    } else {
      d->setItemStatus( ( *it2 ), RegionHidden );
    }
    ++it2;
  }
}

QStringList HolidayRegionSelector::languageFilter() const
{
  return d->m_languageFilter;
}

void HolidayRegionSelector::setSearchHidden( bool hideSearch )
{
  d->m_ui.searchLineWidget->setHidden( hideSearch );
}

bool HolidayRegionSelector::searchHidden() const
{
  return d->m_ui.searchLineWidget->isHidden();
}

void HolidayRegionSelector::setLanguageHidden( bool hideLanguage )
{
  d->m_ui.regionTreeWidget->setColumnHidden( Private::LanguageColumn, hideLanguage );
}

bool HolidayRegionSelector::languageHidden() const
{
  return d->m_ui.regionTreeWidget->isColumnHidden( Private::LanguageColumn );
}

void HolidayRegionSelector::setDescriptionHidden( bool hideDescription )
{
  d->m_ui.regionTreeWidget->setColumnHidden( Private::DescriptionColumn, hideDescription );
}

bool HolidayRegionSelector::descriptionHidden() const
{
  return d->m_ui.regionTreeWidget->isColumnHidden( Private::DescriptionColumn );
}

