/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2024 Fritzing

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/

#include "advancedpartssearch.h"
#include <QApplication>
#include <QTimer>

AdvancedPartsSearch::AdvancedPartsSearch(QWidget *parent)
    : QWidget(parent)
    , m_searchLineEdit(nullptr)
    , m_searchButton(nullptr)
    , m_clearButton(nullptr)
    , m_advancedToggleButton(nullptr)
    , m_advancedGroup(nullptr)
    , m_categoryCombo(nullptr)
    , m_manufacturerCombo(nullptr)
    , m_familyCombo(nullptr)
    , m_ratingSlider(nullptr)
    , m_ratingLabel(nullptr)
    , m_showObsoleteCheck(nullptr)
    , m_showContribCheck(nullptr)
    , m_showUserCheck(nullptr)
    , m_showCoreCheck(nullptr)
    , m_basicLayout(nullptr)
    , m_mainLayout(nullptr)
    , m_advancedLayout(nullptr)
    , m_advancedMode(false)
{
    setupUI();
    connectSignals();
    resetToDefaults();
}

void AdvancedPartsSearch::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(4);

    setupBasicSearch();
    setupAdvancedFilters();

    m_mainLayout->addLayout(m_basicLayout);
    m_mainLayout->addWidget(m_advancedGroup);
}

void AdvancedPartsSearch::setupBasicSearch()
{
    m_basicLayout = new QHBoxLayout();
    m_basicLayout->setContentsMargins(0, 0, 0, 0);
    m_basicLayout->setSpacing(4);

    // Search input
    m_searchLineEdit = new QLineEdit(this);
    m_searchLineEdit->setPlaceholderText(tr("Search parts by name, description, tags..."));
    m_searchLineEdit->setClearButtonEnabled(true);
    m_searchLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Search button
    m_searchButton = new QPushButton(tr("Search"), this);
    m_searchButton->setDefault(true);
    m_searchButton->setMaximumWidth(80);

    // Clear button
    m_clearButton = new QPushButton(tr("Clear"), this);
    m_clearButton->setMaximumWidth(60);

    // Advanced toggle button
    m_advancedToggleButton = new QPushButton(tr("Advanced"), this);
    m_advancedToggleButton->setCheckable(true);
    m_advancedToggleButton->setMaximumWidth(80);

    m_basicLayout->addWidget(m_searchLineEdit);
    m_basicLayout->addWidget(m_searchButton);
    m_basicLayout->addWidget(m_clearButton);
    m_basicLayout->addWidget(m_advancedToggleButton);
}

void AdvancedPartsSearch::setupAdvancedFilters()
{
    m_advancedGroup = new QGroupBox(tr("Advanced Filters"), this);
    m_advancedGroup->setCheckable(true);
    m_advancedGroup->setChecked(false);
    m_advancedGroup->setVisible(false);

    m_advancedLayout = new QHBoxLayout(m_advancedGroup);
    m_advancedLayout->setContentsMargins(8, 8, 8, 8);
    m_advancedLayout->setSpacing(8);

    // Category filter
    auto *categoryLabel = new QLabel(tr("Category:"), this);
    m_categoryCombo = new QComboBox(this);
    m_categoryCombo->setEditable(true);
    m_categoryCombo->addItem(tr("All Categories"), "");
    m_categoryCombo->setMaximumWidth(150);

    // Manufacturer filter
    auto *manufacturerLabel = new QLabel(tr("Manufacturer:"), this);
    m_manufacturerCombo = new QComboBox(this);
    m_manufacturerCombo->setEditable(true);
    m_manufacturerCombo->addItem(tr("All Manufacturers"), "");
    m_manufacturerCombo->setMaximumWidth(150);

    // Family filter
    auto *familyLabel = new QLabel(tr("Family:"), this);
    m_familyCombo = new QComboBox(this);
    m_familyCombo->setEditable(true);
    m_familyCombo->addItem(tr("All Families"), "");
    m_familyCombo->setMaximumWidth(150);

    // Rating filter
    auto *ratingLabel = new QLabel(tr("Min Rating:"), this);
    m_ratingSlider = new QSlider(Qt::Horizontal, this);
    m_ratingSlider->setRange(0, 5);
    m_ratingSlider->setValue(0);
    m_ratingSlider->setMaximumWidth(100);
    m_ratingLabel = new QLabel("0", this);
    m_ratingLabel->setMinimumWidth(20);

    // Checkboxes for part sources
    m_showCoreCheck = new QCheckBox(tr("Core"), this);
    m_showCoreCheck->setChecked(true);
    m_showContribCheck = new QCheckBox(tr("Contrib"), this);
    m_showContribCheck->setChecked(true);
    m_showUserCheck = new QCheckBox(tr("User"), this);
    m_showUserCheck->setChecked(true);
    m_showObsoleteCheck = new QCheckBox(tr("Obsolete"), this);
    m_showObsoleteCheck->setChecked(false);

    // Add widgets to layout
    m_advancedLayout->addWidget(categoryLabel);
    m_advancedLayout->addWidget(m_categoryCombo);
    m_advancedLayout->addWidget(manufacturerLabel);
    m_advancedLayout->addWidget(m_manufacturerCombo);
    m_advancedLayout->addWidget(familyLabel);
    m_advancedLayout->addWidget(m_familyCombo);
    m_advancedLayout->addWidget(ratingLabel);
    m_advancedLayout->addWidget(m_ratingSlider);
    m_advancedLayout->addWidget(m_ratingLabel);
    m_advancedLayout->addWidget(m_showCoreCheck);
    m_advancedLayout->addWidget(m_showContribCheck);
    m_advancedLayout->addWidget(m_showUserCheck);
    m_advancedLayout->addWidget(m_showObsoleteCheck);
    m_advancedLayout->addStretch();
}

