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

#include <KDebug>
#include <KLocale>

using namespace KHolidays;

class HolidayRegionSelector::Private
{
public:
  Private()
  {
  }

  ~Private()
  {
  }

  // Reorder this to change column order
  enum Column {
    RegionColumn = 0,
    SelectColumn,
    SecondaryColumn,
    LanguageColumn,
    DescriptionColumn
  };

  void clearSelection();
  void clearSecondarySelection();
  QTreeWidgetItem *findItem( const QString &holidayRegionCode );
  void initItem( QTreeWidgetItem *listItem, HolidayRegion *region );
  QString itemRegion( QTreeWidgetItem *item );
  QString itemLanguage( QTreeWidgetItem *item );
  SelectionStatus itemStatus( QTreeWidgetItem *item );
  void setItemSelected( QTreeWidgetItem *item, SelectionStatus status );

  QAbstractItemView::SelectionMode m_primarySelectionMode, m_secondarySelectionMode;
  QStringList m_languageFilter;
  QStringList m_holidayRegionCodes;
  Ui::holidayRegionSelector m_ui;
};

void HolidayRegionSelector::Private::clearSelection()
{
  m_ui.regionTreeWidget->blockSignals( true );
  QTreeWidgetItemIterator it( m_ui.regionTreeWidget, QTreeWidgetItemIterator::Checked );
  while ( *it ) {
    (*it)->setCheckState( Private::SelectColumn, Qt::Unchecked );
    (*it)->setCheckState( Private::SecondaryColumn, Qt::Unchecked );
    ++it;
  }
  m_ui.regionTreeWidget->blockSignals( false );
}

void HolidayRegionSelector::Private::clearSecondarySelection()
{
  m_ui.regionTreeWidget->blockSignals( true );
  QTreeWidgetItemIterator it( m_ui.regionTreeWidget, QTreeWidgetItemIterator::Checked );
  while ( *it ) {
    (*it)->setCheckState( Private::SecondaryColumn, Qt::Unchecked );
    ++it;
  }
  m_ui.regionTreeWidget->blockSignals( false );
}

QTreeWidgetItem *HolidayRegionSelector::Private::findItem( const QString &holidayRegionCode )
{
  QTreeWidgetItemIterator it( m_ui.regionTreeWidget );
  while ( *it ) {
    if ( (*it)->data( HolidayRegionSelector::Private::RegionColumn, Qt::UserRole ) == holidayRegionCode ) {
      return (*it);
    }
  ++it;
  }
  return 0;
}

void HolidayRegionSelector::Private::initItem( QTreeWidgetItem *listItem, HolidayRegion *region )
{
  m_ui.regionTreeWidget->blockSignals( true );
  QString languageName = KGlobal::locale()->languageCodeToName( region->languageCode() );
  listItem->setCheckState( Private::SelectColumn, Qt::Unchecked );
  listItem->setToolTip( Private::SelectColumn, i18n("<p>Select to use Holiday Region</p>") );
  listItem->setWhatsThis( Private::SelectColumn, i18n("<p>Select to use Holiday Region</p>") );
  listItem->setCheckState( Private::SecondaryColumn, Qt::Unchecked );
  listItem->setToolTip( Private::SecondaryColumn, i18n("<p>Select to use Holiday Region for Days Off</p>") );
  listItem->setWhatsThis( Private::SecondaryColumn, i18n("<p>Select to use Holiday Region for Days Off</p>") );
  listItem->setText( Private::RegionColumn, region->name() );
  QString toolTip = i18n("<p><b>Region:</b> %1<br/>"
                         "<b>Language:</b> %2<br/>"
                         "<b>Description:</b> %3</p>",
                         region->name(), languageName, region->description() );
  listItem->setToolTip( Private::RegionColumn, toolTip );
  listItem->setData( Private::RegionColumn, Qt::UserRole, region->regionCode() );
  listItem->setText( Private::LanguageColumn, languageName );
  listItem->setData( Private::LanguageColumn, Qt::UserRole, region->languageCode() );
  listItem->setText( Private::DescriptionColumn, region->description() );
  listItem->setToolTip( Private::DescriptionColumn, region->description() );
  m_ui.regionTreeWidget->blockSignals( false );

  QString comboText = i18nc("Combobox label, Holiday Region not used", "Not Used");
  comboText = i18nc("Combobox label, use Holiday Region for information only", "Information");
  comboText = i18nc("Combobox label, use Holiday Region for days off", "Days Off");
  comboText = i18n("<p>You can choose to display the Holiday Region for information only, or to use the Holiday Region when displaying or calculating days off such as Public Holidays.  If you choose to use the Holiday Region for Days Off, then only those Holiday Events marked in the Holiday Region as Days Off will be used for non-work days, Holiday Events that are not marked in the Holiday Region as Days Off will continue to be work days.</p>");
}

