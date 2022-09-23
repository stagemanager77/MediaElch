#pragma once

#include "data/concert/Concert.h"
#include "data/movie/Movie.h"
#include "data/music/Album.h"
#include "data/music/Artist.h"
#include "data/tv_show/TvShow.h"
#include "data/tv_show/TvShowEpisode.h"
#include "globals/Globals.h"
#include "scrapers/ScraperResult.h"

#include <QObject>
#include <QPointer>
#include <QTableWidgetItem>

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject* parent, Movie* movie);
    explicit Storage(QObject* parent, Concert* concert);
    explicit Storage(QObject* parent, TvShow* show);
    explicit Storage(QObject* parent, TvShowEpisode* episode);
    explicit Storage(QObject* parent, Artist* artist);
    explicit Storage(QObject* parent, Album* album);
    explicit Storage(QObject* parent, QVector<ScraperSearchResult> results);
    explicit Storage(QObject* parent, QSet<MovieScraperInfo> infosToLoad);
    explicit Storage(QObject* parent, QSet<ShowScraperInfo> infosToLoad);
    explicit Storage(QObject* parent, QSet<ConcertScraperInfo> infosToLoad);
    explicit Storage(QObject* parent, QSet<MusicScraperInfo> infosToLoad);
    explicit Storage(QObject* parent, QVector<ImageType> infosToLoad);
    explicit Storage(QObject* parent,
        QHash<mediaelch::scraper::MovieScraper*, mediaelch::scraper::MovieIdentifier> ids);
    explicit Storage(QObject* parent, QTableWidgetItem* item);
    explicit Storage(QObject* parent, QVector<TvShowEpisode*> episodes);
    Movie* movie() const;
    Concert* concert() const;
    TvShow* show() const;
    TvShowEpisode* episode() const;
    Artist* artist() const;
    Album* album() const;
    QVector<ScraperSearchResult> results() const;
    QSet<MovieScraperInfo> movieInfosToLoad() const;
    QSet<ShowScraperInfo> showInfosToLoad() const;
    QSet<ConcertScraperInfo> concertInfosToLoad() const;
    QSet<MusicScraperInfo> musicInfosToLoad() const;
    QVector<ImageType> imageInfosToLoad() const;
    QHash<mediaelch::scraper::MovieScraper*, mediaelch::scraper::MovieIdentifier> ids() const;
    QTableWidgetItem* tableWidgetItem() const;
    QVector<TvShowEpisode*> episodes() const;
    static QVariant toVariant(QObject* parent, Movie* movie);
    static QVariant toVariant(QObject* parent, Concert* concert);
    static QVariant toVariant(QObject* parent, TvShow* show);
    static QVariant toVariant(QObject* parent, TvShowEpisode* episode);
    static QVariant toVariant(QObject* parent, Artist* artist);
    static QVariant toVariant(QObject* parent, Album* album);
    static QVariant toVariant(QObject* parent, QVector<ScraperSearchResult> results);
    static QVariant toVariant(QObject* parent, QSet<MovieScraperInfo> infosToLoad);
    static QVariant toVariant(QObject* parent, QSet<ShowScraperInfo> infosToLoad);
    static QVariant toVariant(QObject* parent, QSet<ConcertScraperInfo> infosToLoad);
    static QVariant toVariant(QObject* parent, QSet<MusicScraperInfo> infosToLoad);
    static QVariant toVariant(QObject* parent, QVector<ImageType> infosToLoad);
    static QVariant toVariant(QObject* parent,
        QHash<mediaelch::scraper::MovieScraper*, mediaelch::scraper::MovieIdentifier> ids);
    static QVariant toVariant(QObject* parent, QTableWidgetItem* item);
    static QVariant toVariant(QObject* parent, QVector<TvShowEpisode*> episodes);

private:
    QPointer<Movie> m_movie;
    QPointer<Concert> m_concert;
    QPointer<TvShow> m_show;
    QPointer<TvShowEpisode> m_episode;
    QPointer<Artist> m_artist;
    QPointer<Album> m_album;
    QVector<ScraperSearchResult> m_results;
    QSet<MusicScraperInfo> m_musicInfosToLoad;
    QSet<MovieScraperInfo> m_movieInfosToLoad;
    QSet<ShowScraperInfo> m_showDetailsToLoad;
    QSet<ConcertScraperInfo> m_concertInfosToLoad;
    QVector<ImageType> m_imageInfosToLoad;
    QHash<mediaelch::scraper::MovieScraper*, mediaelch::scraper::MovieIdentifier> m_ids;
    QTableWidgetItem* m_tableWidgetItem = nullptr;
    QVector<TvShowEpisode*> m_episodes;
};

Q_DECLARE_METATYPE(Storage*)
