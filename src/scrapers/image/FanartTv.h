#pragma once

#include "globals/Globals.h"
#include "network/NetworkManager.h"
#include "scrapers/image/ImageProviderInterface.h"
#include "scrapers/movie/MovieScraper.h"
#include "scrapers/tv_show/TvScraper.h"

#include <QComboBox>
#include <QLineEdit>
#include <QMap>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QVector>

namespace mediaelch {
namespace scraper {
class TheTvDb;
class TMDb;
} // namespace scraper
} // namespace mediaelch

class FanartTv : public ImageProviderInterface
{
    Q_OBJECT
public:
    explicit FanartTv(QObject* parent = nullptr);
    ~FanartTv() override = default;
    QString name() const override;
    QUrl siteUrl() const override;
    QString identifier() const override;
    mediaelch::Locale defaultLanguage() override;
    const QVector<mediaelch::Locale>& supportedLanguages() override;
    void movieImages(Movie* movie, TmdbId tmdbId, QVector<ImageType> types) override;
    void moviePosters(TmdbId tmdbId) override;
    void movieBackdrops(TmdbId tmdbId) override;
    void movieLogos(TmdbId tmdbId) override;
    void movieBanners(TmdbId tmdbId) override;
    void movieThumbs(TmdbId tmdbId) override;
    void movieClearArts(TmdbId tmdbId) override;
    void movieCdArts(TmdbId tmdbId) override;
    void concertImages(Concert* concert, TmdbId tmdbId, QVector<ImageType> types) override;
    void concertPosters(TmdbId tmdbId) override;
    void concertBackdrops(TmdbId tmdbId) override;
    void concertLogos(TmdbId tmdbId) override;
    void concertClearArts(TmdbId tmdbId) override;
    void concertCdArts(TmdbId tmdbId) override;
    void tvShowImages(TvShow* show, TvDbId tvdbId, QVector<ImageType> types, const mediaelch::Locale& locale) override;
    void tvShowPosters(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowBackdrops(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowLogos(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowClearArts(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowCharacterArts(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowBanners(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowEpisodeThumb(TvDbId tvdbId,
        SeasonNumber season,
        EpisodeNumber episode,
        const mediaelch::Locale& locale) override;
    void tvShowSeason(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowSeasonBanners(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowSeasonBackdrops(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowSeasonThumbs(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowThumbs(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void artistFanarts(QString mbId) override;
    void artistLogos(QString mbId) override;
    void artistThumbs(QString mbId) override;
    void albumCdArts(QString mbId) override;
    void albumThumbs(QString mbId) override;
    void artistImages(Artist* artist, QString mbId, QVector<ImageType> types) override;
    void albumImages(Album* album, QString mbId, QVector<ImageType> types) override;
    void albumBooklets(QString mbId) override;
    QVector<ImageType> provides() override;
    bool hasSettings() const override;
    void loadSettings(ScraperSettings& settings) override;
    void saveSettings(ScraperSettings& settings) override;
    QWidget* settingsWidget() override;
    static void insertPoster(QVector<Poster>& posters, Poster b, QString language, QString preferredDiscType);

public slots:
    void searchMovie(QString searchStr, int limit = 0) override;
    void searchConcert(QString searchStr, int limit = 0) override;
    void searchTvShow(QString searchStr, mediaelch::Locale locale, int limit = 0) override;
    void searchArtist(QString searchStr, int limit = 0) override;
    void searchAlbum(QString artistName, QString searchStr, int limit = 0) override;

private slots:
    void onSearchMovieFinished(QVector<ScraperSearchResult> results, ScraperError error);
    void onLoadMovieDataFinished();
    void onLoadAllMovieDataFinished();
    void onLoadAllConcertDataFinished();
    void onSearchTvShowFinished(mediaelch::scraper::ShowSearchJob* searchJob);
    void onLoadTvShowDataFinished();
    void onLoadAllTvShowDataFinished();

private:
    QVector<ImageType> m_provides;
    QString m_apiKey;
    QString m_personalApiKey;
    mediaelch::network::NetworkManager m_network;
    int m_searchResultLimit = 0;
    mediaelch::scraper::TheTvDb* m_tvdb = nullptr;
    mediaelch::scraper::ShowSearchJob* m_currentSearchJob = nullptr;
    mediaelch::scraper::TMDb* m_tmdb;
    QString m_language;
    QString m_preferredDiscType;
    QWidget* m_widget;
    QComboBox* m_box;
    QComboBox* m_discBox;
    QLineEdit* m_personalApiKeyEdit;
    // Multiple languages, but no way to query for it and also no offical list of languages.
    QVector<mediaelch::Locale> m_supportedLanguages = {mediaelch::Locale::English};

    mediaelch::network::NetworkManager* network();
    QVector<Poster> parseMovieData(QString json, ImageType type);
    void loadMovieData(TmdbId tmdbId, ImageType type);
    void loadMovieData(TmdbId tmdbId, QVector<ImageType> types, Movie* movie);
    void loadConcertData(TmdbId tmdbId, QVector<ImageType> types, Concert* concert);
    QVector<Poster> parseTvShowData(QString json, ImageType type, SeasonNumber season = SeasonNumber::NoSeason);
    void loadTvShowData(TvDbId tvdbId, ImageType type, SeasonNumber season = SeasonNumber::NoSeason);
    void loadTvShowData(TvDbId tvdbId, QVector<ImageType> types, TvShow* show);
    QString keyParameter();
};