QString HolidayRegionSelector::Private::itemRegion( QTreeWidgetItem *item )
{
  return item->data( Private::RegionColumn, Qt::UserRole ).toString();
}

QString HolidayRegionSelector::Private::itemLanguage( QTreeWidgetItem *item )
{
  return item->data( Private::LanguageColumn, Qt::UserRole ).toString();
}

HolidayRegionSelector::SelectionStatus HolidayRegionSelector::Private::itemStatus( QTreeWidgetItem *item )
{
  return (HolidayRegionSelector::SelectionStatus)
         item->data( Private::SelectColumn, Qt::UserRole ).toInt();
}

void HolidayRegionSelector::Private::setItemSelected( QTreeWidgetItem *item, SelectionStatus status )
{
  if ( m_primarySelectionMode == QAbstractItemView::NoSelection ) {
    return;
  }

  if ( m_primarySelectionMode == QAbstractItemView::SingleSelection &&
    status >= RegionSelected ) {
    clearSelection();
  } else if ( m_secondarySelectionMode == QAbstractItemView::SingleSelection &&
              status >= RegionSelectedSecondary ) {
    clearSecondarySelection();
  }

  Qt::CheckState selectStatus = Qt::Unchecked;
  Qt::CheckState secondaryStatus = Qt::Unchecked;
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
  case RegionNotSelected:
    break;
  case RegionSelected:
    selectStatus = Qt::Checked;
    break;
  case RegionSelectedSecondary:
    selectStatus = Qt::Checked;
    secondaryStatus = Qt::Checked;
    break;
    default:
    break;
  }

  m_ui.regionTreeWidget->blockSignals( true );
  item->setData( Private::SelectColumn, Qt::UserRole, status );
  item->setCheckState( Private::SecondaryColumn, secondaryStatus );
  item->setCheckState( Private::SelectColumn, selectStatus );
  item->setHidden( hidden );
  item->setDisabled( disabled );
  m_ui.regionTreeWidget->blockSignals( false );
}

HolidayRegionSelector::HolidayRegionSelector( QWidget *parent )
                     : QWidget( parent ),
                       d( new Private )
{
  d->m_ui.setupUi( this );

  // Setup the columns
  d->m_ui.regionTreeWidget->setColumnCount( 5 );
  d->m_ui.regionTreeWidget->setHeaderLabels( QStringList() << i18nc( "Header for Holiday Region column", "Region" )
                                                           << i18nc( "Header for Select column", "Select" )
                                                           << i18nc( "Header for Days Off column", "Days Off" )
                                                           << i18nc( "Header for Language column", "Language" )
                                                           << i18nc( "Header for Description column", "Description" ) );
  QTreeWidgetItem *headerItem = d->m_ui.regionTreeWidget->headerItem();
  QString text = i18n("<p>This column selects to use the Holiday Region</p>");
  headerItem->setToolTip( Private::SelectColumn, text );
  headerItem->setWhatsThis( Private::SelectColumn, text );
  text = i18n("<p>This column selects to use the Holiday Region for Days Off</p>");
  headerItem->setToolTip( Private::SecondaryColumn, text );
  headerItem->setWhatsThis( Private::SecondaryColumn, text );
  text = i18n("<p>This column displays the name of the Holiday Region</p>");
  headerItem->setToolTip( Private::RegionColumn, text );
  headerItem->setWhatsThis( Private::RegionColumn, text );
  text = i18n("<p>This column displays the language of the Holiday Region</p>");
  headerItem->setToolTip( Private::LanguageColumn, text );
  headerItem->setWhatsThis( Private::LanguageColumn, text );
  text = i18n("<p>This column displays the description of the Holiday Region</p>");
  headerItem->setToolTip( Private::DescriptionColumn, text );
  headerItem->setWhatsThis( Private::DescriptionColumn, text );

  d->m_ui.regionTreeWidget->setSelectionMode( QAbstractItemView::NoSelection );
  d->m_ui.regionTreeWidget->setItemsExpandable( false );
  d->m_ui.regionTreeWidget->setUniformRowHeights( true );
  d->m_ui.regionTreeWidget->setAllColumnsShowFocus( true );
  connect( d->m_ui.regionTreeWidget, SIGNAL( itemChanged( QTreeWidgetItem*, int ) ),
           this,                     SLOT(   itemChanged( QTreeWidgetItem*, int ) ) );

  QMap<QString, QStringList> regionCodeMap;
  QMap<QString, HolidayRegion*> regionMap;
  foreach ( const QString &regionCode, HolidayRegion::regionCodes() ) {
    regionMap[regionCode] = new HolidayRegion( regionCode );
    QString country = regionMap[regionCode]->countryCode().split('-').at(0);
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
                         KGlobal::locale()->countryCodeToName( country ) );
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
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::SecondaryColumn );
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::RegionColumn );
  d->m_ui.regionTreeWidget->resizeColumnToContents( Private::LanguageColumn );

  // Setup search widget
  d->m_ui.searchLineWidget->searchLine()->addTreeWidget( d->m_ui.regionTreeWidget );

  // Default to MultiSelection mode
  setSelectionMode( QAbstractItemView::MultiSelection, QAbstractItemView::MultiSelection );
}