void AdvancedPartsSearch::connectSignals()
{
    // Basic search signals
    connect(m_searchLineEdit, &QLineEdit::textChanged, this, &AdvancedPartsSearch::onSearchTextChanged);
    connect(m_searchLineEdit, &QLineEdit::returnPressed, this, &AdvancedPartsSearch::onSearchClicked);
    connect(m_searchButton, &QPushButton::clicked, this, &AdvancedPartsSearch::onSearchClicked);
    connect(m_clearButton, &QPushButton::clicked, this, &AdvancedPartsSearch::onClearClicked);
    connect(m_advancedToggleButton, &QPushButton::toggled, this, &AdvancedPartsSearch::onAdvancedToggleClicked);

    // Advanced filter signals
    connect(m_categoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_manufacturerCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_familyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_ratingSlider, &QSlider::valueChanged, this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_showObsoleteCheck, &QCheckBox::toggled, this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_showContribCheck, &QCheckBox::toggled, this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_showUserCheck, &QCheckBox::toggled, this, &AdvancedPartsSearch::onFilterChanged);
    connect(m_showCoreCheck, &QCheckBox::toggled, this, &AdvancedPartsSearch::onFilterChanged);

    // Rating slider label update
    connect(m_ratingSlider, &QSlider::valueChanged, [this](int value) {
        m_ratingLabel->setText(QString::number(value));
    });
}

// Search criteria getters
QString AdvancedPartsSearch::getSearchText() const
{
    return m_searchLineEdit->text().trimmed();
}

QString AdvancedPartsSearch::getCategory() const
{
    return m_categoryCombo->currentData().toString();
}

QString AdvancedPartsSearch::getManufacturer() const
{
    return m_manufacturerCombo->currentData().toString();
}

QString AdvancedPartsSearch::getFamily() const
{
    return m_familyCombo->currentData().toString();
}

int AdvancedPartsSearch::getMinRating() const
{
    return m_ratingSlider->value();
}

bool AdvancedPartsSearch::getShowObsolete() const
{
    return m_showObsoleteCheck->isChecked();
}

bool AdvancedPartsSearch::getShowContrib() const
{
    return m_showContribCheck->isChecked();
}

bool AdvancedPartsSearch::getShowUser() const
{
    return m_showUserCheck->isChecked();
}

bool AdvancedPartsSearch::getShowCore() const
{
    return m_showCoreCheck->isChecked();
}

// Search criteria setters
void AdvancedPartsSearch::setSearchText(const QString &text)
{
    m_searchLineEdit->setText(text);
}

void AdvancedPartsSearch::setCategory(const QString &category)
{
    int index = m_categoryCombo->findData(category);
    if (index >= 0) {
        m_categoryCombo->setCurrentIndex(index);
    } else {
        m_categoryCombo->setCurrentText(category);
    }
}

