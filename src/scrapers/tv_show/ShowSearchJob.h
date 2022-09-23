#pragma once

#include "data/Locale.h"
#include "scrapers/ScraperError.h"
#include "scrapers/ScraperResult.h"
#include "scrapers/tv_show/ShowIdentifier.h"
#include "utils/Meta.h"
#include "workers/Job.h"

#include <QDate>
#include <QObject>
#include <QString>

namespace mediaelch {
namespace scraper {

/// \brief A TV show search request resolved by a scraper.
class ShowSearchJob : public worker::Job
{
    Q_OBJECT

public:
    /// \brief Configuration object for a TV show search.
    struct Config
    {
        /// \brief The search string
        QString query;
        /// \brief Language key for the scraper, e.g. "en-US", "de-DE", ...
        Locale locale = Locale::English;
        /// \brief Whether to include adult (NFSW) search results.
        /// \details The scraper may or may not support adult search results.
        bool includeAdult = false;
    };

    /// \brief Search result of a TV show search request.
    struct Result
    {
        /// \brief Title shown to the user.
        QString title;
        /// \brief Release date of the TV show.
        /// \details Date is used for showing the year behind the search result.
        QDate released;
        /// \brief Scraper specific identifier that may be used for scraping a TV show.
        /// \details The identifier can be passed to scrape().
        ShowIdentifier identifier;
        /// \brief Returns true if the search result has title and identifier filled with data.
        bool isValid() const;
    };

public:
    /// \brief Extract the title and year from a search query.
    /// \details This function checks for common patterns and extract the title
    ///          and year if a pattern matches.
    /// \returns Title/Year pair if a pattern matched, empty string pair otherwise.
    static QPair<QString, QString> extractTitleAndYear(const QString& query);

public:
    /// \brief Create a TV show search.
    explicit ShowSearchJob(Config config, QObject* parent = nullptr);
    virtual ~ShowSearchJob() = default;

public:
    ELCH_NODISCARD const Config& config() const;
    ELCH_NODISCARD const ScraperError& scraperError() const;
    ELCH_NODISCARD const QVector<ShowSearchJob::Result>& results() const;


signals:
    /// \brief   Signal emitted when the search() request has finished.
    /// \details A simple wrapper around finished() to avoid static_asserts
    ///          from Job* to ShowSearchJob*.
    ///          Use hasError() and results() to know whether the request was successful.
    void searchFinished(mediaelch::scraper::ShowSearchJob* job, QPrivateSignal);

protected:
    void setScraperError(ScraperError error);

protected:
    QVector<ShowSearchJob::Result> m_results;

private:
    ScraperError m_scraperError;
    const Config m_config;
};

QVector<ScraperSearchResult> toOldScraperSearchResult(const QVector<ShowSearchJob::Result>& searchResults);

} // namespace scraper
} // namespace mediaelch