HolidayRegionSelector::~HolidayRegionSelector()
{
  delete d;
}

QStringList HolidayRegionSelector::holidayRegions() const
{
  return d->m_holidayRegionCodes;
}

void HolidayRegionSelector::setSelectionMode( QAbstractItemView::SelectionMode primarySelectionMode,
                                              QAbstractItemView::SelectionMode secondarySelectionMode )
{
  d->m_primarySelectionMode = primarySelectionMode;

  // Secondary selection mode is only valid if primary mode = MultiSelection,
  // i.e. you only need to choose a Days Off Region if you can choose multiple regions

  if ( primarySelectionMode >= QAbstractItemView::MultiSelection ) {
    d->m_primarySelectionMode = QAbstractItemView::MultiSelection;
    d->m_ui.regionTreeWidget->setColumnHidden( Private::SelectColumn, false );
    if ( secondarySelectionMode >= QAbstractItemView::MultiSelection ) {
      d->m_secondarySelectionMode = QAbstractItemView::MultiSelection;
      d->m_ui.regionTreeWidget->setColumnHidden( Private::SecondaryColumn, false );
    } else if ( secondarySelectionMode == QAbstractItemView::SingleSelection ) {
      d->m_secondarySelectionMode = secondarySelectionMode;
      d->m_ui.regionTreeWidget->setColumnHidden( Private::SecondaryColumn, false );
    } else {
      d->m_secondarySelectionMode = secondarySelectionMode;
      d->m_ui.regionTreeWidget->setColumnHidden( Private::SecondaryColumn, true );
    }
  } else if ( primarySelectionMode == QAbstractItemView::SingleSelection ) {
    d->m_ui.regionTreeWidget->setColumnHidden( Private::SelectColumn, false );
    d->m_ui.regionTreeWidget->setColumnHidden( Private::SecondaryColumn, true );
    d->m_secondarySelectionMode = QAbstractItemView::NoSelection;
  } else { // NoSelection
    d->m_ui.regionTreeWidget->setColumnHidden( Private::SelectColumn, true );
    d->m_ui.regionTreeWidget->setColumnHidden( Private::SecondaryColumn, true );
    d->m_secondarySelectionMode = QAbstractItemView::NoSelection;
  }
}

QAbstractItemView::SelectionMode HolidayRegionSelector::primarySelectionMode() const
{
  return d->m_primarySelectionMode;
}

QAbstractItemView::SelectionMode HolidayRegionSelector::secondarySelectionMode() const
{
  return d->m_secondarySelectionMode;
}

void HolidayRegionSelector::setPrimarySelectionText( const QString &headerText,
                                                     const QString &headerToolTip,
                                                     const QString &headerWhatsThis,
                                                     const QString &itemText,
                                                     const QString &itemToolTip,
                                                     const QString &itemWhatsThis )
{
  d->m_ui.regionTreeWidget->headerItem()->setText( Private::SelectColumn, headerText );
  d->m_ui.regionTreeWidget->headerItem()->setToolTip( Private::SelectColumn, headerToolTip );
  d->m_ui.regionTreeWidget->headerItem()->setWhatsThis( Private::SelectColumn, headerWhatsThis );

  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    (*it)->setText( Private::SelectColumn, itemText );
    (*it)->setToolTip( Private::SelectColumn, itemToolTip );
    (*it)->setWhatsThis( Private::SelectColumn, itemWhatsThis );
    ++it;
  }
}