void AdvancedPartsSearch::setManufacturer(const QString &manufacturer)
{
    int index = m_manufacturerCombo->findData(manufacturer);
    if (index >= 0) {
        m_manufacturerCombo->setCurrentIndex(index);
    } else {
        m_manufacturerCombo->setCurrentText(manufacturer);
    }
}

void AdvancedPartsSearch::setFamily(const QString &family)
{
    int index = m_familyCombo->findData(family);
    if (index >= 0) {
        m_familyCombo->setCurrentIndex(index);
    } else {
        m_familyCombo->setCurrentText(family);
    }
}

void AdvancedPartsSearch::setMinRating(int rating)
{
    m_ratingSlider->setValue(rating);
}

void AdvancedPartsSearch::setShowObsolete(bool show)
{
    m_showObsoleteCheck->setChecked(show);
}

void AdvancedPartsSearch::setShowContrib(bool show)
{
    m_showContribCheck->setChecked(show);
}

void AdvancedPartsSearch::setShowUser(bool show)
{
    m_showUserCheck->setChecked(show);
}

void AdvancedPartsSearch::setShowCore(bool show)
{
    m_showCoreCheck->setChecked(show);
}

// Filter management
void AdvancedPartsSearch::addCategoryFilter(const QString &category)
{
    if (!category.isEmpty() && !m_categories.contains(category)) {
        m_categories.append(category);
        m_categoryCombo->addItem(category, category);
    }
}

void AdvancedPartsSearch::addManufacturerFilter(const QString &manufacturer)
{
    if (!manufacturer.isEmpty() && !m_manufacturers.contains(manufacturer)) {
        m_manufacturers.append(manufacturer);
        m_manufacturerCombo->addItem(manufacturer, manufacturer);
    }
}

void AdvancedPartsSearch::addFamilyFilter(const QString &family)
{
    if (!family.isEmpty() && !m_families.contains(family)) {
        m_families.append(family);
        m_familyCombo->addItem(family, family);
    }
}

void AdvancedPartsSearch::clearFilters()
{
    m_searchLineEdit->clear();
    m_categoryCombo->setCurrentIndex(0);
    m_manufacturerCombo->setCurrentIndex(0);
    m_familyCombo->setCurrentIndex(0);
    m_ratingSlider->setValue(0);
    m_showObsoleteCheck->setChecked(false);
    m_showContribCheck->setChecked(true);
    m_showUserCheck->setChecked(true);
    m_showCoreCheck->setChecked(true);
}

void AdvancedPartsSearch::resetToDefaults()
{
    clearFilters();
    setAdvancedMode(false);
}

// UI state management
void AdvancedPartsSearch::setAdvancedMode(bool advanced)
{
    m_advancedMode = advanced;
    m_advancedToggleButton->setChecked(advanced);
    m_advancedGroup->setVisible(advanced);
    m_advancedGroup->setChecked(advanced);
}

bool AdvancedPartsSearch::isAdvancedMode() const
{
    return m_advancedMode;
}

void AdvancedPartsSearch::toggleAdvancedMode()
{
    setAdvancedMode(!m_advancedMode);
}

void AdvancedPartsSearch::focusSearch()
{
    if (m_searchLineEdit != nullptr) {
        m_searchLineEdit->setFocus(Qt::OtherFocusReason);
    }
}

void AdvancedPartsSearch::updateFilterLists()
{
    // This would be called when parts are loaded to populate filter lists
    // Implementation would depend on the parts data structure
}

// Private slots
void AdvancedPartsSearch::onSearchTextChanged()
{
    // Emit signal with a small delay to avoid too many searches while typing
    QTimer::singleShot(300, this, &AdvancedPartsSearch::searchCriteriaChanged);
}

void AdvancedPartsSearch::onFilterChanged()
{
    emit searchCriteriaChanged();
}

void AdvancedPartsSearch::onClearClicked()
{
    clearFilters();
    emit clearRequested();
}

void AdvancedPartsSearch::onSearchClicked()
{
    emit searchRequested();
}

void AdvancedPartsSearch::onAdvancedToggleClicked()
{
    setAdvancedMode(m_advancedToggleButton->isChecked());
}
