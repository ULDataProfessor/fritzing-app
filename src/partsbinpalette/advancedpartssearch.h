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

#ifndef ADVANCEDPARTSSEARCH_H
#define ADVANCEDPARTSSEARCH_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSlider>
#include <QSpinBox>
#include <QStringList>

class AdvancedPartsSearch : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedPartsSearch(QWidget *parent = nullptr);
    ~AdvancedPartsSearch() = default;

    // Search criteria getters
    QString getSearchText() const;
    QString getCategory() const;
    QString getManufacturer() const;
    QString getFamily() const;
    int getMinRating() const;
    bool getShowObsolete() const;
    bool getShowContrib() const;
    bool getShowUser() const;
    bool getShowCore() const;

    // Search criteria setters
    void setSearchText(const QString &text);
    void setCategory(const QString &category);
    void setManufacturer(const QString &manufacturer);
    void setFamily(const QString &family);
    void setMinRating(int rating);
    void setShowObsolete(bool show);
    void setShowContrib(bool show);
    void setShowUser(bool show);
    void setShowCore(bool show);

    // Filter management
    void addCategoryFilter(const QString &category);
    void addManufacturerFilter(const QString &manufacturer);
    void addFamilyFilter(const QString &family);
    void clearFilters();
    void resetToDefaults();

    // UI state management
    void setAdvancedMode(bool advanced);
    bool isAdvancedMode() const;
    void toggleAdvancedMode();
    void focusSearch();

signals:
    void searchCriteriaChanged();
    void searchRequested();
    void clearRequested();

private slots:
    void onSearchTextChanged();
    void onFilterChanged();
    void onClearClicked();
    void onSearchClicked();
    void onAdvancedToggleClicked();

private:
    void setupUI();
    void setupBasicSearch();
    void setupAdvancedFilters();
    void connectSignals();
    void updateFilterLists();

    // Basic search components
    QLineEdit *m_searchLineEdit;
    QPushButton *m_searchButton;
    QPushButton *m_clearButton;
    QPushButton *m_advancedToggleButton;

    // Advanced filter components
    QGroupBox *m_advancedGroup;
    QComboBox *m_categoryCombo;
    QComboBox *m_manufacturerCombo;
    QComboBox *m_familyCombo;
    QSlider *m_ratingSlider;
    QLabel *m_ratingLabel;
    QCheckBox *m_showObsoleteCheck;
    QCheckBox *m_showContribCheck;
    QCheckBox *m_showUserCheck;
    QCheckBox *m_showCoreCheck;

    // Layout components
    QHBoxLayout *m_basicLayout;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_advancedLayout;

    // State
    bool m_advancedMode;
    QStringList m_categories;
    QStringList m_manufacturers;
    QStringList m_families;
};

#endif // ADVANCEDPARTSSEARCH_H