void HolidayRegionSelector::setSecondarySelectionText( const QString &headerText,
                                                       const QString &headerToolTip,
                                                       const QString &headerWhatsThis,
                                                       const QString &itemText,
                                                       const QString &itemToolTip,
                                                       const QString &itemWhatsThis )
{
  d->m_ui.regionTreeWidget->headerItem()->setText( Private::SecondaryColumn, headerText );
  d->m_ui.regionTreeWidget->headerItem()->setToolTip( Private::SecondaryColumn, headerToolTip );
  d->m_ui.regionTreeWidget->headerItem()->setWhatsThis( Private::SecondaryColumn, headerWhatsThis );

  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    (*it)->setText( Private::SecondaryColumn, itemText );
    (*it)->setToolTip( Private::SecondaryColumn, itemToolTip );
    (*it)->setWhatsThis( Private::SecondaryColumn, itemWhatsThis );
    ++it;
  }
}

void HolidayRegionSelector::setHolidayRegionStatus( const QString &holidayRegionCode,
                                                    HolidayRegionSelector::SelectionStatus status )
{
  if ( primarySelectionMode() == QAbstractItemView::NoSelection ) {
    return;
  }

  QTreeWidgetItem *item = d->findItem( holidayRegionCode );
  if ( item ) {
    d->setItemSelected( item, status );
  }
}

HolidayRegionSelector::SelectionStatus
HolidayRegionSelector::holidayRegionStatus( const QString &holidayRegionCode ) const
{
  QTreeWidgetItem *item = d->findItem( holidayRegionCode );
  if ( item ) {
    return d->itemStatus( item );
  }
  return HolidayRegionSelector::RegionHidden;
}

QHash<QString, HolidayRegionSelector::SelectionStatus>
HolidayRegionSelector::holidayRegionsStatus() const
{
  QHash<QString, HolidayRegionSelector::SelectionStatus> selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    selection.insert( d->itemRegion( (*it) ), d->itemStatus( (*it) ) );
    ++it;
  }
  return selection;
}

QStringList HolidayRegionSelector::primarySelection() const
{
  if ( primarySelectionMode() == QAbstractItemView::NoSelection ) {
    return QStringList();
  }

  QStringList selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    if ( d->itemStatus( (*it) ) >= RegionSelected ) {
      selection.append( d->itemRegion( (*it) ) );
    }
    ++it;
  }
  return selection;
}

QStringList HolidayRegionSelector::secondarySelection() const
{
  if ( primarySelectionMode() == QAbstractItemView::NoSelection ||
       secondarySelectionMode() == QAbstractItemView::NoSelection ) {
    return QStringList();
  }

  if ( primarySelectionMode() == QAbstractItemView::SingleSelection ) {
    return primarySelection();
  }

  // MultiSelection
  QStringList selection;
  QTreeWidgetItemIterator it( d->m_ui.regionTreeWidget );
  while ( *it ) {
    if ( d->itemStatus( (*it) ) == RegionSelectedSecondary ) {
      selection.append( d->itemRegion( (*it) ) );
    }
    ++it;
  }
  return selection;
}

void HolidayRegionSelector::itemChanged( QTreeWidgetItem *item, int column )
{
  if ( column == Private::SelectColumn ) {
    if ( item->checkState( Private::SelectColumn ) == Qt::Unchecked ) {
      d->setItemSelected( item, RegionNotSelected );
    } else {
      d->setItemSelected( item, RegionSelected );
    }
  } else if ( column == Private::SecondaryColumn &&
              item->checkState( Private::SecondaryColumn ) == Qt::Checked ) {
    d->setItemSelected( item, RegionSelectedSecondary );
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
    if ( !d->m_languageFilter.contains( (*it)->data( Private::LanguageColumn, Qt::UserRole ).toString() ) ) {
      d->setItemSelected( (*it), RegionNotSelected );
    }
    ++it;
  }
  // Now hide those languages not in the new list
  d->m_languageFilter = languages;
  QTreeWidgetItemIterator it2( d->m_ui.regionTreeWidget );
  while ( *it2 ) {
    QString language = (*it2)->data( Private::LanguageColumn, Qt::UserRole ).toString();
    if ( d->m_languageFilter.contains( language ) ) {
      // Make sure the parent is always visible, otherwise the child is not visible
      if ( (*it2)->parent() && (*it2)->parent() != d->m_ui.regionTreeWidget->invisibleRootItem() ) {
        d->setItemSelected( (*it2)->parent(), RegionNotSelected );
      }
    } else {
      d->setItemSelected( (*it2), RegionHidden );
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

#include "holidayregionselector.moc"
