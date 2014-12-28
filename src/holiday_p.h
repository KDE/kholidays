/*
  This file is part of the kholidays library.

  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>
  Copyright (c) 2008 David Jarvie <djarvie@kde.org>
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

#ifndef KHOLIDAYS_HOLIDAY_P_H
#define KHOLIDAYS_HOLIDAY_P_H

#include "holiday.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QLocale>
#include <QtCore/QSharedData>

namespace KHolidays {

class HolidayPrivate : public QSharedData
{
  public:
    HolidayPrivate()
    {
    }

    HolidayPrivate( const HolidayPrivate &other ) : QSharedData( other )
    {
        mObservedDate = other.mObservedDate;
        mDuration = other.mDuration;
        mName = other.mName;
        mDescription = other.mDescription;
        mDayType = other.mDayType;
    }

    QDate mObservedDate;
    int mDuration;
    QString mName;
    QString mDescription;
    Holiday::DayType mDayType;
};

}

// Copied from qlocale_data_p.h and qlocale.h
// Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
// To later be replaced by OpenCodes or public Qt api

static const unsigned char language_code_list[] =
"  \0" // AnyLanguage
"  \0" // C
"ab\0" // Abkhazian
"om\0" // Oromo
"aa\0" // Afar
"af\0" // Afrikaans
"sq\0" // Albanian
"am\0" // Amharic
"ar\0" // Arabic
"hy\0" // Armenian
"as\0" // Assamese
"ay\0" // Aymara
"az\0" // Azerbaijani
"ba\0" // Bashkir
"eu\0" // Basque
"bn\0" // Bengali
"dz\0" // Dzongkha
"bh\0" // Bihari
"bi\0" // Bislama
"br\0" // Breton
"bg\0" // Bulgarian
"my\0" // Burmese
"be\0" // Belarusian
"km\0" // Khmer
"ca\0" // Catalan
"zh\0" // Chinese
"co\0" // Corsican
"hr\0" // Croatian
"cs\0" // Czech
"da\0" // Danish
"nl\0" // Dutch
"en\0" // English
"eo\0" // Esperanto
"et\0" // Estonian
"fo\0" // Faroese
"fj\0" // Fijian
"fi\0" // Finnish
"fr\0" // French
"fy\0" // Western Frisian
"gd\0" // Gaelic
"gl\0" // Galician
"ka\0" // Georgian
"de\0" // German
"el\0" // Greek
"kl\0" // Greenlandic
"gn\0" // Guarani
"gu\0" // Gujarati
"ha\0" // Hausa
"he\0" // Hebrew
"hi\0" // Hindi
"hu\0" // Hungarian
"is\0" // Icelandic
"id\0" // Indonesian
"ia\0" // Interlingua
"ie\0" // Interlingue
"iu\0" // Inuktitut
"ik\0" // Inupiak
"ga\0" // Irish
"it\0" // Italian
"ja\0" // Japanese
"jv\0" // Javanese
"kn\0" // Kannada
"ks\0" // Kashmiri
"kk\0" // Kazakh
"rw\0" // Kinyarwanda
"ky\0" // Kirghiz
"ko\0" // Korean
"ku\0" // Kurdish
"rn\0" // Rundi
"lo\0" // Lao
"la\0" // Latin
"lv\0" // Latvian
"ln\0" // Lingala
"lt\0" // Lithuanian
"mk\0" // Macedonian
"mg\0" // Malagasy
"ms\0" // Malay
"ml\0" // Malayalam
"mt\0" // Maltese
"mi\0" // Maori
"mr\0" // Marathi
"mh\0" // Marshallese
"mn\0" // Mongolian
"na\0" // Nauru
"ne\0" // Nepali
"nb\0" // NorwegianBokmal
"oc\0" // Occitan
"or\0" // Oriya
"ps\0" // Pashto
"fa\0" // Persian
"pl\0" // Polish
"pt\0" // Portuguese
"pa\0" // Punjabi
"qu\0" // Quechua
"rm\0" // Romansh
"ro\0" // Romanian
"ru\0" // Russian
"sm\0" // Samoan
"sg\0" // Sango
"sa\0" // Sanskrit
"sr\0" // Serbian
"os\0" // Ossetic
"st\0" // Southern Sotho
"tn\0" // Tswana
"sn\0" // Shona
"sd\0" // Sindhi
"si\0" // Sinhala
"ss\0" // Swati
"sk\0" // Slovak
"sl\0" // Slovenian
"so\0" // Somali
"es\0" // Spanish
"su\0" // Sundanese
"sw\0" // Swahili
"sv\0" // Swedish
"sc\0" // Sardinian
"tg\0" // Tajik
"ta\0" // Tamil
"tt\0" // Tatar
"te\0" // Telugu
"th\0" // Thai
"bo\0" // Tibetan
"ti\0" // Tigrinya
"to\0" // Tongan
"ts\0" // Tsonga
"tr\0" // Turkish
"tk\0" // Turkmen
"ty\0" // Tahitian
"ug\0" // Uighur
"uk\0" // Ukrainian
"ur\0" // Urdu
"uz\0" // Uzbek
"vi\0" // Vietnamese
"vo\0" // Volapuk
"cy\0" // Welsh
"wo\0" // Wolof
"xh\0" // Xhosa
"yi\0" // Yiddish
"yo\0" // Yoruba
"za\0" // Zhuang
"zu\0" // Zulu
"nn\0" // NorwegianNynorsk
"bs\0" // Bosnian
"dv\0" // Divehi
"gv\0" // Manx
"kw\0" // Cornish
"ak\0" // Akan
"kok" // Konkani
"gaa" // Ga
"ig\0" // Igbo
"kam" // Kamba
"syr" // Syriac
"byn" // Blin
"gez" // Geez
"kfo" // Koro
"sid" // Sidamo
"cch" // Atsam
"tig" // Tigre
"kaj" // Jju
"fur" // Friulian
"ve\0" // Venda
"ee\0" // Ewe
"wal" // Walamo
"haw" // Hawaiian
"kcg" // Tyap
"ny\0" // Nyanja
"fil" // Filipino
"gsw" // Swiss German
"ii\0" // Sichuan Yi
"kpe" // Kpelle
"nds" // Low German
"nr\0" // South Ndebele
"nso" // Northern Sotho
"se\0" // Northern Sami
"trv" // Taroko
"guz" // Gusii
"dav" // Taita
"ff\0" // Fulah
"ki\0" // Kikuyu
"saq" // Samburu
"seh" // Sena
"nd\0" // North Ndebele
"rof" // Rombo
"shi" // Tachelhit
"kab" // Kabyle
"nyn" // Nyankole
"bez" // Bena
"vun" // Vunjo
"bm\0" // Bambara
"ebu" // Embu
"chr" // Cherokee
"mfe" // Morisyen
"kde" // Makonde
"lag" // Langi
"lg\0" // Ganda
"bem" // Bemba
"kea" // Kabuverdianu
"mer" // Meru
"kln" // Kalenjin
"naq" // Nama
"jmc" // Machame
"ksh" // Colognian
"mas" // Masai
"xog" // Soga
"luy" // Luyia
"asa" // Asu
"teo" // Teso
"ssy" // Saho
"khq" // Koyra Chiini
"rwk" // Rwa
"luo" // Luo
"cgg" // Chiga
"tzm" // Central Morocco Tamazight
"ses" // Koyraboro Senni
"ksb" // Shambala
"brx" // Bodo
"av\0" // Avaric
"ch\0" // Chamorro
"ce\0" // Chechen
"cu\0" // Church
"cv\0" // Chuvash
"cr\0" // Cree
"ht\0" // Haitian
"hz\0" // Herero
"ho\0" // Hiri Motu
"kr\0" // Kanuri
"kv\0" // Komi
"kg\0" // Kongo
"kj\0" // Kwanyama
"li\0" // Limburgish
"lu\0" // LubaKatanga
"lb\0" // Luxembourgish
"nv\0" // Navaho
"ng\0" // Ndonga
"oj\0" // Ojibwa
"pi\0" // Pali
"wa\0" // Walloon
"agq" // Aghem
"bas" // Basaa
"dje" // Zarma
"dua" // Duala
"dyo" // JolaFonyi
"ewo" // Ewondo
"ksf" // Bafia
"mgh" // MakhuwaMeetto
"mua" // Mundang
"nmg" // Kwasio
"nus" // Nuer
"sah" // Sakha
"sbp" // Sangu
"swc" // Congo Swahili
"twq" // Tasawaq
"vai" // Vai
"wae" // Walser
"yav" // Yangben
"ae\0" // Avestan
"ast" // Asturian
"jgo" // Ngomba
"kkj" // Kako
"mgo" // Meta
"nnh" // Ngiemboon
"an\0" // Aragonese
"akk" // Akkadian
"egy" // AncientEgyptian
"grc" // AncientGreek
"arc" // Aramaic
"ban" // Balinese
"bax" // Bamun
"bbc" // BatakToba
"bug" // Buginese
"bku" // Buhid
"xcr" // Carian
"ccp" // Chakma
"myz" // ClassicalMandaic
"cop" // Coptic
"doi" // Dogri
"cjm" // EasternCham
"eky" // EasternKayah
"ett" // Etruscan
"got" // Gothic
"hnn" // Hanunoo
"inh" // Ingush
"hmd" // LargeFloweryMiao
"lep" // Lepcha
"lif" // Limbu
"lis" // Lisu
"khb" // Lu
"xlc" // Lycian
"xld" // Lydian
"man" // Mandingo
"mni" // Manipuri
"xmr" // Meroitic
"nod" // NorthernThai
"sga" // OldIrish
"non" // OldNorse
"peo" // OldPersian
"otk" // OldTurkish
"pal" // Pahlavi
"xpr" // Parthian
"phn" // Phoenician
"pra" // PrakritLanguage
"rej" // Rejang
"xsa" // Sabaean
"smp" // Samaritan
"sat" // Santali
"saz" // Saurashtra
"srb" // Sora
"syl" // Sylheti
"tbw" // Tagbanwa
"blt" // TaiDam
"tdd" // TaiNua
"uga" // Ugaritic
"bss" // Akoose
"lkt" // Lakota
"zgh" // Standard Moroccan Tamazight
;

static const unsigned char country_code_list[] =
"ZZ\0" // AnyCountry
"AF\0" // Afghanistan
"AL\0" // Albania
"DZ\0" // Algeria
"AS\0" // AmericanSamoa
"AD\0" // Andorra
"AO\0" // Angola
"AI\0" // Anguilla
"AQ\0" // Antarctica
"AG\0" // AntiguaAndBarbuda
"AR\0" // Argentina
"AM\0" // Armenia
"AW\0" // Aruba
"AU\0" // Australia
"AT\0" // Austria
"AZ\0" // Azerbaijan
"BS\0" // Bahamas
"BH\0" // Bahrain
"BD\0" // Bangladesh
"BB\0" // Barbados
"BY\0" // Belarus
"BE\0" // Belgium
"BZ\0" // Belize
"BJ\0" // Benin
"BM\0" // Bermuda
"BT\0" // Bhutan
"BO\0" // Bolivia
"BA\0" // BosniaAndHerzegowina
"BW\0" // Botswana
"BV\0" // BouvetIsland
"BR\0" // Brazil
"IO\0" // BritishIndianOceanTerritory
"BN\0" // Brunei
"BG\0" // Bulgaria
"BF\0" // BurkinaFaso
"BI\0" // Burundi
"KH\0" // Cambodia
"CM\0" // Cameroon
"CA\0" // Canada
"CV\0" // CapeVerde
"KY\0" // CaymanIslands
"CF\0" // CentralAfricanRepublic
"TD\0" // Chad
"CL\0" // Chile
"CN\0" // China
"CX\0" // ChristmasIsland
"CC\0" // CocosIslands
"CO\0" // Colombia
"KM\0" // Comoros
"CD\0" // CongoKinshasa
"CG\0" // CongoBrazzaville
"CK\0" // CookIslands
"CR\0" // CostaRica
"CI\0" // IvoryCoast
"HR\0" // Croatia
"CU\0" // Cuba
"CY\0" // Cyprus
"CZ\0" // CzechRepublic
"DK\0" // Denmark
"DJ\0" // Djibouti
"DM\0" // Dominica
"DO\0" // DominicanRepublic
"TL\0" // EastTimor
"EC\0" // Ecuador
"EG\0" // Egypt
"SV\0" // ElSalvador
"GQ\0" // EquatorialGuinea
"ER\0" // Eritrea
"EE\0" // Estonia
"ET\0" // Ethiopia
"FK\0" // FalklandIslands
"FO\0" // FaroeIslands
"FJ\0" // Fiji
"FI\0" // Finland
"FR\0" // France
"GG\0" // Guernsey
"GF\0" // FrenchGuiana
"PF\0" // FrenchPolynesia
"TF\0" // FrenchSouthernTerritories
"GA\0" // Gabon
"GM\0" // Gambia
"GE\0" // Georgia
"DE\0" // Germany
"GH\0" // Ghana
"GI\0" // Gibraltar
"GR\0" // Greece
"GL\0" // Greenland
"GD\0" // Grenada
"GP\0" // Guadeloupe
"GU\0" // Guam
"GT\0" // Guatemala
"GN\0" // Guinea
"GW\0" // GuineaBissau
"GY\0" // Guyana
"HT\0" // Haiti
"HM\0" // HeardAndMcDonaldIslands
"HN\0" // Honduras
"HK\0" // HongKong
"HU\0" // Hungary
"IS\0" // Iceland
"IN\0" // India
"ID\0" // Indonesia
"IR\0" // Iran
"IQ\0" // Iraq
"IE\0" // Ireland
"IL\0" // Israel
"IT\0" // Italy
"JM\0" // Jamaica
"JP\0" // Japan
"JO\0" // Jordan
"KZ\0" // Kazakhstan
"KE\0" // Kenya
"KI\0" // Kiribati
"KP\0" // NorthKorea
"KR\0" // SouthKorea
"KW\0" // Kuwait
"KG\0" // Kyrgyzstan
"LA\0" // Laos
"LV\0" // Latvia
"LB\0" // Lebanon
"LS\0" // Lesotho
"LR\0" // Liberia
"LY\0" // Libya
"LI\0" // Liechtenstein
"LT\0" // Lithuania
"LU\0" // Luxembourg
"MO\0" // Macau
"MK\0" // Macedonia
"MG\0" // Madagascar
"MW\0" // Malawi
"MY\0" // Malaysia
"MV\0" // Maldives
"ML\0" // Mali
"MT\0" // Malta
"MH\0" // MarshallIslands
"MQ\0" // Martinique
"MR\0" // Mauritania
"MU\0" // Mauritius
"YT\0" // Mayotte
"MX\0" // Mexico
"FM\0" // Micronesia
"MD\0" // Moldova
"MC\0" // Monaco
"MN\0" // Mongolia
"MS\0" // Montserrat
"MA\0" // Morocco
"MZ\0" // Mozambique
"MM\0" // Myanmar
"NA\0" // Namibia
"NR\0" // Nauru
"NP\0" // Nepal
"NL\0" // Netherlands
"CW\0" // CuraSao
"NC\0" // NewCaledonia
"NZ\0" // NewZealand
"NI\0" // Nicaragua
"NE\0" // Niger
"NG\0" // Nigeria
"NU\0" // Niue
"NF\0" // NorfolkIsland
"MP\0" // NorthernMarianaIslands
"NO\0" // Norway
"OM\0" // Oman
"PK\0" // Pakistan
"PW\0" // Palau
"PS\0" // PalestinianTerritories
"PA\0" // Panama
"PG\0" // PapuaNewGuinea
"PY\0" // Paraguay
"PE\0" // Peru
"PH\0" // Philippines
"PN\0" // Pitcairn
"PL\0" // Poland
"PT\0" // Portugal
"PR\0" // PuertoRico
"QA\0" // Qatar
"RE\0" // Reunion
"RO\0" // Romania
"RU\0" // Russia
"RW\0" // Rwanda
"KN\0" // SaintKittsAndNevis
"LC\0" // SaintLucia
"VC\0" // SaintVincentAndTheGrenadines
"WS\0" // Samoa
"SM\0" // SanMarino
"ST\0" // SaoTomeAndPrincipe
"SA\0" // SaudiArabia
"SN\0" // Senegal
"SC\0" // Seychelles
"SL\0" // SierraLeone
"SG\0" // Singapore
"SK\0" // Slovakia
"SI\0" // Slovenia
"SB\0" // SolomonIslands
"SO\0" // Somalia
"ZA\0" // SouthAfrica
"GS\0" // SouthGeorgiaAndTheSouthSandwichIslands
"ES\0" // Spain
"LK\0" // SriLanka
"SH\0" // SaintHelena
"PM\0" // SaintPierreAndMiquelon
"SD\0" // Sudan
"SR\0" // Suriname
"SJ\0" // SvalbardAndJanMayenIslands
"SZ\0" // Swaziland
"SE\0" // Sweden
"CH\0" // Switzerland
"SY\0" // Syria
"TW\0" // Taiwan
"TJ\0" // Tajikistan
"TZ\0" // Tanzania
"TH\0" // Thailand
"TG\0" // Togo
"TK\0" // Tokelau
"TO\0" // Tonga
"TT\0" // TrinidadAndTobago
"TN\0" // Tunisia
"TR\0" // Turkey
"TM\0" // Turkmenistan
"TC\0" // TurksAndCaicosIslands
"TV\0" // Tuvalu
"UG\0" // Uganda
"UA\0" // Ukraine
"AE\0" // UnitedArabEmirates
"GB\0" // UnitedKingdom
"US\0" // UnitedStates
"UM\0" // UnitedStatesMinorOutlyingIslands
"UY\0" // Uruguay
"UZ\0" // Uzbekistan
"VU\0" // Vanuatu
"VA\0" // VaticanCityState
"VE\0" // Venezuela
"VN\0" // Vietnam
"VG\0" // BritishVirginIslands
"VI\0" // UnitedStatesVirginIslands
"WF\0" // WallisAndFutunaIslands
"EH\0" // WesternSahara
"YE\0" // Yemen
"IC\0" // CanaryIslands
"ZM\0" // Zambia
"ZW\0" // Zimbabwe
"CP\0" // ClippertonIsland
"ME\0" // Montenegro
"RS\0" // Serbia
"BL\0" // Saint Barthelemy
"MF\0" // Saint Martin
"419" // LatinAmericaAndTheCaribbean
"AC\0" // AscensionIsland
"AX\0" // AlandIslands
"DG\0" // DiegoGarcia
"EA\0" // CeutaAndMelilla
"IM\0" // IsleOfMan
"JE\0" // Jersey
"TA\0" // TristanDaCunha
"SS\0" // SouthSudan
"BQ\0" // Bonaire
"SX\0" // SintMaarten
"XK\0" // Kosovo
;

static QString languageToCode(QLocale::Language language)
{
    if (language == QLocale::AnyLanguage)
        return QString();
    if (language == QLocale::C)
        return QLatin1String("C");

    const unsigned char *c = language_code_list + 3*(uint(language));

    QString code(c[2] == 0 ? 2 : 3, Qt::Uninitialized);

    code[0] = ushort(c[0]);
    code[1] = ushort(c[1]);
    if (c[2] != 0)
        code[2] = ushort(c[2]);

    return code;
}

static QLocale::Language codeToLanguage(const QString &code)
{
    int len = code.length();
    if (len != 2 && len != 3)
        return QLocale::C;
    ushort uc1 = len-- > 0 ? code[0].toLower().unicode() : 0;
    ushort uc2 = len-- > 0 ? code[1].toLower().unicode() : 0;
    ushort uc3 = len-- > 0 ? code[2].toLower().unicode() : 0;

    const unsigned char *c = language_code_list;
    for (; *c != 0; c += 3) {
        if (uc1 == c[0] && uc2 == c[1] && uc3 == c[2])
            return QLocale::Language((c - language_code_list)/3);
    }

    // legacy codes
    if (uc1 == 'n' && uc2 == 'o' && uc3 == 0) { // no -> nb
        Q_STATIC_ASSERT(QLocale::Norwegian == QLocale::NorwegianBokmal);
        return QLocale::Norwegian;
    }
    if (uc1 == 't' && uc2 == 'l' && uc3 == 0) { // tl -> fil
        Q_STATIC_ASSERT(QLocale::Tagalog == QLocale::Filipino);
        return QLocale::Tagalog;
    }
    if (uc1 == 's' && uc2 == 'h' && uc3 == 0) { // sh -> sr[_Latn]
        Q_STATIC_ASSERT(QLocale::SerboCroatian == QLocale::Serbian);
        return QLocale::SerboCroatian;
    }
    if (uc1 == 'm' && uc2 == 'o' && uc3 == 0) { // mo -> ro
        Q_STATIC_ASSERT(QLocale::Moldavian == QLocale::Romanian);
        return QLocale::Moldavian;
    }

    return QLocale::C;
}

static QString countryToCode(QLocale::Country country)
{
    if (country == QLocale::AnyCountry)
        return QString();

    const unsigned char *c = country_code_list + 3*(uint(country));

    QString code(c[2] == 0 ? 2 : 3, Qt::Uninitialized);

    code[0] = ushort(c[0]);
    code[1] = ushort(c[1]);
    if (c[2] != 0)
        code[2] = ushort(c[2]);

    return code;
}

static QLocale::Country codeToCountry(const QString &code)
{
    int len = code.length();
    if (len != 2 && len != 3)
        return QLocale::AnyCountry;
    ushort uc1 = len-- > 0 ? code[0].toUpper().unicode() : 0;
    ushort uc2 = len-- > 0 ? code[1].toUpper().unicode() : 0;
    ushort uc3 = len-- > 0 ? code[2].toUpper().unicode() : 0;

    const unsigned char *c = country_code_list;
    for (; *c != 0; c += 3) {
        if (uc1 == c[0] && uc2 == c[1] && uc3 == c[2])
            return QLocale::Country((c - country_code_list)/3);
    }

    return QLocale::AnyCountry;
}

// End Qt copied code

#endif // KHOLIDAYS_HOLIDAY_P_H
